#pragma once
#include "Common.h"
#include "MapManager.h"

#define PLAYER_UID_START	1
#define PLAYER_UID_END	    10000
#define MONSTER_UID_START	10001
#define MONSTER_UID_END		20000

class UIDTable
{
public:
    // 獲取特定等級的經驗值
    int GetPlayUID()
    {
        ++Play_UID;
        jsonObject["Play_UID"] = Play_UID;
        saveJson();
        return Play_UID;
    }
    int GetMonsterUID()
    {
        ++Monster_UID;
        jsonObject["Monster_UID"] = Monster_UID;
        saveJson();
        return Monster_UID;
    }
    void parseTable(QString fileName)
    {
        QString appDir = QCoreApplication::applicationDirPath();
        filePath = appDir + fileName;
        jsonObject = Common::readJsonFile(filePath).object();

        Play_UID    = jsonObject["Play_UID"].toInt();
        Monster_UID = jsonObject["Monster_UID"].toInt();
    }
    void saveJson()
    {
        QJsonDocument jsonDocument = QJsonDocument(jsonObject);
        Common::writeJsonFile(filePath, jsonDocument);
    }
private:
    QJsonObject jsonObject;
    QString filePath;
    QMap<int, int> Monster_EXPTable;
    QMap<int, int> Monster_MoneyTable;
    int Play_UID;
    int Monster_UID;
};
class MonsterTable
{
public:
    // 獲取特定等級的經驗值
    int GetEXP(int level)
    {
        auto it = Monster_EXPTable.find(level);
        if (it != Monster_EXPTable.end())
        {
            return it.value();
        }
        // 如果等級不存在，返回一個適當的預設值（這裡返回0）
        return 0;
    }
    int GetMoney(int level)
    {
        auto it = Monster_EXPTable.find(level);
        if (it != Monster_EXPTable.end())
        {
            return it.value();
        }
        // 如果等級不存在，返回一個適當的預設值（這裡返回0）
        return 0;
    }
    void parseTable(QString fileName)
    {
        QString appDir = QCoreApplication::applicationDirPath();
        QString filePath = appDir + fileName;
        QJsonObject jsonObject = Common::readJsonFile(filePath).object();

        QJsonObject EXP = jsonObject["EXP"].toObject();
        for (auto it = EXP.begin(); it != EXP.end(); ++it)
        {
            int level = it.key().toInt();
            int experience = it.value().toInt();
            Monster_EXPTable[level] = experience;
        }
        QJsonObject Money = jsonObject["Money"].toObject();
        for (auto it = Money.begin(); it != Money.end(); ++it)
        {
            int level = it.key().toInt();
            int Money = it.value().toInt();
            Monster_MoneyTable[level] = Money;
        }
    }
private:
    QMap<int, int> Monster_EXPTable;
    QMap<int, int> Monster_MoneyTable;

};
class ExperienceTable
{
public:
    // 獲取特定等級的經驗值
    int GetEXP(int level)
    {
        auto it = experienceTable.find(level);
        if (it != experienceTable.end())
        {
            return it.value();
        }
        // 如果等級不存在，返回一個適當的預設值（這裡返回0）
        return 0;
    }
    void parseTable(QString fileName)
    {
        QString appDir = QCoreApplication::applicationDirPath();
        QString filePath = appDir + fileName;
        QJsonObject jsonObject = Common::readJsonFile(filePath).object();

        for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it)
        {
            int level = it.key().toInt();
            int experience = it.value().toInt();
            experienceTable[level] = experience;
        }
    }
private:
    QMap<int, int> experienceTable;


};

class MUD_Engine
{
public:
	MUD_Engine();
    void player_login(Player* player);
    void player_logout(Player* player);

	void play(MassageData& p_massagedata,Player* player,int& Minorcommand);
	void Scenes_Info(MassageData& p_massagedata,Player* player, int& Minorcommand);
    UIDTable UID_Table;                 //UID序號表

private:
	ExperienceTable EXP_Table;          //玩家升級表
	MonsterTable Mon_Table;             //怪物EXP與Money表


	QMap<int, Role*> Role_Map;    //儲存所有角色 <UID,Role>

    Role* Get_Role(int UID);
    void Die_Role(int UID);

    //生成怪物
	void Spawn_Monsters(MonsterID MID,QPoint pos);

	MapManager Map;
	void idle(MassageData& p_massagedata,QString& str , Player* player, int Minorcommand);
	void Move(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
	void Observe(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
	void Attack(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
	void UseItem(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
	void UseEQ(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
	void Store(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);

};