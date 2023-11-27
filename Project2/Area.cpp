#include "Area.h"

void Area::Draw_Cell(int number, D2D1_RECT_F originalRect) {

    D2D1_RECT_F Rect;
    ID2D1SolidColorBrush* pBrush;
    // 將原本給的originalRect範圍縮小
    float shrinkAmount = 10.0f;
    Rect.left = originalRect.left + shrinkAmount;
    Rect.top = originalRect.top + shrinkAmount;
    Rect.right = originalRect.right - shrinkAmount;
    Rect.bottom = originalRect.bottom - shrinkAmount;


    switch (number)
    {
    case APPLE_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->AppleBitmap, Rect);

    }
                     break;
    case BAR_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->BarBitmap, Rect);

    }
                   break;
    case BELL_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->BellBitmap, Rect);

    }
                    break;
    case LEMON_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->LemonBitmap, Rect);

    }
                     break;
    case ORANGE_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->OrangeBitmap, Rect);

    }
                      break;
    case SEVEN_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->SevenBitmap, Rect);

    }
                     break;
    case STAR_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->StarBitmap, Rect);

    }
                    break;
    case WATERMELOM_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->WatermelonBitmap, Rect);

    }
                          break;
    case RED_ONCEMORE_NUMBER: {
        Rect.left = originalRect.left - shrinkAmount;
        Rect.top = originalRect.top - shrinkAmount;
        Rect.right = originalRect.right + shrinkAmount;
        Rect.bottom = originalRect.bottom + shrinkAmount;

        WCHAR scoreStr[64];
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中
        swprintf_s(scoreStr, L"ONCE\nMORE                      ");
        m_pRenderTarget->DrawText(
            scoreStr,
            26,
            m_pTextFormat,
            Rect,
            pBrush
        );
    }
                            break;
    case BLUE_ONCEMORE_NUMBER: {
        Rect.left = originalRect.left - shrinkAmount;
        Rect.top = originalRect.top - shrinkAmount;
        Rect.right = originalRect.right + shrinkAmount;
        Rect.bottom = originalRect.bottom + shrinkAmount;

        WCHAR scoreStr[64];
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &pBrush);
        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中
        swprintf_s(scoreStr, L"ONCE\nMORE                      ");
        m_pRenderTarget->DrawText(
            scoreStr,
            26,
            m_pTextFormat,
            Rect,
            pBrush
        );
    }
                             break;
    default:
        break;
    }
}

