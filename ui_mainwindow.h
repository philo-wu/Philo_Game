/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_title;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_select;
    QPushButton *pushButton_show;
    QPushButton *pushButton_change;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox_JsontoEecel;
    QCheckBox *checkBox_ExceltoJson;
    QTableWidget *tableWidget_show;
    QMenuBar *menubar;
    QMenu *menuQt_Excel_to_Json;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(832, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_title = new QLabel(centralwidget);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        QFont font;
        font.setPointSize(20);
        label_title->setFont(font);
        label_title->setMouseTracking(false);
        label_title->setTabletTracking(false);
        label_title->setAcceptDrops(false);
        label_title->setLayoutDirection(Qt::LeftToRight);
        label_title->setAutoFillBackground(false);
        label_title->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_title);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_select = new QPushButton(centralwidget);
        pushButton_select->setObjectName(QString::fromUtf8("pushButton_select"));

        verticalLayout->addWidget(pushButton_select);

        pushButton_show = new QPushButton(centralwidget);
        pushButton_show->setObjectName(QString::fromUtf8("pushButton_show"));

        verticalLayout->addWidget(pushButton_show);

        pushButton_change = new QPushButton(centralwidget);
        pushButton_change->setObjectName(QString::fromUtf8("pushButton_change"));

        verticalLayout->addWidget(pushButton_change);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        checkBox_JsontoEecel = new QCheckBox(centralwidget);
        checkBox_JsontoEecel->setObjectName(QString::fromUtf8("checkBox_JsontoEecel"));

        verticalLayout_2->addWidget(checkBox_JsontoEecel);

        checkBox_ExceltoJson = new QCheckBox(centralwidget);
        checkBox_ExceltoJson->setObjectName(QString::fromUtf8("checkBox_ExceltoJson"));

        verticalLayout_2->addWidget(checkBox_ExceltoJson);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        tableWidget_show = new QTableWidget(centralwidget);
        if (tableWidget_show->columnCount() < 8)
            tableWidget_show->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_show->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_show->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_show->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_show->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_show->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_show->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_show->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_show->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        if (tableWidget_show->rowCount() < 12)
            tableWidget_show->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(6, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(7, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(8, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(9, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(10, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(11, __qtablewidgetitem19);
        tableWidget_show->setObjectName(QString::fromUtf8("tableWidget_show"));
        tableWidget_show->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget_show->setAutoScroll(true);
        tableWidget_show->horizontalHeader()->setVisible(true);
        tableWidget_show->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget_show->horizontalHeader()->setHighlightSections(true);
        tableWidget_show->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(tableWidget_show);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 832, 20));
        menuQt_Excel_to_Json = new QMenu(menubar);
        menuQt_Excel_to_Json->setObjectName(QString::fromUtf8("menuQt_Excel_to_Json"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuQt_Excel_to_Json->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_title->setText(QCoreApplication::translate("MainWindow", "Qt_Excel_to_Json_Philo", nullptr));
        pushButton_select->setText(QCoreApplication::translate("MainWindow", "\351\201\270\346\223\207\346\252\224\346\241\210", nullptr));
        pushButton_show->setText(QCoreApplication::translate("MainWindow", "\351\241\257\347\244\272", nullptr));
        pushButton_change->setText(QCoreApplication::translate("MainWindow", "\350\275\211\346\252\224", nullptr));
        checkBox_JsontoEecel->setText(QCoreApplication::translate("MainWindow", "Json_to_Excel (\346\234\252\345\257\246\344\275\234)", nullptr));
        checkBox_ExceltoJson->setText(QCoreApplication::translate("MainWindow", "Excel_to_Json", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_show->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\345\272\217\350\231\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_show->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\351\226\213\351\227\234\345\212\237\350\203\275", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_show->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\344\273\273\345\213\231\345\205\247\345\256\271", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_show->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\347\215\216\345\213\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_show->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\344\273\273\345\213\231\346\242\235\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_show->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\344\273\273\345\213\231\345\217\203\346\225\2701", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_show->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\344\273\273\345\213\231\345\217\203\346\225\2702", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_show->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "\344\273\273\345\213\231\345\256\214\346\210\220\346\225\270\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_show->verticalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_show->verticalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_show->verticalHeaderItem(2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_show->verticalHeaderItem(3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_show->verticalHeaderItem(4);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_show->verticalHeaderItem(5);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_show->verticalHeaderItem(6);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_show->verticalHeaderItem(7);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_show->verticalHeaderItem(8);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_show->verticalHeaderItem(9);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_show->verticalHeaderItem(10);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_show->verticalHeaderItem(11);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\210\227", nullptr));
        menuQt_Excel_to_Json->setTitle(QCoreApplication::translate("MainWindow", "Qt_Excel_to_Json", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
