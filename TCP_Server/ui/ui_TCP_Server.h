/********************************************************************************
** Form generated from reading UI file 'TCP_Server.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCP_SERVER_H
#define UI_TCP_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCP_ServerClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QLineEdit *LE_Servar_Name;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_7;
    QLineEdit *LE_Servar_IP;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_10;
    QLineEdit *LE_Servar_UserTotal;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_9;
    QLineEdit *LE_Servar_Port;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QLineEdit *LE_Servar_State;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *LE_Servar_Sec;
    QSpacerItem *horizontalSpacer_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget_log;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget_User;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Btn_Start;
    QPushButton *Btn_Pause;
    QPushButton *pushButton_4;
    QPushButton *pushButton;

    void setupUi(QMainWindow *TCP_ServerClass)
    {
        if (TCP_ServerClass->objectName().isEmpty())
            TCP_ServerClass->setObjectName(QString::fromUtf8("TCP_ServerClass"));
        TCP_ServerClass->resize(600, 400);
        centralWidget = new QWidget(TCP_ServerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(55, 0));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_8);

        LE_Servar_Name = new QLineEdit(centralWidget);
        LE_Servar_Name->setObjectName(QString::fromUtf8("LE_Servar_Name"));
        LE_Servar_Name->setFocusPolicy(Qt::ClickFocus);
        LE_Servar_Name->setStyleSheet(QString::fromUtf8("background-color: rgb(255,255,255);\n"
"color: rgb(0, 0, 0);"));
        LE_Servar_Name->setMaxLength(18);
        LE_Servar_Name->setReadOnly(false);

        horizontalLayout_10->addWidget(LE_Servar_Name);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(66, 0));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_7);

        LE_Servar_IP = new QLineEdit(centralWidget);
        LE_Servar_IP->setObjectName(QString::fromUtf8("LE_Servar_IP"));
        LE_Servar_IP->setFocusPolicy(Qt::NoFocus);
        LE_Servar_IP->setStyleSheet(QString::fromUtf8("background-color: rgb(200,200,200);\n"
"color: rgb(0, 0, 0);"));
        LE_Servar_IP->setReadOnly(true);

        horizontalLayout_9->addWidget(LE_Servar_IP);


        verticalLayout_4->addLayout(horizontalLayout_9);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(66, 0));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(label_10);

        LE_Servar_UserTotal = new QLineEdit(centralWidget);
        LE_Servar_UserTotal->setObjectName(QString::fromUtf8("LE_Servar_UserTotal"));
        LE_Servar_UserTotal->setMaximumSize(QSize(66, 16777215));
        LE_Servar_UserTotal->setFocusPolicy(Qt::NoFocus);
        LE_Servar_UserTotal->setStyleSheet(QString::fromUtf8("background-color: rgb(200,200,200);\n"
"color: rgb(0, 0, 0);"));
        LE_Servar_UserTotal->setReadOnly(true);

        horizontalLayout_12->addWidget(LE_Servar_UserTotal);


        verticalLayout_3->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(66, 0));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_9);

        LE_Servar_Port = new QLineEdit(centralWidget);
        LE_Servar_Port->setObjectName(QString::fromUtf8("LE_Servar_Port"));
        LE_Servar_Port->setMaximumSize(QSize(66, 16777215));
        LE_Servar_Port->setFocusPolicy(Qt::ClickFocus);
        LE_Servar_Port->setStyleSheet(QString::fromUtf8("background-color: rgb(255,255,255);\n"
"color: rgb(0, 0, 0);"));
        LE_Servar_Port->setMaxLength(5);
        LE_Servar_Port->setReadOnly(false);

        horizontalLayout_11->addWidget(LE_Servar_Port);


        verticalLayout_3->addLayout(horizontalLayout_11);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(66, 0));
        label_6->setMaximumSize(QSize(66, 16777215));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_6);

        LE_Servar_State = new QLineEdit(centralWidget);
        LE_Servar_State->setObjectName(QString::fromUtf8("LE_Servar_State"));
        LE_Servar_State->setMaximumSize(QSize(66, 16777215));
        LE_Servar_State->setFocusPolicy(Qt::NoFocus);
        LE_Servar_State->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 17, 17);\n"
"color: rgb(0, 0, 0);"));
        LE_Servar_State->setReadOnly(true);

        horizontalLayout_8->addWidget(LE_Servar_State);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        LE_Servar_Sec = new QLineEdit(centralWidget);
        LE_Servar_Sec->setObjectName(QString::fromUtf8("LE_Servar_Sec"));
        LE_Servar_Sec->setMinimumSize(QSize(0, 0));
        LE_Servar_Sec->setMaximumSize(QSize(66, 16777215));
        LE_Servar_Sec->setFocusPolicy(Qt::NoFocus);
        LE_Servar_Sec->setStyleSheet(QString::fromUtf8("background-color: rgb(200,200,200);\n"
"color: rgb(0, 0, 0);"));
        LE_Servar_Sec->setReadOnly(true);

        horizontalLayout_3->addWidget(LE_Servar_Sec);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget_log = new QTableWidget(tab);
        if (tableWidget_log->columnCount() < 2)
            tableWidget_log->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_log->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_log->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget_log->rowCount() < 1)
            tableWidget_log->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_log->setVerticalHeaderItem(0, __qtablewidgetitem2);
        tableWidget_log->setObjectName(QString::fromUtf8("tableWidget_log"));
        tableWidget_log->horizontalHeader()->setVisible(false);
        tableWidget_log->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidget_log, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tableWidget_User = new QTableWidget(tab_2);
        if (tableWidget_User->columnCount() < 5)
            tableWidget_User->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_User->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_User->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_User->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_User->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_User->setHorizontalHeaderItem(4, __qtablewidgetitem7);
        if (tableWidget_User->rowCount() < 4)
            tableWidget_User->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_User->setVerticalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_User->setVerticalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_User->setVerticalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_User->setVerticalHeaderItem(3, __qtablewidgetitem11);
        tableWidget_User->setObjectName(QString::fromUtf8("tableWidget_User"));
        tableWidget_User->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_User->horizontalHeader()->setDefaultSectionSize(118);
        tableWidget_User->horizontalHeader()->setHighlightSections(false);
        tableWidget_User->verticalHeader()->setVisible(false);

        gridLayout_2->addWidget(tableWidget_User, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Btn_Start = new QPushButton(centralWidget);
        Btn_Start->setObjectName(QString::fromUtf8("Btn_Start"));

        horizontalLayout_2->addWidget(Btn_Start);

        Btn_Pause = new QPushButton(centralWidget);
        Btn_Pause->setObjectName(QString::fromUtf8("Btn_Pause"));
        Btn_Pause->setEnabled(false);

        horizontalLayout_2->addWidget(Btn_Pause);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        TCP_ServerClass->setCentralWidget(centralWidget);

        retranslateUi(TCP_ServerClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TCP_ServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *TCP_ServerClass)
    {
        TCP_ServerClass->setWindowTitle(QCoreApplication::translate("TCP_ServerClass", "TCP_Server", nullptr));
        label_8->setText(QCoreApplication::translate("TCP_ServerClass", "\344\274\272\346\234\215\345\231\250\345\220\215\347\250\261 :", nullptr));
        label_7->setText(QCoreApplication::translate("TCP_ServerClass", "\344\274\272\346\234\215\345\231\250 IP :", nullptr));
        LE_Servar_IP->setText(QString());
        label_10->setText(QCoreApplication::translate("TCP_ServerClass", "\347\267\232\344\270\212\344\272\272\346\225\270 :", nullptr));
        label_9->setText(QCoreApplication::translate("TCP_ServerClass", "\344\274\272\346\234\215\345\231\250\347\253\257\345\217\243 :", nullptr));
        label_6->setText(QCoreApplication::translate("TCP_ServerClass", "\344\274\272\346\234\215\345\231\250\347\213\200\346\205\213 :", nullptr));
        LE_Servar_State->setText(QCoreApplication::translate("TCP_ServerClass", "\346\234\252\345\225\237\345\213\225", nullptr));
        label->setText(QCoreApplication::translate("TCP_ServerClass", "\345\225\237\345\213\225\346\231\202\351\225\267 : ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_log->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TCP_ServerClass", "time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_log->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TCP_ServerClass", "data", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_log->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TCP_ServerClass", "\346\226\260\345\242\236\345\210\227", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("TCP_ServerClass", "\344\274\272\346\234\215\345\231\250\347\213\200\346\263\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_User->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TCP_ServerClass", "\347\224\250\346\210\266\345\220\215\347\250\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_User->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("TCP_ServerClass", "\347\225\266\345\211\215IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_User->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("TCP_ServerClass", "\347\253\257\345\217\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_User->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("TCP_ServerClass", "\347\231\273\351\231\270\346\231\202\351\226\223", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_User->horizontalHeaderItem(4);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("TCP_ServerClass", "\347\231\273\351\231\270\346\231\202\351\225\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_User->verticalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("TCP_ServerClass", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_User->verticalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("TCP_ServerClass", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_User->verticalHeaderItem(2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("TCP_ServerClass", "\346\226\260\345\242\236\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_User->verticalHeaderItem(3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("TCP_ServerClass", "\346\226\260\345\242\236\345\210\227", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("TCP_ServerClass", "\347\224\250\346\210\266\346\270\205\345\226\256", nullptr));
        Btn_Start->setText(QCoreApplication::translate("TCP_ServerClass", "\345\225\237\345\213\225\344\274\272\346\234\215\345\231\250", nullptr));
        Btn_Pause->setText(QCoreApplication::translate("TCP_ServerClass", "\344\274\272\346\234\215\345\231\250\346\232\253\345\201\234", nullptr));
        pushButton_4->setText(QCoreApplication::translate("TCP_ServerClass", "PushButton", nullptr));
        pushButton->setText(QCoreApplication::translate("TCP_ServerClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TCP_ServerClass: public Ui_TCP_ServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCP_SERVER_H
