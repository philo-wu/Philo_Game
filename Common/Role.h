#pragma once


#include "Equipment.h"
#include <QCoreApplication>

enum RoleID
{
    Role_NULL,
    Role_Player,
    Role_Monster,
    Role_NPC
};
class NPC;
class Role
{
public:
    Role() { ; }
    Role(QString p_name, int p_HP, int p_MP)
    {
        NAME = p_name;
        HPMAX = p_HP;
        HP = HPMAX;
        MPMAX = p_MP;
        MP = MPMAX;
    }
    ~Role()
    {
        ;
    }
protected:
    QString NAME;
    int HP;
    int HPMAX;
    int MP;
    int MPMAX;
    int ATK;
    int DEF;
    int LV;
    int EXP;
    int Money;
    int UID;
    QPoint Position;
public:
    virtual void Attack(Role* r ,QString& str)
    {
        if (r->Get_HP() > 0)
        {
            str += Get_NAME() + " 攻擊  " + r->Get_NAME() + "\n";
            r->beAttack(ATK, str);
        }
    }
    virtual void beAttack(int number, QString& str)
    {
        str += Get_NAME() + " 承受 " + QString::number(number) + " 傷害" + "\n";
        HP -= number;
        if (HP < 0)
            HP = 0;
    }
    virtual void beHealingHP(int number, QString& str)
    {
        str += Get_NAME() + " 生命完全回復!!\n";
        HP += number;
        if (HP > HPMAX)
            HP = HPMAX;
    }
    virtual void beHealingMP(int number, QString& str)
    {
        str += Get_NAME() + " 魔力完全回復!!\n";
        MP += number;
        if (MP > MPMAX)
            MP = MPMAX;
    }
    bool isAlived()
    {
        return (HP > 0) ? true : false;
    }
    void Set_NAME(QString name) {
        NAME = name;
    }
    virtual void Set_HP(int number) {
        HP = number;
        HPMAX = number;
    }
    void Set_HPMAX(int number) {
        HPMAX = number;
    }

    virtual void Set_MP(int number) {
        MP = number;
        MPMAX = number;
    }
    void Set_MPMAX(int number) {
        MPMAX = number;
    }
    void Set_ATK(int number) {
        ATK = number;
    }
    void Set_DEF(int number) {
        DEF = number;
    }
    void Set_LV(int number) {
        LV = number;
    }
    void Set_EXP(int number) {
        EXP = number;
    }
    void Set_Money(int number) {
        Money = number;
    }
    void Set_UID(int number) {
        UID = number;
    }
    void Set_Position(QPoint& position) {
        Position = position;
    }
    void Set_Role(
            QString name,
            int HP,
            int HPMAX,
            int MP,
            int MPMAX,
            int ATK,
            int DEF,
            int LV,
            int EXP,
            int Money,
            int UID,
            QPoint& position) {
        Set_NAME(name);
        Set_HP(HP);
        Set_HPMAX(HPMAX);
        Set_MP(MP);
        Set_MPMAX(MPMAX);
        Set_ATK(ATK);
        Set_DEF(DEF);
        Set_LV(LV);
        Set_EXP(EXP);
        Set_Money(Money);
        Set_UID(UID);
        Set_Position(position);
    }

    QString Get_NAME()
    {
        return NAME;
    }
    int Get_HP()
    {
        return HP;
    }
    int Get_MP()
    {
        return MP;
    }
    int Get_HPMAX()
    {
        return HPMAX;
    }
    int Get_MPMAX()
    {
        return MPMAX;
    }

    int Get_ATK()
    {
        return ATK;
    }
    int Get_DEF()
    {
        return DEF;
    }
    int Get_LV()
    {
        return LV;
    }
    int Get_EXP()
    {
        return EXP;
    }
    int Get_Money()
    {
        return Money;
    }
    int Get_UID() {
        return UID;
    }
    QPoint Get_Position()
    {
        return Position;
    }
    virtual void show()
    {
        qDebug() << "NAME = " << NAME;
        qDebug() << "HP = " << HP;
        qDebug() << "MP = " << MP;
        qDebug() << "ATK = " << ATK;
        qDebug() << "DEF = " << DEF;
        qDebug() << "LV = " << LV;
        qDebug() << "EXP = " << EXP;
        qDebug() << "Money = " << Money;
        qDebug() << "Position = (" << Position.x() << "," << Position.y() <<")";

    }
};
class NPC : public Role
{
public:
    NPC(QString p_name) //NPC預設為100HP,0MP
        : Role(p_name,100,0)
    {
        ;
    }
    ~NPC()
    {
        ;
    }
public:
    void beAttack(int number, QString& str) override
    {
        str +=Get_NAME() +"無法被攻擊";
        qDebug() << "NPC 無法被攻擊  ";
    }
};
