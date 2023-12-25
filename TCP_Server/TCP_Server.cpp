#include "TCP_Server.h"
const QByteArray MyPacket::PACKET_SEPARATOR = "\/\/";

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
    LoadDataBase("/data/database.json" , Account_DataBase);

    Load_Setting();

    //eventThread = new QThread();
    //eventManager = new EventManager();

    //// 將事件管理器移動到事件線程
    //eventManager->moveToThread(eventThread);
    //// 連接事件線程的啟動信號
    //connect(eventThread, &QThread::started, eventManager, &EventManager::processEvents);
    //// 啟動事件線程
    //eventThread->start();
    m_server = new QTcpServer(this);
    ET = new EventThread();
    MUD = new MUD_Engine();
    ET->start();
    connect(ET, &EventThread::writeDataToSocket, this, [=](QTcpSocket* socket ,QByteArray packet) {
        Send_Packet(socket, packet);
        });
    connect(this, SIGNAL(SendFinish()), ET, SLOT(ThreadFinish()));  //

}
TCP_Server::~TCP_Server()
{
    delete UM;
    delete MUD;
    ET->exit();
    //delete ET; //使用exit();

    //  @dalete
    //delete timer;     //當TCP_Servere關閉時會自動delete (父類關閉)
    //delete m_server;  //當TCP_Servere關閉時會自動delete (父類關閉)

}
void TCP_Server::update()
{
    // 更新在線時間
    foreach(User p_user, UM->Get_Users()) {
        qDebug() << " 帳戶 : " << (p_user.m_Account);
        qDebug() << " timeout : " << QString::number(p_user.m_Player->Get_playstate());

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
void TCP_Server::LoadDataBase(QString fileName, QJsonDocument& jsonDocument)
{

    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = appDir + fileName;
    jsonDocument = Common::readJsonFile(filePath);
    if (jsonDocument.isArray()) {
        // 取得 JSON 陣列
        QJsonArray jsonArray = jsonDocument.array();
        // 在這裡進行讀取和修改操作
        for (int row = 0; row < jsonArray.size(); ++row) {
            QJsonObject jsonObject = jsonArray[row].toObject();

            // 讀取資料，例如：
            User p_user;
            p_user.m_Account = jsonObject["Account"].toString();
            p_user.player_Update(jsonObject["Player"].toObject());

            if (!UM->User_Add(p_user))
                QMessageBox::critical(nullptr, "系統錯誤", "Error : LoadDataBase\nUser_Add失敗");
        }
    }
}
void TCP_Server::SaveDataBase(QString fileName, QJsonDocument& jsonDocument)
{
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = appDir + fileName;

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << jsonDocument.toJson(QJsonDocument::Indented);
        file.close();
    }
    else
    {
        QMessageBox::critical(nullptr, "系統錯誤", "錯誤: SaveDataBase\n無法打開檔案");
    }
}
void TCP_Server::SavePlayer(User& user)
{
    QJsonDocument jsonDocument;
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = appDir + ("/data/database.json");
    jsonDocument = Common::readJsonFile(filePath);
    QJsonArray jsonArray = jsonDocument.array();

    // 尋找特定帳戶
    for (int i = 0; i < jsonArray.size(); ++i)
    {
        QJsonObject jsonObject = jsonArray[i].toObject();
        if (jsonObject["Account"].toString() == user.m_Account)
        {
            // 更新其他資料
            QJsonObject Player;
            Player["NAME"] = user.m_Account;
            Player["HP"] = user.m_Player->Get_HP();
            Player["MP"] = user.m_Player->Get_MP();
            Player["HPMAX"] = user.m_Player->Get_HPMAX();
            Player["MPMAX"] = user.m_Player->Get_MPMAX();
            Player["ATK"] = user.m_Player->Get_ATK();
            Player["DEF"] = user.m_Player->Get_DEF();
            Player["LV"] = user.m_Player->Get_LV();
            Player["EXP"] = user.m_Player->Get_EXP();
            Player["UID"] = user.m_Player->Get_UID();
            Player["Money"] = user.m_Player->Get_Money();
            Player["playstate"] = user.m_Player->Get_playstate();

            QJsonObject Position;
            Position["X"] = user.m_Player->Get_Position().x();
            Position["Y"] = user.m_Player->Get_Position().y();
            Player["Position"] = Position;

            jsonObject["Player"] = Player;
            jsonArray[i] = jsonObject;
            break;
        }
    }
    // 保存資料庫
    jsonDocument = QJsonDocument(jsonArray);
    SaveDataBase("/data/database.json", jsonDocument);

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

    m_server->listen(QHostAddress::Any, ui->LE_Servar_Port->text().toInt());
    connect(m_server, SIGNAL(newConnection()), this, SLOT(slot_newConnection()));  //
}
void TCP_Server::stopServer()
{
    if (m_server->isListening()) {
        m_server->close();
    }
    foreach(User p_user, UM->Get_Users()) {
        QJsonObject userObject;
        if (p_user.isOnline())
        {
            p_user.SetOnline(0);
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
        QJsonObject Player;
        Player["NAME"] = Data.m_Account;
        Player["HP"] = 100;
        Player["MP"] = 100;
        Player["HPMAX"] = 100;
        Player["MPMAX"] = 100;
        Player["ATK"] = 1;
        Player["DEF"] = 1;
        Player["LV"] = 1;
        Player["EXP"] = 0;
        Player["UID"] = MUD->UID_Table.GetPlayUID();
        Player["Money"] = 0;
        Player["playstate"] = Player_Idle;
        QJsonObject Position;
        Position["X"] = 9;
        Position["Y"] = 2;
        Player["Position"] = Position;
        newData["Player"] = Player;

        jsonArray.append(newData);
        jsonDocument = QJsonDocument(jsonArray);
        Common::writeJsonFile(filePath, jsonDocument);

        User p_User;
        p_User.m_Account = Data.m_Account;

        if (!UM->User_Add(p_User))
            QMessageBox::critical(nullptr, "系統錯誤", "Error : LoadDataBase\nUser_Add失敗");
        Log("創建帳號成功 Account: " + Data.m_Account);
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
    default:
    break;
    }
}
void TCP_Server::updateUserList()
{
    int row = 0;
    ui->tableWidget_User->setRowCount(UM->Get_Users().size());
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
        if (p_user.isOnline())
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
        p_user.SetOnline(0);
        p_user.m_setting.Reset();
        UM->User_Add(p_user);
        MUD->player_logout(p_user.m_Player);

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
    
    //if (0)
    //{
    //    MassageData p_massagedata;
    //    p_massagedata.m_Time = QDateTime::currentDateTime();

    //    auto head = Packet_head(m_Setting.Version, "MAIN_S_C_PAUSE");
    //    auto body = Packet_body(MAIN_S_C_PAUSE, p_massagedata);
    //    MyPacket receivedPacket(head, body);
    //    QByteArray Bytes = receivedPacket.toQByteArray();
    //    socket->write(Common::Encryption_byXOR(Bytes, XOR_KEY));
    //    return;
    //}

    //MyPacket Packet(Common::Encryption_byXOR(socket->readAll(), XOR_KEY));
    QByteArray Bytes = Common::Encryption_byXOR(socket->readAll(), XOR_KEY);
    const char* split = MyPacket::PACKET_SEPARATOR;
    QList<QByteArray> packets = Bytes.split(*split);

    for (const QByteArray& packetData : packets) {
        if (!packetData.isEmpty()) {
            MyPacket Packet(packetData);
            switch (Packet.getCommand()) {
            case MAIN_C_S_LOGIN: {
                Server_to_Client(MAIN_S_C_LOGIN, socket, Packet);
                break;
            }
            case MAIN_C_S_CHAT: {
                Server_to_Client(MAIN_S_C_CHAT, socket, Packet);
                break;
            }
            case MAIN_C_S_SINGUP: {
                Server_to_Client(MAIN_S_C_SINGUP, socket, Packet);
                break;
            }
            case MAIN_C_S_LOGININIT: {
                Server_to_Client(MAIN_S_C_LOGININIT, socket, Packet);
                break;
            }
            case MAIN_C_S_GAMEING: {
                Server_to_Client(MAIN_S_C_GAMEING, socket, Packet);
            }
                                 break;
            case MAIN_C_S_ROLEINFO: {
                Server_to_Client(MAIN_S_C_ROLEINFO, socket, Packet);
            }
                                  break;
            default:
                break;
            }
        }
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
    case MAIN_S_C_GAMEING: {
        Send_MudGame(socket, Packet);
    }
        break;
    case MAIN_S_C_ROLEINFO: {
        Send_RoleInfo(socket, Packet);
    }
        break;

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
            if (p_user.isOnline())
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
                p_user.SetOnline(1);

                p_setting.m_IP = ipv4String;
                p_setting.m_Port = socket->peerPort();
                p_setting.m_LoginTime = Packet.body.massageData.m_Time;
                p_setting.m_LoginSec = 0;
                UM->User_UpdateConnection(p_user, p_setting);
                MUD->player_login(p_user.m_Player);

                UserTotal += 1;
                ui->LE_Servar_UserTotal->setText(QString::number(UserTotal));
                Log("玩家登入 Account: " + p_user.m_Account);
            }
        }
        else
        {
            Log("玩家角色不存在 Account: " + p_user.m_Account);
        }
    }


    MassageData p_massagedata;
    p_massagedata.m_Account = Packet.body.massageData.m_Account;
    p_massagedata.m_errorcode = errorcode;
    p_massagedata.m_Time = QDateTime::currentDateTime();

    // @新封包格式 實際應用
    QByteArray Bytes;
    Bytes = MyPacket(m_Setting.Version, "MAIN_S_C_LOGIN", MAIN_S_C_LOGIN, p_massagedata).toQByteArray();
    // @緩衝區 實際應用
    ET->addEvent(socket, Bytes);

}
void TCP_Server::Send_Chat(QTcpSocket* socket , MyPacket Packet)
{
    MassageData p_massagedata = Packet.body.massageData;;

    QByteArray Bytes;
    Bytes = MyPacket(m_Setting.Version, "MAIN_S_C_CHAT", MAIN_S_C_CHAT, p_massagedata).toQByteArray();

    for (int i = 0; i < m_sockets.size(); i++)
    {
        //socket->write(Common::Encryption_byXOR(Bytes, XOR_KEY));
        //QMetaObject::invokeMethod(eventManager, "addEvent", Qt::QueuedConnection,
        //    Q_ARG(QByteArray, Bytes), Q_ARG(QTcpSocket*, socket));
        ET->addEvent(m_sockets[i], Bytes);
    }
}
void TCP_Server::Send_Singup(QTcpSocket* socket , MyPacket Packet)
{
    Errorcode errorcode = Common::doesUserExist(Packet.body.massageData.m_Account, Account_DataBase);
    if (errorcode == Errorcode_OK)
        SingUp("/data/database.json", Account_DataBase, Packet.body.massageData);

    MassageData p_massagedata;
    p_massagedata.m_errorcode = errorcode;
    p_massagedata.m_Time = QDateTime::currentDateTime();

    QByteArray Bytes;
    Bytes = MyPacket(m_Setting.Version, "MAIN_S_C_SINGUP", MAIN_S_C_SINGUP, p_massagedata).toQByteArray();
    ET->addEvent(socket, Bytes);
}
void TCP_Server::Send_LoginInit(QTcpSocket* socket)
{
    QJsonArray jsonArray;
    foreach(User p_user, UM->Get_Users()) {
        QJsonObject userObject;
        if(p_user.isOnline())
            jsonArray.append(p_user.m_Account);
    }


    MassageData p_massagedata;
    p_massagedata.m_Data["ServerName"] = Server_Name;
    p_massagedata.m_Data["UserList"] = jsonArray;
    p_massagedata.m_errorcode = Errorcode_OK;
    p_massagedata.m_Time = QDateTime::currentDateTime();

    QByteArray Bytes;
    Bytes = MyPacket(m_Setting.Version, "MAIN_S_C_LOGININIT", MAIN_S_C_LOGININIT, p_massagedata).toQByteArray();
    ET->addEvent(socket, Bytes);

}

void TCP_Server::Send_MudGame(QTcpSocket* socket, MyPacket Packet)
{
    User p_user;
    UM->User_find(Packet.body.massageData.m_Account, p_user);

    int Command = Packet.body.massageData.m_Data["Command"].toString().toInt();
    //若有玩家指令才執行
    if (Command != -1)
    {
        qDebug() << " play : " << QString::number(p_user.m_Player->Get_playstate());
        MassageData p_massagedata1;
        MUD->play(p_massagedata1, p_user.m_Player, Command);
        qDebug() << " played : " << QString::number(p_user.m_Player->Get_playstate());
        QByteArray Bytes1;
        Bytes1 = MyPacket(m_Setting.Version, "MAIN_S_C_GAMEING", MAIN_S_C_GAMEING, p_massagedata1).toQByteArray();
        ET->addEvent(socket, Bytes1);
        UM->User_Add(p_user); //更新熱資料
        qDebug() << " Save : " << QString::number(p_user.m_Player->Get_playstate());

        SavePlayer(p_user); //更新DataBase
        Send_RoleInfo(socket, Packet);
        qDebug() << " Saved : " << QString::number(p_user.m_Player->Get_playstate());

    }
    //發送場景訊息
    MassageData p_massagedata;
    qDebug() << " Scenes_Info : " << QString::number(p_user.m_Player->Get_playstate());
    MUD->Scenes_Info(p_massagedata,p_user.m_Player, Command);
    qDebug() << " Scenes_Infoed : " << QString::number(p_user.m_Player->Get_playstate());

    QByteArray Bytes;
    Bytes = MyPacket(m_Setting.Version, "MAIN_S_C_GAMEING", MAIN_S_C_GAMEING, p_massagedata).toQByteArray();

    ET->addEvent(socket, Bytes);
}
void TCP_Server::Send_RoleInfo(QTcpSocket* socket, MyPacket Packet)
{
    User p_user;
    UM->User_find(Packet.body.massageData.m_Account, p_user);
    QJsonObject RoleInfo;
    RoleInfo["NAME"] = p_user.m_Player->Get_NAME();
    RoleInfo["HP"] = QString::number(p_user.m_Player->Get_HP());
    RoleInfo["MP"] = QString::number(p_user.m_Player->Get_MP());
    RoleInfo["HPMAX"] = QString::number(p_user.m_Player->Get_HPMAX());
    RoleInfo["MPMAX"] = QString::number(p_user.m_Player->Get_MPMAX());
    RoleInfo["ATK"] = QString::number(p_user.m_Player->Get_ATK());
    RoleInfo["DEF"] = QString::number(p_user.m_Player->Get_DEF());
    RoleInfo["LV"] = QString::number(p_user.m_Player->Get_LV());
    RoleInfo["EXP"] = QString::number(p_user.m_Player->Get_EXP());
    RoleInfo["Money"] = QString::number(p_user.m_Player->Get_Money());
    // 不提供玩家當前座標資訊
    //QJsonObject Position;
    //Position["X"] = QString::number(p_user.m_Player->Get_Position().x());
    //Position["Y"] = QString::number(p_user.m_Player->Get_Position().y());
    //RoleInfo["Position"] = Position;

    MassageData p_massagedata;
    p_massagedata.m_Data["ServerName"] = Server_Name;
    p_massagedata.m_Data["RoleInfo"] = RoleInfo;
    p_massagedata.m_errorcode = Errorcode_OK;
    p_massagedata.m_Time = QDateTime::currentDateTime();

    QByteArray Bytes;
    Bytes = MyPacket(m_Setting.Version, "MAIN_S_C_ROLEINFO", MAIN_S_C_ROLEINFO, p_massagedata).toQByteArray();
    ET->addEvent(socket, Bytes);
}

// @緩衝區  通知MainThread處理事件
void TCP_Server::Send_Packet(QTcpSocket* socket, QByteArray Packet)
{
    // @加密
    // 加密後傳輸
    // @多緒Locker
    QMutex mutex;
    {
        QMutexLocker locker(&mutex);
        socket->write(Common::Encryption_byXOR(Packet, XOR_KEY));
        //socket->write(Packet);
        emit SendFinish();
    }
}
