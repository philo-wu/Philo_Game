#pragma once

#include <QFile>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "User.h"
#include "CSS_style.h"


class Common
{
public:
	// return "yyyy-MM-dd hh:mm:ss"
	static QString Get_currentTime() {
		QDateTime currentDateTime = QDateTime::currentDateTime();
		QString currentDateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
		return currentDateTimeString;
	}
    static QJsonDocument  readJsonFile(QString filePath) {

        QJsonDocument jsonDocument;
        // 讀取 JSON 檔案
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Error", "Failed to open file for reading!");

            return jsonDocument;
        }

        // 讀取 JSON 內容
        QByteArray jsonData = file.readAll();
        file.close();
        jsonDocument = QJsonDocument::fromJson(jsonData);

        return jsonDocument;
    }

    static void writeJsonFile(QString filePath , QJsonDocument jsonDocument) {

        // 寫入  JSON 檔案
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for writing.";
            return;
        }

        // 寫入 JSON 內容
        //QJsonDocument modifiedJsonDocument(jsonArray);
        file.write(jsonDocument.toJson(QJsonDocument::Indented));
        file.close();
    }

    static Errorcode doesUserExist(const QString targetUser, const QJsonDocument jsonDoc) {
        if (jsonDoc.isArray()) {
            QJsonArray jsonArray = jsonDoc.array();

            for (const auto& jsonValue : jsonArray) {
                if (jsonValue.isObject()) {
                    QJsonObject jsonObject = jsonValue.toObject();

                    // 檢查 User 屬性是否存在並且與目標相符
                    if (jsonObject.contains("Account") && jsonObject["Account"].toString() == targetUser) {
                        return Errorcode_ACCOUNT_EXIST;  // 找到了目標 User
                    }
                }
            }
        }
        return Errorcode_OK;  // 找不到目標 User
    }
    static Errorcode isUserCredentialsValid(const QString inputUser, const QString inputPass, const QJsonDocument jsonDoc) {
        if (jsonDoc.isArray()) {
            QJsonArray jsonArray = jsonDoc.array();

            for (const auto& jsonValue : jsonArray) {
                if (jsonValue.isObject()) {
                    QJsonObject jsonObject = jsonValue.toObject();

                    // 檢查 User 和 Pass 屬性是否存在並且與提供的相符
                    if (jsonObject.contains("Account") && 
                        jsonObject["Account"].toString() == inputUser) {
                        if (jsonObject["Pass"].toString() == inputPass)
                            return Errorcode_OK;
                        else
                            return Errorcode_PASSWORD_ERROR;
                    }
                }
            }
        }

        return Errorcode_ACCOUNT_NOTEXIST;
    }
};

class UserManager
{
public:
    QList<User> m_Users;

    QList<User>& Get_Users() {
        return m_Users;
    }

    bool User_Add(User p_User) {
        // 檢查是否已經存在相同的 User
        int index = -1;
        for (int i = 0; i < m_Users.size(); ++i) {
            if (m_Users.at(i).m_Account == p_User.m_Account) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            // 如果存在，進行更新
            m_Users[index] = p_User;
        }
        else {
            // 如果不存在，追加到列表中
            m_Users.append(p_User);
        }

        return true;
    }
    bool User_Remove(const User p_User) {
        int index = m_Users.indexOf(p_User);
        if (index != -1) {
            m_Users.removeAt(index);
            return true;
        }
        return false;
    }

    bool User_find(QString p_account, User& p_User) {
        int index = -1;
        for (int i = 0; i < m_Users.size(); ++i) {
            if (m_Users.at(i).m_Account == p_account) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            p_User =  m_Users.at(index);
            return true;
        }
        else {
            qDebug() << "User not found in the list.";
            p_User = User();
            return false;
        }
        
    }
    bool User_find(QString p_IP, quint16 p_Port, User& p_User) {
        int index = -1;
        for (int i = 0; i < m_Users.size(); ++i) {
            if (m_Users.at(i).m_setting.m_IP == p_IP && m_Users.at(i).m_setting.m_Port == p_Port) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            p_User = m_Users.at(index);
            return true;
        }
        else {
            qDebug() << "User not found in the list.";
            p_User = User();
            return false;
        }
    }

    bool User_UpdateConnection(User& p_User,ConnectionSetting p_setting) {
        int index = m_Users.indexOf(p_User);
        if (index != -1) {
            p_User.m_setting = p_setting;
            m_Users[index] = p_User;
            return true;
        }
        return false;
    }

};