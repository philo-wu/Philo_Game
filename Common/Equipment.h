#pragma once
#include <QString>
#include <QPoint>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

enum equipmentParts
{
    Part_Helmet,
    Part_Armor,
    Part_Shoe,
    Part_Weapon
};
enum equipmentID
{
    Eq_Null,
    Tiro_Helmet,
    Tiro_Armor,
    Tiro_Shoe,
    Tiro_Sword,
    Copper_Helmet,
    Copper_Armor,
    Copper_Shoe,
    Copper_Sword,
    Iron_Helmet,
    Iron_Armor,
    Iron_Shoe,
    Iron_Sword,
    Gold_Helmet,
    Gold_Armor,
    Gold_Shoe,
    Gold_Sword,
    Forest_Helmet,
    Forest_Armor,
    Forest_Shoe,
    Forest_Sword,
    Ruins_Helmet,
    Ruins_Armor,
    Ruins_Shoe,
    Ruins_Sword
};
class equipment
{
    QString name;
    equipmentParts Part;
    equipmentID UID;
    int ATK;
    int DEF;
    int Price;
};