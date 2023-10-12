#pragma once

#include "framework.h"


// �����O Tree
class Tree {
protected:
    std::string treeType;

public:
    Tree(const std::string& type) : treeType(type) {}

    void grow() {
        std::cout << "���ܤj�F" << std::endl;
    }

    void shedLeaves() {
        std::cout << "���l���F" << std::endl;
    }
};

// �l���O AppleTree
class FruitTree : public Tree {
private:
    std::string Fruit;

public:
    FruitTree(const std::string& type, std::string fruit) : Tree(type), Fruit(fruit) {}

    void Fruit_name() {
        std::cout << "�o����O" << Fruit << " ��." << std::endl;
    }
};

// �l���O AppleTree
class AppleTree : public Tree {
private:
    int numberOfApples;

public:
    AppleTree(const std::string& type, int apples) : Tree(type), numberOfApples(apples) {}

    void produceApples() {
        std::cout << "ī�G�𲣥ͤF" << numberOfApples << " ��ī�G." << std::endl;
    }
};

// �l���O BananaTree
class BananaTree : public Tree {
private:
    int numberOfBananas;

public:
    BananaTree(const std::string& type, int bananas) : Tree(type), numberOfBananas(bananas) {}

    void produceBananas() {
        std::cout << "�����𲣥ͤF" << numberOfBananas << " ��ī�G." << std::endl;
    }
};
