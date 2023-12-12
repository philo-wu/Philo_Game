#pragma once

#include <QtWidgets/QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>
#include <QNetworkInterface>

#include <QDateTime>
#include <QTimer>
#include <QSettings>

#include "./ui/ui_TCP_Server.h"
#include "Common.h"

enum ServerState {
    SERVER_START,                  // 成功
    SERVER_STOP,
    SERVER_PAUSE
};

class TCP_Server : public QMainWindow
{
    Q_OBJECT

public:
    TCP_Server(QWidget *parent = nullptr);
    ~TCP_Server();

    QTcpServer* m_server; 
    QTimer* timer;
    QList<QTcpSocket*> m_sockets;   
    ConnectionSetting m_Setting;
    QString Server_Name;
    int UserTotal = 0;
    int Server_State = SERVER_STOP;
    CSS m_CSS;
    void update();

    void Load_Setting();
    void Save_Setting();

    void loadDataBase(QString fileName, QJsonDocument& jsonDocument);
    void SingUp(QString fileName, QJsonDocument& jsonDocument,MassageData Data);
    void updateServerState();
    void updateUserList();
    void startServer();    
    void stopServer();

    void Log(QString log);

    // Server指令
    void Send_Login(QTcpSocket* socket , MyPacket Packet);
    void Send_Chat(QTcpSocket* socket , MyPacket Packet);
    void Send_Singup(QTcpSocket* socket , MyPacket Packet);
    void Send_LoginInit(QTcpSocket* socket);
public slots:
    void on_Btn_Start_clicked();
    void on_Btn_Pause_clicked();

    void slot_newConnection();
    void slot_disConnected();
    void Client_to_Server();   
    void Server_to_Client(Command command ,QTcpSocket* socket , MyPacket Packet);

private:
    Ui::TCP_ServerClass* ui;
    QJsonDocument Account_DataBase; //User資訊與帳號密碼不共存
    UserManager* UM;
};
