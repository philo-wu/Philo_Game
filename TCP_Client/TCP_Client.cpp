#include "TCP_Client.h"
#include "Dialog_Login.h"

TCP_Client::TCP_Client(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
    connectToServer();

}

TCP_Client::~TCP_Client()
{
    delete ui;
}


void TCP_Client::connectToServer()
{
    m_socket = new QTcpSocket(this);

    //连接到服务器

    // 尝试连接到IP为"127.0.0.1" & 端口号为19999服务器
    // 如果想要实现局域网通信, 只需将第一个IP地址设置为“服务器”所在主机的IP地址即可
    // 如  m_socket->connectToHost("170.29.19.65", 19999);
    m_socket->connectToHost(QHostAddress::LocalHost, 19999);

    qDebug() << "Port" << m_socket->localPort();

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(slot_readMessage()));   // 告诉socket, 要用slot_readMessage()去处理接收的消息.

    connect(ui->Btn_Send, SIGNAL(clicked()), this, SLOT(slot_btnSendMsg()));

    connect(ui->Btn_Signout, SIGNAL(clicked()), this, SLOT(slot_login()));

}

void TCP_Client::slot_readMessage()   // 只会在socket接收到server消息时调用
{
    QString str = m_socket->readAll().data();
    ui->TB_Chat->setText(ui->TB_Chat->toPlainText() + "\n" + str);
}

void TCP_Client::slot_btnSendMsg()
{

    QString str = ui->lineEdit->text();
    m_socket->write(str.toStdString().data());    // Exception
    ui->lineEdit->clear();
}

void TCP_Client::slot_login() {
    Dialog_Login* Dlg = new Dialog_Login(this);
    Dlg->setModal(true);
    Dlg->exec();
}