#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    topology_init();

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
    system("likwid-topology -g --output top.txt");
    QFile topFile("./top.txt");

    // Error Check the file
    if (!topFile.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", topFile.errorString());

    // Convert file into stream to show it in text box
    QTextStream inStream(&topFile);
    inStream.setCodec("UTF-8");
    ui->Topology_Text->setText(inStream.readAll());
    //ui->Topology_Text->setAlignment(Qt::AlignCenter);
    QFont topFont = ui->Topology_Text->font();
    topFont.setPointSize(12);
    topFont.setBold(true);
    topFont.setFamily("Ubuntu Mono"); // Try to make this based off of the system to avoid default crash
    ui->Topology_Text->setFont(topFont);

    // Setup CPI Stack Items
    item = nullptr;
    scene = new QGraphicsScene(this);
}

MainWindow::~MainWindow()
{
    // Clean up
    delete item;
    delete scene;
    delete ui;
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
        executeUserApplication();

        // Update the CPI Stack Tab
        generateCPIStack();

        // Execute Likwid Example
        likwidExample();
    }
    else
        ui->Application_Text->setText("Please Load an Application!");

}

void MainWindow::executeUserApplication()
{
    //TODO: Write in all of the likwid tools
    QString runString = application_ + " 2>&1 | tee output.txt";
    QString test = "likwid-perfscope -g ENERGY -C S0:7 -r 10 -t 500ms ";
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
    // Run Python Post Processing Script
    QString runString = "python ../UI_PostProcessing/simpleStackedBarExample.py";
    system(runString.toStdString().c_str());

    // Setup the image
    QImage image("../bin/Results/CPI_Stack.png");
    if (item == nullptr)
        item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    else
    {
        // Remove the current item
        scene->removeItem(item);
        delete item;

        // Build the new item
        item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    }

    // Set the scene and place the item
    ui->CPI_Stack_GraphicsView->setScene(scene);
    scene->addItem(item);
}

void MainWindow::likwidExample()
{
    int i, j;
    int err;
    int* cpus;
    int gid;
    double result = 0.0;
    char estr[] = "L2_LINES_IN_ALL:PMC0,L2_TRANS_L2_WB:PMC1";
    //perfmon_setVerbosity(3);
    // Load the topology module and print some values.
    err = topology_init();
    if (err < 0)
    {
        printf("Failed to initialize LIKWID's topology module\n");
        return;
    }

    err = numa_init();
    if (err < 0)
    {
        printf("Failed to initialize LIKWID's numa module\n");
    }

    // Initialize the perfmon maps
    perfmon_init_maps();

    // CpuInfo_t contains global information like name, CPU family, ...
    CpuInfo_t info = get_cpuInfo();
    // CpuTopology_t contains information about the topology of the CPUs.
    CpuTopology_t topo = get_cpuTopology();
    // Create affinity domains. Commonly only needed when reading Uncore counters
    affinity_init();

    printf("Likwid example on a %s with %d CPUs\n", info->name, topo->numHWThreads);

    cpus = (int*)malloc(topo->numHWThreads * sizeof(int));
    if (!cpus)
        return;

    for (i=0;i<topo->numHWThreads;i++)
    {
        cpus[i] = topo->threadPool[i].apicId;
    }

    for (int t = 0; t < topo->numHWThreads; t++)
    {
        perfmon_check_counter_map(cpus[t]);
    }

    // Must be called before perfmon_init() but only if you want to use another
    // access mode as the pre-configured one. For direct access (0) you have to
    // be root.
    //accessClient_setaccessmode(0);

    // Initialize the perfmon module.
    err = perfmon_init(topo->numHWThreads, cpus);
    if (err < 0)
    {
        printf("Failed to initialize LIKWID's performance monitoring module\n");
        topology_finalize();
        return;
    }

    int numGroups = perfmon_getNumberOfGroups();
    int numEvents = perfmon_getNumberOfEvents(0);
    std::vector<int> numEventsPerGroup;

    for (int k = 0; k < numGroups; k++)
    {
        numEventsPerGroup.push_back(perfmon_getNumberOfEvents(k));
    }

    cout << "Number of Groups " << numGroups << " and number of events per group " << numEventsPerGroup.size();
    char* test = perfmon_getGroupInfoLong(0);

    // Add eventset string to the perfmon module.
    gid = perfmon_addEventSet(estr);
    if (gid < 0)
    {
        printf("Failed to add event string %s to LIKWID's performance monitoring module\n", estr);
        perfmon_finalize();
        topology_finalize();
        return;
    }

    // Setup the eventset identified by group ID (gid).
    err = perfmon_setupCounters(gid);
    if (err < 0)
    {
        printf("Failed to setup group %d in LIKWID's performance monitoring module\n", gid);
        perfmon_finalize();
        topology_finalize();
        return;
    }
    // Start all counters in the previously set up event set.
    err = perfmon_startCounters();
    if (err < 0)
    {
        printf("Failed to start counters for group %d for thread %d\n",gid, (-1*err)-1);
        perfmon_finalize();
        topology_finalize();
        return;
    }
    // Perform something
    // TODO: Perform the program here
    // Stop all counters in the previously started event set.
    err = perfmon_stopCounters();
    if (err < 0)
    {
        printf("Failed to stop counters for group %d for thread %d\n",gid, (-1*err)-1);
        perfmon_finalize();
        topology_finalize();
        return;
    }


    // Print the result of every thread/CPU for all events in estr.
    char* ptr = strtok(estr,",");
    j = 0;
    while (ptr != NULL)
    {
        for (i = 0;i < topo->numHWThreads; i++)
        {
            result = perfmon_getResult(gid, j, i);
            printf("Measurement result for event set %s at CPU %d: %f\n", ptr, cpus[i], result);
        }
        ptr = strtok(NULL,",");
        j++;
    }


    free(cpus);
    // Uninitialize the perfmon module.
    perfmon_finalize();
    affinity_finalize();
    // Uninitialize the topology module.
    topology_finalize();
}
