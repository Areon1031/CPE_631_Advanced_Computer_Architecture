/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "customview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextEdit *Application_Text;
    QLabel *Application_Label;
    QPushButton *ApplicationLoad_pushButton;
    QPushButton *RunTest_pushButton;
    QLabel *Logo;
    QTabWidget *tabWidget;
    QWidget *Topology_Tab;
    QTextBrowser *Topology_Text;
    QWidget *CacheMiss_Tab;
    QWidget *MemoryUsage_Tab;
    QWidget *CPIStack_Tab;
    CustomView *CPI_Stack_GraphicsView;
    QWidget *ApplicationOutput_Tab;
    QTextBrowser *ApplicationOutput_Text;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1077, 609);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Application_Text = new QTextEdit(centralWidget);
        Application_Text->setObjectName(QStringLiteral("Application_Text"));
        Application_Text->setGeometry(QRect(690, 30, 281, 31));
        Application_Text->setReadOnly(true);
        Application_Label = new QLabel(centralWidget);
        Application_Label->setObjectName(QStringLiteral("Application_Label"));
        Application_Label->setGeometry(QRect(690, 10, 161, 17));
        ApplicationLoad_pushButton = new QPushButton(centralWidget);
        ApplicationLoad_pushButton->setObjectName(QStringLiteral("ApplicationLoad_pushButton"));
        ApplicationLoad_pushButton->setGeometry(QRect(980, 31, 89, 30));
        RunTest_pushButton = new QPushButton(centralWidget);
        RunTest_pushButton->setObjectName(QStringLiteral("RunTest_pushButton"));
        RunTest_pushButton->setGeometry(QRect(980, 510, 89, 30));
        Logo = new QLabel(centralWidget);
        Logo->setObjectName(QStringLiteral("Logo"));
        Logo->setGeometry(QRect(20, 10, 261, 131));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(20, 150, 1041, 351));
        Topology_Tab = new QWidget();
        Topology_Tab->setObjectName(QStringLiteral("Topology_Tab"));
        Topology_Text = new QTextBrowser(Topology_Tab);
        Topology_Text->setObjectName(QStringLiteral("Topology_Text"));
        Topology_Text->setGeometry(QRect(0, 0, 1031, 321));
        tabWidget->addTab(Topology_Tab, QString());
        CacheMiss_Tab = new QWidget();
        CacheMiss_Tab->setObjectName(QStringLiteral("CacheMiss_Tab"));
        tabWidget->addTab(CacheMiss_Tab, QString());
        MemoryUsage_Tab = new QWidget();
        MemoryUsage_Tab->setObjectName(QStringLiteral("MemoryUsage_Tab"));
        tabWidget->addTab(MemoryUsage_Tab, QString());
        CPIStack_Tab = new QWidget();
        CPIStack_Tab->setObjectName(QStringLiteral("CPIStack_Tab"));
        CPI_Stack_GraphicsView = new CustomView(CPIStack_Tab);
        CPI_Stack_GraphicsView->setObjectName(QStringLiteral("CPI_Stack_GraphicsView"));
        CPI_Stack_GraphicsView->setGeometry(QRect(0, 0, 1041, 321));
        tabWidget->addTab(CPIStack_Tab, QString());
        ApplicationOutput_Tab = new QWidget();
        ApplicationOutput_Tab->setObjectName(QStringLiteral("ApplicationOutput_Tab"));
        ApplicationOutput_Text = new QTextBrowser(ApplicationOutput_Tab);
        ApplicationOutput_Text->setObjectName(QStringLiteral("ApplicationOutput_Text"));
        ApplicationOutput_Text->setGeometry(QRect(0, 0, 1041, 321));
        tabWidget->addTab(ApplicationOutput_Tab, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1077, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Application_Label->setText(QApplication::translate("MainWindow", "Application Under Test", Q_NULLPTR));
        ApplicationLoad_pushButton->setText(QApplication::translate("MainWindow", "Load", Q_NULLPTR));
        RunTest_pushButton->setText(QApplication::translate("MainWindow", "Run Test", Q_NULLPTR));
        Logo->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(Topology_Tab), QApplication::translate("MainWindow", "Architecture Topology", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(CacheMiss_Tab), QApplication::translate("MainWindow", "Cache Misses", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(MemoryUsage_Tab), QApplication::translate("MainWindow", "Memory Usage", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(CPIStack_Tab), QApplication::translate("MainWindow", "CPI Stack", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(ApplicationOutput_Tab), QApplication::translate("MainWindow", "Application Output", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
