#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCP_Server.h"

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>



class TCP_Server : public QMainWindow
{
    Q_OBJECT

public:
    TCP_Server(QWidget *parent = nullptr);
    ~TCP_Server();

    QTcpServer* m_server; //QT自帶

    QList<QTcpSocket*> m_sockets;   // 连接到server的所有客户.  链表方式, 在服务器端的一个备份(客户端的socket)

    void startServer();    // 启动一个server
public slots:
    void slot_newConnection();    //  对应客户端的 connectToHost();

    void slot_readMessage();   // 每一个socket绑定
private:
    Ui::TCP_ServerClass* ui;
};
