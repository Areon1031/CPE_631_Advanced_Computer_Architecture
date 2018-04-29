/**
  mainwindow.cpp

  Main Window implementation file for the Quick Performance Application
  Author: Kyle Ray
  CPE 631 Advanced Computer Architecture
  Project
**/


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Green Run Button
    QPalette pal = QPalette();
    pal.setColor(QPalette::Button, Qt::green);
    ui->RunTest_pushButton->setPalette(pal);

    // Set up tool tips
    ui->ExecuteCore_Text->setToolTip("Provide the core ID that you want to execute your application on.");
    ui->Perfscope_pushButton->setToolTip("Start real time graphing of power and energy consumed");
    ui->RunTest_pushButton->setToolTip("Run executable with performance metrics selected");
    ui->ApplicationLoad_pushButton->setToolTip("Load application executable");
    ui->PerfGroups_List->setToolTip("Double click to add");
    ui->PerfMetrics_List->setToolTip("Double click to add metric, make sure to add a compatible counter (match counter with last entry in metric i.e. PMC use PMC0-4)");
    ui->PerfCounters_List->setToolTip("Double click to add");
    ui->ChosenPerfGroups_List->setToolTip("Double click to remove");
    ui->ChosenPerfMetrics_List->setToolTip("Double click to remove");
    ui->ChosenPerfCounters_List->setToolTip("Double click to remove");
    ui->Features_List->setToolTip("Select and use enable/disable button to turn feature on/off");
    ui->Breakdown_pushButton->setToolTip("Run loaded application with perf and collect generic measurements, provides graphical view of counts.");
    ui->LikwidCommand_Text->setToolTip("Likwid perfctr command using current selections");

    // Alignment
    ui->ExecuteCore_Text->setText("0");
    ui->ExecuteCore_Text->setAlignment(Qt::AlignCenter);

    // Initially don't start in this mode
    perfscopeMode_ = false;

    // Initial perf command string
    likwidPerfCommand_ = "likwid-perfctr -C 0 -M 1 ";
    ui->LikwidCommand_Text->setText(likwidPerfCommand_);

    // Setup the Logo
    QPixmap logo("usr/share/Logo/UAH_Logo.png");
    ui->Logo->setPixmap(logo);
    ui->Logo->setScaledContents(true);

    // Run Topology
    getTopology();

    // Run likwid-perfctr -a to get performance groups
    getPerformanceGroups();

    // Run likwid-perfctr -e to get performance metrics allowed on current machine
    getPerformanceMetrics();

    // Get CPU Feature List
    getFeatureList();

    // Setup CPI Stack Items
    cpiItem_ = nullptr;
    cpiScene_ = new QGraphicsScene(this);

    // Setup Breakdown Items
    perfItem_ = nullptr;
    perfScene_ = new QGraphicsScene(this);

    // Safe values for load and output directories
    // Help to guard against trying to run "Load an Application"
    // as well as store files at "Please select an output directory"
    safeApplication_ = "Load an Application!";
    safeOutDir_ = "Please select an output directory!";
}

// Destructor
MainWindow::~MainWindow()
{
    // Clean up
    delete cpiItem_;
    delete perfItem_;
    delete cpiScene_;
    delete perfScene_;
    delete ui;
}

// Method to gather topology information
void MainWindow::getTopology()
{
    // Execute likwid topology
    system("likwid-topology -c -C -g --output top.txt");
    QFile topFile("./top.txt");

    // Error Check the file
    if (!topFile.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", topFile.errorString());

    // Convert file into stream to show it in text box
    QTextStream inStream(&topFile);
    inStream.setCodec("UTF-8");
    ui->Topology_Text->setText(inStream.readAll());
    QFont topFont = ui->Topology_Text->font();
    topFont.setPointSize(12);
    topFont.setBold(true);
    topFont.setFamily("Ubuntu Mono");
    ui->Topology_Text->setFont(topFont);
}

// Method to gather performance group information
void MainWindow::getPerformanceGroups()
{
    // Execute likwid-perfctr -a to get performance groups
    system("likwid-perfctr -a > perfGroups.txt");
    QFile perfGroupFile("./perfGroups.txt");

    // Error Check the file
    if (!perfGroupFile.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", perfGroupFile.errorString());

    // Read the supported performance groups and populate the list
    QTextStream perfInStream(&perfGroupFile);
    perfInStream.setCodec("UTF-8");
    perfInStream.readLine();
    perfInStream.readLine();

    // Read the data from the stream
    while(!perfInStream.atEnd())
    {

        // Format the string
        QStringList perfGroupList = perfInStream.readLine().split("\t");
        QString perfGroup = perfGroupList.at(0);
        perfGroup = perfGroup.remove(" ");
        QString desc = perfGroupList.at(1);

        // Place the information on the GUI
        ui->PerfGroups_List->addItem(perfGroup);
        ui->PerfGroupsDescription_List->addItem(desc);
    }
}

// Method to gather performance metrics information
void MainWindow::getPerformanceMetrics()
{
    // Execute likwid-perfctr -a to get performance groups
    system("likwid-perfctr -e > perfMetrics.txt");
    QFile perfMetricFile("./perfMetrics.txt");

    // Error Check the file
    if (!perfMetricFile.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", perfMetricFile.errorString());

    bool readingCounters = true;
    bool readingMetrics = false;

    // Read the supported performance groups and populate the list
    QTextStream perfInStream(&perfMetricFile);
    perfInStream.setCodec("UTF-8");
    perfInStream.readLine();
    perfInStream.readLine();

    // Read the data from the stream
    while(!perfInStream.atEnd())
    {
        // Grab the current performance macro and description
        QString perfMetric = perfInStream.readLine();
        if (perfMetric.isEmpty())
        {
            readingCounters = false;
            continue;
        }
        else if (!readingCounters && !readingMetrics)
        {
            perfInStream.readLine();

            readingMetrics = true;
            continue;
        }

        // Add the current option to the list
        if (readingCounters)
            ui->PerfCounters_List->addItem(perfMetric);
        else
            ui->PerfMetrics_List->addItem(perfMetric);
    }
}

// Method to retrieve features information
void MainWindow::getFeatureList()
{
    // Clear the current features list
    ui->Features_List->clear();
    ui->FeaturesStatus_List->clear();

    // Execute likwid-perfctr -a to get performance groups
    QString runString = "likwid-features -c " + (executeCore_.isEmpty() ? "0" : executeCore_) + " -l > cpuFeatures.txt";
    system(runString.toStdString().c_str());
    QFile featuresFile("./cpuFeatures.txt");

    // Error Check the file
    if (!featuresFile.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", featuresFile.errorString());

    // Read the supported performance groups and populate the list
    QTextStream featureInStream(&featuresFile);
    featureInStream.setCodec("UTF-8");
    featureInStream.readLine();

    // Read the data from the stream
    while(!featureInStream.atEnd())
    {
        // Grab the current feature
        QStringList currFeatureList = featureInStream.readLine().remove("\t").split(" ");
        currFeatureList.removeAll("");
        QString feature = currFeatureList.at(0);
        QString status = currFeatureList.at(1);

        // Add the current option to the list
        ui->Features_List->addItem(feature);
        ui->FeaturesStatus_List->addItem(status);
    }
}

// Method to display the resolution of a feature change to the user
void MainWindow::updateFeaturesResultOutput()
{
    // Open the features results file
    QFile featuresFile("./featuresListResults.txt");

    // Error Check the file
    if (!featuresFile.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", featuresFile.errorString());

    // Read the supported performance groups and populate the list
    QTextStream featureInStream(&featuresFile);
    featureInStream.setCodec("UTF-8");

    // Update the output
    ui->FeatureOperations_Text->setText(featureInStream.readAll());
}

// Method to enable/disable perfscope mode
void MainWindow::enableLikwidPerfScope(bool enable)
{
    if (enable)
        system("usr/share/scripts/scopeMe.sh usr/share/scripts/");
    else
        system("usr/share/scripts/killScopeForever.sh");
}


/*************************************************************
 * SLOTS
 * **********************************************************/
void MainWindow::on_ApplicationLoad_pushButton_clicked()
{
    // Prompt the user to find the application
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setFilter(QDir::Executable);
    fileDialog.setDirectory(QDir::currentPath());

    // Only accept the first file selected by the user
    QString fileName = QString();
    if (fileDialog.exec())
        fileName = fileDialog.selectedFiles().at(0);

    // Make sure there was a file selected
    if (fileName.isNull())
    {
        QMessageBox::information(0, "info", "Could not open file");
        return;
    }

    // Update member and display choice to user
    application_ = fileName;
    ui->Application_Text->setText(fileName);
}

void MainWindow::on_RunTest_pushButton_clicked()
{
    // Run application if loaded
    if (!application_.isEmpty() && !ui->Application_Text->toPlainText().contains(safeApplication_))
    {
        if (!outputDir_.isEmpty() && !ui->OutDirectory_Text->toPlainText().contains(safeOutDir_))
        {
            // Generate Likwid String based off of selections from user
            generateLikwidPerfCommand();

            // Read Command Line Arguments
            readCommandLineArgs();

            // Execute the user application
            executeUserApplication();

            // Update the CPI Stack Tab
            if (ui->ChosenPerfGroups_List->count() > 0)
                generateCPIStack();
        }
        else
            ui->OutDirectory_Text->setText(safeOutDir_);
    }
    else
        ui->Application_Text->setText(safeApplication_);

}

void MainWindow::generateLikwidPerfCommand()
{
    // Add user specified groups
    QString perfString;

    // Base Command, only working on one core in this version
    likwidPerfCommand_ = "likwid-perfctr -C " + (executeCore_.isEmpty() ? "0" : executeCore_) + " -M 1 ";
    if (!perfscopeMode_)
    {
        if (ui->PerfGroup_Tab->isEnabled())
        {
            for (int i = 0; i < ui->ChosenPerfGroups_List->count(); ++i)
                perfString += ("-g " + ui->ChosenPerfGroups_List->item(i)->text() + " ");

            // Update overall likwid command
            if (!perfString.isNull())
                likwidPerfCommand_ += perfString;
        }
        else if (ui->PerfMetric_Tab->isEnabled())
        {
            // TODO: Output an error message if the counters and metrics don't sync
            if (ui->ChosenPerfMetrics_List->count() != ui->ChosenPerfCounters_List->count())
                return;

            for (int i = 0; i < ui->ChosenPerfMetrics_List->count(); ++i)
            {
                perfString += ("-g " +                                                      // Group
                         ui->ChosenPerfMetrics_List->item(i)->text().split(',').at(0) +     // Metric
                         ":" +                                                              // Separator
                         ui->ChosenPerfCounters_List->item(i)->text().split(',').at(0));    // Counter
            }

            // Update overall likwid command
            if (!perfString.isNull())
                likwidPerfCommand_ += perfString;
        }
    }

    likwidPerfCommand_ += " -f " + application_ + " " + commandLineArgs_ + " 2>&1 | tee " + outputDir_ + "/output.txt";
    ui->LikwidCommand_Text->setText(likwidPerfCommand_);
}

void MainWindow::readCommandLineArgs()
{
    // Read Command Line Arguments from the Text Box if any
    commandLineArgs_ = ui->CommandLineArgs_Text->toPlainText();
}

void MainWindow::executeUserApplication()
{
    //TODO: Write in all of the likwid tools
    QString runString = likwidPerfCommand_;
    //QString test = "likwid-perfscope -g ENERGY -C 0 -r 10 -t 500ms ";
    //test += runString;
    system(runString.toStdString().c_str());
    //system(test.toStdString().c_str());

    // Open the output from the program and display it to the user
    QFile outputFile(outputDir_ + "/output.txt");

    // Error Check the file
    if (!outputFile.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", outputFile.errorString());

    // Convert file into stream to show it in text box
    QTextStream inStream(&outputFile);
    inStream.setCodec("UTF-8");
    ui->ApplicationOutput_Text->setText(inStream.readAll());

    // Update the Font so it is easier to read
    QFont outFont = ui->ApplicationOutput_Text->font();
    outFont.setPointSize(12);
    outFont.setBold(true);
    outFont.setFamily("Ubuntu Mono"); // Try to make this based off of the system to avoid default crash
    ui->ApplicationOutput_Text->setFont(outFont);

    // Set the focus to the Application Output Tab
    ui->tabWidget->setCurrentIndex(QuickTabs::APP_OUT);

    outputFile.close();
}

// TODO: This may just need to be removed
void MainWindow::generateCPIStack()
{
    // Likwid doesn't really support CPI for individual components like originally thought

    // Read CPI Information from the resulting file
    QFile cpiInFile(outputDir_ + "/output.txt");
    QFile cpiOutFile(outputDir_ + "/cpiInfo.txt");

    // Error Check the file
    if (!cpiInFile.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", cpiInFile.errorString());

    if (!cpiOutFile.open(QIODevice::WriteOnly))
        QMessageBox::information(0, "info", cpiOutFile.errorString());

    // Convert file into stream to show it in text box
    QTextStream cpiInStream(&cpiInFile);
    cpiInStream.setCodec("UTF-8");

    QTextStream cpiOutStream(&cpiOutFile);
    cpiOutStream.setCodec("UTF-8");

    // Read through each line grabbing the cpi information
    // Read the data from the stream
    while(!cpiInStream.atEnd())
    {
        // Grab the current performance macro and description
        QString currLine = cpiInStream.readLine();
        if (currLine.contains("group", Qt::CaseInsensitive))
        {
            // Grab the group name
            QString group = currLine.remove(" ");
            cpiOutStream << group << ": ";
        }

        if (currLine.contains("cpi", Qt::CaseInsensitive))
        {
            // Process the number after the comma
            QString cpi = currLine.mid(4).remove(" ");
            cpiOutStream << cpi << "\n";
        }
    }

    cpiInFile.close();
    cpiOutFile.close();

    // Run Python Post Processing Script
    QString runString = "python usr/share/UI_PostProcessing/genCPIStack.py " + outputDir_ + "/cpiInfo.txt " + outputDir_;
    //QString runString = "python ../UI_PostProcessing/simpleStackedBarExample.py";
    system(runString.toStdString().c_str());

    // Give the image time to process
    //std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    // Setup the image
    QImage image(outputDir_ + "/CPI_Stack.png");
    if (cpiItem_ == nullptr)
        cpiItem_ = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    else
    {
        // Remove the current item
        cpiScene_->removeItem(cpiItem_);
        delete cpiItem_;

        // Build the new item
        cpiItem_ = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    }

    // Set the scene and place the item
    ui->CPI_Stack_GraphicsView->setScene(cpiScene_);
    cpiScene_->addItem(cpiItem_);
}

void MainWindow::generateBreakdown()
{
    if (!application_.isEmpty() && !ui->Application_Text->toPlainText().contains(safeApplication_))
    {
        if (!outputDir_.isEmpty() && !ui->OutDirectory_Text->toPlainText().contains(safeOutDir_))
        {
            if (ui->PerfBranches_checkBox->isChecked() ||
            ui->PerfCache_checkBox->isChecked() ||
            ui->PerfMemory_checkBox->isChecked())
            {
                // Run perf command on the application on another core to streamline it
                // TODO: Only run the options selected by the user
                QString perfCommand = "likwid-pin -c " + (executeCore_.isEmpty() ? "0" : executeCore_) + " ";
                perfCommand += "perf stat -C " + (executeCore_.isEmpty() ? "0" : executeCore_) + " ";
                perfCommand += "-e branch-instructions,branch-misses,cache-misses,cache-references,mem-loads,mem-stores,instructions ";
                perfCommand += application_ + " " + commandLineArgs_ + " 2>&1 | tee ";
                perfCommand += outputDir_ + "/breakDown.txt" ;

                // Execute the perf stat command
                system(perfCommand.toStdString().c_str());

                // Read Perf Information from the resulting file
                QFile breakdownFile(outputDir_ + "/breakDown.txt");
                QFile breakdownOutFile(outputDir_ + "/breakdownInfo.txt");

                // Error Check the file
                if (!breakdownFile.open(QIODevice::ReadOnly))
                    QMessageBox::information(0, "info", breakdownFile.errorString());

                // Error Check the file
                if (!breakdownOutFile.open(QIODevice::WriteOnly))
                    QMessageBox::information(0, "info", breakdownOutFile.errorString());


                // Convert file into stream to process it
                QTextStream breakdownInStream(&breakdownFile);
                breakdownInStream.setCodec("UTF-8");

                // Open an output stream to write data for python to read
                QTextStream breakdownOutStream(&breakdownOutFile);
                breakdownOutStream.setCodec("UTF-8");

                QStringList values;
                QStringList finalValues;
                QStringList finalMetrics;

                while(!breakdownInStream.atEnd())
                {
                    QString currLine = breakdownInStream.readLine();

                    // Check for the three supported events
                    if (currLine.contains("branch-instructions", Qt::CaseInsensitive) ||
                            currLine.contains("branch-misses", Qt::CaseInsensitive))
                    {
                        if (ui->PerfBranches_checkBox->isChecked())
                        {
                            values = currLine.remove(",").split(" ");
                            values.removeAll("");
                            finalValues.append(values.at(0));
                            finalMetrics.append(values.at(1));
                            continue;
                        }
                    }
                    else if (currLine.contains("cache-misses", Qt::CaseInsensitive) ||
                            currLine.contains("cache-references", Qt::CaseInsensitive))
                    {
                        if (ui->PerfCache_checkBox->isChecked())
                        {
                            values = currLine.remove(",").split(" ");
                            values.removeAll("");
                            finalValues.append(values.at(0));
                            finalMetrics.append(values.at(1));
                            continue;
                        }
                    }
                    else if (currLine.contains("mem-loads", Qt::CaseInsensitive) ||
                             currLine.contains("mem-stores", Qt::CaseInsensitive))
                    {
                        if (ui->PerfMemory_checkBox->isChecked())
                        {
                            values = currLine.remove(",").split(" ");
                            values.removeAll("");
                            finalValues.append(values.at(0));
                            finalMetrics.append(values.at(1));
                            continue;
                        }
                    }
                }

                // Build the final output
                QString breakdownOut;
                for (int i = 0; i < finalValues.count(); ++i)
                    breakdownOut += finalMetrics.at(i) + ":" + finalValues.at(i) + " \n";

                // Write the value to the file
                breakdownOutStream << breakdownOut;

                // Output the GUI element
                ui->BreakdownOutput_Text->setText(breakdownOut);

                // Close the files
                breakdownFile.close();
                breakdownOutFile.close();

                // Read the breakdown file and run python to process the perf data
                QString runString = "python usr/share/UI_PostProcessing/genBreakdownChart.py " + outputDir_ + "/breakdownInfo.txt " + outputDir_ ;
                system(runString.toStdString().c_str());

                // Setup the image
                QImage image(outputDir_ + "/PerfBreakdown.png");
                if (perfItem_ == nullptr)
                    perfItem_ = new QGraphicsPixmapItem(QPixmap::fromImage(image));
                else
                {
                    // Remove the current item
                    perfScene_->removeItem(perfItem_);
                    delete perfItem_;

                    // Build the new item
                    perfItem_ = new QGraphicsPixmapItem(QPixmap::fromImage(image));
                }

                // Set the scene and place the item
                ui->BreakdownChart_GraphicsView->setScene(perfScene_);
                perfScene_->addItem(perfItem_);
            }
            else
                ui->BreakdownOutput_Text->setText("Please check one of the modules before running breakdown!");
        }
        else
            ui->OutDirectory_Text->setText(safeOutDir_);
    }
    else
        ui->Application_Text->setText(safeApplication_);
}

void MainWindow::on_PerfGroups_List_doubleClicked(const QModelIndex &index)
{
    // Check for valid index
    if (index.isValid())
    {
        for (int i = 0; i < ui->ChosenPerfGroups_List->count(); ++i)
            if (ui->ChosenPerfGroups_List->item(i)->text() == ui->PerfGroups_List->currentItem()->text())
                return;

        // If the item doesn't exist in the list then add it
        ui->ChosenPerfGroups_List->addItem(ui->PerfGroups_List->currentItem()->clone());

        // Disable the perf metric because counters can already be taken up
        ui->PerfMetric_Tab->setDisabled(true);
    }

    // Update current command
    generateLikwidPerfCommand();
}

void MainWindow::on_ChosenPerfGroups_List_doubleClicked(const QModelIndex &index)
{
    // Check for valid index
    if (index.isValid())
    {
        // Remove the current item
        if (ui->ChosenPerfGroups_List->count() > 0)
            delete ui->ChosenPerfGroups_List->item(ui->ChosenPerfGroups_List->currentIndex().row());

        if (ui->ChosenPerfGroups_List->count() == 0)
            ui->PerfMetric_Tab->setDisabled(false);
    }

    // Update current command
    generateLikwidPerfCommand();
}

void MainWindow::on_PerfCounters_List_doubleClicked(const QModelIndex &index)
{
    // Check for valid index
    if (index.isValid())
    {
        // Check if the item is already in the chosen list
        for (int i = 0; i < ui->ChosenPerfCounters_List->count(); ++i)
            if (ui->ChosenPerfCounters_List->item(i)->text() == ui->PerfCounters_List->currentItem()->text())
               return;

        // If the item doesn't exist in the list then add it
        ui->ChosenPerfCounters_List->addItem(ui->PerfCounters_List->currentItem()->clone());

        // Disable the perf group because counters can already be taken up
        ui->PerfGroup_Tab->setDisabled(true);
    }

    // Update current command
    generateLikwidPerfCommand();
}

void MainWindow::on_PerfMetrics_List_doubleClicked(const QModelIndex &index)
{
    // Check for valid index
    if (index.isValid())
    {
        // Check if the item is already in the chosen list
        for (int i = 0; i < ui->ChosenPerfMetrics_List->count(); ++i)
            if (ui->ChosenPerfMetrics_List->item(i)->text() == ui->PerfMetrics_List->currentItem()->text())
                return;

        // If the item doesn't exist in the list then add it
        ui->ChosenPerfMetrics_List->addItem(ui->PerfMetrics_List->currentItem()->clone());

        // Disable the perf group because counters can already be taken up
        ui->PerfGroup_Tab->setDisabled(true);

        // Disable CPI Stack for now
        ui->CPIStack_Tab->setDisabled(true);
    }

    // Update current command
    generateLikwidPerfCommand();
}

void MainWindow::on_ChosenPerfCounters_List_doubleClicked(const QModelIndex &index)
{
    // Check for valid index
    if (index.isValid())
    {
        // Remove the current item
        if (ui->ChosenPerfCounters_List->count() > 0)
            delete ui->ChosenPerfCounters_List->item(ui->ChosenPerfCounters_List->currentIndex().row());

        if ((ui->ChosenPerfCounters_List->count() == 0) && (ui->ChosenPerfMetrics_List->count() == 0))
            ui->PerfGroup_Tab->setDisabled(false);
    }

    // Update current command
    generateLikwidPerfCommand();
}

void MainWindow::on_ChosenPerfMetrics_List_doubleClicked(const QModelIndex &index)
{
    // Check for valid index
    if (index.isValid())
    {
        // Remove the current item
        if (ui->ChosenPerfMetrics_List->count() > 0)
            delete ui->ChosenPerfMetrics_List->item(ui->ChosenPerfMetrics_List->currentIndex().row());

        if ((ui->ChosenPerfCounters_List->count() == 0) && (ui->ChosenPerfMetrics_List->count() == 0))
        {
            ui->PerfGroup_Tab->setDisabled(false);
            ui->CPIStack_Tab->setDisabled(false);
        }
    }

    // Update current command
    generateLikwidPerfCommand();
}

void MainWindow::enableFeature(bool enable)
{
    QStringList currFeature = ui->Features_List->currentItem()->text().split(' ');
    if (currFeature.length() == 0)
        return;

    QString feature = currFeature.at(0);
    QString command;
    if (enable)
        command = "likwid-features -c " + (executeCore_.isEmpty() ? "0" : executeCore_) + " -e " + feature + " > featuresListResults.txt";
    else
        command = "likwid-features -c " + (executeCore_.isEmpty() ? "0" : executeCore_) + " -d " + feature + " > featuresListResults.txt";

    // Execute the command
    system(command.toStdString().c_str());

    // Update the list
    getFeatureList();
    updateFeaturesResultOutput();
}

void MainWindow::on_FeatureEnable_pushButton_clicked()
{
    if (ui->Features_List->currentRow() >= 0)
        enableFeature(true);
}

void MainWindow::on_FeatureDisable_pushButton_clicked()
{
    if (ui->Features_List->currentRow() >= 0)
        enableFeature(false);
}

void MainWindow::on_Application_Text_textChanged()
{
    // Update the current command
    generateLikwidPerfCommand();
}

void MainWindow::on_CommandLineArgs_Text_textChanged()
{
    // Read Command Line Arguments from the Text Box if any
    commandLineArgs_ = ui->CommandLineArgs_Text->toPlainText();

    // Update current command
    generateLikwidPerfCommand();
}

void MainWindow::on_Breakdown_pushButton_clicked()
{
    // Run the perf command
    generateBreakdown();
}

void MainWindow::on_Perfscope_pushButton_clicked()
{
    // Change color of the button to notify the user of which mode
    // White = Normal
    // Green = Perfscope Mode
    QPalette pal = QPalette();
    pal.setColor(QPalette::Button, (perfscopeMode_ ? Qt::white : Qt::green));
    ui->Perfscope_pushButton->setPalette(pal);

    // Control what is enabled based on this button press
    if (perfscopeMode_)
    { // will be turning it off so activate other widgets
        ui->PerfGroup_Tab->setDisabled(false);
        ui->PerfMetric_Tab->setDisabled(false);
        ui->CPIStack_Tab->setDisabled(false);
        ui->Perfscope_pushButton->setText("Start Perf Scope");

        // Turn off perfscope
        enableLikwidPerfScope(false);
    }
    else
    { // will be turning it on so deactive other widgets
        ui->PerfGroup_Tab->setDisabled(true);
        ui->PerfMetric_Tab->setDisabled(true);
        ui->CPIStack_Tab->setDisabled(true);
        ui->Perfscope_pushButton->setText("Stop Perf Scope");

        // Start Perfscope
        enableLikwidPerfScope(true);
    }

    // Invert the flag
    perfscopeMode_ = !perfscopeMode_;
}

void MainWindow::on_ExecuteCore_Text_textChanged()
{
    // TODO: Clean up the regex
    executeCore_ = ui->ExecuteCore_Text->toPlainText().remove(QRegExp("[^a-zA-Z\\d\\s]")).remove(QRegExp("[a-zA-Z]+(?: [a-zA-Z]+)*")).remove(" ");
    generateLikwidPerfCommand();
    getFeatureList();
}

void MainWindow::on_OutDirectory_pushButton_clicked()
{
    // Prompt the user to find the application
    QFileDialog fileDialog(this);
    fileDialog.setOption(QFileDialog::ShowDirsOnly, true);
    fileDialog.setDirectory(QDir::currentPath());

    QString dir = fileDialog.getExistingDirectory(this, "Select Directory", QDir::currentPath(), QFileDialog::ShowDirsOnly);

    // Update member and display choice to user
    outputDir_ = dir;
    ui->OutDirectory_Text->setText(dir);
}

void MainWindow::on_OutDirectory_Text_textChanged()
{
    // Save the output directory and update the likwid command to include it
    outputDir_ = ui->OutDirectory_Text->toPlainText();
    generateLikwidPerfCommand();
}
