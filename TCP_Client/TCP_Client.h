#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCP_Client.h"

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>


class TCP_Client : public QMainWindow
{
    Q_OBJECT
public:
    TCP_Client(QWidget *parent = nullptr);
    ~TCP_Client();

    QTcpSocket* m_socket;      // 客户端套接字

    void connectToServer();    // 连接到服务器

private slots:
    void slot_readMessage();   // 处理接收服务器方发送的消息
    void slot_btnSendMsg();    // 点击发送按钮后，后发送消息

private:
    Ui::TCP_ClientClass* ui;
};
