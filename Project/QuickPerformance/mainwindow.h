/**
  mainwindow.h

  Main Window header file for the Quick Performance Application
  Author: Kyle Ray
  CPE 631 Advanced Computer Architecture
  Project
**/


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

#include <thread>
#include <chrono>

// Enumeration for Tabs
enum QuickTabs
{
    TOPOLOGY = 0,
    PERF_STAT,
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

    // Feature Control
    void on_FeatureEnable_pushButton_clicked();
    void on_FeatureDisable_pushButton_clicked();

    // Application Selection
    void on_Application_Text_textChanged();
    void on_CommandLineArgs_Text_textChanged();

    // Special Buttons
    void on_Breakdown_pushButton_clicked();
    void on_Perfscope_pushButton_clicked();

    // Core #
    void on_ExecuteCore_Text_textChanged();

    // Output
    void on_OutDirectory_pushButton_clicked();
    void on_OutDirectory_Text_textChanged();

private:
    // Reference to the UI
    Ui::MainWindow *ui;

    // Application File
    QString application_;
    QString safeApplication_;

    // Output Directory
    QString outputDir_;
    QString safeOutDir_;

    // Command Line Arguments for Application
    QString commandLineArgs_;

    // Likwid String
    QString likwidPerfCommand_;

    // Stethoscope Mode
    bool perfscopeMode_;

    // Current Core
    QString executeCore_;

    // Custom View Items
    QGraphicsItem* cpiItem_;
    QGraphicsItem* perfItem_;
    QGraphicsScene* cpiScene_;
    QGraphicsScene* perfScene_;

    // Execution Methods
    void generateLikwidPerfCommand();
    void readCommandLineArgs();
    void executeUserApplication();
    void generateCPIStack();
    void generateBreakdown();

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

    // Perfscope thread (test threads)
    std::thread spawn(){ return std::thread( [this] { this->executeUserApplication(); } ); }
    std::thread spawnPerfScope(){ return std::thread( [this] { this->enableLikwidPerfScope(true); } ); }
};

#endif // MAINWINDOW_H
