#include "framework.h"
#include "Engine.h"


Engine::Engine(Common* pcommon , HWND p_hwnd) : m_pDirect2dFactory(NULL), m_pRenderTarget(NULL), m_pWhiteBrush(NULL)
{
    //snake = new Snake();
    //food = new Food();
    //food->Reset(snake , isFoodOnBorderChecked );

    common = pcommon;
    m_hwnd = p_hwnd;
    InitializeD2D();
    playing = false;
    common->BM = new BitmapManager(
                            common,
                            m_pDirect2dFactory,
                            m_pRenderTarget,
                            m_pDWriteFactory,
                            m_pTextFormat,
                            m_pWhiteBrush);
    common->SM = new ScoreManager();
    common->ESM = new EngineStateManager();
    updata_Json();
    common->BM->init(m_hwnd);

    // init map
    common->SM->Bet_call_map.clear();
    for (int i = 0; i < CELL_TOTAL; ++i) {
        common->SM->Bet_call_map.insert({ i, 0 });
    }
    // 初始化燈亮時間
    for (int i = 0; i < BET_TOTAL; ++i) {
        common->ESM->Bet_Light_map[i] = 0;
    }

    for (int i = 0; i < GAME_TOTAL; ++i) {
        common->ESM->Game_Light_map[i] = 0;
    }

    for (int i = 0; i < 2; ++i) {
        common->ESM->Compare_Light_map[i] = 0;
    }
    m_area_Bet = new Area_Bet(common);
    m_area_Function = new Area_Function(common);
    m_area_Game = new Area_Game(common);


}

Engine::~Engine()
{
    SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pWhiteBrush);
}

HRESULT Engine::InitializeD2D()
{
    // 初始化 Direct2D
    D2D1_SIZE_U size = D2D1::SizeU(SCREEN_WIDTH, SCREEN_HEIGHT);
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
    m_pDirect2dFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(m_hwnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
        &m_pRenderTarget
    );

    // Initialize text writing factory and format
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(m_pDWriteFactory),
        reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
    );

    m_pDWriteFactory->CreateTextFormat(
        L"Verdana",
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        20,
        L"", //locale
        &m_pTextFormat
    );

    //m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中
    m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING); //靠右
    m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    m_pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::White),
        &m_pWhiteBrush
    );





    
    return S_OK;
}

void Engine::KeyUp(WPARAM wParam)
{

}
void Engine::updata_Json()
{   
    // 讀取倍率表
    std::string path1 = common->currentPath.string() + "/Images/倍率表.json";
    std::ifstream inFile(path1);
    if (!inFile.is_open()) {
        //OutputDebugString(L"無法打開 JSON 文件\n");
        MessageBox(m_hwnd, L"倍率表讀取失敗", L"錯誤", MB_OK);
    }
    //else
        //OutputDebugString(L"JSON開啟成功\n");
    json Data;
    inFile >> Data;
    inFile.close();

    common->SM->Bet_map[BAR_NUMBER] = Data["Table"]["Bar"]["ratio"];
    common->SM->Bet_map[SEVEN_NUMBER] = Data["Table"]["Seven"]["ratio"];
    common->SM->Bet_map[STAR_NUMBER] = Data["Table"]["Star"]["ratio"];
    common->SM->Bet_map[WATERMELOM_NUMBER] = Data["Table"]["Bell"]["ratio"];
    common->SM->Bet_map[BELL_NUMBER] = Data["Table"]["Watermelon"]["ratio"];
    common->SM->Bet_map[LEMON_NUMBER] = Data["Table"]["Lemon"]["ratio"];
    common->SM->Bet_map[ORANGE_NUMBER] = Data["Table"]["Orange"]["ratio"];
    common->SM->Bet_map[APPLE_NUMBER] = Data["Table"]["Apple"]["ratio"];

    common->BM->png_map[BAR_NUMBER] = Data["Table"]["Bar"]["filepath"];
    common->BM->png_map[SEVEN_NUMBER] = Data["Table"]["Seven"]["filepath"];
    common->BM->png_map[STAR_NUMBER] = Data["Table"]["Star"]["filepath"];
    common->BM->png_map[WATERMELOM_NUMBER] = Data["Table"]["Bell"]["filepath"];
    common->BM->png_map[BELL_NUMBER] = Data["Table"]["Watermelon"]["filepath"];
    common->BM->png_map[LEMON_NUMBER] = Data["Table"]["Lemon"]["filepath"];
    common->BM->png_map[ORANGE_NUMBER] = Data["Table"]["Orange"]["filepath"];
    common->BM->png_map[APPLE_NUMBER] = Data["Table"]["Apple"]["filepath"];

    std::vector<int> positionValues = Data["Position"].get<std::vector<int>>();

    for (size_t i = 0; i < positionValues.size(); ++i) {
        common->BM->position[i] = positionValues[i];
    }

}

void Engine::Reset()
{
    // This method reset the game, given that the game was won or lost
    if (!playing)
    {
        //snake->Reset();
        //food->Reset(snake, isFoodOnBorderChecked );
        //score = 5;
    }
}

void Engine::Logic()
{
    // This is the logic part of the engine.
    if (playing)
    {
        //更新現在時間
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() % 1000;
        long long& currentTime = common->ESM->currentTime;
        long long& endTime = common->ESM->endTime;

        currentTime = seconds * 1000 + milliseconds;

        common->ESM->updateLightStatus();


        //  設開始為N 結束為Y
        //  從n開始 到23 再從0開始 到n
        //  若Y大於N 則再從N到Y
        //  若N小於Y 則從N到23 再從0到Y
        
        int& state = common->ESM->state;
        bool& bet_starting = common->ESM->bet_starting;
        bool& bet_started = common->ESM->bet_started;
        bool& bet_settling = common->ESM->bet_settling;

        bool& compare_starting = common->ESM->compare_starting;
        bool& compare_SmallOrBig = common->ESM->compare_SmallOrBig;
        bool& compare_settling = common->ESM->compare_settling;

        bool& autoing = common->ESM->autoing;
        int& position = common->ESM->position;
        int& endCompare = common->ESM->endCompare;


        // 狀態機
        switch (state) {
        case STATE_IDLE:{  // 閒置
            if (common->ESM->Game_Light_call_map.empty() &&
                common->ESM->Compare_Light_call_map.empty() &&
                currentTime >= endTime + IDLETIME &&
                !autoing) {
                m_area_Bet->Logic_idle();
                m_area_Game->Logic_idle();
            }
            else if (autoing && currentTime > endTime + AUTOTIME) {
                // auto
                Logic_auto();

            }
            if (bet_starting) { //等待開始遊戲
                if (!common->SM->CheckBet()) {
                    MessageBox(NULL, L"請先下注", L"錯誤", MB_OK);
                    bet_starting = 0;
                }
                else {
                    common->ESM->Light_Clear();
                    state = STATE_BET_BEFORE;
                }
            }

        }
        break;
        case STATE_BET_BEFORE: {
            state = STATE_BET_GAMING;
        }
        break;
        case STATE_BET_GAMING: {//遊戲bet
            if (bet_starting) {
                bet_starting = 0;
                if (!common->ESM->bet_started) {
                    common->ESM->bet_started = 1;
                }
                std::srand(static_cast<unsigned int>(std::time(nullptr)));
                common->ESM->endPosition = std::rand() % 24; //

                int cellNumber = common->BM->Get_CellNumber(common->ESM->position);
                common->ESM->SetLightStatus(common->ESM->Game_Light_call_map, common->ESM->currentTime, common->ESM->position, 0);

                int currentHour = common->ESM->position; //設開始為N 結束為Y

                m_area_Bet->Logic_Bet();
                m_area_Game->Logic_Bet();
                bet_settling = 1;
            }
            if (bet_settling &&
                currentTime > endTime) //動畫結束
                state = STATE_BET_SETTLING;
        }
        break;

        case STATE_BET_SETTLING: {  //結算bet
            if (bet_settling) {
                int number = common->BM->Get_CellNumber(position);
                m_area_Bet->Settlement(number, autoing);
                bet_settling = 0;
            }

            if (common->ESM->autoing) { //TODO 自動事件
                common->SM->WinToScore();
            }

            if (compare_starting) { //玩家決定進入比大小
                state = STATE_COMPARE_BEFORE;
            }

            if (common->SM->GetWinScore() == 0) { //遊戲失敗或玩家決定得分
                state = STATE_IDLE;
            }
        }
        break;
        case STATE_COMPARE_BEFORE: {
            state = STATE_COMPARE_GAMING;
        }
         break;
        case STATE_COMPARE_GAMING: {// 遊戲Compare
            if (compare_starting) { //等待猜大小
                compare_starting = 0;
                m_area_Game->Logic_Compare();
                compare_settling = 1;
            }
            if(compare_settling &&
                currentTime > endTime) //動畫結束
                state = STATE_COMPARE_SETTLING;
        }

        break;
        case STATE_COMPARE_SETTLING: {// 結算Compare
            if (compare_settling) {
                if (endCompare < 5) {
                    if (compare_SmallOrBig == 0)
                        common->SM->AddWinScore(common->SM->GetWinScore());
                    else
                        common->SM->CostWinScore(common->SM->GetWinScore());
                }
                else {
                    if (compare_SmallOrBig == 1)
                        common->SM->AddWinScore(common->SM->GetWinScore());
                    else
                        common->SM->CostWinScore(common->SM->GetWinScore());
                }
                compare_settling = 0;
            }
            if (common->SM->GetWinScore() > 0) { //遊戲勝利
                if (compare_starting) { //玩家決定進入比大小
                    state = STATE_COMPARE_BEFORE;
                }
            }
            else {
                state = STATE_IDLE;
            }
        }
        break;
        default:
        break;
        }
    }
}

HRESULT Engine::Draw()
{

    auto frameStart = std::chrono::steady_clock::now();

    // This is the drawing method of the engine.
    // It simply draws all the elements in the game using Direct2D
    //HRESULT hr;

    m_pRenderTarget->BeginDraw();


    m_pRenderTarget->Clear(D2D1::ColorF(176.0f/255.0f, 151.0f / 205, 95.0f / 255.0f,1.0f));

    //繪製圍牆
    //D2D1_RECT_F bound_rectangle = D2D1::RectF(1.0f, 1.0f, SCREEN_WIDTH - 3, SCREEN_HEIGHT - 3);
    ID2D1SolidColorBrush* pBlackBrush;
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &pBlackBrush);
    //m_pRenderTarget->DrawRectangle(&bound_rectangle, pBlackBrush, 7.0f);

    D2D1_RECT_F destinationRect = D2D1::RectF(
        1,
        1,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    m_pRenderTarget->DrawBitmap(common->BM->BackgroundBitmap, destinationRect);



    D2D1_RECT_F rectangle4 = D2D1::RectF(1, 1, SCREEN_WIDTH, 50 - 3);
    ID2D1SolidColorBrush* pBrush;
    WCHAR scoreStr[64];
    //m_pRenderTarget->FillRectangle(&rectangle4, pBrush);
    //swprintf_s(scoreStr, L"狀態::%d                                              ", common->ESM->state);
    //m_pRenderTarget->DrawText(
    //    scoreStr,
    //    48,
    //    m_pTextFormat,
    //    rectangle4,
    //    pBrush
    //);
    // Draw score
    D2D1_RECT_F win_rectangle     = D2D1::RectF(SCREEN_WIDTH / 3  -110 , 85, SCREEN_WIDTH / 3  +110, 140);
    D2D1_RECT_F credits_rectangle = D2D1::RectF(SCREEN_WIDTH / 3*2-110 , 85, SCREEN_WIDTH / 3*2+110, 140);
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
    m_pRenderTarget->FillRectangle(&win_rectangle, pBrush);
    m_pRenderTarget->FillRectangle(&credits_rectangle, pBrush);

    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
    swprintf_s(scoreStr, L"BONUS/WIN 贏得分數 \n %d                                         ", common->SM->GetWinScore());
    m_pRenderTarget->DrawText(
        scoreStr,
        48,
        m_pTextFormat,
        win_rectangle,
        pBrush
    );
    swprintf_s(scoreStr, L"CREDITS 目前總分數 \n   %d                                      ", common->SM->GetScore());
    m_pRenderTarget->DrawText(
        scoreStr,
        48,
        m_pTextFormat,
        credits_rectangle,
        pBrush
    );

    // 遊戲區域
    m_area_Game->Draw(GRID_X, GRID_Y, GRID_WIDTH, GRID_HEIGHT);
    // 下注區域
    m_area_Bet->Draw(BET_X, BET_Y, BET_WIDTH, BET_HEIGHT);
    // 功能鍵
    m_area_Function->Draw(FUNCTION_X, FUNCTION_Y, FUNCTION_WIDTH, FUNCTION_HEIGHT);


    m_pRenderTarget->EndDraw();

    return S_OK;
}

void Engine::ClearDraw(){
    m_pRenderTarget->BeginDraw();
    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));  // 以白色清空背景
    m_pRenderTarget->EndDraw();
    InvalidateRect(m_hwnd, NULL, TRUE);
}

void Engine::Logic_auto() {
    if (!common->SM->CheckBet()) {
        MessageBox(NULL, L"請先下注", L"錯誤", MB_OK);
        common->ESM->autoing = 0;
    }
    else {
        common->ESM->bet_starting = 1;
    }
}