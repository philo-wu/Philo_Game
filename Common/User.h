#pragma once

#include <QString>
#include <QDataStream>
#include <QByteArray>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextCodec>

#include "framework.h"

class role
{
public:
    int HP;
    //int MP;
    int ATK;
    int DEF;
};
class DeviceSetting
{
public:
    QString	    m_IP;			    //IP
    int	        m_Port = 0;			//端口
    QDateTime	m_LoginTime;	    //登入時間
    int	        m_LoginSec = -1;	//登入時長
    QString     Version;
    // @版本號
    void SetVersion()
    {
        Version = QString::number(MAJOR_VERSION) + "." + QString::number(MINOR_VERSION) + "." + QString::number(PATCH_VERSION);
    }
};
class ConnectionSetting
{
public:
    QString	    m_IP;			    //IP
    int	        m_Port = 0;			//端口
    //QString	    m_User;			//使用者名稱
    QDateTime	m_LoginTime;	    //登入時間
    int	        m_LoginSec = -1;	//登入時長

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
};

class Packet_head
{
public:
    Packet_head() { ; } //空建構用於接收資料
    Packet_head(QString p_version, QString p_protocol)
        : Version(p_version), Protocol(p_protocol)
    {} //非空建構用於發送資料
private:
    QString Version;
    QString Protocol;
public:
    QJsonObject toJsonObject() const {
        QJsonObject obj;
        obj["Version"] = Version;
        obj["Protocol"] = Protocol;
        return obj;
    }
    void fromJsonObject(const QJsonObject& obj) {
        Version = obj["Version"].toString();
        Protocol = obj["Protocol"].toString();
    }
};
class Packet_body
{
public:
    Packet_body() { ; } //空建構用於接收資料
    Packet_body(quint32 p_command, MassageData p_massagedata)
        : command(p_command), massageData(p_massagedata)
    {} //非空建構用於發送資料
    quint32 command = 0; // 指令
    MassageData massageData; // 包含指令相關資料的類別
public:
    Command getCommand() const {
        return static_cast<Command>(command);
    }
    void setCommand(Command cmd) {
        command = static_cast<quint32>(cmd);
    }
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

};
// @新封包格式
class MyPacket
{
public:
    // @加解密
    MyPacket(Packet_head p_head, Packet_body p_body)
        : head(p_head), body(p_body)
    {}
    MyPacket(QByteArray bs)
        : head(), body()
    {
        QJsonDocument receivedJsonDoc = QJsonDocument::fromJson(bs);
        if (!receivedJsonDoc.isNull())
            fromJsonObject(receivedJsonDoc.object());
    }
    Packet_head head;
    Packet_body body;
public:
    Command getCommand() const {
        return static_cast<Command>(body.getCommand());
    }
    QJsonObject toJsonObject() const {
        QJsonObject obj;
        obj["body"] = body.toJsonObject();
        obj["head"] = head.toJsonObject();
        return obj;

    }
    void fromJsonObject(const QJsonObject& obj) {
        head.fromJsonObject(obj["head"].toObject());
        body.fromJsonObject(obj["body"].toObject());
    }

    QByteArray toQByteArray()
    {
        QJsonDocument jsonDoc(toJsonObject());
        QByteArray bs = jsonDoc.toJson();
        return bs;
    }

};
