#include "framework.h"
#include "Engine.h"
#include "Tree.h"

Engine::Engine() : m_pDirect2dFactory(NULL), m_pRenderTarget(NULL), m_pWhiteBrush(NULL)
{
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
    // 文字置中
    //m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

    m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    m_pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::White),
        &m_pWhiteBrush
    );

    return S_OK;
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

    //    keyPressed = false;
    //}
}

HRESULT Engine::Draw(POINT point, int pxSize, Tree* tree)
{

    // This is the drawing method of the engine.
    // It simply draws all the elements in the game using Direct2D
    //HRESULT hr;


    m_pRenderTarget->BeginDraw();
    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

    //是否清空畫面
    if (do_clear)
    {
        m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
        do_clear = 0;
        frist_start = 1;
    }

    if(frist_start)
    {     

        //繪製功能列底色
        D2D1_COLOR_F white_Color = D2D1::ColorF(0.8f, 0.8f, 0.8f, 1.0f);
        ID2D1SolidColorBrush* pWhiteBrush;
        m_pRenderTarget->CreateSolidColorBrush(white_Color, &pWhiteBrush);
        //m_pRenderTarget->DrawRectangle(&rectangle, pBlackBrush, 7.0f);
        m_pRenderTarget->FillRectangle(&Rect_functionColumn, pWhiteBrush);
        frist_start = 0;

        //繪製草地
        D2D1_COLOR_F customColor = D2D1::ColorF(204.0f / 255.0f, 153.0f / 255.0f, 102.0f / 255.0f, 1.0f);
        ID2D1SolidColorBrush* pGreenBrush;
        m_pRenderTarget->CreateSolidColorBrush(customColor, &pGreenBrush);
        //m_pRenderTarget->DrawRectangle(&rectangle, pBlackBrush, 7.0f);
        m_pRenderTarget->FillRectangle(&Rect_drawingArea, pGreenBrush);
    }
    if (do_drawMap)
    {
        m_pRenderTarget->DrawBitmap(Map_Bitmap, Rect_drawingArea);
        do_drawMap = 0;
    }
    if (tree->treeBitmap && point.x >0 && point.y >50)
    {

        m_pRenderTarget->DrawBitmap(tree->treeBitmap, D2D1::RectF(point.x, point.y, point.x + pxSize, point.y + pxSize));//Rect為樹的位子加上恆定長寬

    }

    //pBitmapLock->Unlock();

    // Draw score
    //D2D1_RECT_F rectangle2 = D2D1::RectF(SCREEN_WIDTH / 2, 0, 100, 200);
    //D2D1_RECT_F rectangle3 = D2D1::RectF(SCREEN_WIDTH / 2, 0, 100, 300);
    //WCHAR scoreStr[64];
    //swprintf_s(scoreStr, L"分數: %d            最高分數: %d              ", score, highScore);
    //m_pRenderTarget->DrawText(
    //    scoreStr,
    //    35,
    //    m_pTextFormat,
    //    rectangle2,
    //    m_pWhiteBrush
    //);
    //swprintf_s(scoreStr, L"FPS : %d                           ",FPS);
    ////m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    //m_pRenderTarget->DrawText(
    //    scoreStr,
    //    35,
    //    m_pTextFormat,
    //    rectangle3,
    //    m_pWhiteBrush
    //);
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

