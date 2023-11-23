#include "framework.h"
#include "Engine.h"


Engine::Engine(Common* pcommon) : m_pDirect2dFactory(NULL), m_pRenderTarget(NULL), m_pWhiteBrush(NULL)
{
    //snake = new Snake();
    //food = new Food();
    //food->Reset(snake , isFoodOnBorderChecked );
    common = pcommon;
    playing = false;

    WinScore = 0;
    Score = 15000;
}

Engine::~Engine()
{
    SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pWhiteBrush);
}

HRESULT Engine::InitializeD2D(HWND m_hwnd)
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

    IWICImagingFactory* pIWICFactory = NULL;
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
    int errorcode = 0;

    // 將讀取所有圖檔
    std::wstring path = common->currentPath.wstring() + L"\\Images\\Apple.png";
    Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &AppleBitmap,m_hwnd, errorcode);
    if (errorcode != 0) { //TODO::error處理
        ;
    }
    path = common->currentPath.wstring() + L"\\Images\\Bar.png";
    Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &BarBitmap, m_hwnd, errorcode);
    if (errorcode != 0) {
        ;
    }
    path = common->currentPath.wstring() + L"\\Images\\Bell.png";
    Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &BellBitmap, m_hwnd, errorcode);
    if (errorcode != 0) {
        ;
    }
    path = common->currentPath.wstring() + L"\\Images\\Lemon.png";
    Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &LemonBitmap, m_hwnd, errorcode);
    if (errorcode != 0) {
        ;
    }
    path = common->currentPath.wstring() + L"\\Images\\Orange.png";
    Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &OrangeBitmap, m_hwnd, errorcode);
    if (errorcode != 0) {
        ;
    }
    path = common->currentPath.wstring() + L"\\Images\\Seven.png";
    Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &SevenBitmap, m_hwnd, errorcode);
    if (errorcode != 0) {
        ;
    }
    path = common->currentPath.wstring() + L"\\Images\\Star.png";
    Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &StarBitmap, m_hwnd, errorcode);
    if (errorcode != 0) {
        ;
    }
    path = common->currentPath.wstring() + L"\\Images\\Watermelon.png";
    Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &WatermelonBitmap, m_hwnd, errorcode);
    if (errorcode != 0) {
        ;
    }
    path = common->currentPath.wstring() + L"\\Images\\Background.png";
    Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &BackgroundBitmap, m_hwnd, errorcode);
    if (errorcode != 0) {
        ;
    }
    path = common->currentPath.wstring() + L"\\Images\\Mid_Background.png";
    Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &Mid_BackgroundBitmap, m_hwnd, errorcode);
    if (errorcode != 0) {
        ;
    }
    // init map
    Bet_call_map.clear();
    for (int i = 0; i < CELL_TOTAL; ++i) {
        Bet_call_map.insert({ i, 0 });
    }

    // 讀取倍率表
    std::string path1 = common->currentPath.string() + "/Images/倍率表.json";
    std::ifstream inFile(path1);
    if (!inFile.is_open()) {
        //OutputDebugString(L"無法打開 JSON 文件\n");
        MessageBox(m_hwnd, L"倍率表讀取失敗", L"錯誤", MB_OK);
        return 1;
    }
    //else
        //OutputDebugString(L"JSON開啟成功\n");
    json Data;
    inFile >> Data;
    inFile.close();
    BettingTable = Data;

    // 初始化燈亮時間

    for (int i = 0; i < BET_TOTAL; ++i) {
        Bet_Light_map[i] = 0;
    }

    for (int i = 0; i < GAME_TOTAL; ++i) {
        Game_Light_map[i] = 0;
    }

    for (int i = 0; i < 2; ++i) {
        Compare_Light_map[i] = 0;
    }
    
    pIWICFactory->Release();
    return S_OK;
}

void Engine::KeyUp(WPARAM wParam)
{

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
        currentTime = seconds * 1000 + milliseconds;
        lightIndex = 0;
        lightIndex_slow = 0;

        updateLightStatus();


        //  設開始為N 結束為Y
        //  從n開始 到23 再從0開始 到n
        //  若Y大於N 則再從N到Y
        //  若N小於Y 則從N到23 再從0到Y

        // auto
        if (autoing && currentTime > endTime + AUTOTIME)
            Logic_auto();


        // 狀態機
        switch (state) {
        case STATE_IDLE:{  // 閒置
            if (Game_Light_call_map.empty() &&
                Compare_Light_call_map.empty() &&
                currentTime >= endTime + IDLETIME &&
                !autoing)
                Logic_idle();

            if (bet_starting) { //等待開始遊戲
                if (!CheckBet()) {
                    MessageBox(NULL, L"請先下注", L"錯誤", MB_OK);
                    bet_starting = 0;
                }
                else {
                    Light_Clear();
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
                Logic_Bet();
                bet_starting = 0;
                bet_settling = 1;
            }
            if (bet_settling &&
                currentTime > endTime)
                state = STATE_BET_SETTLING;
        }
        break;

        case STATE_BET_SETTLING: {  //結算bet
            if (bet_settling) {
                int number = Get_CellNumber(position);
                Settlement(number, autoing);
                bet_settling = 0;
            }

            if (compare_starting) { //玩家決定進入比大小
                state = STATE_COMPARE_BEFORE;
            }

            if (WinScore == 0) { //遊戲失敗或玩家決定得分
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
                Logic_Compare();
                compare_settling = 1;
            }
            if(compare_settling &&
                currentTime > endTime)
                state = STATE_COMPARE_SETTLING;
        }

        break;
        case STATE_COMPARE_SETTLING: {// 結算Compare
            if (compare_settling) {
                if (endCompare < 5) {
                    if (compare_SmallOrBig == 0)
                        AddWinScore(GetWinScore());
                    else
                        CostWinScore(GetWinScore());
                }
                else {
                    if (compare_SmallOrBig == 1)
                        AddWinScore(GetWinScore());
                    else
                        CostWinScore(GetWinScore());
                }
                compare_settling = 0;
            }
            if (WinScore > 0) { //遊戲勝利
                state = STATE_BET_SETTLING;
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
int Engine::Get_CellScore(int number) {
    switch (number)
    {
    case APPLE_NUMBER: {
        return 5;
    }
        break;
    case BAR_NUMBER: {
        return 100;
    }
        break;
    case BELL_NUMBER: {
        return 20;
    }
        break;
    case LEMON_NUMBER: {
        return 15;
    }
        break;
    case ORANGE_NUMBER: {
        return 10;
    }
        break;
    case SEVEN_NUMBER: {
        return 40;
    }
        break;
    case STAR_NUMBER: {
        return 30;
    }
        break;
    case WATERMELOM_NUMBER: {
        return 20;
    }
        break;

    default:
        break;
    }
}
int Engine::Get_CellNumber(int light_number) {
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

void Engine::Bet_call(int number, int amount) {
    // 檢查是否存在該號碼的下注紀錄
    auto it = Bet_call_map.find(number);
    if (it != Bet_call_map.end()) {
        // 如果該號碼已存在，更新下注金額
        int cost = Get_CellScore(number);
        if (amount == 0) {
            AddScore(cost*it->second);
            it->second = 0;
        }
        else {
            if(CostScore(cost * amount))
                it->second += amount;
            else
                MessageBox(NULL, L"金額不足", L"錯誤", MB_OK);
        }
    }
    else {
        // 如果該號碼不存在，新增一筆下注紀錄
        MessageBox(NULL, L"號碼不存在", L"錯誤", MB_OK);
        //Bet_call_map[number] = amount;
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

    m_pRenderTarget->DrawBitmap(BackgroundBitmap, destinationRect);



    // UI設計基準紅線 未來刪除
    D2D1_RECT_F rectangle4 = D2D1::RectF(1, 1, SCREEN_WIDTH, 50 - 3);
    ID2D1SolidColorBrush* pBrush;
    WCHAR scoreStr[64];
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
    //m_pRenderTarget->FillRectangle(&rectangle4, pBrush);
    swprintf_s(scoreStr, L"狀態::%d                                              ", state);
    m_pRenderTarget->DrawText(
        scoreStr,
        48,
        m_pTextFormat,
        rectangle4,
        pBrush
    );
    // Draw score
    D2D1_RECT_F win_rectangle     = D2D1::RectF(SCREEN_WIDTH / 3  -120 , 70, SCREEN_WIDTH / 3  +120, 150);
    D2D1_RECT_F credits_rectangle = D2D1::RectF(SCREEN_WIDTH / 3*2-120 , 70, SCREEN_WIDTH / 3*2+120, 150);
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);

    swprintf_s(scoreStr, L"BONUS/WIN 贏得分數 \n %d                                         ", WinScore);
    m_pRenderTarget->DrawText(
        scoreStr,
        48,
        m_pTextFormat,
        win_rectangle,
        pBrush
    );
    swprintf_s(scoreStr, L"CREDITS 目前總分數 \n   %d                                      ", Score);
    m_pRenderTarget->DrawText(
        scoreStr,
        48,
        m_pTextFormat,
        credits_rectangle,
        pBrush
    );

    // 遊戲區域
    Draw_Game(GRID_X, GRID_Y, GRID_WIDTH, GRID_HEIGHT);
    // 下注區域
    Draw_Bet(BET_X, BET_Y, BET_WIDTH, BET_HEIGHT);
    // 功能鍵
    Draw_Function(FUNCTION_X, FUNCTION_Y, FUNCTION_WIDTH, FUNCTION_HEIGHT);


    //m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
    //m_pRenderTarget->FillRectangle(&function_rectangle, pBrush);

    m_pRenderTarget->EndDraw();

    return S_OK;
}

void Engine::ClearDraw(HWND hWnd){
    m_pRenderTarget->BeginDraw();
    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));  // 以白色清空背景
    m_pRenderTarget->EndDraw();
    InvalidateRect(hWnd, NULL, TRUE);
}

void Engine::Draw_Cell(int number, D2D1_RECT_F originalRect) {

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
        m_pRenderTarget->DrawBitmap(AppleBitmap, Rect);

        }
        break;
    case BAR_NUMBER: {
        m_pRenderTarget->DrawBitmap(BarBitmap, Rect);

    }
        break;
    case BELL_NUMBER: {
        m_pRenderTarget->DrawBitmap(BellBitmap, Rect);

    }
        break;
    case LEMON_NUMBER: {
        m_pRenderTarget->DrawBitmap(LemonBitmap, Rect);

    }
        break;
    case ORANGE_NUMBER: {
        m_pRenderTarget->DrawBitmap(OrangeBitmap, Rect);

    }
        break;
    case SEVEN_NUMBER: {
        m_pRenderTarget->DrawBitmap(SevenBitmap, Rect);

    }
        break;
    case STAR_NUMBER: {
        m_pRenderTarget->DrawBitmap(StarBitmap, Rect);

    }
        break;
    case WATERMELOM_NUMBER: {
        m_pRenderTarget->DrawBitmap(WatermelonBitmap, Rect);

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
void Engine::Draw_Game(int x, int y, int width, int height) {
    ID2D1SolidColorBrush* pBrush;

    D2D1_RECT_F game_rectangle = D2D1::RectF(x + width * 1, y + height * 1, x + width * 6, y + height * 6);
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &pBrush);
    //m_pRenderTarget->FillRectangle(&game_rectangle, pBrush);
    ///正中間背景
    m_pRenderTarget->DrawBitmap(Mid_BackgroundBitmap, game_rectangle);
    // 比大小區域
    D2D1_RECT_F game_guess_rectangle = D2D1::RectF(x + width * 3, y + height * 4.5, x + width * 4, y + height * 5);
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(55.0f / 255.0f, 22.0f / 205, 20.0f / 255.0f, 1.0f)), &pBrush);
    m_pRenderTarget->FillRectangle(&game_guess_rectangle, pBrush);
    WCHAR scoreStr[64];
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightPink), &pBrush);
    m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中
    swprintf_s(scoreStr, L"%d                                                  ", Comparenumber);
    m_pRenderTarget->DrawText(
        scoreStr,
        30,
        m_pTextFormat,
        game_guess_rectangle,
        pBrush
    );
    if (isLight(Compare_Light_map, 0)) { //TODO 判斷大小燈亮
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
    if (isLight(Compare_Light_map, 1)) { //TODO 判斷大小燈亮
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
            if ((i == 0 || i == GAME_SIZE-1) ||
                (j == 0 || j == GAME_SIZE-1)) {
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
                if (isLight(Game_Light_map, light_number)) {
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
                Draw_Cell(Get_CellNumber(light_number), grid_rectangle);

                //燈號
                if (isLight(Game_Light_map, light_number)) {
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
void Engine::Draw_Bet(int x, int y, int width, int height) {
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
        int m_score = Get_CellScore(i);
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
        int bet = Bet_call_map[i];
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

        if (isLight(Bet_Light_map, i))  //TODO 判斷是否旋轉到此號碼
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

        if (isLight(Bet_Light_map , i)) { //TODO 判斷是否旋轉到此號碼
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
void Engine::Draw_Function(int x, int y, int width, int height) {    
    D2D1_RECT_F function_rectangle = D2D1::RectF(x, y, x + width * BET_TOTAL, y + height); // BET_TOTAL為還原width
    ID2D1SolidColorBrush* pBrush;
    ID2D1SolidColorBrush* p_Pen_Brush;
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &p_Pen_Brush);
    WCHAR scoreStr[64];
    m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中

    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
    m_pRenderTarget->FillRectangle(&function_rectangle, pBrush);

    for (int i = 0; i < BET_TOTAL; ++i) {
        D2D1_RECT_F bet_rectangle = D2D1::RectF(x + width *i , y, x + width * (i + 1), y + height * 0.5);
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
        m_pRenderTarget->DrawRectangle(&bet_rectangle, pBrush, 4.0f);
        if (bet_settling || compare_settling || GetWinScore() > 0)
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
        else
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
        m_pRenderTarget->FillRectangle(&bet_rectangle, pBrush);

        D2D1_RECT_F Add_1_rectangle  = D2D1::RectF(x + width * i        , y                , x + width * (i + 0.5), y + height * 0.25);
        D2D1_RECT_F Add_10_rectangle = D2D1::RectF(x + width * (i + 0.5), y                , x + width * (i + 1)  , y + height * 0.25);
        D2D1_RECT_F Clear_rectangle  = D2D1::RectF(x + width * i        , y + height * 0.25, x + width * (i + 1)  , y + height * 0.5);
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
        m_pRenderTarget->DrawRectangle(&Add_1_rectangle , pBrush, 2.0f);
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
    D2D1_RECT_F exit_rectangle  = D2D1::RectF(x + width * 0.225, y + height * BET_RATIO, x + width * 1.525, y + height);
    D2D1_RECT_F small_rectangle = D2D1::RectF(x + width * 1.725, y + height * BET_RATIO, x + width * 2.625, y + height);
    D2D1_RECT_F big_rectangle   = D2D1::RectF(x + width * 2.825, y + height * BET_RATIO, x + width * 3.725, y + height);
    D2D1_RECT_F score_rectangle = D2D1::RectF(x + width * 3.925, y + height * BET_RATIO, x + width * 5.225, y + height);
    D2D1_RECT_F auto_rectangle  = D2D1::RectF(x + width * 5.425, y + height * BET_RATIO, x + width * 6.325, y + height);
    D2D1_RECT_F start_rectangle = D2D1::RectF(x + width * 6.525, y + height * BET_RATIO, x + width * 7.825, y + height);


    //繪製綠色按鈕
    if (state != 0)
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
    if (state != 0)
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
    if (state != STATE_BET_SETTLING)
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
    if (state != STATE_BET_SETTLING &&
        state != STATE_COMPARE_SETTLING)
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
    if(autoing)
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightYellow), &pBrush);
    else if(state != STATE_IDLE)
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

void Engine::Logic_Bet(){

        if (!bet_started) {
            bet_started = 1;
        }


        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        endPosition = std::rand() % 24; //

        int cellNumber = Get_CellNumber(position);
        SetLightStatus(Game_Light_call_map, currentTime, position, 0);
        SetLightStatus(Bet_Light_call_map, currentTime, cellNumber, 0);

        int currentHour = position; //設開始為N 結束為Y


        for (int i = 0; i < GAME_TOTAL; ++i) { //從n開始 到23 再從0開始 到n
            currentHour = (currentHour + 1) % 24;
            SetLightStatus(Game_Light_call_map, currentTime + lightsecond * lightIndex, currentHour, 1);
            SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 1), currentHour, 0);
            ++lightIndex;
        }
        if (endPosition > position) { //若Y大於N
            //MessageBox(NULL, L"Y大於N", L"測試", MB_OK);
            for (int i = 0; i <= endPosition; ++i) {
                currentHour = (currentHour + 1) % 24;
                SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), currentHour, 1);
                SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 2), currentHour, 0);
                lightIndex += 2;
            }
        }
        else {  //若Y小於N
            //MessageBox(NULL, L"Y小於N", L"測試", MB_OK);
            for (int i = position; i < GAME_TOTAL; ++i) {
                currentHour = (currentHour + 1) % 24;
                SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), currentHour, 1);
                SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 1), currentHour, 0);
                ++lightIndex;

            }
            for (int i = 0; i <= endPosition; ++i) {
                currentHour = (currentHour + 1) % 24;
                SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), currentHour, 1);
                SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 2), currentHour, 0);
                lightIndex += 2;
            }
        }

        //std::wstring  WStr = std::to_wstring(lightsecond * (lightIndex));
        //OutputDebugString(L"currentTime = ");
        //OutputDebugString(WStr.c_str());
        //OutputDebugString(L"\n");
        cellNumber = Get_CellNumber(currentHour);

        for (int i = 0; i <= 4; ++i) {
            SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), currentHour, 1);
            SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 1), currentHour, 0);
            SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex), cellNumber, 1);
            SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex + 1), cellNumber, 0);
            lightIndex += 2;
        }
        SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), currentHour, 1);
        SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex), cellNumber, 1);

        endTime = currentTime + lightsecond * (lightIndex); //更新結束時間
        position = currentHour; //更新起點
        // 結算
    
}
void Engine::Logic_Compare() {
    // 清空面板
    SetLightStatus(Game_Light_call_map, currentTime, position, 0);
    if (endCompare < 5)
        SetLightStatus(Compare_Light_call_map, currentTime, SMALL_NUMBER, 0);
    else
        SetLightStatus(Compare_Light_call_map, currentTime, BIG_NUMBER, 0);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    endCompare = std::rand() % 10; //   
    int timeadd = 0, timediv = 10;
    for (int i = 0; i <= 10; ++i) {
        std::srand(static_cast<unsigned int>((std::time(nullptr) + i) % timediv++));
        int random_number1 = std::rand() % 10;
        SetCompareNumber(currentTime + lightsecond * (lightIndex), random_number1);
        if (random_number1 < 5) {
            SetLightStatus(Compare_Light_call_map, currentTime + lightsecond * (lightIndex), SMALL_NUMBER, 1);
            SetLightStatus(Compare_Light_call_map, currentTime + lightsecond * (lightIndex + 1), SMALL_NUMBER, 0);

            for (int i = 18; i <= GAME_TOTAL; ++i) {
                int j = i % 24; //
                SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
                SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 1), j, 0);
            }
        }
        else {
            SetLightStatus(Compare_Light_call_map, currentTime + lightsecond * (lightIndex), BIG_NUMBER, 1);
            SetLightStatus(Compare_Light_call_map, currentTime + lightsecond * (lightIndex + 1), BIG_NUMBER, 0);
            for (int i = 6; i <= 12; ++i) {
                int j = i % 24; //
                SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
                SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 1), j, 0);
            }
        }
        lightIndex += 2;
    }
    SetCompareNumber(currentTime + lightsecond * (lightIndex), endCompare);
    endTime = currentTime + lightsecond * (lightIndex); //更新結束時間
    if (endCompare < 5) {
        SetLightStatus(Compare_Light_call_map, currentTime + lightsecond * (lightIndex), SMALL_NUMBER, 1);
        for (int i = 18; i <= GAME_TOTAL; ++i) {
            int j = i % 24; //
            SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
            SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 3), j, 0);
        }
    }
    else {
        SetLightStatus(Compare_Light_call_map, currentTime + lightsecond * (lightIndex), BIG_NUMBER, 1);
        for (int i = 6; i <= 12; ++i) {
            int j = i % 24; //
            SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
            SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 3), j, 0);
        }
    }
    SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 3), position, 1);
    // 結算
}
void Engine::Logic_settle() {


    if (autoing) {
        WinToScore();
    }
}
void Engine::Logic_idle() {
    //OutputDebugString(L"idle\n");
    idleing = 1;
    // 清空面板
    SetLightStatus(Game_Light_call_map, currentTime, position, 0);
    SetLightStatus(Bet_Light_call_map, currentTime, Get_CellNumber(position), 0);

    for (int i = 0; i < GAME_TOTAL; i += 2) {
        SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
        SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 1), i, 0);
    }
    for (int i = 0; i < CELL_TOTAL; i += 2) {
        SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
        SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex + 1), i, 0);
    }
    lightIndex += 2;

    for (int i = 1; i < GAME_TOTAL; i += 2) {
        SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
        SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 1), i, 0);
    }
    for (int i = 1; i < CELL_TOTAL; i += 2) {
        SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
        SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex + 1), i, 0);
    }
    lightIndex += 2;

    for (int i = 0; i < GAME_TOTAL; ++i) {
        SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
        SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 5), i, 0);
        int j = i % 8;
        SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
        SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex + 1), j, 0);

        ++lightIndex;
    }

    if (bet_started) {

        for (int i = 0; i <= position; ++i) {
            SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex), i, 1);
            SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 5), i, 0);
            int j = i % 8;
            SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex), j, 1);
            SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex + 5), j, 0);
            ++lightIndex;
        }

        SetLightStatus(Game_Light_call_map, currentTime + lightsecond * (lightIndex + 4), position, 1);
        SetLightStatus(Bet_Light_call_map, currentTime + lightsecond * (lightIndex + 4), Get_CellNumber(position), 1);

    }
    endTime = currentTime + lightsecond * (lightIndex); //更新結束時間
}
void Engine::Logic_auto() {
    int amount = 0;
    for (int i = 0; i < CELL_TOTAL; ++i) {
        amount += Bet_call_map[i];
    }
    if (amount == 0) {
        MessageBox(NULL, L"請先下注", L"錯誤", MB_OK);
        autoing = 0;
    }
    else {
        bet_starting = 1;
    }
}

bool Engine::CheckBet() {
    //int amount = 0;
    for (int i = 0; i < CELL_TOTAL; ++i) {
        //amount += Bet_call_map[i];
        if (Bet_call_map[i] > 0)
            return true;
    }
    return false;
}

bool Engine::isLight(std::map<int, bool> map, int number) {
    auto it = map.find(number);
    if (it != map.end()) {
        return it->second;
    }
    // 如果找不到對應的鍵值，也返回 false
    return false;
}
void Engine::SetLightStatus(std::multimap<int, std::pair<int, bool>> &map, int time, int number, bool islight) {
    std::pair<int, bool> ppair;
    ppair.first = number;
    ppair.second = islight;
    map.insert(std::make_pair(time, ppair));
}
void Engine::SetCompareNumber(int time, int number) {
    Compare_Number_map.insert(std::make_pair(time, number));
}
void Engine::updateLightStatus() {
    for (auto it = Bet_Light_call_map.begin(); it != Bet_Light_call_map.end();) {
        if (it->first <= currentTime) {
            // 更新 Bet_Light_map
            if (it->second.first == RED_ONCEMORE_NUMBER || it->second.first == BLUE_ONCEMORE_NUMBER) {
                it = Bet_Light_call_map.erase(it);
            }
            else {
                Bet_Light_map[it->second.first] = it->second.second;
                // 刪除已更新的資訊
                it = Bet_Light_call_map.erase(it);
            }
        }
        else {
            ++it;
        }
    }

    for (auto it = Game_Light_call_map.begin(); it != Game_Light_call_map.end();) {
        if (it->first <= currentTime) {
            // 更新 Bet_Light_map
            Game_Light_map[it->second.first] = it->second.second;

            // 刪除已更新的資訊
            it = Game_Light_call_map.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto it = Compare_Light_call_map.begin(); it != Compare_Light_call_map.end();) {
        if (it->first <= currentTime) {
            // 更新 Bet_Light_map
            Compare_Light_map[it->second.first] = it->second.second;
            // 刪除已更新的資訊
            it = Compare_Light_call_map.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto it = Compare_Number_map.begin(); it != Compare_Number_map.end();) {
        if (it->first <= currentTime) {
            // 更新 Bet_Light_map
            Comparenumber = it->second;
            // 刪除已更新的資訊
            it = Compare_Number_map.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Engine::Light_Clear() {
    Game_Light_call_map.clear();
    Bet_Light_call_map.clear();
    for (int i = 0; i < GAME_TOTAL; ++i) {
        SetLightStatus(Game_Light_call_map, currentTime, i, 0);
    }
    for (int i = 0; i < CELL_TOTAL; ++i) {
        SetLightStatus(Bet_Light_call_map, currentTime, i, 0);
    }
}