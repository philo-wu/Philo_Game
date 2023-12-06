#include "TCP_Server.h"

TCP_Server::TCP_Server(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
    startServer();
}


TCP_Server::~TCP_Server()
{

}



void TCP_Server::startServer()
{
    m_server = new QTcpServer(this);

    m_server->listen(QHostAddress::Any, 19999);

    connect(m_server, SIGNAL(newConnection()), this, SLOT(slot_newConnection()));  //
}

void TCP_Server::slot_newConnection()
{
    // 把新加入的socket放入链表中
    QTcpSocket* socket = m_server->nextPendingConnection();
    m_sockets.push_back(socket);

    connect(socket, SIGNAL(readyRead()), this, SLOT(Client_to_Server()));
}

// 每一个socket处理收到消息的函数
void TCP_Server::Client_to_Server()
{
    QTcpSocket* socket = (QTcpSocket*)QObject::sender();  // 获得是哪个socket收到了消息

    MyPacket Packet;
    Packet.deserialize(socket->readAll());
    //Command Command = Packet.getCommand();
    //MassageData Data = Packet.massageData;



    switch (Packet.getCommand()){
    case MAIN_C_S_LOGIN :{
        //TODO 驗證帳號密碼並回傳
        MyPacket receivedPacket;
        receivedPacket.setCommand(MAIN_S_C_LOGIN);
        receivedPacket.massageData.m_User = Packet.massageData.m_User;
        receivedPacket.massageData.m_Data = "";
        receivedPacket.massageData.m_errorcode = 0;
        receivedPacket.massageData.m_Time = QDateTime::currentDateTime();

        QByteArray serializedPacket = receivedPacket.serialize();
        socket->write(serializedPacket);
    }
        break;
    case MAIN_C_S_ACTION:{
        MyPacket receivedPacket;
        receivedPacket.setCommand(MAIN_S_C_ACTION);
        receivedPacket.massageData.m_User = Packet.massageData.m_User;
        //QString str = +" < " + currentDateTimeString + " > : \n" + Packet.massageData.m_Data;
        receivedPacket.massageData.m_Data = Packet.massageData.m_Data;
        receivedPacket.massageData.m_errorcode = 0;
        receivedPacket.massageData.m_Time = QDateTime::currentDateTime();

        QByteArray serializedPacket = receivedPacket.serialize();
        for (int i = 0; i < m_sockets.size(); i++)
        {
            m_sockets[i]->write(serializedPacket);
        }
    }
        break;
    default:
        break;
    }
}
void TCP_Server::Server_to_Client(MyPacket packet)
{

} 
