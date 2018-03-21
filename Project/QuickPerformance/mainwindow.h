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

    // Execution Methods
    void executeUserApplication();
    void generateCPIStack();

    // Destructor
    ~MainWindow();

private slots:
    void on_ApplicationLoad_pushButton_clicked();

    void on_RunTest_pushButton_clicked();

private:
    // Reference to the UI
    Ui::MainWindow *ui;

    // Application File
    QString application_;

    QGraphicsItem* item;
    QGraphicsScene* scene;
};

#endif // MAINWINDOW_H
