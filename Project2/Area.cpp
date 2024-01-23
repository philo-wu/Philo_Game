#include "Area.h"

void Area::Draw_Cell(int number, D2D1_RECT_F originalRect) {

    D2D1_RECT_F Rect;
    // �N�쥻����originalRect�d���Y�p
    float shrinkAmount = 10.0f;
    Rect.left = originalRect.left + shrinkAmount;
    Rect.top = originalRect.top + shrinkAmount;
    Rect.right = originalRect.right - shrinkAmount;
    Rect.bottom = originalRect.bottom - shrinkAmount;


    switch (number)
    {
    case APPLE_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->cell_vector[number], Rect);
    }
                     break;
    case BAR_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->cell_vector[number], Rect);
    }
                   break;
    case BELL_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->cell_vector[number], Rect);
    }
                    break;
    case LEMON_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->cell_vector[number], Rect);
    }
                     break;
    case ORANGE_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->cell_vector[number], Rect);
    }
                      break;
    case SEVEN_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->cell_vector[number], Rect);
    }
                     break;
    case STAR_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->cell_vector[number], Rect);
    }
                    break;
    case WATERMELOM_NUMBER: {
        m_pRenderTarget->DrawBitmap(BM->cell_vector[number], Rect);
    }
                          break;
    case RED_ONCEMORE_NUMBER: {
        Rect.left = originalRect.left - shrinkAmount;
        Rect.top = originalRect.top - shrinkAmount;
        Rect.right = originalRect.right + shrinkAmount;
        Rect.bottom = originalRect.bottom + shrinkAmount;

        WCHAR scoreStr[64];
        m_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //�m��
        swprintf_s(scoreStr, L"ONCE\nMORE                      ");
        m_pRenderTarget->DrawText(
            scoreStr,
            26,
            m_pTextFormat,
            Rect,
            m_pBrush
        );
    }
                            break;
    case BLUE_ONCEMORE_NUMBER: {
        Rect.left = originalRect.left - shrinkAmount;
        Rect.top = originalRect.top - shrinkAmount;
        Rect.right = originalRect.right + shrinkAmount;
        Rect.bottom = originalRect.bottom + shrinkAmount;

        WCHAR scoreStr[64];
        m_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //�m��
        swprintf_s(scoreStr, L"ONCE\nMORE                      ");
        m_pRenderTarget->DrawText(
            scoreStr,
            26,
            m_pTextFormat,
            Rect,
            m_pBrush
        );
    }
                             break;
    default:
        break;
    }
}

