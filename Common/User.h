#pragma once

#include <QString>
#include <QDataStream>
#include <QByteArray>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


class role
{
    int HP;
    //int MP;
    int ATK;
    int DEF;
};

class ConnectionSetting
{
public:
    QString	    m_IP;			//IP
    int	        m_Port = 0;			    //端口
    //QString	    m_User;			//使用者名稱
    QDateTime	m_LoginTime;	//登入時間
    int	        m_LoginSec = -1;	    //登入時長

    void Reset() {
        m_IP = "";
        m_Port = 0;
        m_LoginTime.setMSecsSinceEpoch(-1);
        m_LoginSec = -1;
    }
};
class User
{
public:
    QString	m_Account;
    //QString	m_Pass; //密碼不應該被握住
    QString	m_Permissions;
    bool Online = 0;
    ConnectionSetting m_setting;
    //role m_role;
    bool operator==(const User& other) const {
        return m_Account == other.m_Account;
    }

};


enum Command {
    MAIN_S_C_PAUSE      ,
    MAIN_C_S_LOGIN      ,        // 登入
    MAIN_S_C_LOGIN      ,        
    MAIN_C_S_CHAT       ,        // 聊天行為
    MAIN_S_C_CHAT       ,
    MAIN_C_S_SINGUP     ,        // 註冊帳號
    MAIN_S_C_SINGUP     ,
    MAIN_C_S_LOGININIT  ,        // 在線清單
    MAIN_S_C_LOGININIT  

};
enum Errorcode {
    Errorcode_OK,                   // 成功
    Errorcode_UNKNOW,               // 成功
    Errorcode_ACCOUNT_NOTEXIST,     // 登入回應
    Errorcode_ACCOUNT_EXIST,
    Errorcode_PASSWORD_ERROR,
    Errorcode_REPEAT_LOGIN
};
class MassageData
{
public:
    QString m_Account;
    //QString m_Pass;
    QJsonObject m_Data;
    Errorcode m_errorcode;
    QDateTime m_Time; //訊息發送時間
    
    // Json取代
    /*
    // 將 MassageData 序列化到資料流
    friend QDataStream& operator<<(QDataStream& out, const MassageData& data) {
        out << data.m_Account << data.m_Pass << data.m_Data << data.m_errorcode << data.m_Time;
        return out;
    }

    // 從資料流中反序列化 MassageData
    friend QDataStream& operator>>(QDataStream& in, MassageData& data) {
        in >> data.m_Account >> data.m_Pass >> data.m_Data >> data.m_errorcode >> data.m_Time;
        return in;
    } 
    */
        // 將 MyPacket 轉換成 QJsonObject
    QJsonObject toJsonObject() const {
        QJsonObject obj;
        obj["Account"] = m_Account;
        obj["Data"] = m_Data;
        obj["ErrorCode"] = static_cast<int>(m_errorcode);
        obj["Time"] = m_Time.toString(Qt::ISODate);
        return obj;
    }

    // 從 QJsonObject 中反序列化 MassageData
    void fromJsonObject(const QJsonObject& obj) {
        m_Account = obj["Account"].toString();
        m_Data = obj["Data"].toObject();
        m_errorcode = static_cast<Errorcode>(obj["ErrorCode"].toInt());
        m_Time = QDateTime::fromString(obj["Time"].toString(), Qt::ISODate);
    }
};

class MyPacket
{
public:


    MyPacket() : command(0) {}

    Command getCommand() const {
        return static_cast<Command>(command);
    }

    void setCommand(Command cmd) {
        command = static_cast<quint32>(cmd);
    }
    /*
    QByteArray serialize() const {
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        stream << command << massageData;
        return byteArray;
    }

    void deserialize(const QByteArray& byteArray) {
        QDataStream stream(byteArray);
        stream >> command >> massageData;
    }
    */
    quint32 command; // 指令
    MassageData massageData; // 包含指令相關資料的類別

    // 添加其他成員資料...
    QJsonObject toJsonObject() const {
        QJsonObject obj;
        obj["Command"] = static_cast<int>(getCommand());
        obj["MassageData"] = massageData.toJsonObject();
        return obj;
    }

    // 從 QJsonObject 中反序列化 MyPacket
    void fromJsonObject(const QJsonObject& obj) {
        setCommand(static_cast<Command>(obj["Command"].toInt()));
        massageData.fromJsonObject(obj["MassageData"].toObject());
    }
private:
};
