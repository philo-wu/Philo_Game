#include "framework.h"
#include "Engine.h"


Engine::Engine(Common* pcommon) : m_pDirect2dFactory(NULL), m_pRenderTarget(NULL), m_pWhiteBrush(NULL)
{
    //snake = new Snake();
    //food = new Food();
    //food->Reset(snake , isFoodOnBorderChecked );
    common = pcommon;
    playing = false;
    keyPressed = false;

    score = 0;
    highScore = 15000;
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
        //std::cerr << "無法打開 JSON 文件" << std::endl;
        //OutputDebugString(L"JSON開啟成功\n");
        MessageBox(m_hwnd, L"倍率表讀取失敗", L"錯誤", MB_OK);
        return 1;
    }
    //else
        //OutputDebugString(L"JSON開啟成功\n");
    json Data;
    inFile >> Data;
    inFile.close();
    BettingTable = Data;



    pIWICFactory->Release();
    return S_OK;
}

void Engine::KeyUp(WPARAM wParam)
{
    if (!keyPressed)
    {
        //if (wParam == VK_UP)
        //    snake->GoUp();
        //if (wParam == VK_DOWN)
        //    snake->GoDown();
        //if (wParam == VK_LEFT)
        //    snake->GoLeft();
        //if (wParam == VK_RIGHT)
        //    snake->GoRight();
        keyPressed = true;
    }
}

void Engine::Reset()
{
    // This method reset the game, given that the game was won or lost
    if (!playing)
    {
        //snake->Reset();
        //food->Reset(snake, isFoodOnBorderChecked );
        score = 5;
    }
}

void Engine::Logic(double elapsedTime)
{
    // This is the logic part of the engine.
    //if (playing)
    //{
    //    snake->Advance();
    //    if (snake->CheckFoodCollision(food->position.x, food->position.y))
    //    {
    //        food->Reset(snake, isFoodOnBorderChecked);
    //        snake->Grow();
    //        score++;
    //        if (score > highScore)
    //            highScore = score;
    //    }

    //    if (snake->CheckSelfCollision())
    //    {
    //        playing = false;
    //    }
    //    else if (food->GameWin)
    //    {
    //        playing = false;
    //        //TODO:寫入勝利畫面
    //    }

    //}
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
    D2D1_RECT_F rectangle4 = D2D1::RectF(SCREEN_WIDTH/2-1, 1.0f, SCREEN_WIDTH/2+1, SCREEN_HEIGHT - 3);
    ID2D1SolidColorBrush* pBrush;
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
    m_pRenderTarget->FillRectangle(&rectangle4, pBrush);

    // Draw score
    D2D1_RECT_F win_rectangle     = D2D1::RectF(SCREEN_WIDTH / 3  -120 , 70, SCREEN_WIDTH / 3  +120, 150);
    D2D1_RECT_F credits_rectangle = D2D1::RectF(SCREEN_WIDTH / 3*2-120 , 70, SCREEN_WIDTH / 3*2+120, 150);
    WCHAR scoreStr[64];
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);

    swprintf_s(scoreStr, L"BONUS/WIN 贏得分數 \n %d                                         ", score);
    m_pRenderTarget->DrawText(
        scoreStr,
        48,
        m_pTextFormat,
        win_rectangle,
        pBrush
    );
    swprintf_s(scoreStr, L"CREDITS 目前總分數 \n   %d                                      ", highScore);
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
    int guess = 0; //TODO 隨機數
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightPink), &pBrush);
    m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中
    swprintf_s(scoreStr, L"%d                                                  ", guess);
    m_pRenderTarget->DrawText(
        scoreStr,
        30,
        m_pTextFormat,
        game_guess_rectangle,
        pBrush
    );
    if (1) { //TODO 判斷是否旋轉到此號碼
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkRed), &pBrush);
        m_pRenderTarget->FillEllipse(
            D2D1::Ellipse(D2D1::Point2F(x + width * 2.75, y + height * 4.75), LIGHT_SIZE, LIGHT_SIZE),
            pBrush);
    }
    else {
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
        m_pRenderTarget->FillEllipse(
            D2D1::Ellipse(D2D1::Point2F(x + width * 2.75, y + height * 4.75), LIGHT_SIZE, LIGHT_SIZE),
            pBrush);
    }
    if (1) { //TODO 判斷是否旋轉到此號碼
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkRed), &pBrush);
        m_pRenderTarget->FillEllipse(
            D2D1::Ellipse(D2D1::Point2F(x + width * 4.25, y + height * 4.75), LIGHT_SIZE, LIGHT_SIZE),
            pBrush);
    }
    else {
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
        m_pRenderTarget->FillEllipse(
            D2D1::Ellipse(D2D1::Point2F(x + width * 4.25, y + height * 4.75), LIGHT_SIZE, LIGHT_SIZE),
            pBrush);
    }




    for (int j = 0; j < GAME_SIZE; ++j) { //遊戲區域分成7*7
        for (int i = 0; i < GAME_SIZE; ++i) {
            if ((i == 0 || i == GAME_SIZE-1) ||
                (j == 0 || j == GAME_SIZE-1)) {
                D2D1_RECT_F grid_rectangle = D2D1::RectF(x + width * i, y + height * j,
                    x + width * (i + 1), y + height * (j + 1));
                m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
                m_pRenderTarget->FillRectangle(&grid_rectangle, pBrush);
                //邊界
                m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
                m_pRenderTarget->DrawRectangle(&grid_rectangle, pBrush, 2.0f);
                //繪製遊戲圖片
                if (j == 0 && i == 0) {
                    // (0, 0) 處理邏輯
                    Draw_Cell(ORANGE_NUMBER, grid_rectangle);
                }
                else if (j == 0 && i == 1) {
                    // (0, 1) 處理邏輯
                    Draw_Cell(BELL_NUMBER, grid_rectangle);
                }
                else if (j == 0 && i == 2) {
                    // (0, 2) 處理邏輯
                    Draw_Cell(BAR_NUMBER, grid_rectangle);
                }
                else if (j == 0 && i == 3) {
                    // (0, 3) 處理邏輯
                    Draw_Cell(BAR_NUMBER, grid_rectangle);
                }
                else if (j == 0 && i == 4) {
                    // (0, 4) 處理邏輯
                    Draw_Cell(APPLE_NUMBER, grid_rectangle);
                }
                else if (j == 0 && i == 5) {
                    // (0, 5) 處理邏輯
                    Draw_Cell(APPLE_NUMBER, grid_rectangle);
                }
                else if (j == 0 && i == 6) {
                    // (0, 6) 處理邏輯
                    Draw_Cell(LEMON_NUMBER, grid_rectangle);
                }
                else if (j == 1 && i == 6) {
                    // (1, 6) 處理邏輯
                    Draw_Cell(WATERMELOM_NUMBER, grid_rectangle);
                }
                else if (j == 2 && i == 6) {
                    // (2, 6) 處理邏輯
                    Draw_Cell(WATERMELOM_NUMBER, grid_rectangle);
                }
                else if (j == 3 && i == 6) {
                    // (3, 6) 處理邏輯
                    WCHAR scoreStr[64];
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &pBrush);
                    m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中
                    swprintf_s(scoreStr, L"ONCE\nMORE                      ");
                    m_pRenderTarget->DrawText(
                        scoreStr,
                        30,
                        m_pTextFormat,
                        grid_rectangle,
                        pBrush
                    );
                }
                else if (j == 4 && i == 6) {
                    // (4, 6) 處理邏輯
                    Draw_Cell(APPLE_NUMBER, grid_rectangle);
                }
                else if (j == 5 && i == 6) {
                    // (5, 6) 處理邏輯
                    Draw_Cell(ORANGE_NUMBER, grid_rectangle);
                }
                else if (j == 6 && i == 6) {
                    // (6, 6) 處理邏輯
                    Draw_Cell(ORANGE_NUMBER, grid_rectangle);
                }
                else if (j == 6 && i == 5) {
                    // (6, 5) 處理邏輯
                    Draw_Cell(BELL_NUMBER, grid_rectangle);
                }
                else if (j == 6 && i == 4) {
                    // (6, 4) 處理邏輯
                    Draw_Cell(SEVEN_NUMBER, grid_rectangle);
                }
                else if (j == 6 && i == 3) {
                    // (6, 3) 處理邏輯
                    Draw_Cell(SEVEN_NUMBER, grid_rectangle);
                }
                else if (j == 6 && i == 2) {
                    // (6, 2) 處理邏輯
                    Draw_Cell(APPLE_NUMBER, grid_rectangle);
                }
                else if (j == 6 && i == 1) {
                    // (6, 1) 處理邏輯
                    Draw_Cell(LEMON_NUMBER, grid_rectangle);
                }
                else if (j == 6 && i == 0) {
                    // (6, 0) 處理邏輯
                    Draw_Cell(LEMON_NUMBER, grid_rectangle);
                }
                else if (j == 5 && i == 0) {
                    // (5, 0) 處理邏輯
                    Draw_Cell(STAR_NUMBER, grid_rectangle);
                }
                else if (j == 4 && i == 0) {
                    // (4, 0) 處理邏輯
                    Draw_Cell(STAR_NUMBER, grid_rectangle);
                }
                else if (j == 3 && i == 0) {
                    // (3, 0) 處理邏輯
                    WCHAR scoreStr[64];
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
                    m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中
                    swprintf_s(scoreStr, L"ONCE\nMORE                      ");
                    m_pRenderTarget->DrawText(
                        scoreStr,
                        30,
                        m_pTextFormat,
                        grid_rectangle,
                        pBrush
                    );
                }
                else if (j == 2 && i == 0) {
                    // (2, 0) 處理邏輯
                    Draw_Cell(APPLE_NUMBER, grid_rectangle);
                }

                else if (j == 1 && i == 0) {
                    // (1, 0) 處理邏輯
                    Draw_Cell(BELL_NUMBER, grid_rectangle);
                }
                else {
                    // 其他格子的處理邏輯
                }


                //製作燈號
                if (1) { //TODO 判斷是否旋轉到此號碼
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkRed), &pBrush);
                    m_pRenderTarget->FillEllipse(
                        D2D1::Ellipse(D2D1::Point2F(x + width * (i + 0.5), y + height * (j + 1) - 8), LIGHT_SIZE, LIGHT_SIZE),
                        pBrush);
                }
                else {
                    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
                    m_pRenderTarget->FillEllipse(
                        D2D1::Ellipse(D2D1::Point2F(x + width * (i + 0.5), y + height * (j + 1) - 8), LIGHT_SIZE, LIGHT_SIZE),
                        pBrush);
                }

            }
        }
    }
}
void Engine::Draw_Bet(int x, int y, int width, int height) {
    ID2D1SolidColorBrush* pBrush;

    D2D1_RECT_F bet_rectangle = D2D1::RectF(x, y, x + width * 8, y + 200);
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pBrush);
    m_pRenderTarget->FillRectangle(&bet_rectangle, pBrush);

    for (int i = 0; i < BET_SIZE; ++i) { //下注區域為8種選項
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
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
        D2D1_RECT_F grid_png_rectangle = D2D1::RectF(x + width * (i), y + 124,
            x + width * (i + 1), y + 200);
        m_pRenderTarget->FillRectangle(&grid_png_rectangle, pBrush);
        Draw_Cell(i, grid_png_rectangle);


        //分界線
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pBrush);
        D2D1_RECT_F grid_rectangle = D2D1::RectF(x + width * (i + 1) - 1, y,
            x + width * (i + 1), y + 200);
        if (i != BET_SIZE - 1)
            m_pRenderTarget->FillRectangle(&grid_rectangle, pBrush);
        if (1) { //TODO 判斷是否旋轉到此號碼
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkRed), &pBrush);
            m_pRenderTarget->FillEllipse(
                D2D1::Ellipse(D2D1::Point2F(x + width * (i + 0.5), y + 8), LIGHT_SIZE, LIGHT_SIZE),
                pBrush);
        }
        else {
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
            m_pRenderTarget->FillEllipse(
                D2D1::Ellipse(D2D1::Point2F(x + width * (i + 0.5), y + 8), LIGHT_SIZE, LIGHT_SIZE),
                pBrush);
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

void Engine::Draw_Function(int x, int y, int width, int height) {    
    D2D1_RECT_F function_rectangle = D2D1::RectF(x, y, x + width * 8, y + height); // 8為將width 切分八分
    ID2D1SolidColorBrush* pBrush;
    ID2D1SolidColorBrush* p_Pen_Brush;
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &p_Pen_Brush);
    WCHAR scoreStr[64];
    m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); //置中

    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
    m_pRenderTarget->FillRectangle(&function_rectangle, pBrush);

    

    // 分配按鈕區域
    // TODO 這裡*的比例為人工計算,具體按鍵公式可在調整
    D2D1_RECT_F exit_rectangle  = D2D1::RectF(x + width * 0.225, y + height * 0.5, x + width * 1.525, y + height);
    D2D1_RECT_F small_rectangle = D2D1::RectF(x + width * 1.725, y + height * 0.5, x + width * 2.625, y + height);
    D2D1_RECT_F big_rectangle   = D2D1::RectF(x + width * 2.825, y + height * 0.5, x + width * 3.725, y + height);
    D2D1_RECT_F score_rectangle = D2D1::RectF(x + width * 3.925, y + height * 0.5, x + width * 5.225, y + height);
    D2D1_RECT_F auto_rectangle  = D2D1::RectF(x + width * 5.425, y + height * 0.5, x + width * 6.325, y + height);
    D2D1_RECT_F start_rectangle = D2D1::RectF(x + width * 6.525, y + height * 0.5, x + width * 7.825, y + height);


    //繪製綠色按鈕
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
    m_pRenderTarget->FillRectangle(&auto_rectangle, pBrush);
    swprintf_s(scoreStr, L"自動\nAUTO                                                  ");
    m_pRenderTarget->DrawText(
        scoreStr,
        30,
        m_pTextFormat,
        auto_rectangle,
        p_Pen_Brush
    );

    //繪製紅色按鈕
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







}