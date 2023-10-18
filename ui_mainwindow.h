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
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox_istoClient;
    QCheckBox *checkBox_istoServer;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox;
    QLabel *label_out_folderPath;
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
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        checkBox_istoClient = new QCheckBox(centralwidget);
        checkBox_istoClient->setObjectName(QString::fromUtf8("checkBox_istoClient"));

        horizontalLayout_4->addWidget(checkBox_istoClient);

        checkBox_istoServer = new QCheckBox(centralwidget);
        checkBox_istoServer->setObjectName(QString::fromUtf8("checkBox_istoServer"));

        horizontalLayout_4->addWidget(checkBox_istoServer);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout_5->addWidget(checkBox_2);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_5->addWidget(checkBox);


        verticalLayout_2->addLayout(horizontalLayout_5);

        label_out_folderPath = new QLabel(centralwidget);
        label_out_folderPath->setObjectName(QString::fromUtf8("label_out_folderPath"));

        verticalLayout_2->addWidget(label_out_folderPath);


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
        if (tableWidget_show->rowCount() < 4)
            tableWidget_show->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_show->setVerticalHeaderItem(3, __qtablewidgetitem11);
        tableWidget_show->setObjectName(QString::fromUtf8("tableWidget_show"));
        tableWidget_show->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget_show->setAutoScroll(true);
        tableWidget_show->horizontalHeader()->setVisible(false);
        tableWidget_show->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget_show->horizontalHeader()->setHighlightSections(true);
        tableWidget_show->verticalHeader()->setVisible(true);

        verticalLayout_3->addWidget(tableWidget_show);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 832, 21));
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
        pushButton_select->setText(QCoreApplication::translate("MainWindow", "\351\201\270\346\223\207Excel\344\270\246\345\273\272\347\253\213Json", nullptr));
        pushButton_show->setText(QCoreApplication::translate("MainWindow", "\344\277\235\347\225\231", nullptr));
        pushButton_change->setText(QCoreApplication::translate("MainWindow", "\350\274\270\345\207\272\350\267\257\345\276\221", nullptr));
        checkBox_istoClient->setText(QCoreApplication::translate("MainWindow", "\350\274\270\345\207\272Client\347\253\257", nullptr));
        checkBox_istoServer->setText(QCoreApplication::translate("MainWindow", "\350\274\270\345\207\272Server\347\253\257", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "\344\277\235\347\225\231", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\344\277\235\347\225\231", nullptr));
        label_out_folderPath->setText(QCoreApplication::translate("MainWindow", "\350\274\270\345\207\272\350\267\257\345\276\221:\351\240\220\350\250\255\347\202\272\345\237\267\350\241\214\346\252\224\345\220\214\347\233\256\351\214\204Json\350\263\207\346\226\231\345\244\276", nullptr));
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
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "\344\270\255\346\226\207\345\220\215\347\250\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_show->verticalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "\350\213\261\346\226\207\345\220\215\347\250\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_show->verticalHeaderItem(2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "\350\263\207\346\226\231\345\236\213\345\210\245", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_show->verticalHeaderItem(3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "\351\241\257\347\244\272\347\270\256\345\257\253", nullptr));
        menuQt_Excel_to_Json->setTitle(QCoreApplication::translate("MainWindow", "Qt_Excel_to_Json", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
