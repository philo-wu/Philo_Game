#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QTimer>
#include <QKeyEvent>
#include <QScrollBar>
#include <QPropertyAnimation>

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
    bool Can_move;
    void update();

    // 本地指令

    void Connect_init();
    void Diglog_Login();
    // Server指令
    void Receive_Chat(MyPacket packet);
    void Receive_LoginInit(MyPacket packet);
    void Receive_MudGame(MyPacket packet);
    void Receive_RoleInfo(MyPacket packet);

    // Client指令
    void Send_Packet(QByteArray& Packet);
    void Send_Chat();
    void Send_LoginInit();
    void Send_MudGame(QString str);
    void Send_MudGame_GetScenes();
    void Send_RoleInfo();

private slots:
    void Server_to_Client();    
    void Client_to_Server(Command command);
    void on_Btn_Signout_clicked();
    void on_Btn_Send_clicked();
    void socketStateChanged(QAbstractSocket::SocketState state);
    void on_Btn_Emoji_clicked();
    void on_catchFace(int row , int column, int page);

    void on_pushButton_clicked();

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
        else if (event->key() == Qt::Key_1) {
            Send_MudGame("1");
        }
        else if (event->key() == Qt::Key_2) {
            Send_MudGame("2");
        }
        else if (event->key() == Qt::Key_3) {
            Send_MudGame("3");
        }
        else if (event->key() == Qt::Key_4) {
            Send_MudGame("4");
        }
        else if (event->key() == Qt::Key_5) {
            Send_MudGame("5");
        }
        else if (event->key() == Qt::Key_6) {
            Send_MudGame("6");
        }
        else if (event->key() == Qt::Key_7) {
            Send_MudGame("7");
        }
        else if (event->key() == Qt::Key_8) {
            Send_MudGame("8");
        }
        else if (event->key() == Qt::Key_9) {
            Send_MudGame("9");
        }
        else if (event->key() == Qt::Key_0) {
            Send_MudGame("0");
        }
        else if (event->key() == Qt::Key_W && Can_move){
            Send_MudGame("101");
        }
        else if (event->key() == Qt::Key_S && Can_move){
            Send_MudGame("102");
        }
        else if (event->key() == Qt::Key_A && Can_move){
            Send_MudGame("103");
        }
        else if (event->key() == Qt::Key_D && Can_move){
            Send_MudGame("104");
        }
        else {
            QWidget::keyPressEvent(event);
        }
    }
};
