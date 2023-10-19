#pragma once
// �����O Fruit
class Fruit {
protected:
    std::wstring  fruitname;
    POINT fruitpoint;
public:
    Fruit(const std::wstring& name) : fruitname(name), fruitBitmap(nullptr) { ; }
    ID2D1Bitmap* fruitBitmap; //ø�ϹϤ�
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
