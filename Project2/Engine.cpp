#include "framework.h"
#include "Engine.h"


Engine::Engine() : m_pDirect2dFactory(NULL), m_pRenderTarget(NULL), m_pWhiteBrush(NULL)
{
    //snake = new Snake();
    //food = new Food();
    //food->Reset(snake , isFoodOnBorderChecked );

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

    //snake->Initialize(m_pRenderTarget);
    //food->Initialize(m_pRenderTarget);

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


    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    //繪製圍牆
    D2D1_RECT_F bound_rectangle = D2D1::RectF(1.0f, 1.0f, SCREEN_WIDTH - 3, SCREEN_HEIGHT - 3);
    ID2D1SolidColorBrush* pBlackBrush;
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &pBlackBrush);
    m_pRenderTarget->DrawRectangle(&bound_rectangle, pBlackBrush, 7.0f);

    D2D1_RECT_F rectangle4 = D2D1::RectF(SCREEN_WIDTH/2-1, 1.0f, SCREEN_WIDTH/2+1, SCREEN_HEIGHT - 3);
    ID2D1SolidColorBrush* pBrush;
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
    m_pRenderTarget->FillRectangle(&rectangle4, pBrush);

    // Draw score
    D2D1_RECT_F win_rectangle = D2D1::RectF(SCREEN_WIDTH / 3 -50 , 70, SCREEN_WIDTH / 3+50, 150);
    D2D1_RECT_F credits_rectangle = D2D1::RectF(SCREEN_WIDTH / 3*2-50 , 70, SCREEN_WIDTH / 3*2+50, 150);
    WCHAR scoreStr[64];

    swprintf_s(scoreStr, L"贏得分數 \n %d                             ", score);
    m_pRenderTarget->DrawText(
        scoreStr,
        35,
        m_pTextFormat,
        win_rectangle,
        m_pWhiteBrush
    );
    swprintf_s(scoreStr, L"目前總分數 \n   %d                         ", highScore);
    m_pRenderTarget->DrawText(
        scoreStr,
        35,
        m_pTextFormat,
        credits_rectangle,
        m_pWhiteBrush
    );
    // 遊戲區域
    int grid_x = SCREEN_WIDTH / 3 - 125; //遊戲區域左上角位置
    int grid_y = 150;//遊戲區域左上角位置
    int grid_width = (SCREEN_WIDTH / 3 + 250) / 7;
    int grid_height = 490 / 7;
    
    D2D1_RECT_F game_rectangle = D2D1::RectF(grid_x, grid_y, grid_x + grid_width* 7, grid_y + grid_height * 7);
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &pBrush);
    m_pRenderTarget->FillRectangle(&game_rectangle, pBrush);
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);

    ID2D1SolidColorBrush* pRedBrush;
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkRed), &pRedBrush);



    for (int i = 0; i < GAME_SIZE; ++i) { //7為遊戲區域分成7*7
        for (int j = 0; j < GAME_SIZE; ++j) {
            if ((i == 0 || i == 6) ||
                (j == 0 || j == 6)
                ) {
                D2D1_RECT_F grid_rectangle = D2D1::RectF(grid_x + grid_width * i, grid_y + grid_height * j,
                    grid_x + grid_width * (i + 1), grid_y + grid_height * (j + 1));
                m_pRenderTarget->FillRectangle(&grid_rectangle, pBrush);
                m_pRenderTarget->FillEllipse(
                    D2D1::Ellipse(D2D1::Point2F(grid_x + grid_width * (i + 0.5), grid_y + grid_height * (j + 1)-8), 6, 6),
                    pRedBrush
                );

            }

        }

    }


    // 下注區域
    D2D1_RECT_F bet_rectangle = D2D1::RectF(SCREEN_WIDTH / 3 - 175, 650, SCREEN_WIDTH / 3 * 2 + 175, 850);
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pBrush);
    m_pRenderTarget->FillRectangle(&bet_rectangle, pBrush);
    // 功能鍵
    D2D1_RECT_F function_rectangle = D2D1::RectF(SCREEN_WIDTH / 3 - 175, 850, SCREEN_WIDTH / 3 * 2 + 175, SCREEN_HEIGHT-5);
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pBrush);
    m_pRenderTarget->FillRectangle(&function_rectangle, pBrush);
    //snake->Draw(m_pRenderTarget);
    //food->Draw(m_pRenderTarget);

    m_pRenderTarget->EndDraw();

    //auto frameEnd = std::chrono::steady_clock::now();
    return S_OK;
}

void Engine::ClearDraw(HWND hWnd)
{
    m_pRenderTarget->BeginDraw();
    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));  // 以白色清空背景
    m_pRenderTarget->EndDraw();
    InvalidateRect(hWnd, NULL, TRUE);
}
