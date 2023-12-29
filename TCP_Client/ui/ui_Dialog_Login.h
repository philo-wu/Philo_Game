/********************************************************************************
** Form generated from reading UI file 'Dialog_Login.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_LOGIN_H
#define UI_DIALOG_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_LoginClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *Btn_Login;
    QPushButton *Btn_Setting;
    QPushButton *Btn_quit;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QLineEdit *lineEdit_Account;
    QPushButton *Btn_ToSignup;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_11;
    QCheckBox *CB_Keeppass;
    QCheckBox *CB_Showpass;
    QSpacerItem *horizontalSpacer_12;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QLineEdit *lineEdit_Pass;
    QPushButton *Btn_Findpass;
    QLabel *label_4;
    QWidget *page_2;
    QPushButton *Btn_Signup;
    QPushButton *Btn_return;
    QPushButton *Btn_Setting_2;
    QPushButton *Btn_quit_2;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *LE_Signup_name;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *LE_Signup_pass;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_14;
    QLineEdit *LE_Signup_pass_double;
    QWidget *page_3;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_12;
    QLineEdit *lineEdit_IP;
    QPushButton *Btn_Setting_OK;
    QPushButton *Btn_Setting_return;
    QPushButton *Btn_quit_3;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_13;
    QLineEdit *lineEdit_Port;

    void setupUi(QDialog *Dialog_LoginClass)
    {
        if (Dialog_LoginClass->objectName().isEmpty())
            Dialog_LoginClass->setObjectName(QString::fromUtf8("Dialog_LoginClass"));
        Dialog_LoginClass->resize(600, 400);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(221, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        Dialog_LoginClass->setPalette(palette);
        verticalLayout_2 = new QVBoxLayout(Dialog_LoginClass);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(Dialog_LoginClass);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Bahnschrift SemiBold"));
        font.setPointSize(48);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        stackedWidget = new QStackedWidget(Dialog_LoginClass);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        Btn_Login = new QPushButton(page);
        Btn_Login->setObjectName(QString::fromUtf8("Btn_Login"));
        Btn_Login->setGeometry(QRect(90, 150, 410, 30));
        Btn_Login->setMinimumSize(QSize(410, 30));
        Btn_Login->setMaximumSize(QSize(410, 16777215));
        Btn_Login->setFocusPolicy(Qt::NoFocus);
        Btn_Setting = new QPushButton(page);
        Btn_Setting->setObjectName(QString::fromUtf8("Btn_Setting"));
        Btn_Setting->setGeometry(QRect(520, 190, 70, 25));
        Btn_Setting->setMinimumSize(QSize(0, 0));
        Btn_Setting->setMaximumSize(QSize(80, 16777215));
        Btn_Setting->setFocusPolicy(Qt::NoFocus);
        Btn_quit = new QPushButton(page);
        Btn_quit->setObjectName(QString::fromUtf8("Btn_quit"));
        Btn_quit->setGeometry(QRect(10, 190, 70, 25));
        Btn_quit->setMinimumSize(QSize(0, 0));
        Btn_quit->setMaximumSize(QSize(80, 16777215));
        Btn_quit->setFocusPolicy(Qt::NoFocus);
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 20, 491, 25));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setMinimumSize(QSize(55, 0));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_8);

        lineEdit_Account = new QLineEdit(layoutWidget);
        lineEdit_Account->setObjectName(QString::fromUtf8("lineEdit_Account"));
        lineEdit_Account->setMinimumSize(QSize(250, 0));
        lineEdit_Account->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_8->addWidget(lineEdit_Account);

        Btn_ToSignup = new QPushButton(layoutWidget);
        Btn_ToSignup->setObjectName(QString::fromUtf8("Btn_ToSignup"));
        Btn_ToSignup->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_8->addWidget(Btn_ToSignup);

        layoutWidget1 = new QWidget(page);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(140, 100, 318, 23));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_10->setSpacing(30);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_11);

        CB_Keeppass = new QCheckBox(layoutWidget1);
        CB_Keeppass->setObjectName(QString::fromUtf8("CB_Keeppass"));
        QFont font1;
        font1.setStrikeOut(false);
        CB_Keeppass->setFont(font1);
        CB_Keeppass->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_10->addWidget(CB_Keeppass);

        CB_Showpass = new QCheckBox(layoutWidget1);
        CB_Showpass->setObjectName(QString::fromUtf8("CB_Showpass"));
        CB_Showpass->setFont(font1);
        CB_Showpass->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_10->addWidget(CB_Showpass);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_12);

        layoutWidget2 = new QWidget(page);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(90, 60, 491, 25));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setMinimumSize(QSize(55, 0));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_9);

        lineEdit_Pass = new QLineEdit(layoutWidget2);
        lineEdit_Pass->setObjectName(QString::fromUtf8("lineEdit_Pass"));
        lineEdit_Pass->setMinimumSize(QSize(250, 0));
        lineEdit_Pass->setFocusPolicy(Qt::StrongFocus);
        lineEdit_Pass->setEchoMode(QLineEdit::Password);

        horizontalLayout_9->addWidget(lineEdit_Pass);

        Btn_Findpass = new QPushButton(layoutWidget2);
        Btn_Findpass->setObjectName(QString::fromUtf8("Btn_Findpass"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Agency FB"));
        font2.setStrikeOut(true);
        Btn_Findpass->setFont(font2);
        Btn_Findpass->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_9->addWidget(Btn_Findpass);

        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(80, 0));
        label_4->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_9->addWidget(label_4);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        Btn_Signup = new QPushButton(page_2);
        Btn_Signup->setObjectName(QString::fromUtf8("Btn_Signup"));
        Btn_Signup->setGeometry(QRect(300, 150, 200, 30));
        Btn_Signup->setMinimumSize(QSize(0, 30));
        Btn_Signup->setMaximumSize(QSize(400, 16777215));
        Btn_return = new QPushButton(page_2);
        Btn_return->setObjectName(QString::fromUtf8("Btn_return"));
        Btn_return->setGeometry(QRect(90, 150, 200, 30));
        Btn_return->setMaximumSize(QSize(400, 16777215));
        Btn_Setting_2 = new QPushButton(page_2);
        Btn_Setting_2->setObjectName(QString::fromUtf8("Btn_Setting_2"));
        Btn_Setting_2->setGeometry(QRect(520, 190, 70, 25));
        Btn_Setting_2->setMinimumSize(QSize(0, 0));
        Btn_Setting_2->setMaximumSize(QSize(80, 16777215));
        Btn_quit_2 = new QPushButton(page_2);
        Btn_quit_2->setObjectName(QString::fromUtf8("Btn_quit_2"));
        Btn_quit_2->setGeometry(QRect(10, 190, 70, 25));
        Btn_quit_2->setMinimumSize(QSize(0, 0));
        Btn_quit_2->setMaximumSize(QSize(80, 16777215));
        layoutWidget3 = new QWidget(page_2);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(90, 20, 405, 25));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(55, 0));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_2);

        LE_Signup_name = new QLineEdit(layoutWidget3);
        LE_Signup_name->setObjectName(QString::fromUtf8("LE_Signup_name"));
        LE_Signup_name->setMinimumSize(QSize(250, 0));

        horizontalLayout_4->addWidget(LE_Signup_name);

        layoutWidget4 = new QWidget(page_2);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(90, 60, 405, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(55, 0));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_3);

        LE_Signup_pass = new QLineEdit(layoutWidget4);
        LE_Signup_pass->setObjectName(QString::fromUtf8("LE_Signup_pass"));
        LE_Signup_pass->setMinimumSize(QSize(250, 0));
        LE_Signup_pass->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(LE_Signup_pass);

        layoutWidget5 = new QWidget(page_2);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(90, 100, 405, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget5);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        label_14->setMinimumSize(QSize(55, 0));

        horizontalLayout->addWidget(label_14);

        LE_Signup_pass_double = new QLineEdit(layoutWidget5);
        LE_Signup_pass_double->setObjectName(QString::fromUtf8("LE_Signup_pass_double"));
        LE_Signup_pass_double->setMinimumSize(QSize(250, 0));
        LE_Signup_pass_double->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(LE_Signup_pass_double);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        layoutWidget6 = new QWidget(page_3);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(90, 20, 405, 25));
        horizontalLayout_13 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget6);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setMinimumSize(QSize(55, 0));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(label_12);

        lineEdit_IP = new QLineEdit(layoutWidget6);
        lineEdit_IP->setObjectName(QString::fromUtf8("lineEdit_IP"));
        lineEdit_IP->setMinimumSize(QSize(250, 0));

        horizontalLayout_13->addWidget(lineEdit_IP);

        Btn_Setting_OK = new QPushButton(page_3);
        Btn_Setting_OK->setObjectName(QString::fromUtf8("Btn_Setting_OK"));
        Btn_Setting_OK->setGeometry(QRect(300, 150, 200, 30));
        Btn_Setting_OK->setMinimumSize(QSize(0, 0));
        Btn_Setting_OK->setMaximumSize(QSize(410, 30));
        Btn_Setting_return = new QPushButton(page_3);
        Btn_Setting_return->setObjectName(QString::fromUtf8("Btn_Setting_return"));
        Btn_Setting_return->setGeometry(QRect(90, 150, 200, 30));
        Btn_Setting_return->setMinimumSize(QSize(0, 0));
        Btn_Setting_return->setMaximumSize(QSize(400, 16777215));
        Btn_quit_3 = new QPushButton(page_3);
        Btn_quit_3->setObjectName(QString::fromUtf8("Btn_quit_3"));
        Btn_quit_3->setGeometry(QRect(10, 190, 70, 25));
        Btn_quit_3->setMinimumSize(QSize(0, 0));
        Btn_quit_3->setMaximumSize(QSize(80, 16777215));
        layoutWidget7 = new QWidget(page_3);
        layoutWidget7->setObjectName(QString::fromUtf8("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(90, 60, 405, 25));
        horizontalLayout_14 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        label_13 = new QLabel(layoutWidget7);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);
        label_13->setMinimumSize(QSize(55, 0));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_13);

        lineEdit_Port = new QLineEdit(layoutWidget7);
        lineEdit_Port->setObjectName(QString::fromUtf8("lineEdit_Port"));
        lineEdit_Port->setMinimumSize(QSize(250, 0));

        horizontalLayout_14->addWidget(lineEdit_Port);

        stackedWidget->addWidget(page_3);

        verticalLayout->addWidget(stackedWidget);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(1, 4);

        retranslateUi(Dialog_LoginClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog_LoginClass);
    } // setupUi

    void retranslateUi(QDialog *Dialog_LoginClass)
    {
        Dialog_LoginClass->setWindowTitle(QCoreApplication::translate("Dialog_LoginClass", "Dialog_Login", nullptr));
        label->setText(QCoreApplication::translate("Dialog_LoginClass", "ChatRoom", nullptr));
        Btn_Login->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\231\273\345\205\245", nullptr));
        Btn_Setting->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\266\262\350\267\257\350\250\255\345\256\232", nullptr));
        Btn_quit->setText(QCoreApplication::translate("Dialog_LoginClass", "\351\227\234\351\226\211", nullptr));
        label_8->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\224\250\346\210\266\345\220\215\347\250\261 :", nullptr));
        Btn_ToSignup->setText(QCoreApplication::translate("Dialog_LoginClass", "\350\250\273\345\206\212\345\270\263\350\231\237", nullptr));
        CB_Keeppass->setText(QCoreApplication::translate("Dialog_LoginClass", "\350\250\230\344\275\217\345\270\263\350\231\237", nullptr));
        CB_Showpass->setText(QCoreApplication::translate("Dialog_LoginClass", "\351\241\257\347\244\272\345\257\206\347\242\274", nullptr));
        label_9->setText(QCoreApplication::translate("Dialog_LoginClass", "\345\257\206\347\242\274 :", nullptr));
        lineEdit_Pass->setText(QString());
        Btn_Findpass->setText(QCoreApplication::translate("Dialog_LoginClass", "\346\211\276\345\233\236\345\257\206\347\242\274", nullptr));
        label_4->setText(QString());
        Btn_Signup->setText(QCoreApplication::translate("Dialog_LoginClass", "\350\250\273\345\206\212", nullptr));
        Btn_return->setText(QCoreApplication::translate("Dialog_LoginClass", "\350\277\224\345\233\236", nullptr));
        Btn_Setting_2->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\266\262\350\267\257\350\250\255\345\256\232", nullptr));
        Btn_quit_2->setText(QCoreApplication::translate("Dialog_LoginClass", "\351\227\234\351\226\211", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\224\250\346\210\266\345\220\215\347\250\261 :", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog_LoginClass", "\345\257\206\347\242\274 :", nullptr));
        label_14->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\242\272\350\252\215\345\257\206\347\242\274 :", nullptr));
        label_12->setText(QCoreApplication::translate("Dialog_LoginClass", "\344\274\272\346\234\215\345\231\250IP :", nullptr));
        lineEdit_IP->setInputMask(QCoreApplication::translate("Dialog_LoginClass", "000.000.000.000", nullptr));
        Btn_Setting_OK->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\242\272\350\252\215", nullptr));
        Btn_Setting_return->setText(QCoreApplication::translate("Dialog_LoginClass", "\350\277\224\345\233\236", nullptr));
        Btn_quit_3->setText(QCoreApplication::translate("Dialog_LoginClass", "\351\227\234\351\226\211", nullptr));
        label_13->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\253\257\345\217\243 :", nullptr));
        lineEdit_Port->setInputMask(QCoreApplication::translate("Dialog_LoginClass", "00000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_LoginClass: public Ui_Dialog_LoginClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_LOGIN_H
