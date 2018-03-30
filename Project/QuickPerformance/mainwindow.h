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

// Enumeration for Tabs
enum QuickTabs
{
    TOPOLOGY = 0,
    CACHE,
    MEMORY,
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
    void on_ApplicationLoad_pushButton_clicked();
    void on_RunTest_pushButton_clicked();
    void on_AddPerfGroup_pushButton_clicked();
    void on_RemovePerfGroup_pushButton_clicked();

private:
    // Reference to the UI
    Ui::MainWindow *ui;

    // Application File
    QString application_;

    // Command Line Arguments for Application
    QString commandLineArgs_;

    // Likwid String
    QString likwidPerfCommand_;

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

    // Perfscope thread
    std::thread spawn(){ return std::thread( [this] { this->executeUserApplication(); } ); }
};

#endif // MAINWINDOW_H
