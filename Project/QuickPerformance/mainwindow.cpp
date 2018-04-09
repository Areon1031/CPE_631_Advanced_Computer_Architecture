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

    // Setup the Logo
    QPixmap logo("../bin/Logo/UAH_Logo.png");
    ui->Logo->setPixmap(logo);
    ui->Logo->setScaledContents(true);

    // Run Topology
    getTopology();

    // Run likwid-perfctr -a to get performance groups
    getPerformanceGroups();

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

void doSomething()
{
    return;
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
        if (ui->ChosenPerfGroups_List->count() > 0)
            generateCPIStack();
    }
    else
        ui->Application_Text->setText("Please Load an Application!");

}

void MainWindow::generateLikwidPerfCommand()
{
    // Add user specified groups
    QString perfString;
    for (int i = 0; i < ui->ChosenPerfGroups_List->count(); ++i)
    {
        perfString += ("-g " + ui->ChosenPerfGroups_List->item(i)->text() + " ");
    }

    // Update overall likwid command
    if (!perfString.isNull())
    {
        likwidPerfCommand_ = "likwid-perfctr -C 1 ";
        likwidPerfCommand_ += perfString;
    }
    else
        likwidPerfCommand_ = "";
}

void MainWindow::readCommandLineArgs()
{
    // Read Command Line Arguments from the Text Box if any
    commandLineArgs_ = ui->CommandLineArgs_Text->toPlainText();
}

void MainWindow::executeUserApplication()
{
    //TODO: Write in all of the likwid tools
    QString runString = likwidPerfCommand_ + application_ + " " + commandLineArgs_ + " 2>&1 | tee output.txt";
    QString test = "likwid-perfscope -g ENERGY -C 1 -r 10 -t 500ms ";
    test += runString;
    //system(runString.toStdString().c_str());
    system(test.toStdString().c_str());

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
}

void MainWindow::generateCPIStack()
{
    // TODO: Update the python post processing to accept data from the gui
    // This may just have the python script parsing the data output.txt
    // from this application and feeding it back.

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


    // Have Python parse the data that was just written


    // Run Python Post Processing Script
    QString runString = "python ../UI_PostProcessing/simpleStackedBarExample.py";
    system(runString.toStdString().c_str());

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

void MainWindow::on_AddPerfGroup_pushButton_clicked()
{
    // Check if the item is already in the chosen list
    for (int i = 0; i < ui->ChosenPerfGroups_List->count(); ++i)
        if (ui->ChosenPerfGroups_List->item(i)->text() == ui->PerfGroups_List->currentItem()->text())
            return;

    // If the item doesn't exist in the list then add it
    ui->ChosenPerfGroups_List->addItem(ui->PerfGroups_List->currentItem()->clone());
}

void MainWindow::on_RemovePerfGroup_pushButton_clicked()
{
    // Remove the current item
    if (ui->ChosenPerfGroups_List->count() > 0)
        delete ui->ChosenPerfGroups_List->item(ui->ChosenPerfGroups_List->currentIndex().row());
}
