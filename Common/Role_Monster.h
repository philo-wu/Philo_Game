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
protected:
    bool IsBoss;
    QList<equipment> Eq_Drop;
};
