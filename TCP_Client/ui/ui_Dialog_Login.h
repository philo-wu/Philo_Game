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
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_8;
    QLineEdit *lineEdit_3;
    QPushButton *Btn_ToSignup;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_9;
    QLineEdit *lineEdit_4;
    QPushButton *Btn_Findpass;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_11;
    QCheckBox *CB_Keeppass_2;
    QCheckBox *CB_Showpass_2;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QPushButton *Btn_Login_2;
    QLabel *label_7;
    QPushButton *Btn_Setting;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QLineEdit *LE_Signup_name;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_3;
    QLineEdit *LE_Signup_pass;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_14;
    QLineEdit *LE_Signup_pass_double;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *Btn_return;
    QPushButton *Btn_Signup;
    QLabel *label_5;
    QPushButton *Btn_Setting_2;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_12;
    QLineEdit *lineEdit_5;
    QSpacerItem *horizontalSpacer_14;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_15;
    QLabel *label_13;
    QLineEdit *lineEdit_6;
    QSpacerItem *horizontalSpacer_16;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *Btn_Setting_return;
    QLabel *label_11;
    QPushButton *Btn_Setting_OK;
    QLabel *label_4;

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
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 10, -1, -1);
        stackedWidget = new QStackedWidget(Dialog_LoginClass);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_4 = new QVBoxLayout(page);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);

        label_8 = new QLabel(page);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(55, 0));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_8);

        lineEdit_3 = new QLineEdit(page);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMinimumSize(QSize(250, 0));

        horizontalLayout_8->addWidget(lineEdit_3);

        Btn_ToSignup = new QPushButton(page);
        Btn_ToSignup->setObjectName(QString::fromUtf8("Btn_ToSignup"));

        horizontalLayout_8->addWidget(Btn_ToSignup);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        label_9 = new QLabel(page);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(55, 0));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_9);

        lineEdit_4 = new QLineEdit(page);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setMinimumSize(QSize(250, 0));

        horizontalLayout_9->addWidget(lineEdit_4);

        Btn_Findpass = new QPushButton(page);
        Btn_Findpass->setObjectName(QString::fromUtf8("Btn_Findpass"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setStrikeOut(true);
        Btn_Findpass->setFont(font1);

        horizontalLayout_9->addWidget(Btn_Findpass);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_10);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(30);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_11);

        CB_Keeppass_2 = new QCheckBox(page);
        CB_Keeppass_2->setObjectName(QString::fromUtf8("CB_Keeppass_2"));

        horizontalLayout_10->addWidget(CB_Keeppass_2);

        CB_Showpass_2 = new QCheckBox(page);
        CB_Showpass_2->setObjectName(QString::fromUtf8("CB_Showpass_2"));

        horizontalLayout_10->addWidget(CB_Showpass_2);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_12);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(page);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_7->addWidget(label_6);

        Btn_Login_2 = new QPushButton(page);
        Btn_Login_2->setObjectName(QString::fromUtf8("Btn_Login_2"));
        Btn_Login_2->setMinimumSize(QSize(150, 30));

        horizontalLayout_7->addWidget(Btn_Login_2);

        label_7 = new QLabel(page);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        Btn_Setting = new QPushButton(page);
        Btn_Setting->setObjectName(QString::fromUtf8("Btn_Setting"));
        Btn_Setting->setMinimumSize(QSize(0, 0));

        horizontalLayout_7->addWidget(Btn_Setting);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 3);
        horizontalLayout_7->setStretch(3, 1);

        horizontalLayout_6->addLayout(horizontalLayout_7);


        verticalLayout_4->addLayout(horizontalLayout_6);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        label_2 = new QLabel(page_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(55, 0));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_2);

        LE_Signup_name = new QLineEdit(page_2);
        LE_Signup_name->setObjectName(QString::fromUtf8("LE_Signup_name"));
        LE_Signup_name->setMinimumSize(QSize(250, 0));

        horizontalLayout_4->addWidget(LE_Signup_name);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        label_3 = new QLabel(page_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(55, 0));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_3);

        LE_Signup_pass = new QLineEdit(page_2);
        LE_Signup_pass->setObjectName(QString::fromUtf8("LE_Signup_pass"));
        LE_Signup_pass->setMinimumSize(QSize(250, 0));

        horizontalLayout_3->addWidget(LE_Signup_pass);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_14 = new QLabel(page_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMinimumSize(QSize(55, 0));

        horizontalLayout->addWidget(label_14);

        LE_Signup_pass_double = new QLineEdit(page_2);
        LE_Signup_pass_double->setObjectName(QString::fromUtf8("LE_Signup_pass_double"));
        LE_Signup_pass_double->setMinimumSize(QSize(250, 0));

        horizontalLayout->addWidget(LE_Signup_pass_double);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        Btn_return = new QPushButton(page_2);
        Btn_return->setObjectName(QString::fromUtf8("Btn_return"));

        horizontalLayout_5->addWidget(Btn_return);

        Btn_Signup = new QPushButton(page_2);
        Btn_Signup->setObjectName(QString::fromUtf8("Btn_Signup"));
        Btn_Signup->setMinimumSize(QSize(150, 30));

        horizontalLayout_5->addWidget(Btn_Signup);

        label_5 = new QLabel(page_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        Btn_Setting_2 = new QPushButton(page_2);
        Btn_Setting_2->setObjectName(QString::fromUtf8("Btn_Setting_2"));
        Btn_Setting_2->setMinimumSize(QSize(0, 0));

        horizontalLayout_5->addWidget(Btn_Setting_2);

        horizontalLayout_5->setStretch(1, 3);
        horizontalLayout_5->setStretch(3, 1);

        horizontalLayout_2->addLayout(horizontalLayout_5);


        verticalLayout_3->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        verticalLayout_5 = new QVBoxLayout(page_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_13);

        label_12 = new QLabel(page_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(55, 0));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(label_12);

        lineEdit_5 = new QLineEdit(page_3);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setMinimumSize(QSize(250, 0));

        horizontalLayout_13->addWidget(lineEdit_5);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_14);


        verticalLayout_5->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_15);

        label_13 = new QLabel(page_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(55, 0));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_13);

        lineEdit_6 = new QLineEdit(page_3);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setMinimumSize(QSize(250, 0));

        horizontalLayout_14->addWidget(lineEdit_6);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_16);


        verticalLayout_5->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(30);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_17);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_18);


        verticalLayout_5->addLayout(horizontalLayout_15);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        Btn_Setting_return = new QPushButton(page_3);
        Btn_Setting_return->setObjectName(QString::fromUtf8("Btn_Setting_return"));
        Btn_Setting_return->setMinimumSize(QSize(0, 0));

        horizontalLayout_12->addWidget(Btn_Setting_return);

        label_11 = new QLabel(page_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_12->addWidget(label_11);

        Btn_Setting_OK = new QPushButton(page_3);
        Btn_Setting_OK->setObjectName(QString::fromUtf8("Btn_Setting_OK"));
        Btn_Setting_OK->setMinimumSize(QSize(150, 30));

        horizontalLayout_12->addWidget(Btn_Setting_OK);

        label_4 = new QLabel(page_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_12->addWidget(label_4);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(2, 3);
        horizontalLayout_12->setStretch(3, 1);

        horizontalLayout_11->addLayout(horizontalLayout_12);


        verticalLayout_5->addLayout(horizontalLayout_11);

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
        label_8->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\224\250\346\210\266\345\220\215\347\250\261 :", nullptr));
        Btn_ToSignup->setText(QCoreApplication::translate("Dialog_LoginClass", "\350\250\273\345\206\212\345\270\263\350\231\237", nullptr));
        label_9->setText(QCoreApplication::translate("Dialog_LoginClass", "\345\257\206\347\242\274 :", nullptr));
        Btn_Findpass->setText(QCoreApplication::translate("Dialog_LoginClass", "\346\211\276\345\233\236\345\257\206\347\242\274", nullptr));
        CB_Keeppass_2->setText(QCoreApplication::translate("Dialog_LoginClass", "\350\250\230\344\275\217\345\257\206\347\242\274", nullptr));
        CB_Showpass_2->setText(QCoreApplication::translate("Dialog_LoginClass", "\351\241\257\347\244\272\345\257\206\347\242\274", nullptr));
        label_6->setText(QString());
        Btn_Login_2->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\231\273\345\205\245", nullptr));
        label_7->setText(QString());
        Btn_Setting->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\266\262\350\267\257\350\250\255\345\256\232", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\224\250\346\210\266\345\220\215\347\250\261 :", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog_LoginClass", "\345\257\206\347\242\274 :", nullptr));
        label_14->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\242\272\350\252\215\345\257\206\347\242\274 :", nullptr));
        Btn_return->setText(QCoreApplication::translate("Dialog_LoginClass", "\350\277\224\345\233\236", nullptr));
        Btn_Signup->setText(QCoreApplication::translate("Dialog_LoginClass", "\350\250\273\345\206\212", nullptr));
        label_5->setText(QString());
        Btn_Setting_2->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\266\262\350\267\257\350\250\255\345\256\232", nullptr));
        label_12->setText(QCoreApplication::translate("Dialog_LoginClass", "\344\274\272\346\234\215\345\231\250IP :", nullptr));
        label_13->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\253\257\345\217\243 :", nullptr));
        Btn_Setting_return->setText(QCoreApplication::translate("Dialog_LoginClass", "\350\277\224\345\233\236", nullptr));
        label_11->setText(QString());
        Btn_Setting_OK->setText(QCoreApplication::translate("Dialog_LoginClass", "\347\242\272\350\252\215", nullptr));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog_LoginClass: public Ui_Dialog_LoginClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_LOGIN_H
