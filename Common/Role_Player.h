#pragma once


#include "Role.h"
#define BACKPACK_MAX 9


enum MUD_Command
{
    Player_Idle,	    //閒置
    //Player_Move,	    //玩家移動
    Player_Observe,	    //玩家戰鬥
    Player_Attack,	    //玩家尋找攻擊目標
    Player_Battle,	    //玩家戰鬥中

    Player_Backpack,    //背包
    Player_UseItem,	    //使用道具
    Player_DropItem,    //丟棄道具
    Player_GoStore,     //商店
    Player_Shopping,    //購物
    Player_Selling
};
enum Battle_Command
{
    Battle_Attack,
    Battle_Item,
    Battle_Run
};
class Player : public Role
{
public:
    Player() { ; }
    Player(QString p_name, int p_HP, int p_MP)
        : Role(p_name, p_HP, p_MP)
    {
        ;
    }
    ~Player()
    {
        ;
    }
    void Add_SightRole(int p_uid)
    {
        Sight_Role.append(p_uid);
    }
    void Clear_SightRole()
    {
        Sight_Role.clear();
    }
    QList<int> Get_SightRole()
    {
        return Sight_Role;
    }
protected:
    QList<int> Sight_Role;
    MUD_Command playstate;
    Battle_Command BattleState = Battle_Attack;
public:
    int total_ATK;
    int total_DEF;
    int total_HPMAX;
    int total_MPMAX;

    void Set_BattleState(Battle_Command number) {
        BattleState = number;
    }
    Battle_Command Get_BattleState() {
        return BattleState;
    }
    void Attack(Role* r, QString& str) override
    {
        if (r->Get_HP() > 0)
        {
            str += Get_NAME() + " 攻擊  " + r->Get_NAME() + "\n";
            r->beAttack(total_ATK, str);
        }
    }
    void beAttack(int number, QString& str)
    {
        int hurt;
        if (number > total_DEF)
            hurt = number - total_DEF;
        else
            hurt = 1;

        str += Get_NAME() + " 承受 " + QString::number(hurt) + " 傷害" + "\n";
        HP -= hurt;
        if (HP < 0)
            HP = 0;
    }
    void beHealingHP(int number, QString& str) override
    {
        str += Get_NAME() + " HP回復" + QString::number(number) + "\n";
        HP += number;
        if (HP > total_HPMAX)
            HP = total_HPMAX;
    }
    void beHealingMP(int number, QString& str) override
    {
        str += Get_NAME() + " MP回復" + QString::number(number) + "\n";
        MP += number;
        if (MP > total_MPMAX)
            MP = total_MPMAX;
    }

    QMap<Item_EquipmentParts, Item_EquipmentID> Eqs_Using; //身上裝備  <部位,Item_EquipmentID>
    QVector<int> Backpack;
    // int Backpack_MAX ; //統一上限BACKPACK_MAX 目前不支援擴充容量

    MUD_Command Get_playstate(){
        return playstate;
    }
    void Set_playstate(MUD_Command p_playstate) {
        //if(playstate != Player_Battle) //戰鬥無法切換狀態
            playstate = p_playstate;
    }
    void Bettle_end()
    {
        if (playstate == Player_Battle) //戰鬥結束
            playstate = Player_Idle;
    }

    bool Backpack_Put(int itemID ,QString& str)
    {
        if (itemID == 0)
        {
            str += "未知物品無法獲得";
            return false;
        }
        if (Backpack.size() + 1 < BACKPACK_MAX)
        {
            str += Get_NAME() + " 獲得了物品";
            Backpack.append(itemID);
            return true;
        }
        else
        {
            str += Get_NAME() + " 背包已滿\n";
            return false;
        }
    }


    bool Backpack_Remove(int index)
    {
        if (index >= 0 && index - 1 < Backpack.size()) 
        {
            Backpack.remove(index);
            return true;

        }
        else
        {
            return false;
        }
    }
    void Set_EQ(Item_EquipmentParts part, Item_EquipmentID EID) 
    {
        Eqs_Using[part] = EID;
    }
    Item_EquipmentID Get_EQ(Item_EquipmentParts part)
    {
        return Eqs_Using[part];
    }


    void Add_EXP(int p_EXP, QString& str)
    {
        str += Get_NAME() + " 獲得" + QString::number(p_EXP) + "EXP\n";
        EXP += p_EXP;
    }
    void Add_Money(int p_Money, QString& str)
    {
        str += Get_NAME() + " 獲得" + QString::number(p_Money) + " 元\n";
        Money += p_Money;
    }
    void Lose_EXP(int p_EXP, QString& str)
    {
        str += Get_NAME() + " 失去" + QString::number(p_EXP) + "EXP\n";
        EXP -= p_EXP;
        if (EXP < 0)
            EXP = 0;

    }
    void Lose_Money(int p_Money, QString& str)
    {
        str += Get_NAME() + " 失去" + QString::number(p_Money) + " 元\n";
        Money -= p_Money;
        if (Money < 0)
            Money = 0;
    }
    bool Cost_Money(int p_Money, QString& str)
    {
        if (p_Money <= Money)
        {
            str += Get_NAME() + " 花費" + QString::number(p_Money) + " 元\n";
            Money -= p_Money;
            return true;
        }
        else
        {
            str += Get_NAME() + " 身上錢不足" + QString::number(p_Money) + " 元\n";
            return false;

        }
    }
    bool Check_LVUP(int LVEXP, QString& str)
    {
        if (EXP >= LVEXP)
        {
            LVUP(str);
            return true;
        }
        return false;
    }
    void LVUP(QString& str)
    {
        str += Get_NAME() + " 升級了!!\n";
        ++LV;
        str += Get_NAME() + " 攻擊提升 1 !!\n";
        ++ATK;
        str += Get_NAME() + " 防禦提升 1 !!\n";
        ++DEF;
        str += Get_NAME() + " 生命上限提升 10 !!\n";
        HPMAX += 10;
        str += Get_NAME() + " 魔力上限提升 5 !!\n";
        MPMAX += 5;
        Rest(str);
    }
    void Rest(QString& str)
    {
        beHealingHP(total_HPMAX, str);
        beHealingMP(total_MPMAX, str);
    }
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

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Error", "Failed to open file for reading!");
        }
        QByteArray jsonData = file.readAll();
        file.close();
        QJsonObject jsonObject = QJsonDocument::fromJson(jsonData).object();

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
