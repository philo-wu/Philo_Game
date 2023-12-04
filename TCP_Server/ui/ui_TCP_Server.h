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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCP_ServerClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget_log;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget_User;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Btn_Start;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton;

    void setupUi(QMainWindow *TCP_ServerClass)
    {
        if (TCP_ServerClass->objectName().isEmpty())
            TCP_ServerClass->setObjectName(QString::fromUtf8("TCP_ServerClass"));
        TCP_ServerClass->resize(600, 400);
        centralWidget = new QWidget(TCP_ServerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
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
        tableWidget_log->setObjectName(QString::fromUtf8("tableWidget_log"));

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
        tableWidget_User->setObjectName(QString::fromUtf8("tableWidget_User"));

        gridLayout_2->addWidget(tableWidget_User, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Btn_Start = new QPushButton(centralWidget);
        Btn_Start->setObjectName(QString::fromUtf8("Btn_Start"));

        horizontalLayout_2->addWidget(Btn_Start);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        TCP_ServerClass->setCentralWidget(centralWidget);

        retranslateUi(TCP_ServerClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TCP_ServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *TCP_ServerClass)
    {
        TCP_ServerClass->setWindowTitle(QCoreApplication::translate("TCP_ServerClass", "TCP_Server", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("TCP_ServerClass", "\344\274\272\346\234\215\345\231\250\347\213\200\346\263\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("TCP_ServerClass", "\347\224\250\346\210\266\346\270\205\345\226\256", nullptr));
        Btn_Start->setText(QCoreApplication::translate("TCP_ServerClass", "\345\225\237\345\213\225\344\274\272\346\234\215\345\231\250", nullptr));
        pushButton_3->setText(QCoreApplication::translate("TCP_ServerClass", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("TCP_ServerClass", "PushButton", nullptr));
        pushButton->setText(QCoreApplication::translate("TCP_ServerClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TCP_ServerClass: public Ui_TCP_ServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCP_SERVER_H
