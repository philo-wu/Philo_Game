#pragma once
#include "Area.h"


class Area_Bet : public Area
{
public:
	Area_Bet(Common* pcommon) : Area(pcommon) { ; }



	void Draw(int x, int y, int width, int height) override {
        ID2D1SolidColorBrush* pBrush;

        D2D1_RECT_F bet_rectangle = D2D1::RectF(x, y, x + width * BET_TOTAL, y + 200);
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pBrush);
        m_pRenderTarget->FillRectangle(&bet_rectangle, pBrush);

        for (int i = 0; i < BET_TOTAL; ++i) { //下注區域為BET_TOTAL種選項
            //頂部分數
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGreen), &pBrush);
            D2D1_RECT_F grid_top_rectangle = D2D1::RectF(x + width * (i), y,
                x + width * (i + 1), y + 50);
            m_pRenderTarget->FillRectangle(&grid_top_rectangle, pBrush);
            grid_top_rectangle = D2D1::RectF(x + width * (i), y + 10,
                x + width * (i + 1), y + 50);
            WCHAR scoreStr[64];
            int m_score = common->SM->Get_CellScore(i);
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
            m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中
            swprintf_s(scoreStr, L"%d                                                  ", m_score);
            m_pRenderTarget->DrawText(
                scoreStr,
                30,
                m_pTextFormat,
                grid_top_rectangle,
                pBrush
            );

            //下注數
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(55.0f / 255.0f, 22.0f / 205, 20.0f / 255.0f, 1.0f)), &pBrush);
            D2D1_RECT_F grid_bottom_rectangle = D2D1::RectF(x + width * (i), y + 50,
                x + width * (i + 1), y + 124);
            m_pRenderTarget->FillRectangle(&grid_bottom_rectangle, pBrush);
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightPink), &pBrush);
            int bet = common->SM->Bet_call_map[i];
            swprintf_s(scoreStr, L"%d                                                  ", bet);
            m_pRenderTarget->DrawText(
                scoreStr,
                38,
                m_pTextFormat,
                grid_bottom_rectangle,
                pBrush
            );
            //圖片
            D2D1_RECT_F grid_png_rectangle = D2D1::RectF(x + width * (i), y + 124,
                x + width * (i + 1), y + 200);

            if (isLight(i))
                m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &pBrush);
            else
                m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
            m_pRenderTarget->FillRectangle(&grid_png_rectangle, pBrush);
            Draw_Cell(i, grid_png_rectangle);


            //分界線
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pBrush);
            D2D1_RECT_F grid_rectangle = D2D1::RectF(x + width * (i + 1) - 1, y,
                x + width * (i + 1), y + 200);
            if (i != BET_TOTAL - 1)
                m_pRenderTarget->FillRectangle(&grid_rectangle, pBrush);

            if (isLight(i)) {
                m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
                m_pRenderTarget->FillEllipse(
                    D2D1::Ellipse(D2D1::Point2F(x + width * (i + 0.5), y + 8), LIGHT_SIZE, LIGHT_SIZE),
                    pBrush);
            }
            else {
                m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkRed), &pBrush);
                m_pRenderTarget->FillEllipse(
                    D2D1::Ellipse(D2D1::Point2F(x + width * (i + 0.5), y + 8), LIGHT_SIZE, LIGHT_SIZE),
                    pBrush);
            }
        }
    }

    void Logic_Bet() {

        int cellNumber = common->SM->Get_CellNumber(common->ESM->position);
        int currentHour = common->ESM->position; //設開始為N 結束為Y
        int lightIndex = 0;

        for (int i = 0; i < GAME_TOTAL; ++i) { //從n開始 到23 再從0開始 到n
            ++lightIndex;
        }
        if (common->ESM->endPosition > common->ESM->position) { //若Y大於N
            for (int i = 0; i <= common->ESM->endPosition; ++i) {
                currentHour = (currentHour + 1) % 24;
                lightIndex += 2;
            }
            int ire1 = lightIndex;

        }
        else {  //若Y小於N
            for (int i = common->ESM->position; i < GAME_TOTAL; ++i) {
                currentHour = (currentHour + 1) % 24;
                ++lightIndex;

            }
            for (int i = 0; i <= common->ESM->endPosition; ++i) {
                currentHour = (currentHour + 1) % 24;
                lightIndex += 2;
            }
            int ire1 = lightIndex;

        }
        cellNumber = common->SM->Get_CellNumber(currentHour);
        for (int i = 0; i <= 4; ++i) {
            common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex), cellNumber, 1);
            common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex + 1), cellNumber, 0);
            lightIndex += 2;
        }
        common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex), cellNumber, 1);

        //common->ESM->endTime = common->ESM->currentTime + lightsecond * (lightIndex); //更新結束時間
        //common->ESM->position = currentHour; //更新起點
        // 結算

    }

    void Logic_idle() {
        //OutputDebugString(L"idle\n");
        common->ESM->idleing = 1;
        long long& currentTime = common->ESM->currentTime;
        long long& endTime = common->ESM->endTime;
        int lightIndex = 0;

        // 清空面板
        common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, currentTime, common->SM->Get_CellNumber(common->ESM->position), 0);


        for (int i = 0; i < CELL_TOTAL; i += 2) {
            common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
            common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, currentTime + lightsecond * (lightIndex + 1), i, 0);
        }
        lightIndex += 2;
        for (int i = 1; i < CELL_TOTAL; i += 2) {
            common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
            common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, currentTime + lightsecond * (lightIndex + 1), i, 0);
        }
        lightIndex += 2;

        for (int i = 0; i < GAME_TOTAL; ++i) {
            int j = i % 8;
            common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
            common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, currentTime + lightsecond * (lightIndex + 1), j, 0);

            ++lightIndex;
        }

        if (common->ESM->bet_started) {

            for (int i = 0; i <= common->ESM->position; ++i) {
                int j = i % 8;
                common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
                common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, currentTime + lightsecond * (lightIndex + 5), j, 0);
                ++lightIndex;
            }

            common->ESM->SetLightStatus(common->ESM->Bet_Light_call_map, currentTime + lightsecond * (lightIndex + 4), common->SM->Get_CellNumber(common->ESM->position), 1);

        }
        //common->ESM->endTime = currentTime + lightsecond * (lightIndex); //更新結束時間
    }

    bool isLight(int number) {
        auto it = common->ESM->Bet_Light_map.find(number);
        if (it != common->ESM->Bet_Light_map.end()) {
            return it->second;
        }
        // 如果找不到對應的鍵值，也返回 false
        return false;
    }

    void Settlement(int number, bool pAutoing) {
        if (number == RED_ONCEMORE_NUMBER) {
            // 清空左邊四個
            for (int i = 0; i < 4; ++i) {
                if (pAutoing) {
                    if (!SM->CostScore((SM->Get_CellScore(i) * common->SM->Bet_call_map[i]))) {
                        MessageBox(NULL, L"金額不足,關閉自動模式", L"錯誤", MB_OK);
                        ESM->autoing = 0;
                    }
                }
                else {
                    common->SM->Bet_call_map[i] = 0;
                }
            }
        }
        else if (number == BLUE_ONCEMORE_NUMBER) {
            // 清空右邊四個
            for (int i = 4; i < CELL_TOTAL; ++i) {
                if (pAutoing) {
                    if (!SM->CostScore((SM->Get_CellScore(i) * common->SM->Bet_call_map[i]))) {
                        MessageBox(NULL, L"金額不足,關閉自動模式", L"錯誤", MB_OK);
                        ESM->autoing = 0;
                    }
                }
                else {
                    common->SM->Bet_call_map[i] = 0;
                }
            }
        }
        else {
            int cost = SM->Get_CellScore(number);
            SM->AddWinScore(common->SM->Bet_call_map[number] * cost * 2); //2為花費加上回報
            for (int i = 0; i < CELL_TOTAL; ++i) {
                if (ESM->autoing) {
                    if (!SM->CostScore((SM->Get_CellScore(i) * common->SM->Bet_call_map[i]))) {
                        MessageBox(NULL, L"金額不足,關閉自動模式", L"錯誤", MB_OK);
                        ESM->autoing = 0;
                    }
                }
                else {
                    common->SM->Bet_call_map[i] = 0;
                }
            }
        }
    };
};
