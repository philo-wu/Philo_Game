#pragma once
// 父類別 Fruit
class Fruit {
protected:
    std::wstring  fruitname;
    POINT fruitpoint;
public:
    Fruit(const std::wstring& name) : fruitname(name), fruitBitmap(nullptr) { ; }
    ID2D1Bitmap* fruitBitmap; //繪圖圖片
    ~Fruit();
    void Release_FruitBitmap()
    {
        if (fruitBitmap) {
            fruitBitmap->Release();
            //重新賦值
            fruitBitmap = NULL;
        }
        std::wstring message = fruitname + L"釋放Bitmap\n";
        OutputDebugString(message.c_str());
    }
};
