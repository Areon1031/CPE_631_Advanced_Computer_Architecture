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
#include <QtWidgets/QCheckBox>
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
    QGridLayout *gridLayout_9;
    QGroupBox *Logo_Group;
    QGridLayout *gridLayout_3;
    QLabel *Logo;
    QGroupBox *Perfscope_Group;
    QGridLayout *gridLayout_8;
    QPushButton *Perfscope_pushButton;
    QTextEdit *ExecuteCore_Text;
    QLabel *ExecuteCore_Label;
    QGroupBox *Application_Group;
    QGridLayout *gridLayout_2;
    QLabel *Application_Label;
    QTextEdit *Application_Text;
    QPushButton *ApplicationLoad_pushButton;
    QLabel *CommandLineArgs_Label;
    QTextEdit *CommandLineArgs_Text;
    QPushButton *RunTest_pushButton;
    QLabel *LikwidCommand_Label;
    QTextEdit *LikwidCommand_Text;
    QTabWidget *tabWidget;
    QWidget *Topology_Tab;
    QGridLayout *gridLayout_4;
    QTextBrowser *Topology_Text;
    QWidget *Breakdown_Tab;
    QGridLayout *gridLayout_13;
    CustomView *BreakdownChart_GraphicsView;
    QGroupBox *Breakdown_Group;
    QGridLayout *gridLayout_12;
    QCheckBox *PerfBranches_checkBox;
    QCheckBox *PerfCache_checkBox;
    QCheckBox *PerfMemory_checkBox;
    QPushButton *Breakdown_pushButton;
    QTextBrowser *BreakdownOutput_Text;
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
    QWidget *Features_Tab;
    QGridLayout *gridLayout_11;
    QTextBrowser *FeatureOperations_Text;
    QListWidget *Features_List;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_10;
    QPushButton *FeatureEnable_pushButton;
    QPushButton *FeatureDisable_pushButton;
    QLabel *FeaturesList_Label;
    QLabel *ChosenPerfCoutners_Label_2;
    QWidget *CPIStack_Tab;
    QGridLayout *gridLayout_6;
    CustomView *CPI_Stack_GraphicsView;
    QWidget *ApplicationOutput_Tab;
    QGridLayout *gridLayout_7;
    QTextBrowser *ApplicationOutput_Text;
    QLabel *OutDirectory_Label;
    QTextEdit *OutDirectory_Text;
    QPushButton *OutDirectory_pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1094, 739);
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
        gridLayout_9 = new QGridLayout(centralWidget);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        Logo_Group = new QGroupBox(centralWidget);
        Logo_Group->setObjectName(QStringLiteral("Logo_Group"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
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


        gridLayout_9->addWidget(Logo_Group, 0, 0, 1, 2);

        Perfscope_Group = new QGroupBox(centralWidget);
        Perfscope_Group->setObjectName(QStringLiteral("Perfscope_Group"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Perfscope_Group->sizePolicy().hasHeightForWidth());
        Perfscope_Group->setSizePolicy(sizePolicy3);
        Perfscope_Group->setMinimumSize(QSize(191, 50));
        gridLayout_8 = new QGridLayout(Perfscope_Group);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        Perfscope_pushButton = new QPushButton(Perfscope_Group);
        Perfscope_pushButton->setObjectName(QStringLiteral("Perfscope_pushButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(Perfscope_pushButton->sizePolicy().hasHeightForWidth());
        Perfscope_pushButton->setSizePolicy(sizePolicy4);
        Perfscope_pushButton->setMaximumSize(QSize(175, 30));

        gridLayout_8->addWidget(Perfscope_pushButton, 2, 0, 1, 1);

        ExecuteCore_Text = new QTextEdit(Perfscope_Group);
        ExecuteCore_Text->setObjectName(QStringLiteral("ExecuteCore_Text"));
        sizePolicy2.setHeightForWidth(ExecuteCore_Text->sizePolicy().hasHeightForWidth());
        ExecuteCore_Text->setSizePolicy(sizePolicy2);
        ExecuteCore_Text->setMinimumSize(QSize(171, 31));
        ExecuteCore_Text->setMaximumSize(QSize(171, 31));
        ExecuteCore_Text->setLayoutDirection(Qt::LeftToRight);
        ExecuteCore_Text->setLineWrapMode(QTextEdit::NoWrap);
        ExecuteCore_Text->setLineWrapColumnOrWidth(0);
        ExecuteCore_Text->setReadOnly(false);

        gridLayout_8->addWidget(ExecuteCore_Text, 1, 0, 1, 1);

        ExecuteCore_Label = new QLabel(Perfscope_Group);
        ExecuteCore_Label->setObjectName(QStringLiteral("ExecuteCore_Label"));
        sizePolicy2.setHeightForWidth(ExecuteCore_Label->sizePolicy().hasHeightForWidth());
        ExecuteCore_Label->setSizePolicy(sizePolicy2);
        ExecuteCore_Label->setMinimumSize(QSize(161, 17));
        ExecuteCore_Label->setMaximumSize(QSize(161, 17));

        gridLayout_8->addWidget(ExecuteCore_Label, 0, 0, 1, 1);


        gridLayout_9->addWidget(Perfscope_Group, 0, 2, 1, 1);

        Application_Group = new QGroupBox(centralWidget);
        Application_Group->setObjectName(QStringLiteral("Application_Group"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(Application_Group->sizePolicy().hasHeightForWidth());
        Application_Group->setSizePolicy(sizePolicy5);
        gridLayout_2 = new QGridLayout(Application_Group);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        Application_Label = new QLabel(Application_Group);
        Application_Label->setObjectName(QStringLiteral("Application_Label"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(Application_Label->sizePolicy().hasHeightForWidth());
        Application_Label->setSizePolicy(sizePolicy6);
        Application_Label->setMaximumSize(QSize(1666666, 17));

        gridLayout_2->addWidget(Application_Label, 0, 0, 1, 1);

        Application_Text = new QTextEdit(Application_Group);
        Application_Text->setObjectName(QStringLiteral("Application_Text"));
        sizePolicy6.setHeightForWidth(Application_Text->sizePolicy().hasHeightForWidth());
        Application_Text->setSizePolicy(sizePolicy6);
        Application_Text->setMinimumSize(QSize(256, 31));
        Application_Text->setMaximumSize(QSize(166666, 31));
        Application_Text->setLineWrapMode(QTextEdit::NoWrap);
        Application_Text->setLineWrapColumnOrWidth(0);
        Application_Text->setReadOnly(true);

        gridLayout_2->addWidget(Application_Text, 1, 0, 1, 1);

        ApplicationLoad_pushButton = new QPushButton(Application_Group);
        ApplicationLoad_pushButton->setObjectName(QStringLiteral("ApplicationLoad_pushButton"));
        sizePolicy6.setHeightForWidth(ApplicationLoad_pushButton->sizePolicy().hasHeightForWidth());
        ApplicationLoad_pushButton->setSizePolicy(sizePolicy6);
        ApplicationLoad_pushButton->setMaximumSize(QSize(100, 30));

        gridLayout_2->addWidget(ApplicationLoad_pushButton, 1, 1, 1, 1);

        CommandLineArgs_Label = new QLabel(Application_Group);
        CommandLineArgs_Label->setObjectName(QStringLiteral("CommandLineArgs_Label"));
        sizePolicy6.setHeightForWidth(CommandLineArgs_Label->sizePolicy().hasHeightForWidth());
        CommandLineArgs_Label->setSizePolicy(sizePolicy6);
        CommandLineArgs_Label->setMaximumSize(QSize(1666666, 17));

        gridLayout_2->addWidget(CommandLineArgs_Label, 2, 0, 1, 1);

        CommandLineArgs_Text = new QTextEdit(Application_Group);
        CommandLineArgs_Text->setObjectName(QStringLiteral("CommandLineArgs_Text"));
        sizePolicy6.setHeightForWidth(CommandLineArgs_Text->sizePolicy().hasHeightForWidth());
        CommandLineArgs_Text->setSizePolicy(sizePolicy6);
        CommandLineArgs_Text->setMinimumSize(QSize(256, 31));
        CommandLineArgs_Text->setMaximumSize(QSize(166666, 31));
        CommandLineArgs_Text->setLineWrapMode(QTextEdit::NoWrap);
        CommandLineArgs_Text->setReadOnly(false);
        CommandLineArgs_Text->setAcceptRichText(true);

        gridLayout_2->addWidget(CommandLineArgs_Text, 3, 0, 1, 1);

        RunTest_pushButton = new QPushButton(Application_Group);
        RunTest_pushButton->setObjectName(QStringLiteral("RunTest_pushButton"));
        sizePolicy6.setHeightForWidth(RunTest_pushButton->sizePolicy().hasHeightForWidth());
        RunTest_pushButton->setSizePolicy(sizePolicy6);
        RunTest_pushButton->setMaximumSize(QSize(100, 30));
        QIcon icon;
        icon.addFile(QStringLiteral("../programBin/Logo/QuickPerformance.ico"), QSize(), QIcon::Normal, QIcon::Off);
        RunTest_pushButton->setIcon(icon);
        RunTest_pushButton->setIconSize(QSize(16, 16));

        gridLayout_2->addWidget(RunTest_pushButton, 3, 1, 1, 1);


        gridLayout_9->addWidget(Application_Group, 0, 3, 1, 2);

        LikwidCommand_Label = new QLabel(centralWidget);
        LikwidCommand_Label->setObjectName(QStringLiteral("LikwidCommand_Label"));
        sizePolicy2.setHeightForWidth(LikwidCommand_Label->sizePolicy().hasHeightForWidth());
        LikwidCommand_Label->setSizePolicy(sizePolicy2);
        LikwidCommand_Label->setMaximumSize(QSize(161, 17));
        LikwidCommand_Label->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(LikwidCommand_Label, 1, 0, 1, 1);

        LikwidCommand_Text = new QTextEdit(centralWidget);
        LikwidCommand_Text->setObjectName(QStringLiteral("LikwidCommand_Text"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(LikwidCommand_Text->sizePolicy().hasHeightForWidth());
        LikwidCommand_Text->setSizePolicy(sizePolicy7);
        LikwidCommand_Text->setMaximumSize(QSize(16777215, 31));
        LikwidCommand_Text->setLineWrapMode(QTextEdit::NoWrap);
        LikwidCommand_Text->setReadOnly(true);
        LikwidCommand_Text->setAcceptRichText(true);

        gridLayout_9->addWidget(LikwidCommand_Text, 1, 1, 1, 4);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy8(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy8.setHorizontalStretch(1);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy8);
        Topology_Tab = new QWidget();
        Topology_Tab->setObjectName(QStringLiteral("Topology_Tab"));
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(Topology_Tab->sizePolicy().hasHeightForWidth());
        Topology_Tab->setSizePolicy(sizePolicy9);
        gridLayout_4 = new QGridLayout(Topology_Tab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        Topology_Text = new QTextBrowser(Topology_Tab);
        Topology_Text->setObjectName(QStringLiteral("Topology_Text"));

        gridLayout_4->addWidget(Topology_Text, 0, 0, 1, 1);

        tabWidget->addTab(Topology_Tab, QString());
        Breakdown_Tab = new QWidget();
        Breakdown_Tab->setObjectName(QStringLiteral("Breakdown_Tab"));
        gridLayout_13 = new QGridLayout(Breakdown_Tab);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        BreakdownChart_GraphicsView = new CustomView(Breakdown_Tab);
        BreakdownChart_GraphicsView->setObjectName(QStringLiteral("BreakdownChart_GraphicsView"));
        BreakdownChart_GraphicsView->setMinimumSize(QSize(651, 361));

        gridLayout_13->addWidget(BreakdownChart_GraphicsView, 0, 0, 2, 1);

        Breakdown_Group = new QGroupBox(Breakdown_Tab);
        Breakdown_Group->setObjectName(QStringLiteral("Breakdown_Group"));
        QSizePolicy sizePolicy10(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(Breakdown_Group->sizePolicy().hasHeightForWidth());
        Breakdown_Group->setSizePolicy(sizePolicy10);
        Breakdown_Group->setMinimumSize(QSize(191, 50));
        gridLayout_12 = new QGridLayout(Breakdown_Group);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        PerfBranches_checkBox = new QCheckBox(Breakdown_Group);
        PerfBranches_checkBox->setObjectName(QStringLiteral("PerfBranches_checkBox"));
        PerfBranches_checkBox->setChecked(true);

        gridLayout_12->addWidget(PerfBranches_checkBox, 0, 0, 1, 1);

        PerfCache_checkBox = new QCheckBox(Breakdown_Group);
        PerfCache_checkBox->setObjectName(QStringLiteral("PerfCache_checkBox"));
        PerfCache_checkBox->setChecked(true);

        gridLayout_12->addWidget(PerfCache_checkBox, 0, 1, 1, 1);

        PerfMemory_checkBox = new QCheckBox(Breakdown_Group);
        PerfMemory_checkBox->setObjectName(QStringLiteral("PerfMemory_checkBox"));

        gridLayout_12->addWidget(PerfMemory_checkBox, 0, 2, 1, 1);

        Breakdown_pushButton = new QPushButton(Breakdown_Group);
        Breakdown_pushButton->setObjectName(QStringLiteral("Breakdown_pushButton"));
        sizePolicy10.setHeightForWidth(Breakdown_pushButton->sizePolicy().hasHeightForWidth());
        Breakdown_pushButton->setSizePolicy(sizePolicy10);
        Breakdown_pushButton->setMaximumSize(QSize(375, 30));

        gridLayout_12->addWidget(Breakdown_pushButton, 1, 0, 1, 3);


        gridLayout_13->addWidget(Breakdown_Group, 0, 1, 1, 1);

        BreakdownOutput_Text = new QTextBrowser(Breakdown_Tab);
        BreakdownOutput_Text->setObjectName(QStringLiteral("BreakdownOutput_Text"));
        QSizePolicy sizePolicy11(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(BreakdownOutput_Text->sizePolicy().hasHeightForWidth());
        BreakdownOutput_Text->setSizePolicy(sizePolicy11);
        BreakdownOutput_Text->setMinimumSize(QSize(391, 200));

        gridLayout_13->addWidget(BreakdownOutput_Text, 1, 1, 1, 1);

        tabWidget->addTab(Breakdown_Tab, QString());
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
        Features_Tab = new QWidget();
        Features_Tab->setObjectName(QStringLiteral("Features_Tab"));
        gridLayout_11 = new QGridLayout(Features_Tab);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        FeatureOperations_Text = new QTextBrowser(Features_Tab);
        FeatureOperations_Text->setObjectName(QStringLiteral("FeatureOperations_Text"));
        QSizePolicy sizePolicy12(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy12.setHorizontalStretch(1);
        sizePolicy12.setVerticalStretch(1);
        sizePolicy12.setHeightForWidth(FeatureOperations_Text->sizePolicy().hasHeightForWidth());
        FeatureOperations_Text->setSizePolicy(sizePolicy12);

        gridLayout_11->addWidget(FeatureOperations_Text, 1, 2, 1, 1);

        Features_List = new QListWidget(Features_Tab);
        Features_List->setObjectName(QStringLiteral("Features_List"));
        sizePolicy12.setHeightForWidth(Features_List->sizePolicy().hasHeightForWidth());
        Features_List->setSizePolicy(sizePolicy12);

        gridLayout_11->addWidget(Features_List, 1, 0, 1, 1);

        groupBox = new QGroupBox(Features_Tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy9.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy9);
        gridLayout_10 = new QGridLayout(groupBox);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        FeatureEnable_pushButton = new QPushButton(groupBox);
        FeatureEnable_pushButton->setObjectName(QStringLiteral("FeatureEnable_pushButton"));
        sizePolicy2.setHeightForWidth(FeatureEnable_pushButton->sizePolicy().hasHeightForWidth());
        FeatureEnable_pushButton->setSizePolicy(sizePolicy2);
        FeatureEnable_pushButton->setMaximumSize(QSize(120, 30));

        gridLayout_10->addWidget(FeatureEnable_pushButton, 0, 0, 1, 1);

        FeatureDisable_pushButton = new QPushButton(groupBox);
        FeatureDisable_pushButton->setObjectName(QStringLiteral("FeatureDisable_pushButton"));
        sizePolicy2.setHeightForWidth(FeatureDisable_pushButton->sizePolicy().hasHeightForWidth());
        FeatureDisable_pushButton->setSizePolicy(sizePolicy2);
        FeatureDisable_pushButton->setMaximumSize(QSize(120, 30));

        gridLayout_10->addWidget(FeatureDisable_pushButton, 1, 0, 1, 1);


        gridLayout_11->addWidget(groupBox, 0, 1, 2, 1);

        FeaturesList_Label = new QLabel(Features_Tab);
        FeaturesList_Label->setObjectName(QStringLiteral("FeaturesList_Label"));
        QSizePolicy sizePolicy13(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy13.setHorizontalStretch(0);
        sizePolicy13.setVerticalStretch(0);
        sizePolicy13.setHeightForWidth(FeaturesList_Label->sizePolicy().hasHeightForWidth());
        FeaturesList_Label->setSizePolicy(sizePolicy13);
        FeaturesList_Label->setMinimumSize(QSize(343, 17));
        FeaturesList_Label->setMaximumSize(QSize(343, 17));

        gridLayout_11->addWidget(FeaturesList_Label, 0, 0, 1, 1);

        ChosenPerfCoutners_Label_2 = new QLabel(Features_Tab);
        ChosenPerfCoutners_Label_2->setObjectName(QStringLiteral("ChosenPerfCoutners_Label_2"));
        sizePolicy13.setHeightForWidth(ChosenPerfCoutners_Label_2->sizePolicy().hasHeightForWidth());
        ChosenPerfCoutners_Label_2->setSizePolicy(sizePolicy13);
        ChosenPerfCoutners_Label_2->setMinimumSize(QSize(343, 17));
        ChosenPerfCoutners_Label_2->setMaximumSize(QSize(343, 17));

        gridLayout_11->addWidget(ChosenPerfCoutners_Label_2, 0, 2, 1, 1);

        tabWidget->addTab(Features_Tab, QString());
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

        gridLayout_9->addWidget(tabWidget, 2, 0, 1, 5);

        OutDirectory_Label = new QLabel(centralWidget);
        OutDirectory_Label->setObjectName(QStringLiteral("OutDirectory_Label"));
        sizePolicy2.setHeightForWidth(OutDirectory_Label->sizePolicy().hasHeightForWidth());
        OutDirectory_Label->setSizePolicy(sizePolicy2);
        OutDirectory_Label->setMaximumSize(QSize(161, 17));
        OutDirectory_Label->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(OutDirectory_Label, 3, 0, 1, 1);

        OutDirectory_Text = new QTextEdit(centralWidget);
        OutDirectory_Text->setObjectName(QStringLiteral("OutDirectory_Text"));
        sizePolicy7.setHeightForWidth(OutDirectory_Text->sizePolicy().hasHeightForWidth());
        OutDirectory_Text->setSizePolicy(sizePolicy7);
        OutDirectory_Text->setMaximumSize(QSize(16777215, 31));
        OutDirectory_Text->setLineWrapMode(QTextEdit::NoWrap);
        OutDirectory_Text->setReadOnly(false);
        OutDirectory_Text->setAcceptRichText(true);

        gridLayout_9->addWidget(OutDirectory_Text, 3, 1, 1, 3);

        OutDirectory_pushButton = new QPushButton(centralWidget);
        OutDirectory_pushButton->setObjectName(QStringLiteral("OutDirectory_pushButton"));
        sizePolicy2.setHeightForWidth(OutDirectory_pushButton->sizePolicy().hasHeightForWidth());
        OutDirectory_pushButton->setSizePolicy(sizePolicy2);
        OutDirectory_pushButton->setMaximumSize(QSize(89, 30));

        gridLayout_9->addWidget(OutDirectory_pushButton, 3, 4, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1094, 22));
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

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Logo_Group->setTitle(QString());
        Logo->setText(QString());
        Perfscope_Group->setTitle(QString());
        Perfscope_pushButton->setText(QApplication::translate("MainWindow", "Start Perf Scope", Q_NULLPTR));
        ExecuteCore_Text->setPlaceholderText(QString());
        ExecuteCore_Label->setText(QApplication::translate("MainWindow", "Execute App on Core #", Q_NULLPTR));
        Application_Group->setTitle(QString());
        Application_Label->setText(QApplication::translate("MainWindow", "Application Under Test", Q_NULLPTR));
        ApplicationLoad_pushButton->setText(QApplication::translate("MainWindow", "Load", Q_NULLPTR));
        CommandLineArgs_Label->setText(QApplication::translate("MainWindow", "Command Line Arguments", Q_NULLPTR));
        RunTest_pushButton->setText(QApplication::translate("MainWindow", "Run Test", Q_NULLPTR));
        LikwidCommand_Label->setText(QApplication::translate("MainWindow", "LIKWID Command", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Topology_Tab), QApplication::translate("MainWindow", "Architecture Topology", Q_NULLPTR));
        Breakdown_Group->setTitle(QString());
        PerfBranches_checkBox->setText(QApplication::translate("MainWindow", "Branches", Q_NULLPTR));
        PerfCache_checkBox->setText(QApplication::translate("MainWindow", "Cache", Q_NULLPTR));
        PerfMemory_checkBox->setText(QApplication::translate("MainWindow", "Memory", Q_NULLPTR));
        Breakdown_pushButton->setText(QApplication::translate("MainWindow", "Create Breakdown", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Breakdown_Tab), QApplication::translate("MainWindow", "Perf First Stop", Q_NULLPTR));
        Application_Label_2->setText(QApplication::translate("MainWindow", "Performance Groups", Q_NULLPTR));
        Application_Label_3->setText(QApplication::translate("MainWindow", "Chosen Performance Groups", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(PerfGroup_Tab), QApplication::translate("MainWindow", "Performance Group Selection", Q_NULLPTR));
        PerfMetrics_Label->setText(QApplication::translate("MainWindow", "Performance Metrics", Q_NULLPTR));
        ChosenPerfMetrics_Label->setText(QApplication::translate("MainWindow", "Chosen Performance Metrics", Q_NULLPTR));
        ChosenPerfCoutners_Label->setText(QApplication::translate("MainWindow", "Chosen Performance Counters", Q_NULLPTR));
        PerfCounters_Label->setText(QApplication::translate("MainWindow", "Performance Counters", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(PerfMetric_Tab), QApplication::translate("MainWindow", "Performance Metric Selection", Q_NULLPTR));
        groupBox->setTitle(QString());
        FeatureEnable_pushButton->setText(QApplication::translate("MainWindow", "Enable", Q_NULLPTR));
        FeatureDisable_pushButton->setText(QApplication::translate("MainWindow", "Disable", Q_NULLPTR));
        FeaturesList_Label->setText(QApplication::translate("MainWindow", "Features List", Q_NULLPTR));
        ChosenPerfCoutners_Label_2->setText(QApplication::translate("MainWindow", "Operation Results", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Features_Tab), QApplication::translate("MainWindow", "Feature Control", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(CPIStack_Tab), QApplication::translate("MainWindow", "CPI Stack", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(ApplicationOutput_Tab), QApplication::translate("MainWindow", "Application Output", Q_NULLPTR));
        OutDirectory_Label->setText(QApplication::translate("MainWindow", "Output Directory", Q_NULLPTR));
        OutDirectory_pushButton->setText(QApplication::translate("MainWindow", "Select Dir", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
