#pragma once

#include "Item.h"

enum Item_EquipmentParts
{
    Part_Weapon,
    Part_Helmet,
    Part_Armor,
    Part_Shoe
    
};
enum Item_EquipmentID
{
    Eq_Null         = 0,
    Newbie_Helmet   = 1,
    Newbie_Armor    = 2,
    Newbie_Shoe     = 3,
    Newbie_Sword    = 4,
    Iron_Helmet     = 5,
    Iron_Armor      = 6,
    Iron_Shoe       = 7,
    Iron_Sword      = 8,
    Forest_Helmet   = 9,
    Forest_Armor    = 10,
    Forest_Shoe     = 11,
    Forest_Sword    = 12,
    Ruins_Helmet    = 13,
    Ruins_Armor     = 14,
    Ruins_Shoe      = 15,
    Ruins_Sword     = 16
};
class Item_Equipment : public Item
{
    Item_EquipmentParts Part;
    int ATK;
    int DEF;
    int HP;
    int MP;
public:
    void Set_ATK(int number)
    {
        ATK = number;
    }
    void Set_DEF(int number)
    {
        DEF = number;
    }
    void Set_HP(int number)
    {
        HP = number;
    }
    void Set_MP(int number)
    {
        MP = number;
    }
    void Set_Part(Item_EquipmentParts number)
    {
        Part = number;
    }

    void Equipment_Create(QJsonObject Json_Equipment)
    {
        Set_ATK(Json_Equipment["ATK"].toInt());
        Set_DEF(Json_Equipment["DEF"].toInt());
        Set_HP(Json_Equipment["HP"].toInt());
        Set_MP(Json_Equipment["MP"].toInt());
        Set_Money(Json_Equipment["Money"].toInt());
        Set_NAME(Json_Equipment["NAME"].toString());
        Set_ItemID(Json_Equipment["ItemID"].toInt());
        Set_Part(static_cast<Item_EquipmentParts>(Json_Equipment["Part"].toInt()));
                
    }
    int Get_ATK()
    {
        return ATK ;
    }
    int Get_DEF()
    {
        return DEF;
    }
    int Get_HP()
    {
        return HP;
    }
    int Get_MP()
    {
        return MP;
    }
    Item_EquipmentParts Get_Part()
    {
        return Part;
    }

    void Show(QString& str)
    {
        str += "ATK : " + QString::number(Get_ATK()) + "\n";
        str += "DEF : " + QString::number(Get_DEF()) + "\n";
        str += "HP  : " + QString::number(Get_HP()) + "\n";
        str += "MP  : " + QString::number(Get_MP()) + "\n";

    }
};


class EquipmentTable
{
public:
    void Get_Equipment(Item_EquipmentID ID, Item_Equipment& p_equipment)
    {
        p_equipment = EquipmentTable[ID];
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
                Item_EquipmentID ID = static_cast<Item_EquipmentID>(jsonObject["EquipmentID"].toInt());
                Item_Equipment p_equipment;
                p_equipment.Equipment_Create(jsonObject["Equipment"].toObject());

                EquipmentTable[ID] = p_equipment;
            }
        }

    }
private:
    QMap<Item_EquipmentID, Item_Equipment> EquipmentTable;


};
