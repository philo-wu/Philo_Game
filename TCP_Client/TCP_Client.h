#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QTimer>
#include <QKeyEvent>

#include "ui_TCP_Client.h"
#include "Common.h"
#include "Dialog_face.h"



class TCP_Client : public QMainWindow
{
    Q_OBJECT
public:
    TCP_Client(QWidget *parent = nullptr);
    ~TCP_Client();
    DeviceSetting m_Setting;
    User Local_User;
    QTcpSocket* m_socket;      
    QTimer* timer;

    void update();

    // 本地指令

    void Connect_init();
    void Diglog_Login();
    // Server指令
    void Receive_Chat(MyPacket packet);
    void Receive_LoginInit(MyPacket packet);

    // Client指令
    void Send_Packet(QByteArray Packet);
    void Send_Chat();
    void Send_LoginInit();

private slots:
    void Server_to_Client();    
    void Client_to_Server(Command command);
    void on_Btn_Signout_clicked();
    void on_Btn_Send_clicked();
    void socketStateChanged(QAbstractSocket::SocketState state);
    void on_Btn_Emoji_clicked();
    void on_catchFace(int row , int column, int page);

private:
    Ui::TCP_ClientClass* ui;
    //Dialog_Login Dlg_Login;
    Dialog_face* face;

protected:
    void keyPressEvent(QKeyEvent* event) override {
        // 檢查是否按下 Enter 鍵
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            on_Btn_Send_clicked();
        }
        else {
            QWidget::keyPressEvent(event);
        }
    }
};
