#pragma once

#include <QtWidgets/QDialog>
#include "ui_Dialog_Login.h"

#include "Common.h"

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QSettings>
#include <QRegExpValidator>
#include <QRegExp>
#include <QMessageBox>

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

	ClientSetting m_Setting;

	// 本地指令
	void Dialog_init();
	void Load_Setting();
	void Save_Setting();
	void Save_IP(QString IP, int Port);


	// Client指令
	void Send_Login();

	// Sever指令
	void Receive_Login(MyPacket packet);

private slots:
	void Server_to_client();
	void Client_to_Server(Command command);     

    void on_Btn_ToSignup_clicked();
    void on_Btn_Login_clicked();
    void on_Btn_Setting_clicked();
	void on_Btn_return_clicked();
    void on_Btn_quit_clicked();
	void on_Btn_Setting_OK_clicked();
private:
	Ui::Dialog_LoginClass* ui;

	int currentIndex;

signals:
	void ToRoom();
	//void Quit();

};
