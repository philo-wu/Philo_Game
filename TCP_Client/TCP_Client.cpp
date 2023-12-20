#include "TCP_Client.h"
#include "Dialog_Login.h"

TCP_Client::TCP_Client(QWidget *parent): 
    QMainWindow(parent),
    ui(new Ui::TCP_ClientClass())
{
    ui->setupUi(this);
    m_socket = new QTcpSocket(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&TCP_Client::update));
    ui->tableWidget_User->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_User->setRowCount(0);

    Diglog_Login();

    Connect_init();
    face = new Dialog_face(this);
    connect(face, SIGNAL(catchFace(int, int, int)), this, SLOT(on_catchFace(int, int, int)));

}

TCP_Client::~TCP_Client()
{
    //  @dalete
    //delete face;      //當TCP_Servere關閉時會自動delete (父類關閉)
    //delete timer;     //當TCP_Servere關閉時會自動delete (父類關閉)
    //delete m_socket;  //當TCP_Servere關閉時會自動delete (父類關閉)
    delete ui;
}
void TCP_Client::update()
{
    m_Setting.m_LoginSec += 1;
    ui->LE_LoginSec->setText(QString::number(m_Setting.m_LoginSec));
}


void TCP_Client::Connect_init()
{
}
void TCP_Client::Diglog_Login()
{
    Dialog_Login* Dlg = new Dialog_Login(m_socket);
    disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(Server_to_Client()));
    //Dlg->setModal(true);
    connect(Dlg, &Dialog_Login::ToRoom, [=]() {
        this->show();
        Dlg->hide();
        m_Setting = Dlg->m_Setting;
        Local_User = Dlg->Local_User;
        ui->LE_Name->setText(Dlg->Local_User.m_Account);
        ui->LE_IP->setText(m_socket->localAddress().toString());
        ui->LE_Port->setText(QString::number(m_socket->localPort()));
        ui->LE_LoginTime->setText(m_Setting.m_LoginTime.toString("yyyy-MM-dd hh:mm:ss"));
        ui->LE_LoginSec->setText(QString::number(m_Setting.m_LoginSec));
        ui->TB_Chat->clear();
        connect(m_socket, SIGNAL(readyRead()), this, SLOT(Server_to_Client()));
        connect(m_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
        timer->start(1000);
        Client_to_Server(MAIN_C_S_LOGININIT);
        });
    this->close();
    Dlg->show();
    //if (Dlg)
    //    delete Dlg;
}


void TCP_Client::Client_to_Server(Command command)
{

    switch (command) {
    case MAIN_C_S_CHAT: {
        Send_Chat();
    }
        break;
    default:
    case MAIN_C_S_LOGININIT: {
        Send_LoginInit();
    }
        break;
    }
}
void TCP_Client::Server_to_Client()
{    
    // @解密
    MyPacket Packet(Common::Encryption_byXOR(m_socket->readAll(), XOR_KEY));

    switch (Packet.getCommand()) {
    case MAIN_S_C_CHAT: {
        Receive_Chat(Packet);
        break;
    }
    case MAIN_S_C_LOGININIT: {
        Receive_LoginInit(Packet);
        break;
    }
    //case MAIN_S_C_PAUSE: {
    //    QMessageBox::critical(nullptr, "錯誤", "伺服器暫停中");
    //    break;
    //}
    default:
        break;
    }
}


void TCP_Client::on_Btn_Signout_clicked()
{
    disconnect(m_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    m_socket->disconnectFromHost();
    Diglog_Login();
}
void TCP_Client::on_Btn_Send_clicked()
{
    Client_to_Server(MAIN_C_S_CHAT);
}
void TCP_Client::on_Btn_Emoji_clicked()
{
    // @表情符號
    QPoint buttonPos = ui->Btn_Emoji->mapToGlobal(QPoint(0, 0));
    face->move(buttonPos.x(), buttonPos.y() - face->height());

    if (face->isHidden())
        face->show();
    else
        face->hide();
}
void TCP_Client::on_catchFace(int row, int column, int page)
{
    // @表情符號
    char32_t  t[] = { 0x1F601,0x0 };	//加上0x00是為了防止表情後面跟隨亂碼
    t[0] = 0x1F601 + row * 11 + column + page * 132;
    QString faceFileName = QString::fromUcs4(t);
    QString str = ui->lineEdit->text();
    ui->lineEdit->setText(str + faceFileName);
    face->hide();
}
void TCP_Client::socketStateChanged(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState) {
        // Socket 斷線，可以在這裡處理相應的邏輯
        QMessageBox::critical(nullptr, "登出", "伺服器斷線");
        on_Btn_Signout_clicked();

    }

}


void TCP_Client::Receive_Chat(MyPacket packet)
{
    if (packet.body.massageData.m_errorcode == Errorcode_OK) {

        QString Account = packet.body.massageData.m_Account;
        QString currentDateTimeString = packet.body.massageData.m_Time.toString("yyyy-MM-dd hh:mm:ss");
        QString str = Account + " < " + currentDateTimeString + " > : \n" + packet.body.massageData.m_Data["Message"].toString() + "\n";
        ui->TB_Chat->setText(ui->TB_Chat->toPlainText()+ str);
    }
    else
    {
        QMessageBox::critical(nullptr, "聊天錯誤", "未知ErrorCode");
    }
}
void TCP_Client::Receive_LoginInit(MyPacket packet)
{
    if (packet.body.massageData.m_errorcode == Errorcode_OK) {
        QJsonArray userListArray = packet.body.massageData.m_Data["UserList"].toArray();
        int row = ui->tableWidget_User->rowCount();
        ui->tableWidget_User->setRowCount(row + userListArray.size());

        foreach(const QJsonValue & userValue, userListArray) {

            QTableWidgetItem* Item = new QTableWidgetItem(userValue.toString());
            ui->tableWidget_User->setItem(row++, 0, Item);
        }
    }
    else
    {
        QMessageBox::critical(nullptr, "玩家清單錯誤", "未知ErrorCode");
    }

    //char32_t  t[] = { 0x1F601,0x0 };	//加上0x00是为了防止表情后面跟随乱码

    //for (char32_t i = 0x1F601; i <= 0x1F64F; ++i)
    //{
    //    t[0] = i;
    //    ui->TB_Chat->insertPlainText(QString::fromUcs4(t));
    //}
}

void TCP_Client::Send_Packet(QByteArray& Packet)
{
    // @加密
    // 加密後傳輸
    m_socket->write(Common::Encryption_byXOR(Packet, XOR_KEY));
}
void TCP_Client::Send_Chat()
{
    QString str = ui->lineEdit->text();
    if (str == "") return;

    MassageData p_massagedata;
    p_massagedata.m_Account = Local_User.m_Account;
    p_massagedata.m_Data["Message"] = str;
    p_massagedata.m_errorcode = Errorcode_OK;
    p_massagedata.m_Time = QDateTime::currentDateTime();
    QByteArray Bytes;
    Bytes = MyPacket(m_Setting.Version, "MAIN_C_S_CHAT", MAIN_C_S_CHAT, p_massagedata).toQByteArray();
    Send_Packet(Bytes);
    ui->lineEdit->clear();
}
void TCP_Client::Send_LoginInit()
{
    MassageData p_massagedata;
    p_massagedata.m_Account = Local_User.m_Account;
    p_massagedata.m_errorcode = Errorcode_OK;
    p_massagedata.m_Time = QDateTime::currentDateTime();

    QByteArray Bytes;
    Bytes = MyPacket(m_Setting.Version, "MAIN_C_S_LOGININIT", MAIN_C_S_LOGININIT, p_massagedata).toQByteArray();
    Send_Packet(Bytes);
}


