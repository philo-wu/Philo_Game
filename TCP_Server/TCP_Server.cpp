#include "TCP_Server.h"

TCP_Server::TCP_Server(QWidget *parent): 
    QMainWindow(parent),
    ui(new Ui::TCP_ServerClass())

{
    ui->setupUi(this);
    UM = new UserManager();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&TCP_Server::update));
    timer->start(1000);

    ui->tableWidget_log->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget_log->setRowCount(0);
    loadDataBase("/database.json" , Account_DataBase);
    Load_Setting();
}
TCP_Server::~TCP_Server()
{

}
void TCP_Server::update()
{
    // 更新在線時間
    foreach(User p_user, UM->Get_Users()) {
        if (p_user.m_setting.m_LoginSec!=-1)
        {
            p_user.m_setting.m_LoginSec += 1;
            UM->User_Add(p_user);
        }
    }
    if (Server_State == SERVER_START)
    {
        m_Setting.m_LoginSec += 1;
        ui->LE_Servar_Sec->setText(QString::number(m_Setting.m_LoginSec));
    }
    updateUserList();
}

void TCP_Server::Load_Setting()
{
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = appDir + "/Setting.ini";
    QSettings settings(filePath, QSettings::IniFormat);
    ui->LE_Servar_Name->setText(settings.value("Server_Name", "ChatRoom").toString());
    ui->LE_Servar_Port->setText(settings.value("Server_Port", 19999).toString());
    Server_Name = ui->LE_Servar_Name->text();
    m_Setting.m_Port = ui->LE_Servar_Port->text().toInt();
    m_Setting.SetVersion();
}
void TCP_Server::Save_Setting()
{
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = appDir + "/Setting.ini";
    QSettings settings(filePath, QSettings::IniFormat);
    settings.setValue("Server_Name", ui->LE_Servar_Name->text());
    settings.setValue("Server_Port", ui->LE_Servar_Port->text());
    settings.setValue("Version", m_Setting.Version);
    Server_Name = ui->LE_Servar_Name->text();
    m_Setting.m_Port = ui->LE_Servar_Port->text().toInt();
}
void TCP_Server::loadDataBase(QString fileName, QJsonDocument &jsonDocument)
{
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = appDir + fileName;
    jsonDocument = Common::readJsonFile(filePath);
    if (Account_DataBase.isArray()) {
        // 取得 JSON 陣列
        QJsonArray jsonArray = Account_DataBase.array();
        ui->tableWidget_User->setRowCount(jsonArray.size());
        // 在這裡進行讀取和修改操作
        for (int row = 0; row < jsonArray.size(); ++row) {
            QJsonObject jsonObject = jsonArray[row].toObject();

            // 讀取資料，例如：
            User p_User;
            p_User.m_Account = jsonObject["Account"].toString();

            if (!UM->User_Add(p_User))
                QMessageBox::critical(nullptr, "系統錯誤", "Error : loadDataBase\nUser_Add失敗");
        }
    }
}

void TCP_Server::startServer()
{
    Save_Setting();
    UserTotal = 0;
    ui->LE_Servar_UserTotal->setText(QString::number(UserTotal));

    Server_State = SERVER_START;

    m_Setting.m_IP = QHostAddress(QHostAddress::LocalHost).toString();
    m_Setting.m_Port = ui->LE_Servar_Port->text().toInt();
    m_Setting.m_LoginSec = 0;

    ui->LE_Servar_Name->setText(Server_Name);
    ui->LE_Servar_IP->setText(m_Setting.m_IP);
    ui->LE_Servar_Port->setText(QString::number(m_Setting.m_Port));

    m_server = new QTcpServer(this);
    m_server->listen(QHostAddress::Any, ui->LE_Servar_Port->text().toInt());
    connect(m_server, SIGNAL(newConnection()), this, SLOT(slot_newConnection()));  //
}
void TCP_Server::stopServer()
{
    if (m_server->isListening()) {
        m_server->close();
        m_server->deleteLater();
    }
    foreach(User p_user, UM->Get_Users()) {
        QJsonObject userObject;
        if (p_user.Online)
        {
            p_user.Online = 0;
            UM->User_UpdateConnection(p_user, p_user.m_setting);
        }
    }

}
void TCP_Server::SingUp(QString fileName, QJsonDocument& jsonDocument,MassageData Data)
{
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = appDir + fileName;
    if (jsonDocument.isArray()) {
        // 取得 JSON 陣列
        QJsonArray jsonArray = jsonDocument.array();
        ui->tableWidget_User->setRowCount(jsonArray.size());
        // 在這裡進行讀取和修改操作
        QJsonObject newData;
        newData["Account"] = Data.m_Account;
        newData["Pass"] = Data.m_Data["Pass"].toString();
        newData["Permissions"] = "member";
        jsonArray.append(newData);
        jsonDocument = QJsonDocument(jsonArray);
        Common::writeJsonFile(filePath, jsonDocument);
    }
    updateUserList();
}
void TCP_Server::Log(QString log)
{
    int row = ui->tableWidget_log->rowCount();
    ui->tableWidget_log->setRowCount(1 + row);

    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    QTableWidgetItem* Item = new QTableWidgetItem(time);
    ui->tableWidget_log->setItem(row, 0, Item);
    Item = new QTableWidgetItem(log);
    ui->tableWidget_log->setItem(row, 1, Item);

}


void TCP_Server::on_Btn_Start_clicked()
{
    switch (Server_State)
    {
    case SERVER_START:
    {
        stopServer();
        Server_State = SERVER_STOP;
        ui->Btn_Start->setText("啟動伺服器");
        ui->Btn_Pause->setEnabled(false);
        ui->LE_Servar_Name->setStyleSheet(m_CSS.Write_EditLine);
        ui->LE_Servar_Port->setStyleSheet(m_CSS.Write_EditLine);
        ui->LE_Servar_Name->setReadOnly(false);
        ui->LE_Servar_Port->setReadOnly(false);
        Log("伺服器停止");

    }
    break;
    case SERVER_STOP:
    {
        startServer();
        ui->Btn_Start->setText("停止伺服器");
        ui->Btn_Pause->setEnabled(true);
        ui->LE_Servar_Name->setStyleSheet(m_CSS.OnlyRead_EditLine);
        ui->LE_Servar_Port->setStyleSheet(m_CSS.OnlyRead_EditLine);
        ui->LE_Servar_Name->setReadOnly(true);
        ui->LE_Servar_Port->setReadOnly(true);
        Log("伺服器啟動");

    }
    break;
    case SERVER_PAUSE:
    {
        Server_State = SERVER_STOP;
        ui->Btn_Start->setText("啟動伺服器");
        ui->Btn_Pause->setText("伺服器暫停");
        ui->Btn_Pause->setEnabled(false);
        ui->LE_Servar_Name->setStyleSheet(m_CSS.Write_EditLine);
        ui->LE_Servar_Port->setStyleSheet(m_CSS.Write_EditLine);
        ui->LE_Servar_Name->setReadOnly(false);
        ui->LE_Servar_Port->setReadOnly(false);
        Log("伺服器停止");

    }
    break;
    default:
    break;
    }
    updateServerState();
}
void TCP_Server::on_Btn_Pause_clicked()
{
    switch (Server_State)
    {
    case SERVER_START:
    {
        Server_State = SERVER_PAUSE;
        ui->Btn_Pause->setText("伺服器繼續");
        Log("伺服器繼續");

    }
    break;
    case SERVER_STOP:
    {

    }
    break;
    case SERVER_PAUSE:
    {
        Server_State = SERVER_START;
        ui->Btn_Pause->setText("伺服器暫停");
        Log("伺服器暫停");

    }
    break;
    default:
    break;
    }
    updateServerState();
}

void TCP_Server::updateServerState()
{
    switch (Server_State)
    {
    case SERVER_START:
    {
        ui->LE_Servar_State->setText("運行中");
        ui->LE_Servar_State->setStyleSheet(m_CSS.ServerState_Start);
    }
    break;
    case SERVER_STOP:
    {
        ui->LE_Servar_State->setText("未啟動");
        ui->LE_Servar_State->setStyleSheet(m_CSS.ServerState_Stop);

    }
    break;
    case SERVER_PAUSE:
    {
        ui->LE_Servar_State->setText("暫停");
        ui->LE_Servar_State->setStyleSheet(m_CSS.ServerState_Pause);
    }
    break;
    default:
    break;
    }
}
void TCP_Server::updateUserList()
{
    int row = 0;
    foreach(User p_user, UM->Get_Users()) {
        QTableWidgetItem* Item = new QTableWidgetItem(p_user.m_Account);
        ui->tableWidget_User->setItem(row, 0, Item);
        Item = new QTableWidgetItem(p_user.m_setting.m_IP);
        ui->tableWidget_User->setItem(row, 1, Item);
        if (p_user.m_setting.m_Port != 0)
            Item = new QTableWidgetItem(QString::number(p_user.m_setting.m_Port));
        else
            Item = new QTableWidgetItem("");
        ui->tableWidget_User->setItem(row, 2, Item);
        if (p_user.Online)
            Item = new QTableWidgetItem(p_user.m_setting.m_LoginTime.toString("yyyy-MM-dd hh:mm:ss"));
        else
            Item = new QTableWidgetItem("");
        ui->tableWidget_User->setItem(row, 3, Item);
        if (p_user.m_setting.m_LoginSec != -1)
            Item = new QTableWidgetItem(QString::number(p_user.m_setting.m_LoginSec));
        else
            Item = new QTableWidgetItem("");
        ui->tableWidget_User->setItem(row, 4, Item);
        ++row;
    }

    
}
void TCP_Server::slot_newConnection()
{
    QTcpSocket* socket = m_server->nextPendingConnection();
    m_sockets.push_back(socket);
    connect(socket, SIGNAL(readyRead()), this, SLOT(Client_to_Server()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(slot_disConnected()));

}
void TCP_Server::slot_disConnected()
{
    // 找到斷線的套接字
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    if (socket) {
        // 從列表中移除斷線的套接字
        quint32 ipv4Address = socket->peerAddress().toIPv4Address();
        QHostAddress ipv4HostAddress;
        ipv4HostAddress.setAddress(ipv4Address);
        QString ipv4String = ipv4HostAddress.toString();
        User p_user;
        UM->User_find(ipv4String, socket->peerPort(), p_user);
        p_user.Online = 0;
        p_user.m_setting.Reset();
        UM->User_Add(p_user);
        UserTotal -= 1;
        ui->LE_Servar_UserTotal->setText(QString::number(UserTotal));
        Log("玩家登出 Account: " + p_user.m_Account);

        m_sockets.removeOne(socket);
        socket->deleteLater();  // 在下一次事件迴圈中刪除套接字

    }
}

void TCP_Server::Client_to_Server()
{
    QTcpSocket* socket = (QTcpSocket*)QObject::sender();  // 获得是哪个socket收到了消息

    if (Server_State == SERVER_PAUSE)
    {
        MassageData p_massagedata;
        p_massagedata.m_Time = QDateTime::currentDateTime();

        auto head = Packet_head(m_Setting.Version, "MAIN_S_C_PAUSE");
        auto body = Packet_body(MAIN_S_C_PAUSE, p_massagedata);
        MyPacket receivedPacket(head, body);
        socket->write(receivedPacket.XOR(XOR_KEY));
        return;
    }

    MyPacket Packet(socket->readAll(), XOR_KEY);

    switch (Packet.getCommand()){
    case MAIN_C_S_LOGIN :{
        Server_to_Client(MAIN_S_C_LOGIN, socket, Packet);
        break;
    }
    case MAIN_C_S_CHAT:{
        Server_to_Client(MAIN_S_C_CHAT, socket, Packet);
        break;
    }
    case MAIN_C_S_SINGUP: {
        Server_to_Client(MAIN_S_C_SINGUP, socket, Packet);
        break;
    }
    case MAIN_C_S_LOGININIT: {
        Server_to_Client(MAIN_S_C_LOGININIT,socket , Packet);
        break;
    }
    case MAIN_S_C_PAUSE: {
        Server_to_Client(MAIN_S_C_LOGININIT, socket, Packet);
        break;
    }
    default:
        break;
    }
}
void TCP_Server::Server_to_Client(Command command , QTcpSocket* socket , MyPacket Packet)
{
    if (Server_State != SERVER_START)
        return;

    switch (command) {
    case MAIN_S_C_LOGIN: {
        Send_Login(socket , Packet);
        break;
    }
    case MAIN_S_C_CHAT: {
        Send_Chat(socket , Packet);
        break;
    }
    case MAIN_S_C_SINGUP: {
        Send_Singup(socket , Packet);
        break;
    }
    case MAIN_S_C_LOGININIT: {
        Send_LoginInit(socket);
        break;
    }
    default:
        break;
    }
} 
void TCP_Server::Send_Login(QTcpSocket* socket , MyPacket Packet)
{
    Errorcode errorcode = Common::isUserCredentialsValid(Packet.body.massageData.m_Account, Packet.body.massageData.m_Data["Pass"].toString(), Account_DataBase);
    if (errorcode == Errorcode_OK) {
        User p_user;
        if (UM->User_find(Packet.body.massageData.m_Account, p_user))
        {
            if (p_user.Online)
            {
                errorcode = Errorcode_REPEAT_LOGIN;
            }
            else
            {
                ConnectionSetting p_setting;
                quint32 ipv4Address = socket->peerAddress().toIPv4Address();
                QHostAddress ipv4HostAddress;
                ipv4HostAddress.setAddress(ipv4Address);
                QString ipv4String = ipv4HostAddress.toString();
                p_user.Online = 1;

                p_setting.m_IP = ipv4String;
                p_setting.m_Port = socket->peerPort();
                p_setting.m_LoginTime = Packet.body.massageData.m_Time;
                p_setting.m_LoginSec = 0;
                UM->User_UpdateConnection(p_user, p_setting);
                UserTotal += 1;
                ui->LE_Servar_UserTotal->setText(QString::number(UserTotal));
                Log("玩家登入 Account: " + p_user.m_Account);
            }
        }
    }


    MassageData p_massagedata;
    p_massagedata.m_Account = Packet.body.massageData.m_Account;
    p_massagedata.m_errorcode = errorcode;
    p_massagedata.m_Time = QDateTime::currentDateTime();

    auto head = Packet_head(m_Setting.Version, "MAIN_S_C_LOGIN");
    auto body = Packet_body(MAIN_S_C_LOGIN, p_massagedata);
    MyPacket receivedPacket(head, body);
    socket->write(receivedPacket.XOR(XOR_KEY));

}
void TCP_Server::Send_Chat(QTcpSocket* socket , MyPacket Packet)
{
    MassageData p_massagedata = Packet.body.massageData;;

    auto head = Packet_head(m_Setting.Version, "MAIN_S_C_CHAT");
    auto body = Packet_body(MAIN_S_C_CHAT, p_massagedata);
    MyPacket receivedPacket(head, body);
    for (int i = 0; i < m_sockets.size(); i++)
    {
        m_sockets[i]->write(receivedPacket.XOR(XOR_KEY));
    }
}
void TCP_Server::Send_Singup(QTcpSocket* socket , MyPacket Packet)
{
    Errorcode errorcode = Common::doesUserExist(Packet.body.massageData.m_Account, Account_DataBase);
    if (errorcode == Errorcode_OK)
        SingUp("/database.json", Account_DataBase, Packet.body.massageData);


    MassageData p_massagedata;
    p_massagedata.m_errorcode = errorcode;
    p_massagedata.m_Time = QDateTime::currentDateTime();

    auto head = Packet_head(m_Setting.Version, "MAIN_S_C_SINGUP");
    auto body = Packet_body(MAIN_S_C_SINGUP, p_massagedata);
    MyPacket receivedPacket(head, body);
    socket->write(receivedPacket.XOR(XOR_KEY));
}
void TCP_Server::Send_LoginInit(QTcpSocket* socket)
{
    QJsonArray jsonArray;
    foreach(User p_user, UM->Get_Users()) {
        QJsonObject userObject;
        if(p_user.Online)
            jsonArray.append(p_user.m_Account);
    }


    MassageData p_massagedata;
    p_massagedata.m_Data["UserList"] = jsonArray;
    p_massagedata.m_errorcode = Errorcode_OK;
    p_massagedata.m_Time = QDateTime::currentDateTime();

    auto head = Packet_head(m_Setting.Version, "MAIN_S_C_LOGININIT");
    auto body = Packet_body(MAIN_S_C_LOGININIT, p_massagedata);
    MyPacket receivedPacket(head, body);
    socket->write(receivedPacket.XOR(XOR_KEY));
}