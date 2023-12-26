#pragma once
#include "Item.h"
enum Item_PotionEffect
{
    PotionEffect_heal,
    PotionEffect_hurt //�ȵL�ϥ�
};
enum Item_PotionID
{
    S_Healing_Potion = 10001,
    M_Healing_Potion = 10002
};
class Item_Potion : public Item
{
    Item_PotionEffect Effect;
    int Value;
public:
    void Set_Effect(Item_PotionEffect number)
    {
        Effect = number;
    }
    void Set_Value(int number)
    {
        Value = number;
    }
    void Potion_Create(QJsonObject Json_Equipment)
    {


        Set_Money(Json_Equipment["Money"].toInt());
        Set_NAME(Json_Equipment["NAME"].toString());
        Set_ItemID(Json_Equipment["ItemID"].toInt());
        Set_Value(Json_Equipment["Value"].toInt());
        Set_Effect(static_cast<Item_PotionEffect>(Json_Equipment["Effect"].toInt()));

    }
    Item_PotionEffect Get_Effect()
    {
        return Effect;
    }
    int Get_Value()
    {
        return Value;
    }
    void Show(QString& str)
    {
        switch (Effect)
        {
        case PotionEffect_heal:
            str += "Effect : �v��\n";
            break;
        case PotionEffect_hurt:
            str += "Effect : �ˮ`\n";
            break;
        default:
            break;
        }
        str += "Value : " + QString::number(Get_Value()) + "\n";
    }
};


class PotionTable
{
public:
    void Get_Potion(Item_PotionID ID, Item_Potion& p_equipment)
    {
        p_equipment = PotionTable[ID];
    }
    void parseTable(QString fileName)
    {
        QString appDir = QCoreApplication::applicationDirPath();
        QString filePath = appDir + fileName;
        // Ū�� JSON �ɮ�
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Error", "Failed to open file for reading!");
        }
        QByteArray jsonData = file.readAll();
        file.close();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);

        if (jsonDocument.isArray()) {
            // ���o JSON �}�C
            QJsonArray jsonArray = jsonDocument.array();
            // �b�o�̶i��Ū���M�ק�ާ@
            for (int row = 0; row < jsonArray.size(); ++row) {
                QJsonObject jsonObject = jsonArray[row].toObject();

                // Ū�����
                Item_PotionID ID = static_cast<Item_PotionID>(jsonObject["PotionID"].toInt());
                Item_Potion p_equipment;
                p_equipment.Potion_Create(jsonObject["Potion"].toObject());

                PotionTable[ID] = p_equipment;
            }
        }

    }
private:
    QMap<Item_PotionID, Item_Potion> PotionTable;


};