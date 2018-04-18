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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
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
    QGridLayout *gridLayout_8;
    QGroupBox *Logo_Group;
    QGridLayout *gridLayout_3;
    QLabel *Logo;
    QGroupBox *Stethoscope_Group;
    QGridLayout *gridLayout_9;
    QPushButton *StethoscopeMode_pushButton;
    QLabel *RefreshRate_Label;
    QTextEdit *RefreshRate_Text;
    QGroupBox *Application_Group;
    QGridLayout *gridLayout_2;
    QLabel *Application_Label;
    QTextEdit *Application_Text;
    QPushButton *ApplicationLoad_pushButton;
    QLabel *CommandLineArgs_Label;
    QTextEdit *CommandLineArgs_Text;
    QPushButton *RunTest_pushButton;
    QTabWidget *tabWidget;
    QWidget *Topology_Tab;
    QGridLayout *gridLayout_4;
    QTextBrowser *Topology_Text;
    QWidget *PerfGroup_Tab;
    QGridLayout *gridLayout_5;
    QLabel *Application_Label_2;
    QLabel *Application_Label_3;
    QListWidget *PerfGroups_List;
    QListWidget *ChosenPerfGroups_List;
    QWidget *PerfMetric_Tab;
    QGridLayout *gridLayout;
    QLabel *PerfMetrics_Label;
    QLabel *ChosenPerfMetrics_Label;
    QLabel *ChosenPerfCoutners_Label;
    QListWidget *PerfMetrics_List;
    QListWidget *ChosenPerfMetrics_List;
    QListWidget *ChosenPerfCounters_List;
    QLabel *PerfCounters_Label;
    QListWidget *PerfCounters_List;
    QWidget *CPIStack_Tab;
    QGridLayout *gridLayout_6;
    CustomView *CPI_Stack_GraphicsView;
    QWidget *ApplicationOutput_Tab;
    QGridLayout *gridLayout_7;
    QTextBrowser *ApplicationOutput_Text;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1082, 686);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout_8 = new QGridLayout(centralWidget);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        Logo_Group = new QGroupBox(centralWidget);
        Logo_Group->setObjectName(QStringLiteral("Logo_Group"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Logo_Group->sizePolicy().hasHeightForWidth());
        Logo_Group->setSizePolicy(sizePolicy1);
        Logo_Group->setMinimumSize(QSize(260, 160));
        gridLayout_3 = new QGridLayout(Logo_Group);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        Logo = new QLabel(Logo_Group);
        Logo->setObjectName(QStringLiteral("Logo"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Logo->sizePolicy().hasHeightForWidth());
        Logo->setSizePolicy(sizePolicy2);
        Logo->setMinimumSize(QSize(200, 100));
        Logo->setMaximumSize(QSize(200, 100));

        gridLayout_3->addWidget(Logo, 0, 0, 1, 1);


        gridLayout_8->addWidget(Logo_Group, 0, 0, 1, 1);

        Stethoscope_Group = new QGroupBox(centralWidget);
        Stethoscope_Group->setObjectName(QStringLiteral("Stethoscope_Group"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Stethoscope_Group->sizePolicy().hasHeightForWidth());
        Stethoscope_Group->setSizePolicy(sizePolicy3);
        Stethoscope_Group->setMinimumSize(QSize(191, 131));
        gridLayout_9 = new QGridLayout(Stethoscope_Group);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        StethoscopeMode_pushButton = new QPushButton(Stethoscope_Group);
        StethoscopeMode_pushButton->setObjectName(QStringLiteral("StethoscopeMode_pushButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(StethoscopeMode_pushButton->sizePolicy().hasHeightForWidth());
        StethoscopeMode_pushButton->setSizePolicy(sizePolicy4);
        StethoscopeMode_pushButton->setMaximumSize(QSize(150, 30));

        gridLayout_9->addWidget(StethoscopeMode_pushButton, 0, 0, 1, 1);

        RefreshRate_Label = new QLabel(Stethoscope_Group);
        RefreshRate_Label->setObjectName(QStringLiteral("RefreshRate_Label"));
        sizePolicy2.setHeightForWidth(RefreshRate_Label->sizePolicy().hasHeightForWidth());
        RefreshRate_Label->setSizePolicy(sizePolicy2);
        RefreshRate_Label->setMaximumSize(QSize(161, 17));

        gridLayout_9->addWidget(RefreshRate_Label, 1, 0, 1, 1);

        RefreshRate_Text = new QTextEdit(Stethoscope_Group);
        RefreshRate_Text->setObjectName(QStringLiteral("RefreshRate_Text"));
        sizePolicy2.setHeightForWidth(RefreshRate_Text->sizePolicy().hasHeightForWidth());
        RefreshRate_Text->setSizePolicy(sizePolicy2);
        RefreshRate_Text->setMaximumSize(QSize(150, 31));
        RefreshRate_Text->setLineWrapMode(QTextEdit::NoWrap);
        RefreshRate_Text->setReadOnly(true);
        RefreshRate_Text->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_9->addWidget(RefreshRate_Text, 2, 0, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);

        RefreshRate_Text->raise();
        StethoscopeMode_pushButton->raise();
        RefreshRate_Label->raise();
        RefreshRate_Text->raise();
        StethoscopeMode_pushButton->raise();
        RefreshRate_Label->raise();

        gridLayout_8->addWidget(Stethoscope_Group, 0, 1, 1, 1);

        Application_Group = new QGroupBox(centralWidget);
        Application_Group->setObjectName(QStringLiteral("Application_Group"));
        sizePolicy2.setHeightForWidth(Application_Group->sizePolicy().hasHeightForWidth());
        Application_Group->setSizePolicy(sizePolicy2);
        gridLayout_2 = new QGridLayout(Application_Group);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        Application_Label = new QLabel(Application_Group);
        Application_Label->setObjectName(QStringLiteral("Application_Label"));
        sizePolicy2.setHeightForWidth(Application_Label->sizePolicy().hasHeightForWidth());
        Application_Label->setSizePolicy(sizePolicy2);
        Application_Label->setMaximumSize(QSize(161, 17));

        gridLayout_2->addWidget(Application_Label, 0, 0, 1, 1);

        Application_Text = new QTextEdit(Application_Group);
        Application_Text->setObjectName(QStringLiteral("Application_Text"));
        sizePolicy2.setHeightForWidth(Application_Text->sizePolicy().hasHeightForWidth());
        Application_Text->setSizePolicy(sizePolicy2);
        Application_Text->setMaximumSize(QSize(281, 31));
        Application_Text->setLineWrapMode(QTextEdit::NoWrap);
        Application_Text->setLineWrapColumnOrWidth(0);
        Application_Text->setReadOnly(true);

        gridLayout_2->addWidget(Application_Text, 1, 0, 1, 1);

        ApplicationLoad_pushButton = new QPushButton(Application_Group);
        ApplicationLoad_pushButton->setObjectName(QStringLiteral("ApplicationLoad_pushButton"));
        sizePolicy2.setHeightForWidth(ApplicationLoad_pushButton->sizePolicy().hasHeightForWidth());
        ApplicationLoad_pushButton->setSizePolicy(sizePolicy2);
        ApplicationLoad_pushButton->setMaximumSize(QSize(89, 30));

        gridLayout_2->addWidget(ApplicationLoad_pushButton, 1, 1, 1, 1);

        CommandLineArgs_Label = new QLabel(Application_Group);
        CommandLineArgs_Label->setObjectName(QStringLiteral("CommandLineArgs_Label"));
        sizePolicy2.setHeightForWidth(CommandLineArgs_Label->sizePolicy().hasHeightForWidth());
        CommandLineArgs_Label->setSizePolicy(sizePolicy2);
        CommandLineArgs_Label->setMaximumSize(QSize(190, 17));

        gridLayout_2->addWidget(CommandLineArgs_Label, 2, 0, 1, 1);

        CommandLineArgs_Text = new QTextEdit(Application_Group);
        CommandLineArgs_Text->setObjectName(QStringLiteral("CommandLineArgs_Text"));
        sizePolicy2.setHeightForWidth(CommandLineArgs_Text->sizePolicy().hasHeightForWidth());
        CommandLineArgs_Text->setSizePolicy(sizePolicy2);
        CommandLineArgs_Text->setMaximumSize(QSize(281, 31));
        CommandLineArgs_Text->setLineWrapMode(QTextEdit::NoWrap);
        CommandLineArgs_Text->setReadOnly(false);
        CommandLineArgs_Text->setAcceptRichText(true);

        gridLayout_2->addWidget(CommandLineArgs_Text, 3, 0, 1, 1);

        RunTest_pushButton = new QPushButton(Application_Group);
        RunTest_pushButton->setObjectName(QStringLiteral("RunTest_pushButton"));
        sizePolicy2.setHeightForWidth(RunTest_pushButton->sizePolicy().hasHeightForWidth());
        RunTest_pushButton->setSizePolicy(sizePolicy2);
        RunTest_pushButton->setMaximumSize(QSize(89, 30));

        gridLayout_2->addWidget(RunTest_pushButton, 3, 1, 1, 1);


        gridLayout_8->addWidget(Application_Group, 0, 2, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(1);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy5);
        Topology_Tab = new QWidget();
        Topology_Tab->setObjectName(QStringLiteral("Topology_Tab"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(Topology_Tab->sizePolicy().hasHeightForWidth());
        Topology_Tab->setSizePolicy(sizePolicy6);
        gridLayout_4 = new QGridLayout(Topology_Tab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        Topology_Text = new QTextBrowser(Topology_Tab);
        Topology_Text->setObjectName(QStringLiteral("Topology_Text"));

        gridLayout_4->addWidget(Topology_Text, 0, 0, 1, 1);

        tabWidget->addTab(Topology_Tab, QString());
        PerfGroup_Tab = new QWidget();
        PerfGroup_Tab->setObjectName(QStringLiteral("PerfGroup_Tab"));
        gridLayout_5 = new QGridLayout(PerfGroup_Tab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        Application_Label_2 = new QLabel(PerfGroup_Tab);
        Application_Label_2->setObjectName(QStringLiteral("Application_Label_2"));

        gridLayout_5->addWidget(Application_Label_2, 0, 0, 1, 1);

        Application_Label_3 = new QLabel(PerfGroup_Tab);
        Application_Label_3->setObjectName(QStringLiteral("Application_Label_3"));

        gridLayout_5->addWidget(Application_Label_3, 0, 1, 1, 1);

        PerfGroups_List = new QListWidget(PerfGroup_Tab);
        PerfGroups_List->setObjectName(QStringLiteral("PerfGroups_List"));

        gridLayout_5->addWidget(PerfGroups_List, 1, 0, 1, 1);

        ChosenPerfGroups_List = new QListWidget(PerfGroup_Tab);
        ChosenPerfGroups_List->setObjectName(QStringLiteral("ChosenPerfGroups_List"));

        gridLayout_5->addWidget(ChosenPerfGroups_List, 1, 1, 1, 1);

        tabWidget->addTab(PerfGroup_Tab, QString());
        PerfMetric_Tab = new QWidget();
        PerfMetric_Tab->setObjectName(QStringLiteral("PerfMetric_Tab"));
        gridLayout = new QGridLayout(PerfMetric_Tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        PerfMetrics_Label = new QLabel(PerfMetric_Tab);
        PerfMetrics_Label->setObjectName(QStringLiteral("PerfMetrics_Label"));

        gridLayout->addWidget(PerfMetrics_Label, 0, 0, 1, 1);

        ChosenPerfMetrics_Label = new QLabel(PerfMetric_Tab);
        ChosenPerfMetrics_Label->setObjectName(QStringLiteral("ChosenPerfMetrics_Label"));

        gridLayout->addWidget(ChosenPerfMetrics_Label, 0, 1, 1, 1);

        ChosenPerfCoutners_Label = new QLabel(PerfMetric_Tab);
        ChosenPerfCoutners_Label->setObjectName(QStringLiteral("ChosenPerfCoutners_Label"));

        gridLayout->addWidget(ChosenPerfCoutners_Label, 0, 2, 1, 1);

        PerfMetrics_List = new QListWidget(PerfMetric_Tab);
        PerfMetrics_List->setObjectName(QStringLiteral("PerfMetrics_List"));

        gridLayout->addWidget(PerfMetrics_List, 1, 0, 1, 1);

        ChosenPerfMetrics_List = new QListWidget(PerfMetric_Tab);
        ChosenPerfMetrics_List->setObjectName(QStringLiteral("ChosenPerfMetrics_List"));

        gridLayout->addWidget(ChosenPerfMetrics_List, 1, 1, 3, 1);

        ChosenPerfCounters_List = new QListWidget(PerfMetric_Tab);
        ChosenPerfCounters_List->setObjectName(QStringLiteral("ChosenPerfCounters_List"));

        gridLayout->addWidget(ChosenPerfCounters_List, 1, 2, 3, 1);

        PerfCounters_Label = new QLabel(PerfMetric_Tab);
        PerfCounters_Label->setObjectName(QStringLiteral("PerfCounters_Label"));

        gridLayout->addWidget(PerfCounters_Label, 2, 0, 1, 1);

        PerfCounters_List = new QListWidget(PerfMetric_Tab);
        PerfCounters_List->setObjectName(QStringLiteral("PerfCounters_List"));

        gridLayout->addWidget(PerfCounters_List, 3, 0, 1, 1);

        tabWidget->addTab(PerfMetric_Tab, QString());
        CPIStack_Tab = new QWidget();
        CPIStack_Tab->setObjectName(QStringLiteral("CPIStack_Tab"));
        gridLayout_6 = new QGridLayout(CPIStack_Tab);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        CPI_Stack_GraphicsView = new CustomView(CPIStack_Tab);
        CPI_Stack_GraphicsView->setObjectName(QStringLiteral("CPI_Stack_GraphicsView"));

        gridLayout_6->addWidget(CPI_Stack_GraphicsView, 0, 0, 1, 1);

        tabWidget->addTab(CPIStack_Tab, QString());
        ApplicationOutput_Tab = new QWidget();
        ApplicationOutput_Tab->setObjectName(QStringLiteral("ApplicationOutput_Tab"));
        gridLayout_7 = new QGridLayout(ApplicationOutput_Tab);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        ApplicationOutput_Text = new QTextBrowser(ApplicationOutput_Tab);
        ApplicationOutput_Text->setObjectName(QStringLiteral("ApplicationOutput_Text"));

        gridLayout_7->addWidget(ApplicationOutput_Text, 0, 0, 1, 1);

        tabWidget->addTab(ApplicationOutput_Tab, QString());

        gridLayout_8->addWidget(tabWidget, 1, 0, 1, 3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1082, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Logo_Group->setTitle(QString());
        Logo->setText(QString());
        Stethoscope_Group->setTitle(QString());
        StethoscopeMode_pushButton->setText(QApplication::translate("MainWindow", "Stethoscope Mode", Q_NULLPTR));
        RefreshRate_Label->setText(QApplication::translate("MainWindow", "Refresh Rate (ms)", Q_NULLPTR));
        RefreshRate_Text->setPlaceholderText(QString());
        Application_Group->setTitle(QString());
        Application_Label->setText(QApplication::translate("MainWindow", "Application Under Test", Q_NULLPTR));
        ApplicationLoad_pushButton->setText(QApplication::translate("MainWindow", "Load", Q_NULLPTR));
        CommandLineArgs_Label->setText(QApplication::translate("MainWindow", "Command Line Arguments", Q_NULLPTR));
        RunTest_pushButton->setText(QApplication::translate("MainWindow", "Run Test", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Topology_Tab), QApplication::translate("MainWindow", "Architecture Topology", Q_NULLPTR));
        Application_Label_2->setText(QApplication::translate("MainWindow", "Performance Groups", Q_NULLPTR));
        Application_Label_3->setText(QApplication::translate("MainWindow", "Chosen Performance Groups", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(PerfGroup_Tab), QApplication::translate("MainWindow", "Performance Group Selection", Q_NULLPTR));
        PerfMetrics_Label->setText(QApplication::translate("MainWindow", "Performance Metrics", Q_NULLPTR));
        ChosenPerfMetrics_Label->setText(QApplication::translate("MainWindow", "Chosen Performance Metrics", Q_NULLPTR));
        ChosenPerfCoutners_Label->setText(QApplication::translate("MainWindow", "Chosen Performance Counters", Q_NULLPTR));
        PerfCounters_Label->setText(QApplication::translate("MainWindow", "Performance Counters", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(PerfMetric_Tab), QApplication::translate("MainWindow", "Performance Metric Selection", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(CPIStack_Tab), QApplication::translate("MainWindow", "CPI Stack", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(ApplicationOutput_Tab), QApplication::translate("MainWindow", "Application Output", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
