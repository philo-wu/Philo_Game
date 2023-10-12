#pragma once

#include "framework.h"


// 父類別 Tree
class Tree {
protected:
    std::string treeType;

public:
    Tree(const std::string& type) : treeType(type) {}

    void grow() {
        std::cout << "樹變大了" << std::endl;
    }

    void shedLeaves() {
        std::cout << "葉子掉了" << std::endl;
    }
};

// 子類別 AppleTree
class FruitTree : public Tree {
private:
    std::string Fruit;

public:
    FruitTree(const std::string& type, std::string fruit) : Tree(type), Fruit(fruit) {}

    void Fruit_name() {
        std::cout << "這顆樹是" << Fruit << " 樹." << std::endl;
    }
};

// 子類別 AppleTree
class AppleTree : public Tree {
private:
    int numberOfApples;

public:
    AppleTree(const std::string& type, int apples) : Tree(type), numberOfApples(apples) {}

    void produceApples() {
        std::cout << "蘋果樹產生了" << numberOfApples << " 個蘋果." << std::endl;
    }
};

// 子類別 BananaTree
class BananaTree : public Tree {
private:
    int numberOfBananas;

public:
    BananaTree(const std::string& type, int bananas) : Tree(type), numberOfBananas(bananas) {}

    void produceBananas() {
        std::cout << "香蕉樹產生了" << numberOfBananas << " 個蘋果." << std::endl;
    }
};
