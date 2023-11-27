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
        m_pWhiteBrush = BM->m_pWhiteBrush;


    }
    // (x.y)��m_pDirect2dFactory->CreateHwndRenderTarget��ܪ�HWND
    // x�����W��x�b��m y�����W��y�b��m 
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
    ID2D1SolidColorBrush* m_pWhiteBrush;

    int lightsecond = 200; //�O�G�ɶ�
    //int lightIndex = 0;


};

