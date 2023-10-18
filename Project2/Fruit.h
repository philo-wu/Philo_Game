#pragma once
// �����O Fruit
class Fruit {
protected:
    std::wstring  fruitname;
    ID2D1Bitmap* fruitBitmap; //ø�ϹϤ�
    POINT fruitpoint;
public:
    Fruit(const std::wstring& name) : fruitname(name), fruitBitmap(nullptr) { ; }
    ~Fruit();
    void Release_FruitBitmap()
    {
        if (fruitBitmap) {
            fruitBitmap->Release();
            //���s���
            fruitBitmap = NULL;
        }
        std::wstring message = fruitname + L"����Bitmap\n";
        OutputDebugString(message.c_str());
    }
};
