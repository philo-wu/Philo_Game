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
            D2D1_RECT_F Clear_rectangle = D2D1::RectF(x + width * i, y + height * 0.25, x + width * (i + 1), y + height * 0.5);
            D2D1_RECT_F Add_1_rectangle = D2D1::RectF(x + width * i, y, x + width * (i + 0.5), y + height * 0.25);
            D2D1_RECT_F Add_10_rectangle = D2D1::RectF(x + width * (i + 0.5), y, x + width * (i + 1), y + height * 0.25);

            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
            m_pRenderTarget->DrawRectangle(&bet_rectangle, pBrush, 4.0f);

            if (ESM->bet_settling || ESM->compare_settling || common->SM->GetWinScore() > 0)
            {
                m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
                m_pRenderTarget->FillRectangle(&bet_rectangle, pBrush);
            }
            else {
                if (isLight(common->ESM->Clear_Light_map, i)) 
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &pBrush);
                else
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
                m_pRenderTarget->FillRectangle(&Clear_rectangle, pBrush);

                if (isLight(common->ESM->One_Light_map, i))
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &pBrush);
                else
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
                m_pRenderTarget->FillRectangle(&Add_1_rectangle, pBrush);

                if (isLight(common->ESM->Ten_Light_map, i))
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &pBrush);
                else
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
                m_pRenderTarget->FillRectangle(&Add_10_rectangle, pBrush);
            }


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
        if (ESM->state != STATE_BET_SETTLING &&
            ESM->state != STATE_COMPARE_SETTLING)
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

    void ClickFunction(int xPos, int yPos, HWND hWnd) {
        int bet_or_function = 0;
        if (yPos >= FUNCTION_Y &&
            yPos < FUNCTION_Y + FUNCTION_HEIGHT * BET_RATIO) {
            bet_or_function = FUNCTION_BET_NUMBER;
        }
        else if (yPos >= FUNCTION_Y + FUNCTION_HEIGHT * BET_RATIO &&
            yPos < FUNCTION_Y + FUNCTION_HEIGHT) {
            bet_or_function = FUNCTION_NUMBER;
        }
        else {
            bet_or_function = GRID_NUMBER;
        }


        switch (bet_or_function)
        {

        case GRID_NUMBER: {
            if (common->ESM->bet_settling || common->ESM->compare_settling) break; //開始遊戲後 動畫停止前不接受指令

            break;
        }
        case FUNCTION_BET_NUMBER: {
            if (common->ESM->bet_settling || common->ESM->compare_settling) break; //開始遊戲後 動畫停止前不接受指令

            if (common->SM->GetWinScore() > 0) {
                MessageBox(hWnd, L"請先按得分", L"錯誤", MB_OK);
                break; //若有得分則不能遊戲
            }
            xPos -= FUNCTION_X;
            yPos -= FUNCTION_Y;
            int width = BET_WIDTH;
            int number , action;
            if (xPos >= width * 0 &&
                xPos <= width * 1) {
                // BAR
                number = BAR_NUMBER;
                if (yPos >= FUNCTION_HEIGHT * 0.25) {
                    //common->SM->Bet_call(BAR_NUMBER, 0);
                    action = 0;
                }
                else if (xPos >= width * 0 &&
                    xPos <= width * 0.5) {
                    //common->SM->Bet_call(BAR_NUMBER, 1);
                    action = 1;

                }
                else if (
                    xPos > width * 0.5 &&
                    xPos <= width * 1) {
                    //common->SM->Bet_call(BAR_NUMBER, 10);
                    action = 10;

                }
            }
            else if (
                xPos >= width * 1 &&
                xPos <= width * 2) {
                // SEVEN
                number = SEVEN_NUMBER;

                if (yPos >= FUNCTION_HEIGHT * 0.25) {
                    //common->SM->Bet_call(SEVEN_NUMBER, 0);
                    action = 0;

                }
                else if (xPos >= width * 1 &&
                    xPos <= width * 1.5) {
                    //common->SM->Bet_call(SEVEN_NUMBER, 1);
                    action = 1;

                }
                else if (
                    xPos > width * 1.5 &&
                    xPos <= width * 2) {
                    //common->SM->Bet_call(SEVEN_NUMBER, 10);
                    action = 10;

                }
            }
            else if (
                xPos >= width * 2 &&
                xPos <= width * 3) {
                // STAR
                number = STAR_NUMBER;

                if (yPos >= FUNCTION_HEIGHT * 0.25) {
                    //common->SM->Bet_call(STAR_NUMBER, 0);
                    action = 0;

                }
                else if (xPos >= width * 2 &&
                    xPos <= width * 2.5) {
                    //common->SM->Bet_call(STAR_NUMBER, 1);
                    action = 1;

                }
                else if (
                    xPos > width * 2.5 &&
                    xPos <= width * 3) {
                    //common->SM->Bet_call(STAR_NUMBER, 10);
                    action = 10;

                }
            }
            else if (
                xPos >= width * 3 &&
                xPos <= width * 4) {
                // WATERMELOM
                number = WATERMELOM_NUMBER;

                if (yPos >= FUNCTION_HEIGHT * 0.25) {
                    //common->SM->Bet_call(WATERMELOM_NUMBER, 0);
                    action = 0;

                }
                else if (xPos >= width * 3 &&
                    xPos <= width * 3.5) {
                    //common->SM->Bet_call(WATERMELOM_NUMBER, 1);
                    action = 1;

                }
                else if (
                    xPos > width * 3.5 &&
                    xPos <= width * 4) {
                    //common->SM->Bet_call(WATERMELOM_NUMBER, 10);
                    action = 10;

                }
            }
            else if (
                xPos >= width * 4 &&
                xPos <= width * 5) {
                // BELL
                number = BELL_NUMBER;

                if (yPos >= FUNCTION_HEIGHT * 0.25) {
                    //common->SM->Bet_call(BELL_NUMBER, 0);
                    action = 0;

                }
                else if (xPos >= width * 4 &&
                    xPos <= width * 4.5) {
                    //common->SM->Bet_call(BELL_NUMBER, 1);
                    action = 1;

                }
                else if (
                    xPos > width * 4.5 &&
                    xPos <= width * 5) {
                    //common->SM->Bet_call(BELL_NUMBER, 10);
                    action = 10;

                }
            }
            else if (
                xPos >= width * 5 &&
                xPos <= width * 6) {
                // LEMON
                number = LEMON_NUMBER;

                if (yPos >= FUNCTION_HEIGHT * 0.25) {
                    //common->SM->Bet_call(LEMON_NUMBER, 0);
                    action = 0;

                }
                else if (xPos >= width * 5 &&
                    xPos <= width * 5.5) {
                    //common->SM->Bet_call(LEMON_NUMBER, 1);
                    action = 1;

                }
                else if (
                    xPos > width * 5.5 &&
                    xPos <= width * 6) {
                    //common->SM->Bet_call(LEMON_NUMBER, 10);
                    action = 10;

                }
            }
            else if (
                xPos >= width * 6 &&
                xPos <= width * 7) {
                // ORANGE
                number = ORANGE_NUMBER;

                if (yPos >= FUNCTION_HEIGHT * 0.25) {
                    //common->SM->Bet_call(ORANGE_NUMBER, 0);
                    action = 0;

                }
                else if (xPos >= width * 6 &&
                    xPos <= width * 6.5) {
                    //common->SM->Bet_call(ORANGE_NUMBER, 1);
                    action = 1;

                }
                else if (
                    xPos > width * 6.5 &&
                    xPos <= width * 7) {
                    //common->SM->Bet_call(ORANGE_NUMBER, 10);
                    action = 10;

                }
            }
            else if (
                xPos >= width * 7 &&
                xPos <= width * 8) {
                // APPLE
                number = APPLE_NUMBER;

                if (yPos >= FUNCTION_HEIGHT * 0.25) {
                    //common->SM->Bet_call(APPLE_NUMBER, 0);
                    action = 0;

                }
                else if (xPos >= width * 7 &&
                    xPos <= width * 7.5) {
                    //common->SM->Bet_call(APPLE_NUMBER, 1);
                    action = 1;

                }
                else if (
                    xPos > width * 7.5 &&
                    xPos <= width * 8) {
                    //common->SM->Bet_call(APPLE_NUMBER, 10);
                    action = 10;

                }

            }
            common->SM->Bet_call(number, action);
            long long currentTime = common->ESM->currentTime;
            // @點擊反應
            if (action == 0) {
                common->ESM->SetLightStatus(common->ESM->Clear_Light_call_map, currentTime , number, 1);
                common->ESM->SetLightStatus(common->ESM->Clear_Light_call_map, currentTime + 200, number, 0);
            }
            else if (action == 1) {
                common->ESM->SetLightStatus(common->ESM->One_Light_call_map, currentTime, number, 1);
                common->ESM->SetLightStatus(common->ESM->One_Light_call_map, currentTime + 200, number, 0);

            }
            else if (action == 10) {
                common->ESM->SetLightStatus(common->ESM->Ten_Light_call_map, currentTime, number, 1);
                common->ESM->SetLightStatus(common->ESM->Ten_Light_call_map, currentTime + 200, number, 0);
            }
            break;
        }
        case FUNCTION_NUMBER: {
            // TODO :: 變數要改成Draw_Function同步 ,目標為修改其中一方即可
            // width * 0.225 為不好的用法 0.225應改成變數

            xPos -= FUNCTION_X;
            int width = FUNCTION_WIDTH;

            if (xPos >= width * 0.225 &&
                xPos <= width * 1.525) {
                // 離開遊戲
                //if (engine->bet_settling || engine->compare_settling) break; //開始遊戲後 動畫停止前不接受指令
                if (common->ESM->state == STATE_IDLE)
                    SendMessage(hWnd, WM_CUSTOM_GAMEEND, 0, 0);
            }
            else if (xPos >= width * 1.725 &&
                xPos <= width * 2.625) {
                // 小
                if (common->ESM->state == STATE_BET_SETTLING ||
                    common->ESM->state == STATE_COMPARE_SETTLING) {
                    common->ESM->compare_starting = 1;
                    common->ESM->SetBigOrSmall(0);
                }
            }
            else if (xPos >= width * 2.825 &&
                xPos <= width * 3.725) {
                // 大
                if (common->ESM->state == STATE_BET_SETTLING ||
                    common->ESM->state == STATE_COMPARE_SETTLING) {
                    common->ESM->compare_starting = 1;
                    common->ESM->SetBigOrSmall(1);
                }

            }
            else if (xPos >= width * 3.925 &&
                xPos <= width * 5.225) {
                // 得分
                if (common->ESM->state == STATE_BET_SETTLING ||
                    common->ESM->state == STATE_COMPARE_SETTLING) {
                    common->SM->WinToScore();
                }
            }
            else if (xPos >= width * 5.425 &&
                xPos <= width * 6.325) {
                // 自動
                if (common->ESM->autoing) {
                    common->ESM->autoing = 0;
                }
                if (common->ESM->state != STATE_IDLE)
                    break;

                if (common->ESM->autoing) {
                    common->ESM->autoing = 0;
                }
                else {
                    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
                    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() % 1000;
                    common->ESM->endTime = seconds * 1000 + milliseconds - 2000; //控制自動開始時間
                    common->ESM->autoing = 1;

                }
            }
            else if (xPos >= width * 6.525 &&
                xPos <= width * 7.825) {
                // 開始
                if (common->ESM->bet_settling || common->ESM->compare_settling) break; //開始遊戲後 動畫停止前不接受指令
                if (common->SM->GetWinScore() > 0) {
                    MessageBox(hWnd, L"請先按得分", L"錯誤", MB_OK);
                    break; //若有得分則不能繼續遊戲
                }
                if (common->ESM->autoing) {
                    MessageBox(hWnd, L"會自動開始", L"錯誤", MB_OK);
                    break; //若開啟自動則由自動啟動
                }
                if (common->ESM->state == STATE_IDLE)
                    common->ESM->bet_starting = 1;
            }
            break;
        }
        default:
            break;
        }
    }

    bool isLight(std::map<int, bool> map, int number) {
        auto it = map.find(number);
        if (it != map.end()) {
            return it->second;
        }
        // 如果找不到對應的鍵值，也返回 false
        return false;
    }

};
