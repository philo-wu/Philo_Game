#pragma once

#include "framework.h"
#include "Direct2D.h"


// 父類別 Tree
class Tree {
protected:
    std::string treeType;
public:
    Tree(const std::string& type) : treeType(type) {}
    ID2D1Bitmap* treeBitmap; //繪圖圖片
    void Release() 
    { 
        if (treeBitmap) {
            treeBitmap->Release();
            //重新賦值
            treeBitmap = NULL;
        }
    }
    void grow() 
    {
        //std::cout << "樹變大了" << std::endl;
    }

    void shedLeaves() 
    {
        //std::cout << "葉子掉了" << std::endl;
    }
};

// 子類別 FruitTree
class FruitTree : public Tree {
private:
    std::string Fruit;
    //水果圖片 原本想一同保存於記憶體,但想不到用途
    //ID2D1Bitmap* FruitBitmap;

public:
    FruitTree(const std::string& type, std::string fruit) : Tree(type), Fruit(fruit) {}

    void Fruit_name() {
        //std::cout << "這顆樹是" << Fruit << " 樹." << std::endl;
    }
};