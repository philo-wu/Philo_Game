#pragma once

#include <QtWidgets/QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>
#include <QNetworkInterface>

#include <QDateTime>
#include <QTimer>
#include <QSettings>

#include "EventManager.h"
#include "./ui/ui_TCP_Server.h"
#include "Common.h"
#include "MUD_Engine.h"
enum ServerState {
    SERVER_START,                  // 成功
    SERVER_STOP
};

//class TcpServerHelper : public QTcpServer
//{
//    Q_OBJECT
//public:
//    explicit TcpServerHelper(QObject* parent = nullptr) : QTcpServer(parent) {}
//protected:
//    //重写incomingConnection,用于多线程通讯，子线程中不能使用主线程中创建的套接字对象
//    void incomingConnection(qintptr socketDescriptor)
//    {
//        emit newSockDescriptor(socketDescriptor);
//    }
//signals:
//    void newSockDescriptor(qintptr _sock);
//};

class TCP_Server : public QMainWindow
{
    Q_OBJECT

public:
    TCP_Server(QWidget *parent = nullptr);
    ~TCP_Server();

    QTcpServer* m_server;
    QTimer* timer;
    QList<QTcpSocket*> m_sockets;   
    DeviceSetting m_Setting;
    QString Server_Name;

    //QThread* eventThread;


    int UserTotal = 0;
    int Server_State = SERVER_STOP;
    CSS m_CSS;
    void update();

    void Load_Setting();
    void Save_Setting();

    void LoadDataBase(QString fileName, QJsonDocument& jsonDocument);
    void SaveDataBase(QString fileName, QJsonDocument& jsonDocument);

    void SavePlayer(User& user);

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
    void Send_MudGame(QTcpSocket* socket, MyPacket Packet);
    void Send_RoleInfo(QTcpSocket* socket, MyPacket Packet);

public slots:
    void on_Btn_Start_clicked();

    void slot_newConnection();
    void slot_disConnected();
    void Client_to_Server();   
    void Server_to_Client(Command command ,QTcpSocket* socket , MyPacket Packet);
    void Send_Packet(QTcpSocket* socket, QByteArray Packet);

signals:
    // @緩衝區 通知EventManager:MainThread目前為空閒狀態
    void SendFinish();

private:
    Ui::TCP_ServerClass* ui;
    QJsonDocument Account_DataBase; //User資訊與帳號密碼不共存
    UserManager* UM; 
    EventThread* ET; //@緩衝區 事件隊列
    MUD_Engine* MUD;
};
