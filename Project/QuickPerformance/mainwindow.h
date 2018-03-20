#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ApplicationLoad_pushButton_clicked();

    void on_RunTest_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    // Application File
    QString application_;
};

#endif // MAINWINDOW_H
