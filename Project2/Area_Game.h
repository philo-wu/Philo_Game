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
        ///�������I��
        m_pRenderTarget->DrawBitmap(BM->Mid_BackgroundBitmap, game_rectangle);
        // ��j�p�ϰ�
        D2D1_RECT_F game_guess_rectangle = D2D1::RectF(x + width * 3, y + height * 4.5, x + width * 4, y + height * 5);
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(55.0f / 255.0f, 22.0f / 205, 20.0f / 255.0f, 1.0f)), &pBrush);
        m_pRenderTarget->FillRectangle(&game_guess_rectangle, pBrush);
        WCHAR scoreStr[64];
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightPink), &pBrush);
        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //�m��
        swprintf_s(scoreStr, L"%d                                                  ", common->ESM->Comparenumber);
        m_pRenderTarget->DrawText(
            scoreStr,
            30,
            m_pTextFormat,
            game_guess_rectangle,
            pBrush
        );
        if (isLight(common->ESM->Compare_Light_map, 0)) { //TODO �P�_�j�p�O�G
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
        if (isLight(common->ESM->Compare_Light_map, 1)) { //TODO �P�_�j�p�O�G
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




        for (int j = 0; j < GAME_SIZE; ++j) { //�C���ϰ����7*7
            for (int i = 0; i < GAME_SIZE; ++i) {
                if ((i == 0 || i == GAME_SIZE - 1) ||
                    (j == 0 || j == GAME_SIZE - 1)) {
                    //�P�_�C����l�s��
                    int light_number = -1;
                    if (j == 0 && i == 0) {
                        // (0, 0) �B�z�޿�
                        light_number = 0;
                    }
                    else if (j == 0 && i == 1) {
                        // (0, 1) �B�z�޿�
                        light_number = 1;
                    }
                    else if (j == 0 && i == 2) {
                        // (0, 2) �B�z�޿�
                        light_number = 2;
                    }
                    else if (j == 0 && i == 3) {
                        // (0, 3) �B�z�޿�
                        light_number = 3;
                    }
                    else if (j == 0 && i == 4) {
                        // (0, 4) �B�z�޿�
                        light_number = 4;
                    }
                    else if (j == 0 && i == 5) {
                        // (0, 5) �B�z�޿�
                        light_number = 5;
                    }
                    else if (j == 0 && i == 6) {
                        // (0, 6) �B�z�޿�
                        light_number = 6;
                    }
                    else if (j == 1 && i == 6) {
                        // (1, 6) �B�z�޿�
                        light_number = 7;
                    }
                    else if (j == 2 && i == 6) {
                        // (2, 6) �B�z�޿�
                        light_number = 8;
                    }
                    else if (j == 3 && i == 6) {
                        // (3, 6) �B�z�޿�
                        light_number = 9;
                    }
                    else if (j == 4 && i == 6) {
                        // (4, 6) �B�z�޿�
                        light_number = 10;
                    }
                    else if (j == 5 && i == 6) {
                        // (5, 6) �B�z�޿�
                        light_number = 11;
                    }
                    else if (j == 6 && i == 6) {
                        // (6, 6) �B�z�޿�
                        light_number = 12;
                    }
                    else if (j == 6 && i == 5) {
                        // (6, 5) �B�z�޿�
                        light_number = 13;
                    }
                    else if (j == 6 && i == 4) {
                        // (6, 4) �B�z�޿�
                        light_number = 14;
                    }
                    else if (j == 6 && i == 3) {
                        // (6, 3) �B�z�޿�
                        light_number = 15;
                    }
                    else if (j == 6 && i == 2) {
                        // (6, 2) �B�z�޿�
                        light_number = 16;
                    }
                    else if (j == 6 && i == 1) {
                        // (6, 1) �B�z�޿�
                        light_number = 17;
                    }
                    else if (j == 6 && i == 0) {
                        // (6, 0) �B�z�޿�
                        light_number = 18;
                    }
                    else if (j == 5 && i == 0) {
                        // (5, 0) �B�z�޿�
                        light_number = 19;
                    }
                    else if (j == 4 && i == 0) {
                        // (4, 0) �B�z�޿�
                        light_number = 20;
                    }
                    else if (j == 3 && i == 0) {
                        // (3, 0) �B�z�޿�
                        light_number = 21;
                    }
                    else if (j == 2 && i == 0) {
                        // (2, 0) �B�z�޿�
                        light_number = 22;
                    }

                    else if (j == 1 && i == 0) {
                        // (1, 0) �B�z�޿�
                        light_number = 23;
                    }
                    else {
                        // ��L��l���B�z�޿�
                        light_number = -1;
                    }
                    D2D1_RECT_F grid_rectangle = D2D1::RectF(x + width * i, y + height * j,
                        x + width * (i + 1), y + height * (j + 1));

                    //����
                    if (isLight(common->ESM->Game_Light_map, light_number)) {
                        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &pBrush);
                    }
                    else {
                        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
                    }
                    m_pRenderTarget->FillRectangle(&grid_rectangle, pBrush);
                    //�¦�ؽu
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
                    m_pRenderTarget->DrawRectangle(&grid_rectangle, pBrush, 2.0f);

                    //�Ϥ�
                    Draw_Cell(common->SM->Get_CellNumber(light_number), grid_rectangle);

                    //�O��
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
        int currentHour = common->ESM->position; //�]�}�l��N ������Y
        int lightIndex = 0;

        for (int i = 0; i < GAME_TOTAL; ++i) { //�qn�}�l ��23 �A�q0�}�l ��n
            currentHour = (currentHour + 1) % 24;
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * lightIndex, currentHour, 1);
            common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex + 1), currentHour, 0);
            ++lightIndex;
        }
        if (common->ESM->endPosition > common->ESM->position) { //�YY�j��N
            //MessageBox(NULL, L"Y�j��N", L"����", MB_OK);
            for (int i = 0; i <= common->ESM->endPosition; ++i) {
                currentHour = (currentHour + 1) % 24;
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex), currentHour, 1);
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime + lightsecond * (lightIndex + 2), currentHour, 0);
                lightIndex += 2;
            }
            int ire = lightIndex;
        }
        else {  //�YY�p��N
            //MessageBox(NULL, L"Y�p��N", L"����", MB_OK);
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

        common->ESM->endTime = common->ESM->currentTime + lightsecond * (lightIndex); //��s�����ɶ�
        common->ESM->position = currentHour; //��s�_�I
        // ����

    }

    void Logic_Compare() {
        long long& currentTime = common->ESM->currentTime;
        long long& endTime = common->ESM->endTime;
        int lightIndex = 0;

        // �M�ŭ��O
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
        common->ESM->endTime = currentTime + lightsecond * (lightIndex); //��s�����ɶ�
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
        // ����
    }

    void Logic_idle() {
        //OutputDebugString(L"idle\n");
        long long& currentTime = common->ESM->currentTime;
        long long& endTime = common->ESM->endTime;
        int lightIndex = 0;
        // �M�ŭ��O
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
        common->ESM->endTime = currentTime + lightsecond * (lightIndex); //��s�����ɶ�
    }

    bool isLight(std::map<int, bool> map, int number) {
        auto it = map.find(number);
        if (it != map.end()) {
            return it->second;
        }
        // �p�G�䤣���������ȡA�]��^ false
        return false;
    }

    void SetCompareNumber(int time, int number) {
        common->ESM->Compare_Number_map.insert(std::make_pair(time, number));
    }
};
