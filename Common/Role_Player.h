#pragma once


#include "Role.h"


enum MUN_Command
{
    Player_Idle,	//閒置
    Player_Move,	//玩家移動
    Player_Observe,	//玩家戰鬥
    Player_Attack,	//玩家攻擊
    Player_UseItem,	//使用道具
    Player_UseEQ,	//使用裝備
    Player_Store    //商店
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
        if(p_uid != UID)
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
    //int UID;

    QMap<equipmentParts, equipment> Eqs_Using;
    QList<int> Sight_Role;
    MUN_Command playstate;

public:
    MUN_Command Get_playstate(){
        return playstate;
    }
    void Set_playstate(MUN_Command p_playstate) {
        playstate = p_playstate;
    }
    void Useitem(int d);
    void Add_EXP(int p_EXP, QString& str)
    {
        str += Get_NAME() + " 獲得" + QString::number(p_EXP) + "EXP\n";
        EXP += p_EXP;
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
    void Add_Money(int p_Money, QString& str)
    {
        str += Get_NAME() + " 獲得" + QString::number(p_Money) + " 元\n";
        Money += p_Money;
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
        beHealingHP(HPMAX, str);
        beHealingMP(MPMAX, str);
    }
};