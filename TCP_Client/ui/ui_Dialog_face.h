/********************************************************************************
** Form generated from reading UI file 'Dialog_face.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_FACE_H
#define UI_DIALOG_FACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_faceClass
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QTableWidget *faceTable_1;
    QWidget *page_2;
    QGridLayout *gridLayout_3;
    QTableWidget *faceTable_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *foreButton;
    QPushButton *backButton;

    void setupUi(QDialog *Dialog_faceClass)
    {
        if (Dialog_faceClass->objectName().isEmpty())
            Dialog_faceClass->setObjectName(QString::fromUtf8("Dialog_faceClass"));
        Dialog_faceClass->resize(342, 274);
        gridLayout = new QGridLayout(Dialog_faceClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(Dialog_faceClass);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        faceTable_1 = new QTableWidget(page);
        faceTable_1->setObjectName(QString::fromUtf8("faceTable_1"));
        faceTable_1->setFocusPolicy(Qt::NoFocus);
        faceTable_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
        faceTable_1->setSelectionMode(QAbstractItemView::SingleSelection);
        faceTable_1->horizontalHeader()->setVisible(false);
        faceTable_1->horizontalHeader()->setDefaultSectionSize(30);
        faceTable_1->verticalHeader()->setVisible(false);
        faceTable_1->verticalHeader()->setDefaultSectionSize(20);

        gridLayout_2->addWidget(faceTable_1, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_3 = new QGridLayout(page_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        faceTable_2 = new QTableWidget(page_2);
        faceTable_2->setObjectName(QString::fromUtf8("faceTable_2"));
        faceTable_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        faceTable_2->setSelectionMode(QAbstractItemView::SingleSelection);
        faceTable_2->horizontalHeader()->setVisible(false);
        faceTable_2->horizontalHeader()->setDefaultSectionSize(30);
        faceTable_2->verticalHeader()->setVisible(false);
        faceTable_2->verticalHeader()->setDefaultSectionSize(20);

        gridLayout_3->addWidget(faceTable_2, 0, 0, 1, 1);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        foreButton = new QPushButton(Dialog_faceClass);
        foreButton->setObjectName(QString::fromUtf8("foreButton"));
        foreButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(foreButton);

        backButton = new QPushButton(Dialog_faceClass);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(backButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Dialog_faceClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog_faceClass);
    } // setupUi

    void retranslateUi(QDialog *Dialog_faceClass)
    {
        Dialog_faceClass->setWindowTitle(QCoreApplication::translate("Dialog_faceClass", "Dialog_face", nullptr));
        foreButton->setText(QCoreApplication::translate("Dialog_faceClass", "\344\270\212\344\270\200\351\240\201", nullptr));
        backButton->setText(QCoreApplication::translate("Dialog_faceClass", "\344\270\213\344\270\200\351\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_faceClass: public Ui_Dialog_faceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_FACE_H
