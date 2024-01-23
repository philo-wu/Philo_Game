#pragma once
#include "Common.h"


class Area
{
public:
    Area(Common* pcommon) {
        common = pcommon;
        BM = common->BM;
        SM = common->SM;
        ESM = common->ESM;
        m_pDirect2dFactory = BM->m_pDirect2dFactory;
        m_pRenderTarget = BM->m_pRenderTarget;
        m_pDWriteFactory = BM->m_pDWriteFactory;
        m_pTextFormat = BM->m_pTextFormat;
        m_pBrush = BM->m_pBrush;
    }
    // (x.y)為m_pDirect2dFactory->CreateHwndRenderTarget選擇的HWND
    // x為左上角x軸位置 y為左上角y軸位置 
    virtual void Draw(int x, int y, int width, int height) { return; }
    void Draw_Cell(int number, D2D1_RECT_F originalRect);

    Common* common;
    BitmapManager* BM;
    ScoreManager* SM;
    EngineStateManager* ESM;

    ID2D1Factory* m_pDirect2dFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    IDWriteFactory* m_pDWriteFactory;
    IDWriteTextFormat* m_pTextFormat;
    ID2D1SolidColorBrush* m_pBrush;

    int lightsecond = 200; //燈亮時間
    //int lightIndex = 0;


};

