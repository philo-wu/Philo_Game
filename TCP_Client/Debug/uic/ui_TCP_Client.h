/********************************************************************************
** Form generated from reading UI file 'TCP_Client.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCP_CLIENT_H
#define UI_TCP_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCP_ClientClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TCP_ClientClass)
    {
        if (TCP_ClientClass->objectName().isEmpty())
            TCP_ClientClass->setObjectName(QString::fromUtf8("TCP_ClientClass"));
        TCP_ClientClass->resize(600, 400);
        menuBar = new QMenuBar(TCP_ClientClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        TCP_ClientClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TCP_ClientClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TCP_ClientClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TCP_ClientClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TCP_ClientClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TCP_ClientClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TCP_ClientClass->setStatusBar(statusBar);

        retranslateUi(TCP_ClientClass);

        QMetaObject::connectSlotsByName(TCP_ClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *TCP_ClientClass)
    {
        TCP_ClientClass->setWindowTitle(QCoreApplication::translate("TCP_ClientClass", "TCP_Client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TCP_ClientClass: public Ui_TCP_ClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCP_CLIENT_H
