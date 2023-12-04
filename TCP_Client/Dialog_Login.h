#pragma once

#include <QDialog>
#include "ui_Dialog_Login.h"

class Dialog_Login : public QDialog
{
	Q_OBJECT

public:
	Dialog_Login(QWidget *parent = nullptr);
	~Dialog_Login();

private:
	Ui::Dialog_LoginClass ui;
};
