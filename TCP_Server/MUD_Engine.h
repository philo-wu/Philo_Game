#pragma once
#include "Common.h"
#include "MapManager.h"



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




class MUD_Engine
{
public:
	MUD_Engine();
    // 將玩家放入場景地圖
    void player_login(Player* player);
    // 將玩家移出場景地圖
    void player_logout(Player* player);
    // 計算玩家數值
    void player_update(Player* player);

    //主要玩家控制邏輯
	void play(MassageData& p_massagedata,Player* player,int& Minorcommand);
    //顯示當前指令相關資訊
	void Scenes_Info(MassageData& p_massagedata,Player* player, int& Minorcommand);
    UIDTable UID_Table;                 //UID序號表

private:
	ExperienceTable EXP_Table;          //玩家經驗表
	MonsterTable    Mon_Table;          //怪物表
    EquipmentTable  EQ_Table;           //裝備表
    PotionTable     Pot_Table;          //藥劑表
    MapManager      Map;                //地圖      

	QMap<int, Role*> Role_Map;    //儲存所有角色 <UID,Role>

    Role* Get_Role(int UID);
    void Die_Role(int UID);

    //生成怪物
	void Spawn_Monsters(MonsterID MID,QPoint pos);

	void idle(MassageData& p_massagedata,QString& str , Player* player, int Minorcommand);
	void Move(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
	void Observe(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
	void Attack(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
	void Backpack(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
    void UseItem(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
    void DropItem(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
	void Store(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);
    void Shopping(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand);

    void Show_Equipment(Player* m_player, QString& str);
    void Show_Backpack(Player* m_player, QString& str);
    void Buy_Item(int ItemID, Player* m_player, QString& str);


};