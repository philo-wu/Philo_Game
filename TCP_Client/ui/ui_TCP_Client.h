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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCP_ClientClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QMainWindow *TCP_ClientClass)
    {
        if (TCP_ClientClass->objectName().isEmpty())
            TCP_ClientClass->setObjectName(QString::fromUtf8("TCP_ClientClass"));
        TCP_ClientClass->resize(614, 404);
        centralWidget = new QWidget(TCP_ClientClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        TCP_ClientClass->setCentralWidget(centralWidget);

        retranslateUi(TCP_ClientClass);

        QMetaObject::connectSlotsByName(TCP_ClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *TCP_ClientClass)
    {
        TCP_ClientClass->setWindowTitle(QCoreApplication::translate("TCP_ClientClass", "TCP_Client", nullptr));
        pushButton->setText(QCoreApplication::translate("TCP_ClientClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TCP_ClientClass: public Ui_TCP_ClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCP_CLIENT_H
