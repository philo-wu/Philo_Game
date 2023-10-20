#pragma once

#include "framework.h"
#include "Direct2D.h"
#include "Fruit.h"


// 父類別 Tree
class Tree {
protected:
    std::wstring using_TreeName;
    POINT tree_Point;
public:
    Tree(const std::wstring name) : using_TreeName(name) {}
    ID2D1Bitmap* treeBitmap; //繪圖圖片 //原本想放protected ,但與D2DRenderTarget的依存關係不好處理
    void Release_TreeBitmap()
    {
        if (treeBitmap) {
            treeBitmap->Release();
            //重新賦值
            treeBitmap = NULL;
        }
        std::wstring message = using_TreeName + L"釋放Bitmap\n";
        OutputDebugString(message.c_str());
    }
};

// 子類別 FruitTree
class FruitTree : public Tree , public  Fruit {
private:
    std::vector<POINT> fruit_Points;
public:
    FruitTree(const std::wstring name, std::wstring fruit) : Tree(name), Fruit(fruit) {}
    FruitTree(Tree& tree, Fruit& fruit) : Tree(tree), Fruit(fruit)
    {
        // 在這裡可以使用基類的資訊進行初始化
        // 例如，可以從 Tree 和 Fruit 中獲取相關資訊來初始化 FruitTree
    }
    void Set_fruit_Points(std::vector<POINT> Points) { 
        fruit_Points  = Points;
    }
    std::vector<POINT> Get_fruit_Points() { 
        return fruit_Points;
    };
    void Release_Bitmap() {
        Release_TreeBitmap();
        Release_FruitBitmap();
    }
};