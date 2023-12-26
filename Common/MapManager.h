#pragma once
#include "Map_Scenes.h"

class MapManager
{
public:
    MapManager()
    {
        // 可以添加額外的初始化邏輯，如果有需要的話
        map = {
            {Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable},
            {Impassable, RuinsBoss, Ruins, Ruins, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable},
            {Impassable, Ruins, Ruins, Ruins, Way, Way, Way, Way, Way, Village, Impassable},
            {Impassable, Ruins, Ruins, Ruins, Impassable, Impassable, Impassable, Way, Impassable, Way, Impassable},
            {Impassable, Impassable, Way, Impassable, Impassable, Impassable, Impassable, Way, Impassable, Way, Impassable},
            {Impassable, Impassable, Way, Way, Way, Village, Forest, Forest, Way, Way, Impassable},
            {Impassable, Impassable, Way, Impassable, Impassable, Impassable, Forest, Forest, Impassable, Way, Impassable},
            {Impassable, Forest, Forest, Forest, Impassable, Impassable, Impassable, Way, Impassable, Way, Impassable},
            {Impassable, Forest, Forest, Forest, Way, Way, Way, Way, Way, Village, Impassable},
            {Impassable, Forest, Forest, Forest, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable},
            {Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable, Impassable}
        };
        QList<int> list;
        UIDmap = {
            {list, list, list, list, list, list, list, list, list, list, list},
            {list, list, list, list, list, list, list, list, list, list, list},
            {list, list, list, list, list, list, list, list, list, list, list},
            {list, list, list, list, list, list, list, list, list, list, list},
            {list, list, list, list, list, list, list, list, list, list, list},
            {list, list, list, list, list, list, list, list, list, list, list},
            {list, list, list, list, list, list, list, list, list, list, list},
            {list, list, list, list, list, list, list, list, list, list, list},
            {list, list, list, list, list, list, list, list, list, list, list},
            {list, list, list, list, list, list, list, list, list, list, list},
            {list, list, list, list, list, list, list, list, list, list, list}

        };
        Weapon_points.append(QPoint(9, 8));
        Armor_points.append(QPoint(5, 5));
        Potion_points.append(QPoint(9, 2));
    }


    SceneID getSceneID(QPoint pos) const
    {
        int row = pos.y();
        int col = pos.x();

        if (col >= 0 && col < map.size() && row >= 0 && row < map[0].size())
            return map[row][col];
        return Impassable; // 或者返回一個適當的預設值
    }


    void setSceneID(QPoint pos, SceneID scene)
    {
        int row = pos.y();
        int col = pos.x();

        if (col >= 0 && col < map.size() && row >= 0 && row < map[0].size())
            map[row][col] = scene;
        // 如果需要處理錯誤，可以添加相應的邏輯
    }
    bool is_Store(StoreID ID, QPoint pos)
    {
        switch (ID)
        {
        case Store_Weapon: {
            return Weapon_points.contains(pos);
            break;
        }
        case Store_Armor: {
            return Armor_points.contains(pos);
            break;
        }
        case Store_Potion: {
            return Potion_points.contains(pos);
            break;
        }
        default:
            break;
        }

        return false;
    }

    void AddUID(QPoint pos, int UID)
    {
        int row = pos.y();
        int col = pos.x();

        if (col >= 0 && col < UIDmap.size() && row >= 0 && row < UIDmap[0].size())
            UIDmap[row][col].append(UID);
        // 如果需要處理錯誤，可以添加相應的邏輯
    }
    void MoveUID(QPoint fromPos, QPoint toPos, int UID)
    {
        int fromRow = fromPos.y();
        int fromCol = fromPos.x();
        int toRow = toPos.y();
        int toCol = toPos.x();

        if (fromCol >= 0 && fromCol < UIDmap.size() && fromRow >= 0 && fromRow < UIDmap[0].size() &&
            toCol >= 0 && toCol < UIDmap.size() && toRow >= 0 && toRow < UIDmap[0].size())
        {
            // 在目標位置添加 UID
            UIDmap[toRow][toCol].append(UID);

            // 在原始位置刪除 UID
            UIDmap[fromRow][fromCol].removeOne(UID);
        }
        // 如果需要處理錯誤，可以添加相應的邏輯
    }
    void RemoveUID(QPoint pos, int UID)
    {
        int row = pos.y();
        int col = pos.x();

        if (col >= 0 && col < UIDmap.size() && row >= 0 && row < UIDmap[0].size())
            UIDmap[row][col].removeOne(UID);
        // 如果需要處理錯誤，可以添加相應的邏輯
    }

    QList<int> GetUIDList(QPoint pos)
    {
        int row = pos.y();
        int col = pos.x();

        if (col >= 0 && col < UIDmap.size() && row >= 0 && row < UIDmap[0].size())
        {
            return UIDmap[row][col];
        }
        else
        {
            // 如果位置無效，您可能希望返回一個默認的列表或處理錯誤的邏輯
            return QList<int>();
        }
    }
private:
    QVector<QVector<SceneID>> map;
    QVector<QVector<QList<int>>> UIDmap;

    QList<QPoint> Weapon_points;
    QList<QPoint> Armor_points;
    QList<QPoint> Potion_points;

};
