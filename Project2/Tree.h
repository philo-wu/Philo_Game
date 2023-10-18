#pragma once

#include "framework.h"
#include "Direct2D.h"
#include "Fruit.h"


// �����O Tree
class Tree {
protected:
    std::wstring treename;
    ID2D1Bitmap* treeBitmap; //ø�ϹϤ�
    POINT treepoint;
public:
    Tree(const std::wstring& name) : treename(name) {}
    ID2D1Bitmap* Get_TreeBitmap() { return treeBitmap; }
    void Set_TreeBitmap(ID2D1Bitmap* pBitmap) { treeBitmap = pBitmap; return; }
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
    std::vector<POINT> fruitpoints;
public:
    FruitTree(const std::wstring& name, std::wstring fruit) : Tree(name), Fruit(fruit) {}
    FruitTree(Tree& tree, Fruit& fruit) : Tree(tree), Fruit(fruit) {

        // MAYBE : �i��`�׽ƻs�Ӥ��O�ϥ�&
        // 
        // �b�o�̥i�H�ϥΰ�������T�i���l��
        // �Ҧp�A�i�H�q Tree �M Fruit �����������T�Ӫ�l�� FruitTree
    }

    void Release_Bitmap() {
        Release_TreeBitmap();
        Release_FruitBitmap();
    }
};