/********************************************************************************
** Form generated from reading UI file 'ExcelToJson.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXCELTOJSON_H
#define UI_EXCELTOJSON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExcelToJsonClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ExcelToJsonClass)
    {
        if (ExcelToJsonClass->objectName().isEmpty())
            ExcelToJsonClass->setObjectName(QString::fromUtf8("ExcelToJsonClass"));
        ExcelToJsonClass->resize(600, 400);
        menuBar = new QMenuBar(ExcelToJsonClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ExcelToJsonClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ExcelToJsonClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ExcelToJsonClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ExcelToJsonClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ExcelToJsonClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ExcelToJsonClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ExcelToJsonClass->setStatusBar(statusBar);

        retranslateUi(ExcelToJsonClass);

        QMetaObject::connectSlotsByName(ExcelToJsonClass);
    } // setupUi

    void retranslateUi(QMainWindow *ExcelToJsonClass)
    {
        ExcelToJsonClass->setWindowTitle(QCoreApplication::translate("ExcelToJsonClass", "ExcelToJson", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExcelToJsonClass: public Ui_ExcelToJsonClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXCELTOJSON_H
