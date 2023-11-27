#pragma once
#include "Area.h"

class Area_Game : public Area
{
public:
	Area_Game(Common* pcommon) : Area(pcommon) { ; }


	void Draw(int x, int y, int width, int height) override {
        ID2D1SolidColorBrush* pBrush;

        D2D1_RECT_F game_rectangle = D2D1::RectF(x + width * 1, y + height * 1, x + width * 6, y + height * 6);
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &pBrush);
        //m_pRenderTarget->FillRectangle(&game_rectangle, pBrush);
        ///正中間背景
        m_pRenderTarget->DrawBitmap(BM->Mid_BackgroundBitmap, game_rectangle);
        // 比大小區域
        D2D1_RECT_F game_guess_rectangle = D2D1::RectF(x + width * 3, y + height * 4.5, x + width * 4, y + height * 5);
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(55.0f / 255.0f, 22.0f / 205, 20.0f / 255.0f, 1.0f)), &pBrush);
        m_pRenderTarget->FillRectangle(&game_guess_rectangle, pBrush);
        WCHAR scoreStr[64];
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightPink), &pBrush);
        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中
        swprintf_s(scoreStr, L"%d                                                  ", common->ESM->Comparenumber);
        m_pRenderTarget->DrawText(
            scoreStr,
            30,
            m_pTextFormat,
            game_guess_rectangle,
            pBrush
        );
        if (isLight(common->ESM->Compare_Light_map, 0)) { //TODO 判斷大小燈亮
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
            m_pRenderTarget->FillEllipse(
                D2D1::Ellipse(D2D1::Point2F(x + width * 2.75, y + height * 4.75), LIGHT_SIZE, LIGHT_SIZE),
                pBrush);
        }
        else {
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkRed), &pBrush);
            m_pRenderTarget->FillEllipse(
                D2D1::Ellipse(D2D1::Point2F(x + width * 2.75, y + height * 4.75), LIGHT_SIZE, LIGHT_SIZE),
                pBrush);
        }
        if (isLight(common->ESM->Compare_Light_map, 1)) { //TODO 判斷大小燈亮
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
            m_pRenderTarget->FillEllipse(
                D2D1::Ellipse(D2D1::Point2F(x + width * 4.25, y + height * 4.75), LIGHT_SIZE, LIGHT_SIZE),
                pBrush);
        }
        else {
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkRed), &pBrush);
            m_pRenderTarget->FillEllipse(
                D2D1::Ellipse(D2D1::Point2F(x + width * 4.25, y + height * 4.75), LIGHT_SIZE, LIGHT_SIZE),
                pBrush);
        }




        for (int j = 0; j < GAME_SIZE; ++j) { //遊戲區域分成7*7
            for (int i = 0; i < GAME_SIZE; ++i) {
                if ((i == 0 || i == GAME_SIZE - 1) ||
                    (j == 0 || j == GAME_SIZE - 1)) {
                    //判斷遊戲格子編號
                    int light_number = -1;
                    if (j == 0 && i == 0) {
                        // (0, 0) 處理邏輯
                        light_number = 0;
                    }
                    else if (j == 0 && i == 1) {
                        // (0, 1) 處理邏輯
                        light_number = 1;
                    }
                    else if (j == 0 && i == 2) {
                        // (0, 2) 處理邏輯
                        light_number = 2;
                    }
                    else if (j == 0 && i == 3) {
                        // (0, 3) 處理邏輯
                        light_number = 3;
                    }
                    else if (j == 0 && i == 4) {
                        // (0, 4) 處理邏輯
                        light_number = 4;
                    }
                    else if (j == 0 && i == 5) {
                        // (0, 5) 處理邏輯
                        light_number = 5;
                    }
                    else if (j == 0 && i == 6) {
                        // (0, 6) 處理邏輯
                        light_number = 6;
                    }
                    else if (j == 1 && i == 6) {
                        // (1, 6) 處理邏輯
                        light_number = 7;
                    }
                    else if (j == 2 && i == 6) {
                        // (2, 6) 處理邏輯
                        light_number = 8;
                    }
                    else if (j == 3 && i == 6) {
                        // (3, 6) 處理邏輯
                        light_number = 9;
                    }
                    else if (j == 4 && i == 6) {
                        // (4, 6) 處理邏輯
                        light_number = 10;
                    }
                    else if (j == 5 && i == 6) {
                        // (5, 6) 處理邏輯
                        light_number = 11;
                    }
                    else if (j == 6 && i == 6) {
                        // (6, 6) 處理邏輯
                        light_number = 12;
                    }
                    else if (j == 6 && i == 5) {
                        // (6, 5) 處理邏輯
                        light_number = 13;
                    }
                    else if (j == 6 && i == 4) {
                        // (6, 4) 處理邏輯
                        light_number = 14;
                    }
                    else if (j == 6 && i == 3) {
                        // (6, 3) 處理邏輯
                        light_number = 15;
                    }
                    else if (j == 6 && i == 2) {
                        // (6, 2) 處理邏輯
                        light_number = 16;
                    }
                    else if (j == 6 && i == 1) {
                        // (6, 1) 處理邏輯
                        light_number = 17;
                    }
                    else if (j == 6 && i == 0) {
                        // (6, 0) 處理邏輯
                        light_number = 18;
                    }
                    else if (j == 5 && i == 0) {
                        // (5, 0) 處理邏輯
                        light_number = 19;
                    }
                    else if (j == 4 && i == 0) {
                        // (4, 0) 處理邏輯
                        light_number = 20;
                    }
                    else if (j == 3 && i == 0) {
                        // (3, 0) 處理邏輯
                        light_number = 21;
                    }
                    else if (j == 2 && i == 0) {
                        // (2, 0) 處理邏輯
                        light_number = 22;
                    }

                    else if (j == 1 && i == 0) {
                        // (1, 0) 處理邏輯
                        light_number = 23;
                    }
                    else {
                        // 其他格子的處理邏輯
                        light_number = -1;
                    }
                    D2D1_RECT_F grid_rectangle = D2D1::RectF(x + width * i, y + height * j,
                        x + width * (i + 1), y + height * (j + 1));

                    //底色
                    if (isLight(common->ESM->Game_Light_map, light_number)) {
                        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &pBrush);
                    }
                    else {
                        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
                    }
                    m_pRenderTarget->FillRectangle(&grid_rectangle, pBrush);
                    //黑色框線
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
                    m_pRenderTarget->DrawRectangle(&grid_rectangle, pBrush, 2.0f);

                    //圖片
                    Draw_Cell(common->SM->Get_CellNumber(light_number), grid_rectangle);

                    //燈號
                    if (isLight(common->ESM->Game_Light_map, light_number)) {
                        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
                    }
                    else {
                        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkRed), &pBrush);
                    }
                    m_pRenderTarget->FillEllipse(
                        D2D1::Ellipse(D2D1::Point2F(x + width * (i + 0.5), y + height * (j + 1) - 8), LIGHT_SIZE, LIGHT_SIZE),
                        pBrush);
                }
            }
        }
	}

    void Logic_Bet() {


        int cellNumber = common->SM->Get_CellNumber(common->ESM->position);
        int currentHour = common->ESM->position; //設開始為N 結束為Y
        int lightIndex = 0;

        for (int i = 0; i < GAME_TOTAL; ++i) { //從n開始 到23 再從0開始 到n
            currentHour = (currentHour + 1) % 24;
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * lightIndex, currentHour, 1);
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex + 1), currentHour, 0);
            ++lightIndex;
        }
        if (common->ESM->endPosition > common->ESM->position) { //若Y大於N
            //MessageBox(NULL, L"Y大於N", L"測試", MB_OK);
            for (int i = 0; i <= common->ESM->endPosition; ++i) {
                currentHour = (currentHour + 1) % 24;
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex), currentHour, 1);
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex + 2), currentHour, 0);
                lightIndex += 2;
            }
            int ire = lightIndex;
        }
        else {  //若Y小於N
            //MessageBox(NULL, L"Y小於N", L"測試", MB_OK);
            for (int i = common->ESM->position; i < GAME_TOTAL; ++i) {
                currentHour = (currentHour + 1) % 24;
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex), currentHour, 1);
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex + 1), currentHour, 0);
                ++lightIndex;

            }
            for (int i = 0; i <= common->ESM->endPosition; ++i) {
                currentHour = (currentHour + 1) % 24;
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex), currentHour, 1);
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex + 2), currentHour, 0);
                lightIndex += 2;
            }
            int itr = lightIndex;
        }

        //std::wstring  WStr = std::to_wstring(lightsecond * (lightIndex));
        //OutputDebugString(L"common->ESM->currentTime = ");
        //OutputDebugString(WStr.c_str());
        //OutputDebugString(L"\n");
        cellNumber = common->SM->Get_CellNumber(currentHour);

        for (int i = 0; i <= 4; ++i) {
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex), currentHour, 1);
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex + 1), currentHour, 0);
            lightIndex += 2;
        }
        common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex), currentHour, 1);

        common->ESM->endTime = common->ESM->currentTime + lightsecond * (lightIndex); //更新結束時間
        common->ESM->position = currentHour; //更新起點
        // 結算

    }

    void Logic_Compare() {
        long long& currentTime = common->ESM->currentTime;
        long long& endTime = common->ESM->endTime;
        int lightIndex = 0;

        // 清空面板
        common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime, common->ESM->position, 0);
        if (common->ESM->endCompare < 5)
            common->ESM->SetLightStatus(common->ESM->Compare_Light_call_map, currentTime, SMALL_NUMBER, 0);
        else
            common->ESM->SetLightStatus(common->ESM->Compare_Light_call_map, currentTime, BIG_NUMBER, 0);

        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        common->ESM->endCompare = std::rand() % 10; //   
        common->ESM->endCompare = 5; //   

        int timeadd = 0, timediv = 10;
        for (int i = 0; i <= 10; ++i) {
            std::srand(static_cast<unsigned int>((std::time(nullptr) + i) % timediv++));
            int random_number1 = std::rand() % 10;
            SetCompareNumber(currentTime + lightsecond * (lightIndex), random_number1);
            if (random_number1 < 5) {
                common->ESM->SetLightStatus(common->ESM->Compare_Light_call_map, currentTime + lightsecond * (lightIndex), SMALL_NUMBER, 1);
                common->ESM->SetLightStatus(common->ESM->Compare_Light_call_map, currentTime + lightsecond * (lightIndex + 1), SMALL_NUMBER, 0);

                for (int i = 18; i <= GAME_TOTAL; ++i) {
                    int j = i % 24; //
                    common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
                    common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex + 1), j, 0);
                }
            }
            else {
                common->ESM->SetLightStatus(common->ESM->Compare_Light_call_map, currentTime + lightsecond * (lightIndex), BIG_NUMBER, 1);
                common->ESM->SetLightStatus(common->ESM->Compare_Light_call_map, currentTime + lightsecond * (lightIndex + 1), BIG_NUMBER, 0);
                for (int i = 6; i <= 12; ++i) {
                    int j = i % 24; //
                    common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
                    common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex + 1), j, 0);
                }
            }
            lightIndex += 2;
        }
        SetCompareNumber(currentTime + lightsecond * (lightIndex), common->ESM->endCompare);
        common->ESM->endTime = currentTime + lightsecond * (lightIndex); //更新結束時間
        if (common->ESM->endCompare < 5) {
            common->ESM->SetLightStatus(common->ESM->Compare_Light_call_map, currentTime + lightsecond * (lightIndex), SMALL_NUMBER, 1);
            for (int i = 18; i <= GAME_TOTAL; ++i) {
                int j = i % 24; //
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex + 3), j, 0);
            }
        }
        else {
            common->ESM->SetLightStatus(common->ESM->Compare_Light_call_map, currentTime + lightsecond * (lightIndex), BIG_NUMBER, 1);
            for (int i = 6; i <= 12; ++i) {
                int j = i % 24; //
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex + 3), j, 0);
            }
        }
        common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex + 3), common->ESM->position, 1);
        // 結算
    }

    void Logic_idle() {
        //OutputDebugString(L"idle\n");
        long long& currentTime = common->ESM->currentTime;
        long long& endTime = common->ESM->endTime;
        int lightIndex = 0;
        // 清空面板
        common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime, common->ESM->position, 0);

        for (int i = 0; i < GAME_TOTAL; i += 2) {
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex + 1), i, 0);
        }

        lightIndex += 2;

        for (int i = 1; i < GAME_TOTAL; i += 2) {
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex + 1), i, 0);
        }

        lightIndex += 2;

        for (int i = 0; i < GAME_TOTAL; ++i) {
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex + 5), i, 0);
            ++lightIndex;
        }

        if (common->ESM->bet_started) {

            for (int i = 0; i <= common->ESM->position; ++i) {
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex + 5), i, 0);
                ++lightIndex;
            }

            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, currentTime + lightsecond * (lightIndex + 4), common->ESM->position, 1);
        }
        common->ESM->endTime = currentTime + lightsecond * (lightIndex); //更新結束時間
    }

    bool isLight(std::map<int, bool> map, int number) {
        auto it = map.find(number);
        if (it != map.end()) {
            return it->second;
        }
        // 如果找不到對應的鍵值，也返回 false
        return false;
    }

    void SetCompareNumber(int time, int number) {
        common->ESM->Compare_Number_map.insert(std::make_pair(time, number));
    }
};
