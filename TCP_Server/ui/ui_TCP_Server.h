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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCP_ServerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TCP_ServerClass)
    {
        if (TCP_ServerClass->objectName().isEmpty())
            TCP_ServerClass->setObjectName(QString::fromUtf8("TCP_ServerClass"));
        TCP_ServerClass->resize(600, 400);
        menuBar = new QMenuBar(TCP_ServerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        TCP_ServerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TCP_ServerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TCP_ServerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TCP_ServerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TCP_ServerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TCP_ServerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TCP_ServerClass->setStatusBar(statusBar);

        retranslateUi(TCP_ServerClass);

        QMetaObject::connectSlotsByName(TCP_ServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *TCP_ServerClass)
    {
        TCP_ServerClass->setWindowTitle(QCoreApplication::translate("TCP_ServerClass", "TCP_Server", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TCP_ServerClass: public Ui_TCP_ServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCP_SERVER_H
