#pragma once

#include "framework.h"
#include "Direct2D.h"


// 父類別 Images
class Images {
protected:
    ID2D1Bitmap* treeBitmap;  //繪圖圖片 
    ID2D1Bitmap* fruitBitmap; //繪圖圖片
    //std::vector<ID2D1Bitmap*> ; //不支援這樣使用 //可能要自己重寫一個vector
public:

    Images() { 
        treeBitmap = NULL;
        fruitBitmap = NULL; 
    };
    void Release_Bitmap()
    {
        if (treeBitmap) {
            treeBitmap->Release();
            //重新賦值
            treeBitmap = NULL;
        }
        if (fruitBitmap) {
            fruitBitmap->Release();
            //重新賦值
            fruitBitmap = NULL;
        }

        std::wstring message =  L"釋放Bitmap\n";
        OutputDebugString(message.c_str());
    }
    void Release_treeBitmap()
    {
        if (treeBitmap) {
            treeBitmap->Release();
            //重新賦值
            treeBitmap = NULL;
        }
    }
    void Release_fruitBitmap()
    {
        if (fruitBitmap) {
            fruitBitmap->Release();
            //重新賦值
            fruitBitmap = NULL;
        }
    }
    ID2D1Bitmap*& Get_treeBitmap() { return treeBitmap; }
    ID2D1Bitmap*& Get_fruitBitmap() { return fruitBitmap; }

};
// 子類別 Tree
class Tree : public Images {
protected:
    std::wstring using_Dialog_TreeName;
    POINT tree_Point;
public:
    Tree(const std::wstring name) : using_Dialog_TreeName(name) ,Images() { }

};

// 子類別 FruitTree
class FruitTree : public Tree  {
private:
    std::vector<POINT> fruit_Points;
    std::wstring  fruit_Name;

public:
    FruitTree(const std::wstring name, std::wstring fruit) : Tree(name) {}
    FruitTree(Tree& tree) : Tree(tree)
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

};