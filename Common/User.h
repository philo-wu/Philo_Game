#pragma once

#include <QString>
#include <QDataStream>
#include <QByteArray>
#include <QDateTime>




class ClientSetting
{
public:
    QString	m_IP;			//IP
    int	m_Port;			    //端口
    QString	m_User;			//使用者名稱
    QDateTime	m_LoginTime;	//登入時間
    int	m_LoginSec;			//登入時長

};

class MassageData
{
public:
    QString m_User;
    QString m_Pass;
    QString m_Data;
    int m_errorcode;
    QDateTime m_Time; //訊息發送時間
    
    // 將 MassageData 序列化到資料流
    friend QDataStream& operator<<(QDataStream& out, const MassageData& data) {
        out << data.m_User << data.m_Pass << data.m_Data << data.m_errorcode << data.m_Time;
        return out;
    }

    // 從資料流中反序列化 MassageData
    friend QDataStream& operator>>(QDataStream& in, MassageData& data) {
        in >> data.m_User >> data.m_Pass >> data.m_Data >> data.m_errorcode >> data.m_Time;
        return in;
    }
};
enum Command {
    MAIN_C_S_LOGIN = 1,        // 登入
    MAIN_S_C_LOGIN = 2,        // 登入回應
    MAIN_C_S_ACTION = 3,       // player action
    MAIN_S_C_ACTION = 4,
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
    quint32 command; // 指令
    MassageData massageData; // 包含指令相關資料的類別

    // 添加其他成員資料...

private:
};
