#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QTimer>

#include "ui_TCP_Client.h"
#include "Common.h"



class TCP_Client : public QMainWindow
{
    Q_OBJECT
public:
    TCP_Client(QWidget *parent = nullptr);
    ~TCP_Client();
    ClientSetting m_Setting;
    QTcpSocket* m_socket;      

    void update();

    // 本地指令

    void Connect_init();
    // Server指令
    void Receive_Chat(MyPacket packet);

    // Client指令
    void Send_Chat();
private slots:
    void Server_to_Client();    
    void Client_to_Server(Command command);
    void on_Btn_Signout_clicked();
    void on_Btn_Send_clicked();

private:
    Ui::TCP_ClientClass* ui;
    //Dialog_Login Dlg_Login;
};
