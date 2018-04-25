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

    // Setup the background
    //this->setStyleSheet("background-color: black");
    //QPalette pal = QPalette();
    //pal.setColor(QPalette::Background, Qt::black);
    //this->setAutoFillBackground(true);
    //this->setPalette(pal);

    // Initially don't start in this mode
    perfscopeMode_ = false;

    // Initial perf command string
    likwidPerfCommand_ = "likwid-perfctr -C 0 -M 1 ";
    ui->LikwidCommand_Text->setText(likwidPerfCommand_);

    // Setup the Logo
    QPixmap logo("../bin/Logo/UAH_Logo.png");
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
    item_ = nullptr;
    scene_ = new QGraphicsScene(this);
}

MainWindow::~MainWindow()
{
    // Clean up
    delete item_;
    delete scene_;
    delete ui;
}

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
        // Grab the current performance macro and description
        QString perfGroup = perfInStream.readLine();
        QString finalString;
        bool foundFirstChar = false;

        // Remove the description from the string as well as unnecessary characters
        for (int i = 0; i < perfGroup.size(); i++)
        {
            // Remove leading whitespace and tabs
            if (perfGroup.at(i) != ' ' && perfGroup.at(i) != '\t')
            {
                finalString += perfGroup.at(i);
                foundFirstChar = true;
            }

            // If the first character has been found, we have the performance group
            // stop processing when we find the start of the description
            if (foundFirstChar && (perfGroup.at(i) == ' ' || perfGroup.at(i) == '\t'))
                break;
        }

        // Add the current option to the list
        ui->PerfGroups_List->addItem(finalString);
    }
}

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

void MainWindow::getFeatureList()
{
    // Clear the current features list
    ui->Features_List->clear();

    // Execute likwid-perfctr -a to get performance groups
    system("likwid-features -c 0 -l > cpuFeatures.txt");
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
        // Only process modifiable features (contains an *)
        QString currFeature = featureInStream.readLine();
        // TODO: Implement safety before final release
        //if (!currFeature.contains('*'))
        //    continue;


        QStringList currFeatureList = currFeature.split(' ');
        QMutableListIterator<QString> it(currFeatureList);
        while (it.hasNext())
        {
            it.next();
            it.value() = it.value().trimmed();
            if (it.value().length() == 0)
                it.remove();
        }

        currFeature = currFeatureList.join("\t\t");

        // Add the current option to the list
        ui->Features_List->addItem(currFeature);
    }
}

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

    ui->FeatureOperations_Text->setText(featureInStream.readAll());
}

void MainWindow::enableLikwidPerfScope(bool enable)
{
    if (enable)
        system("./scopeMe.sh");
    else
        system("./killScopeForever.sh");
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
    if (!application_.isEmpty())
    {
        // Run the application with the likwid toolset
        //std::thread userApp = spawn();
        //userApp.join();

        // Generate Likwid String based off of selections from user
        generateLikwidPerfCommand();

        // Read Command Line Arguments
        readCommandLineArgs();

        // Execute the user application
        executeUserApplication();

        // Update the CPI Stack Tab
        if (ui->ChosenPerfGroups_List->count() > 0 && ui->CPIStack_Tab->isEnabled())
            generateCPIStack();
    }
    else
        ui->Application_Text->setText("Please Load an Application!");

}

void MainWindow::generateLikwidPerfCommand()
{
    // Add user specified groups
    QString perfString;

    // Base Command
    likwidPerfCommand_ = "likwid-perfctr -C 0 -M 1 ";
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

    likwidPerfCommand_ += " -f " + application_ + " " + commandLineArgs_ + " 2>&1 | tee output.txt";;
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
    QFile outputFile("./output.txt");

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

void MainWindow::generateCPIStack()
{
    // TODO: Update the python post processing to accept data from the gui
    // This may just have the python script parsing the data output.txt
    // from this application and feeding it back.

    // Likwid doesn't really support CPI for individual components like originally thought
    // Will probably try to add a sort of breakdown chart instead of cpi stack

    // Read CPI Information from the resulting file
    QFile cpiInFile("./output.txt");
    QFile cpiOutFile("./cpiInfo.txt");

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
    QString runString = "python ../UI_PostProcessing/genCPIStack.py";
    //QString runString = "python ../UI_PostProcessing/simpleStackedBarExample.py";
    system(runString.toStdString().c_str());

    // Give the image time to process
    //std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    // Setup the image
    QImage image("../bin/Results/CPI_Stack.png");
    if (item_ == nullptr)
        item_ = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    else
    {
        // Remove the current item
        scene_->removeItem(item_);
        delete item_;

        // Build the new item
        item_ = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    }

    // Set the scene and place the item
    ui->CPI_Stack_GraphicsView->setScene(scene_);
    scene_->addItem(item_);
}

void MainWindow::generateBreakdown()
{
    if (!application_.isEmpty())
    {
        // Run perf command on the application on another core to streamline it
        QString perfCommand = "perf stat -e branch-instructions,branch-misses,cache-misses,cache-references,mem-loads,mem-stores,instructions ";
        perfCommand += application_ + " 2>&1 | tee breakDown.txt" ;
        system(perfCommand.toStdString().c_str());

        // TODO: Update the python post processing to accept data from the gui
        // This may just have the python script parsing the data output.txt
        // from this application and feeding it back.

        // Likwid doesn't really support CPI for individual components like originally thought
        // Will probably try to add a sort of breakdown chart instead of cpi stack

        // Read CPI Information from the resulting file
        QFile breakdownFile("./breakDown.txt");

        // Error Check the file
        if (!breakdownFile.open(QIODevice::ReadOnly))
            QMessageBox::information(0, "info", breakdownFile.errorString());

        // Convert file into stream to show it in text box
        QTextStream breakdownInStream(&breakdownFile);
        breakdownInStream.setCodec("UTF-8");
        ui->BreakdownOutput_Text->setText(breakdownInStream.readAll());

        breakdownFile.close();

//        // Run Python Post Processing Script
//        QString runString = "python ../UI_PostProcessing/genCPIStack.py";
//        //QString runString = "python ../UI_PostProcessing/simpleStackedBarExample.py";
//        system(runString.toStdString().c_str());

//        // Give the image time to process
//        //std::this_thread::sleep_for(std::chrono::milliseconds(10000));

//        // Setup the image
//        QImage image("../bin/Results/CPI_Stack.png");
//        if (item_ == nullptr)
//            item_ = new QGraphicsPixmapItem(QPixmap::fromImage(image));
//        else
//        {
//            // Remove the current item
//            scene_->removeItem(item_);
//            delete item_;

//            // Build the new item
//            item_ = new QGraphicsPixmapItem(QPixmap::fromImage(image));
//        }

//        // Set the scene and place the item
//        ui->CPI_Stack_GraphicsView->setScene(scene_);
//        scene_->addItem(item_);
    }
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
//        // Check if the item is already in the chosen list
//        for (int i = 0; i < ui->ChosenPerfCounters_List->count(); ++i)
//            if (ui->ChosenPerfCounters_List->item(i)->text() == ui->PerfCounters_List->currentItem()->text())
//                return;

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
        command = "likwid-features -c 0 -e " + feature + " > featuresListResults.txt";
    else
        command = "likwid-features -c 0 -d " + feature + " > featuresListResults.txt";

    // Execute the command
    system(command.toStdString().c_str());

    // Update the list
    getFeatureList();
    updateFeaturesResultOutput();
}

void MainWindow::on_FeatureEnable_pushButton_clicked()
{
    enableFeature(true);
}

void MainWindow::on_FeatureDisable_pushButton_clicked()
{
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
    generateBreakdown();
}

void MainWindow::on_Perfscope_pushButton_clicked()
{
    // Change color of the button to notify the user of which mode
    // White = Normal
    // Green = Stethoscope Mode
    QPalette pal = QPalette();
    pal.setColor(QPalette::Button, (perfscopeMode_ ? Qt::white : Qt::green));
    ui->Perfscope_pushButton->setPalette(pal);

    // Control what is enabled based on this button press
    if (perfscopeMode_)
    { // will be turning it off so activate other widgets
        ui->PerfGroup_Tab->setDisabled(false);
        ui->PerfMetric_Tab->setDisabled(false);
        ui->CPIStack_Tab->setDisabled(false);
        //ui->RefreshRate_Text->setReadOnly(true);

        // Turn off perfscope
        enableLikwidPerfScope(false);
    }
    else
    { // will be turning it on so deactive other widgets
        ui->PerfGroup_Tab->setDisabled(true);
        ui->PerfMetric_Tab->setDisabled(true);
        ui->CPIStack_Tab->setDisabled(true);
        //ui->RefreshRate_Text->setReadOnly(false);

        // Start Perfscope
        enableLikwidPerfScope(true);
    }

    // Invert the flag
    perfscopeMode_ = !perfscopeMode_;
}
