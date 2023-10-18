#pragma once

#include "framework.h"
#include "Direct2D.h"
#include "Fruit.h"


// 父類別 Tree
class Tree {
protected:
    std::wstring treename;
    ID2D1Bitmap* treeBitmap; //繪圖圖片
    POINT treepoint;
public:
    Tree(const std::wstring& name) : treename(name) {}
    ID2D1Bitmap* Get_TreeBitmap() { return treeBitmap; }
    void Set_TreeBitmap(ID2D1Bitmap* pBitmap) { treeBitmap = pBitmap; return; }
    void Release_TreeBitmap()
    {
        if (treeBitmap) {
            treeBitmap->Release();
            //重新賦值
            treeBitmap = NULL;
        }
        std::wstring message = treename + L"釋放Bitmap\n";
        OutputDebugString(message.c_str());
    }
};

// 子類別 FruitTree
class FruitTree : public Tree , public  Fruit {
private:
    std::vector<POINT> fruitpoints;
public:
    FruitTree(const std::wstring& name, std::wstring fruit) : Tree(name), Fruit(fruit) {}
    FruitTree(Tree& tree, Fruit& fruit) : Tree(tree), Fruit(fruit) {

        // MAYBE : 進行深度複製而不是使用&
        // 
        // 在這裡可以使用基類的資訊進行初始化
        // 例如，可以從 Tree 和 Fruit 中獲取相關資訊來初始化 FruitTree
    }

    void Release_Bitmap() {
        Release_TreeBitmap();
        Release_FruitBitmap();
    }
};