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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCP_ClientClass
{
public:
    QWidget *mainWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer;
    QPushButton *Btn_Signout;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QLineEdit *LE_Name;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLineEdit *LE_IP;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QLineEdit *LE_Port;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_3;
    QLineEdit *LE_LoginTime;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_2;
    QLineEdit *LE_LoginSec;
    QLabel *label;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_12;
    QTextBrowser *TB_Chat;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_7;
    QTableWidget *tableWidget_User;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Btn_Emoji;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *Btn_Send;

    void setupUi(QMainWindow *TCP_ClientClass)
    {
        if (TCP_ClientClass->objectName().isEmpty())
            TCP_ClientClass->setObjectName(QString::fromUtf8("TCP_ClientClass"));
        TCP_ClientClass->resize(614, 404);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(74, 74, 74, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush2(QColor(28, 25, 70, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush2);
        QBrush brush3(QColor(0, 50, 89, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush3);
        QBrush brush4(QColor(0, 27, 47, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush4);
        TCP_ClientClass->setPalette(palette);
        TCP_ClientClass->setStyleSheet(QString::fromUtf8(""));
        mainWidget = new QWidget(TCP_ClientClass);
        mainWidget->setObjectName(QString::fromUtf8("mainWidget"));
        verticalLayout_2 = new QVBoxLayout(mainWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer);

        Btn_Signout = new QPushButton(mainWidget);
        Btn_Signout->setObjectName(QString::fromUtf8("Btn_Signout"));
        Btn_Signout->setFocusPolicy(Qt::NoFocus);
        Btn_Signout->setStyleSheet(QString::fromUtf8("background-color: rgb(180, 0, 0);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_13->addWidget(Btn_Signout);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_6 = new QLabel(mainWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(55, 0));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_6);

        LE_Name = new QLineEdit(mainWidget);
        LE_Name->setObjectName(QString::fromUtf8("LE_Name"));
        LE_Name->setFocusPolicy(Qt::NoFocus);
        LE_Name->setStyleSheet(QString::fromUtf8("background-color: rgb(74, 74, 74);\n"
"color: rgb(255, 255, 255);"));
        LE_Name->setReadOnly(true);

        horizontalLayout_8->addWidget(LE_Name);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_4 = new QLabel(mainWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(55, 0));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_4);

        LE_IP = new QLineEdit(mainWidget);
        LE_IP->setObjectName(QString::fromUtf8("LE_IP"));
        LE_IP->setFocusPolicy(Qt::NoFocus);
        LE_IP->setStyleSheet(QString::fromUtf8("background-color: rgb(74, 74, 74);\n"
"color: rgb(255, 255, 255);"));
        LE_IP->setReadOnly(true);

        horizontalLayout_6->addWidget(LE_IP);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_5 = new QLabel(mainWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(55, 0));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_5);

        LE_Port = new QLineEdit(mainWidget);
        LE_Port->setObjectName(QString::fromUtf8("LE_Port"));
        LE_Port->setFocusPolicy(Qt::NoFocus);
        LE_Port->setStyleSheet(QString::fromUtf8("background-color: rgb(74, 74, 74);\n"
"color: rgb(255, 255, 255);"));
        LE_Port->setReadOnly(true);

        horizontalLayout_7->addWidget(LE_Port);


        verticalLayout_4->addLayout(horizontalLayout_7);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 1);
        verticalLayout_4->setStretch(2, 1);

        horizontalLayout_5->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_3 = new QLabel(mainWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(55, 0));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_3);

        LE_LoginTime = new QLineEdit(mainWidget);
        LE_LoginTime->setObjectName(QString::fromUtf8("LE_LoginTime"));
        LE_LoginTime->setFocusPolicy(Qt::NoFocus);
        LE_LoginTime->setStyleSheet(QString::fromUtf8("background-color: rgb(74, 74, 74);\n"
"color: rgb(255, 255, 255);"));
        LE_LoginTime->setReadOnly(true);

        horizontalLayout_11->addWidget(LE_LoginTime);


        verticalLayout_3->addLayout(horizontalLayout_11);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_2 = new QLabel(mainWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(55, 0));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_2);

        LE_LoginSec = new QLineEdit(mainWidget);
        LE_LoginSec->setObjectName(QString::fromUtf8("LE_LoginSec"));
        LE_LoginSec->setFocusPolicy(Qt::NoFocus);
        LE_LoginSec->setStyleSheet(QString::fromUtf8("background-color: rgb(74, 74, 74);\n"
"color: rgb(255, 255, 255);"));
        LE_LoginSec->setReadOnly(true);

        horizontalLayout_9->addWidget(LE_LoginSec);

        label = new QLabel(mainWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_9->addWidget(label);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_8 = new QLabel(mainWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        horizontalLayout_10->addWidget(label_8);


        verticalLayout_3->addLayout(horizontalLayout_10);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(2, 1);

        horizontalLayout_5->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        horizontalLayout_5->addLayout(verticalLayout);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 1);
        horizontalLayout_5->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(-1, -1, -1, 10);
        TB_Chat = new QTextBrowser(mainWidget);
        TB_Chat->setObjectName(QString::fromUtf8("TB_Chat"));
        QPalette palette1;
        QBrush brush5(QColor(0, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush5);
        palette1.setBrush(QPalette::Active, QPalette::HighlightedText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush);
        TB_Chat->setPalette(palette1);
        TB_Chat->setFocusPolicy(Qt::NoFocus);
        TB_Chat->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_12->addWidget(TB_Chat);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(-1, -1, -1, 0);
        label_7 = new QLabel(mainWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(10, 92, 117);\n"
"color: rgb(255, 255, 255);"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_7);

        tableWidget_User = new QTableWidget(mainWidget);
        if (tableWidget_User->columnCount() < 1)
            tableWidget_User->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_User->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget_User->setObjectName(QString::fromUtf8("tableWidget_User"));
        tableWidget_User->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_User->horizontalHeader()->setVisible(false);
        tableWidget_User->verticalHeader()->setVisible(false);

        verticalLayout_5->addWidget(tableWidget_User);


        horizontalLayout_12->addLayout(verticalLayout_5);

        horizontalLayout_12->setStretch(0, 2);

        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Btn_Emoji = new QPushButton(mainWidget);
        Btn_Emoji->setObjectName(QString::fromUtf8("Btn_Emoji"));
        Btn_Emoji->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(Btn_Emoji);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(mainWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFocusPolicy(Qt::ClickFocus);
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(74, 74, 74);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(lineEdit);

        Btn_Send = new QPushButton(mainWidget);
        Btn_Send->setObjectName(QString::fromUtf8("Btn_Send"));
        Btn_Send->setFocusPolicy(Qt::ClickFocus);
        Btn_Send->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 100, 100);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(Btn_Send);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 4);
        TCP_ClientClass->setCentralWidget(mainWidget);

        retranslateUi(TCP_ClientClass);

        QMetaObject::connectSlotsByName(TCP_ClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *TCP_ClientClass)
    {
        TCP_ClientClass->setWindowTitle(QCoreApplication::translate("TCP_ClientClass", "TCP_Client", nullptr));
        Btn_Signout->setText(QCoreApplication::translate("TCP_ClientClass", "\347\231\273\345\207\272", nullptr));
        label_6->setText(QCoreApplication::translate("TCP_ClientClass", "\347\224\250\346\210\266\345\220\215\347\250\261 :", nullptr));
        label_4->setText(QCoreApplication::translate("TCP_ClientClass", "\346\234\254\345\234\260IP :", nullptr));
        label_5->setText(QCoreApplication::translate("TCP_ClientClass", "\347\253\257\345\217\243 :", nullptr));
        label_3->setText(QCoreApplication::translate("TCP_ClientClass", "\347\231\273\345\205\245\346\231\202\351\226\223 :", nullptr));
        label_2->setText(QCoreApplication::translate("TCP_ClientClass", "\345\234\250\347\267\232\346\231\202\351\226\223 :", nullptr));
        label->setText(QCoreApplication::translate("TCP_ClientClass", "\347\247\222", nullptr));
        label_8->setText(QString());
        label_7->setText(QCoreApplication::translate("TCP_ClientClass", "\347\267\232\344\270\212\347\224\250\346\210\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_User->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TCP_ClientClass", "User", nullptr));
        Btn_Emoji->setText(QCoreApplication::translate("TCP_ClientClass", "\360\237\230\200", nullptr));
        lineEdit->setText(QString());
        Btn_Send->setText(QCoreApplication::translate("TCP_ClientClass", "\347\231\274\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TCP_ClientClass: public Ui_TCP_ClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCP_CLIENT_H
