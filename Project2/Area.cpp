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

int Area::Get_CellNumber(int light_number) {
    switch (light_number)
    {
    case 0: {
        return ORANGE_NUMBER;
    }
    case 1: {
        return BELL_NUMBER;
    }
    case 2: {
        return BAR_NUMBER;
    }
    case 3: {
        return BAR_NUMBER;
    }
    case 4: {
        return APPLE_NUMBER;
    }
    case 5: {
        return APPLE_NUMBER;
    }
    case 6: {
        return LEMON_NUMBER;
    }
    case 7: {
        return WATERMELOM_NUMBER;
    }
    case 8: {
        return WATERMELOM_NUMBER;
    }
    case 9: {
        return BLUE_ONCEMORE_NUMBER;
    }
    case 10: {
        return APPLE_NUMBER;
    }
    case 11: {
        return ORANGE_NUMBER;
    }
    case 12: {
        return ORANGE_NUMBER;
    }
    case 13: {
        return BELL_NUMBER;
    }
    case 14: {
        return SEVEN_NUMBER;
    }
    case 15: {
        return SEVEN_NUMBER;
    }
    case 16: {
        return APPLE_NUMBER;
    }
    case 17: {
        return LEMON_NUMBER;
    }
    case 18: {
        return LEMON_NUMBER;
    }
    case 19: {
        return STAR_NUMBER;
    }
    case 20: {
        return STAR_NUMBER;
    }
    case 21: {
        return RED_ONCEMORE_NUMBER;
    }
    case 22: {
        return APPLE_NUMBER;
    }
    case 23: {
        return BELL_NUMBER;
    }
    default:
        // 其他格子的處理邏輯
        return -1;
    }
}