#pragma once

#include "framework.h"
#include "Direct2D.h"
#include "Fruit.h"


// �����O Tree
class Tree {
protected:
    std::wstring treename;
    POINT tree_Point;
public:
    Tree(const std::wstring name) : treename(name) {}
    ID2D1Bitmap* treeBitmap; //ø�ϹϤ� //�쥻�Q��protected ,���PD2DRenderTarget���̦s���Y���n�B�z
    void Release_TreeBitmap()
    {
        if (treeBitmap) {
            treeBitmap->Release();
            //���s���
            treeBitmap = NULL;
        }
        std::wstring message = treename + L"����Bitmap\n";
        OutputDebugString(message.c_str());
    }
};

// �l���O FruitTree
class FruitTree : public Tree , public  Fruit {
private:
    std::vector<POINT> fruit_Points;
public:
    FruitTree(const std::wstring name, std::wstring fruit) : Tree(name), Fruit(fruit) {}
    FruitTree(Tree& tree, Fruit& fruit) : Tree(tree), Fruit(fruit)
    {
        // �b�o�̥i�H�ϥΰ�������T�i���l��
        // �Ҧp�A�i�H�q Tree �M Fruit �����������T�Ӫ�l�� FruitTree
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