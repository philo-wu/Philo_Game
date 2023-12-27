#pragma once
#include "Role.h"
enum MonsterID
{
    LV1_Slime,
    LV2_Wolf,
    LV3_Goblin,
    LV4_ForestSlime,
    LV5_ForestWolf,
    LV6_ForestGoblin,
    LV7_RuinSlime,
    LV8_RuinWolf,
    LV9_RuinGoblin,
    LV10_Dragon,
};

class Monster : public Role
{
public:
    Monster()
    {
        ;
    }
    Monster(QString p_name, int p_HP, int p_MP,int ATK,int DEF)
        : Role(p_name, p_HP, p_MP)
    {
        Set_ATK(ATK);
        Set_DEF(DEF);
    }
    ~Monster()
    {
        ;
    }
    void Monster_Create(QJsonObject Json_Mon)
    {
        QPoint pos = QPoint(0, 0);
        Set_Role(Json_Mon["NAME"].toString(),
            Json_Mon["HP"].toInt(),
            Json_Mon["HP"].toInt(),
            0, //怪物目前無魔力
            0,
            Json_Mon["ATK"].toInt(),
            Json_Mon["DEF"].toInt(),
            Json_Mon["LV"].toInt(),
            Json_Mon["EXP"].toInt(),
            Json_Mon["Money"].toInt(),
            0,
            pos);
        Set_IsBoss(Json_Mon["IsBoss"].toInt());
        Set_DropChance(Json_Mon["total_DropChance"].toInt());
        QJsonArray dropListArray = Json_Mon["DropList"].toArray();
        DropList.clear();
        for (const QJsonValue& dropItemValue : dropListArray) {
            QJsonObject dropItem = dropItemValue.toObject();
            DropList_Add(dropItem["ItemID"].toInt(), dropItem["Probability"].toInt());
        }
    }
    void Set_IsBoss(bool bol)
    {
        IsBoss = bol;
    }

    void Set_DropChance(int number)
    {
        total_DropChance = number;
    }
    bool Get_IsBoss()
    {
        return IsBoss;
    }
    int Get_DropChance()
    {
        return total_DropChance;
    }
    void DropList_Add(int ItemID, int DropChance)
    {
        DropList.append(qMakePair(ItemID, DropChance));
    }
    void DropList_Clear()
    {
        DropList.clear();
    }
    QList<QPair<int, int>> Get_DropList()
    {
        return DropList;
    }
protected:
    bool IsBoss =false;
    QList<QPair<int,int>> DropList;
    int total_DropChance; //全部掉落機率 100為100% 0為0%
};

class MonsterTable
{
public:
    void Get_Monster(MonsterID ID, Monster& p_monster)
    {
        p_monster = MonsterTable[ID];
    }
    void parseTable(QString fileName)
    {
        QString appDir = QCoreApplication::applicationDirPath();
        QString filePath = appDir + fileName;
        // 讀取 JSON 檔案
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Error", "Failed to open file for reading!");
        }
        QByteArray jsonData = file.readAll();
        file.close();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);

        if (jsonDocument.isArray()) {
            // 取得 JSON 陣列
            QJsonArray jsonArray = jsonDocument.array();
            // 在這裡進行讀取和修改操作
            for (int row = 0; row < jsonArray.size(); ++row) {
                QJsonObject jsonObject = jsonArray[row].toObject();

                // 讀取資料
                MonsterID ID = static_cast<MonsterID>(jsonObject["MonsterID"].toInt());
                Monster p_monster;
                p_monster.Monster_Create(jsonObject["Monster"].toObject());

                MonsterTable[ID] = p_monster;
            }
        }

    }
private:
    QMap<MonsterID, Monster> MonsterTable;


};
