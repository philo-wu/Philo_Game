#pragma once
#include "Area.h"



class Area_Function : public Area
{
public:
	Area_Function(Common* pcommon) : Area(pcommon) { ; }

	void Draw(int x, int y, int width, int height) override {

        D2D1_RECT_F function_rectangle = D2D1::RectF(x, y, x + width * BET_TOTAL, y + height); // BET_TOTAL為還原width
        ID2D1SolidColorBrush* pBrush;
        ID2D1SolidColorBrush* p_Pen_Brush;
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &p_Pen_Brush);
        WCHAR scoreStr[64];
        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中

        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
        m_pRenderTarget->FillRectangle(&function_rectangle, pBrush);

        for (int i = 0; i < BET_TOTAL; ++i) {
            D2D1_RECT_F bet_rectangle = D2D1::RectF(x + width * i, y, x + width * (i + 1), y + height * 0.5);
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
            m_pRenderTarget->DrawRectangle(&bet_rectangle, pBrush, 4.0f);
            if (ESM->bet_settling || ESM->compare_settling || common->SM->GetWinScore() > 0)
                m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
            else
                m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
            m_pRenderTarget->FillRectangle(&bet_rectangle, pBrush);

            D2D1_RECT_F Add_1_rectangle = D2D1::RectF(x + width * i, y, x + width * (i + 0.5), y + height * 0.25);
            D2D1_RECT_F Add_10_rectangle = D2D1::RectF(x + width * (i + 0.5), y, x + width * (i + 1), y + height * 0.25);
            D2D1_RECT_F Clear_rectangle = D2D1::RectF(x + width * i, y + height * 0.25, x + width * (i + 1), y + height * 0.5);
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
            m_pRenderTarget->DrawRectangle(&Add_1_rectangle, pBrush, 2.0f);
            m_pRenderTarget->DrawRectangle(&Add_10_rectangle, pBrush, 2.0f);

            swprintf_s(scoreStr, L"1                                                  ");
            m_pRenderTarget->DrawText(
                scoreStr,
                30,
                m_pTextFormat,
                Add_1_rectangle,
                p_Pen_Brush
            );
            swprintf_s(scoreStr, L"10                                                  ");
            m_pRenderTarget->DrawText(
                scoreStr,
                30,
                m_pTextFormat,
                Add_10_rectangle,
                p_Pen_Brush
            );
            swprintf_s(scoreStr, L"CLEAR                                                  ");
            m_pRenderTarget->DrawText(
                scoreStr,
                30,
                m_pTextFormat,
                Clear_rectangle,
                p_Pen_Brush
            );
        }



        // 分配功能鍵區域
        // TODO 這裡*的比例為人工計算,具體按鍵公式可在調整
        D2D1_RECT_F exit_rectangle = D2D1::RectF(x + width * 0.225, y + height * BET_RATIO, x + width * 1.525, y + height);
        D2D1_RECT_F small_rectangle = D2D1::RectF(x + width * 1.725, y + height * BET_RATIO, x + width * 2.625, y + height);
        D2D1_RECT_F big_rectangle = D2D1::RectF(x + width * 2.825, y + height * BET_RATIO, x + width * 3.725, y + height);
        D2D1_RECT_F score_rectangle = D2D1::RectF(x + width * 3.925, y + height * BET_RATIO, x + width * 5.225, y + height);
        D2D1_RECT_F auto_rectangle = D2D1::RectF(x + width * 5.425, y + height * BET_RATIO, x + width * 6.325, y + height);
        D2D1_RECT_F start_rectangle = D2D1::RectF(x + width * 6.525, y + height * BET_RATIO, x + width * 7.825, y + height);


        //繪製綠色按鈕
        if (ESM->state != STATE_IDLE)
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
        else
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pBrush);
        m_pRenderTarget->FillRectangle(&exit_rectangle, pBrush);
        swprintf_s(scoreStr, L"離開遊戲\nEXIT                                                  ");
        m_pRenderTarget->DrawText(
            scoreStr,
            30,
            m_pTextFormat,
            exit_rectangle,
            p_Pen_Brush
        );
        if (ESM->state != STATE_IDLE)
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
        else
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pBrush);
        m_pRenderTarget->FillRectangle(&start_rectangle, pBrush);
        swprintf_s(scoreStr, L"開始\nSTART                                                  ");
        m_pRenderTarget->DrawText(
            scoreStr,
            30,
            m_pTextFormat,
            start_rectangle,
            p_Pen_Brush
        );

        //繪製黃色按鈕
        if (ESM->state != STATE_BET_SETTLING)
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
        else
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &pBrush);
        m_pRenderTarget->FillRectangle(&small_rectangle, pBrush);
        swprintf_s(scoreStr, L"小\nSMALL                                                  ");
        m_pRenderTarget->DrawText(
            scoreStr,
            30,
            m_pTextFormat,
            small_rectangle,
            p_Pen_Brush
        );

        m_pRenderTarget->FillRectangle(&big_rectangle, pBrush);
        swprintf_s(scoreStr, L"大\nBIG                                                  ");
        m_pRenderTarget->DrawText(
            scoreStr,
            30,
            m_pTextFormat,
            big_rectangle,
            p_Pen_Brush
        );


        //繪製紅色按鈕
        if (ESM->state != STATE_BET_SETTLING &&
            ESM->state != STATE_COMPARE_SETTLING)
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
        else
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
        m_pRenderTarget->FillRectangle(&score_rectangle, pBrush);
        swprintf_s(scoreStr, L"得分\nSCORE                                                  ");
        m_pRenderTarget->DrawText(
            scoreStr,
            30,
            m_pTextFormat,
            score_rectangle,
            p_Pen_Brush
        );
        if (ESM->autoing)
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightYellow), &pBrush);
        else if (ESM->state != STATE_IDLE)
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
        else
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &pBrush);
        m_pRenderTarget->FillRectangle(&auto_rectangle, pBrush);
        swprintf_s(scoreStr, L"自動\nAUTO                                                  ");
        m_pRenderTarget->DrawText(
            scoreStr,
            30,
            m_pTextFormat,
            auto_rectangle,
            p_Pen_Brush
        );
    }



};
