#pragma once

#include <QtWidgets/QDialog>
#include "ui_Dialog_Login.h"

class Dialog_Login : public QDialog
{
	Q_OBJECT

public:
	Dialog_Login(QWidget *parent = nullptr);
	~Dialog_Login();

private slots:
    void on_Btn_ToSignup_clicked();

    void on_Btn_Login_2_clicked();

    void on_Btn_Setting_clicked();

private:
	Ui::Dialog_LoginClass* ui;
};
