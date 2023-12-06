#include "TCP_Client.h"
#include "Dialog_Login.h"

TCP_Client::TCP_Client(QWidget *parent): 
    QMainWindow(parent),
    ui(new Ui::TCP_ClientClass())
{
    ui->setupUi(this);
    m_socket = new QTcpSocket(this);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&TCP_Client::update));

    Dialog_Login* Dlg = new Dialog_Login(m_socket,this);
    Dlg->setModal(true);
    connect(Dlg, &Dialog_Login::ToRoom, [=]() {
        this->show();
        //m_socket = Dlg->m_socket;
        m_Setting = Dlg->m_Setting;
        ui->LE_Name->setText(m_Setting.m_User);
        ui->LE_IP->setText(m_socket->localAddress().toString());
        ui->LE_Port->setText(QString::number(m_socket->localPort()));
        ui->LE_LoginTime->setText(m_Setting.m_LoginTime.toString("yyyy-MM-dd hh:mm:ss"));
        ui->LE_LoginSec->setText(QString::number(m_Setting.m_LoginSec));
        timer->start(1000);
        });
    Dlg->exec();
    if (Dlg)
        delete Dlg;
    Connect_init();


}

TCP_Client::~TCP_Client()
{
    delete ui;
}
void TCP_Client::update()
{
    m_Setting.m_LoginSec += 1;
    ui->LE_LoginSec->setText(QString::number(m_Setting.m_LoginSec));
}


void TCP_Client::Connect_init()
{
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(Server_to_Client())); 
}

void TCP_Client::Client_to_Server(Command command)
{

    switch (command) {
    case MAIN_C_S_ACTION: {
        Send_Chat();
    }
                       break;
    default:
        break;
    }
}
void TCP_Client::Server_to_Client()
{
    MyPacket Packet;
    Packet.deserialize(m_socket->readAll());
    //Command receivedCommand = Packet.getCommand();
    //MassageData receivedData = Packet.massageData;

    switch (Packet.getCommand()) {
    case MAIN_S_C_ACTION: {
        Receive_Chat(Packet);
    }
        break;
    default:
        break;
    }
}


void TCP_Client::on_Btn_Signout_clicked()
{

}
void TCP_Client::on_Btn_Send_clicked()
{
    Client_to_Server(MAIN_C_S_ACTION);
}

void TCP_Client::Receive_Chat(MyPacket packet)
{
    // TODO 處理更複雜的登入失敗訊息
    if (packet.massageData.m_errorcode == 0) {

        QString Name = packet.massageData.m_User;

        QString currentDateTimeString = packet.massageData.m_Time.toString("yyyy-MM-dd hh:mm:ss");
        QString str = Name + " < " + currentDateTimeString + " > : \n" + packet.massageData.m_Data + "\n";
        ui->TB_Chat->setText(ui->TB_Chat->toPlainText()+ str);
    }
    else
    {
        QMessageBox::critical(nullptr, "Error", "An error occurred!");
    }
}


void TCP_Client::Send_Chat()
{
    MyPacket packet;
    QString str = ui->lineEdit->text();
    packet.setCommand(MAIN_C_S_ACTION);
    packet.massageData.m_User = m_Setting.m_User;
    packet.massageData.m_Data = str;
    packet.massageData.m_errorcode = 0;
    packet.massageData.m_Time = QDateTime::currentDateTime();
    ui->lineEdit->clear();

    // 將封包序列化成 QByteArray 以便發送
    QByteArray serializedPacket = packet.serialize();
    m_socket->write(serializedPacket);    // Exception
}
