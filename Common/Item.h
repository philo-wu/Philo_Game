#pragma once
#include <QString>
#include <QPoint>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QCoreApplication>

#define EQUIPMENT_UID_START	1
#define EQUIPMENT_UID_END	10000
#define POTION_UID_START	10001
#define POTION_UID_END		20000

class Item
{
    QString NAME;
    int ItemID;
    int Money;
public:
    void Set_ItemID(int number)
    {
        ItemID = number;
    }
    void Set_NAME(QString name)
    {
        NAME = name;
    }
    void Set_Money(int number)
    {
        Money = number;
    }

    int Get_ItemID()
    {
        return ItemID;
    }
    QString Get_NAME()
    {
        return NAME;
    }
    int Get_Money()
    {
        return Money;
    }
};
