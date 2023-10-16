#pragma once

#include "framework.h"
#include "Direct2D.h"


// �����O Tree
class Tree {
protected:
    std::string treeType;
public:
    Tree(const std::string& type) : treeType(type) {}
    ID2D1Bitmap* treeBitmap; //ø�ϹϤ�
    void Release() 
    { 
        if (treeBitmap) {
            treeBitmap->Release();
            //���s���
            treeBitmap = NULL;
        }
    }
    void grow() 
    {
        //std::cout << "���ܤj�F" << std::endl;
    }

    void shedLeaves() 
    {
        //std::cout << "���l���F" << std::endl;
    }
};

// �l���O FruitTree
class FruitTree : public Tree {
private:
    std::string Fruit;
    //���G�Ϥ� �쥻�Q�@�P�O�s��O����,���Q����γ~
    //ID2D1Bitmap* FruitBitmap;

public:
    FruitTree(const std::string& type, std::string fruit) : Tree(type), Fruit(fruit) {}

    void Fruit_name() {
        //std::cout << "�o����O" << Fruit << " ��." << std::endl;
    }
};