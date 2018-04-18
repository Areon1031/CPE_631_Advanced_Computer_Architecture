#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui>

#include <likwid.h> // May not be necessary, remove later if needed
#include <thread>
#include <chrono>

// Enumeration for Tabs
enum QuickTabs
{
    TOPOLOGY = 0,
    PERF_GROUPS,
    PERF_METRICS,
    FEATURE_CONTROL,
    CPI,
    APP_OUT
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit MainWindow(QWidget *parent = 0);

    // Destructor
    ~MainWindow();

private slots:
    // Push Button Control
    void on_ApplicationLoad_pushButton_clicked();
    void on_RunTest_pushButton_clicked();

    // Double Click (Move Data)
    void on_PerfGroups_List_doubleClicked(const QModelIndex &index);
    void on_ChosenPerfGroups_List_doubleClicked(const QModelIndex &index);
    void on_PerfCounters_List_doubleClicked(const QModelIndex &index);
    void on_PerfMetrics_List_doubleClicked(const QModelIndex &index);
    void on_ChosenPerfCounters_List_doubleClicked(const QModelIndex &index);
    void on_ChosenPerfMetrics_List_doubleClicked(const QModelIndex &index);


    void on_StethoscopeMode_pushButton_clicked();

    void on_FeatureEnable_pushButton_clicked();

    void on_FeatureDisable_pushButton_clicked();

private:
    // Reference to the UI
    Ui::MainWindow *ui;

    // Application File
    QString application_;

    // Command Line Arguments for Application
    QString commandLineArgs_;

    // Likwid String
    QString likwidPerfCommand_;

    // Stethoscope Mode
    bool stethoscopeMode_;

    QGraphicsItem* item_;
    QGraphicsScene* scene_;

    // Execution Methods
    void generateLikwidPerfCommand();
    void readCommandLineArgs();
    void executeUserApplication();
    void generateCPIStack();

    // Likwid Utility
    void getTopology();
    void getPerformanceGroups();
    void getPerformanceMetrics();
    void getFeatureList();

    // Likwid Perfscope
    void enableLikwidPerfScope(bool enable);

    // Features
    void updateFeaturesResultOutput();
    void enableFeature(bool enable);

    // Perfscope thread
    std::thread spawn(){ return std::thread( [this] { this->executeUserApplication(); } ); }
    std::thread spawnPerfScope(){ return std::thread( [this] { this->enableLikwidPerfScope(true); } ); }
};

#endif // MAINWINDOW_H
