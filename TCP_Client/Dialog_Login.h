#pragma once

#include <QtWidgets/QDialog>
#include "ui_Dialog_Login.h"

#include "Common.h"

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QSettings>
#include <QRegExpValidator>
#include <QRegExp>
#include <QTimer>
#include <QProgressDialog>
#include <QMessageBox>

#include "qstringliteral.h"

#define PAGEINDEX_LOGIN 0
#define PAGEINDEX_CREATE 1
#define PAGEINDEX_SETTING 2

class Dialog_Login : public QDialog
{
	Q_OBJECT

public:
	Dialog_Login(QTcpSocket* p_Socket,QWidget *parent = nullptr);
	~Dialog_Login();
	void Connect_init();
	QTcpSocket* m_socket; 
	QTimer* m_timer;
	User Local_User;
	ConnectionSetting m_Setting;
	QProgressDialog* logining_Dialog;
	// 本地指令
	void Dialog_init();
	void Load_Setting();
	void Save_Setting(QString Account = NULL);
	void Save_IP(QString IP, int Port);


	// Client指令
	void Send_Login(QString User, QString Pass);
	void Send_SignUp(QString User, QString Pass);
	// Sever指令
	void Receive_Login(MyPacket packet);
	void Receive_SignUp(MyPacket packet);

private slots:
	void Server_to_Client();
	void Client_to_Server(Command command);     

    void on_Btn_ToSignup_clicked();
    void on_Btn_Login_clicked();
    void on_Btn_Setting_clicked();
	void on_Btn_return_clicked();
    void on_Btn_quit_clicked();
	void on_Btn_Setting_OK_clicked();
    void on_Btn_Signup_clicked();
    void on_CB_Showpass_stateChanged(int arg1);

    void on_CB_Keeppass_stateChanged(int arg1);

private:
	Ui::Dialog_LoginClass* ui;

	int currentIndex;

signals:
	void ToRoom();
protected:
	void closeEvent(QCloseEvent* event) override {
		on_Btn_quit_clicked();
		return;
	}
};
