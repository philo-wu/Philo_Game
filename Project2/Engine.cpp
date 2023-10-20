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

HRESULT Engine::Draw(POINT point, int OriginalSize, int pxSize, FruitTree* tree , json Map_saveData , json Tree_saveData, std::vector<POINT> Map_treepoints)
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

    if (frist_start)
    {

        //繪製功能列底色
        D2D1_COLOR_F white_Color = D2D1::ColorF(0.8f, 0.8f, 0.8f, 1.0f);
        ID2D1SolidColorBrush* pWhiteBrush;
        m_pRenderTarget->CreateSolidColorBrush(white_Color, &pWhiteBrush);
        //m_pRenderTarget->DrawRectangle(&rectangle, pBlackBrush, 7.0f);
        m_pRenderTarget->FillRectangle(&Rect_functionColumn, pWhiteBrush);
        frist_start = 0;
    }
    //if(do_drawMap)
    {
        //繪製草地
        D2D1_COLOR_F customColor = D2D1::ColorF(204.0f / 255.0f, 153.0f / 255.0f, 102.0f / 255.0f, 1.0f);
        ID2D1SolidColorBrush* pGreenBrush;
        m_pRenderTarget->CreateSolidColorBrush(customColor, &pGreenBrush);
        //m_pRenderTarget->DrawRectangle(&rectangle, pBlackBrush, 7.0f);
        m_pRenderTarget->FillRectangle(&Rect_drawingArea, pGreenBrush);
    }
    // 讀取Map存檔
    //if (do_drawMap)
    //{
    //    m_pRenderTarget->DrawBitmap(Map_Bitmap, Rect_drawingArea);
    //    do_drawMap = 0;
    //}
    // 
    //if (tree->treeBitmap && point.x >0 && point.y >50)
    //{

    //    m_pRenderTarget->DrawBitmap(tree->treeBitmap, D2D1::RectF(point.x, point.y, point.x + pxSize, point.y + pxSize));//Rect為樹的位子加上恆定長寬

    //}
    // 先繪製已儲存元件  // 無考慮繪製優先度問題
    double scalingRatio = static_cast<double>(pxSize) / OriginalSize;
    int scalingPx = DIALOG_TREELOAD_FRUIT_PX * scalingRatio;

    for (auto& tree : Map_saveData.items()) {
        std::string treeName = tree.key();
        std::cout << "樹名稱: " << treeName << std::endl;
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string stdStr ;
        IWICImagingFactory* pIWICFactory = NULL;
        CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);

        // 在 Tree_saveData 中查找對應樹的資料
        if (Tree_saveData.contains(treeName)) {
            ID2D1Bitmap* tree_Bitmap;
            //樹圖片: Tree_saveData[treeName]["image"]
            std::wstring Png = converter.from_bytes(stdStr);
            std::wstring path = currentPath.wstring() + L"/Images/" + Png;
            Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &tree_Bitmap, phWnd);

            //樹座標:  Tree_saveData[treeName]["coordinates"]
            for (const auto& coordinate : Tree_saveData[treeName]["coordinates"])
            {
                POINT tree_Point;
                tree_Point.x = coordinate["X"];
                tree_Point.y = coordinate["Y"];
                if (tree_Bitmap)
                {
                    m_pRenderTarget->DrawBitmap(tree_Bitmap, D2D1::RectF(tree_Point.x, tree_Point.y, tree_Point.x + pxSize, tree_Point.y + pxSize));
                    // 檢查樹是否有 Fruit
                    if (Tree_saveData[treeName].contains("Fruit")) {
                        ID2D1Bitmap* fruit_Bitmap;
                        //水果圖片:  Tree_saveData[treeName]["Fruit"]["image"]
                        Png = converter.from_bytes(stdStr);
                        path = currentPath.wstring() + L"/Images/" + Png;
                        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &fruit_Bitmap, phWnd);
                        //水果座標:  Tree_saveData[treeName]["Fruit"]["coordinates"]
                        for (auto& coordinate : Tree_saveData[treeName]["Fruit"]["coordinates"]) {
                            UINT drawpoint_x = tree_Point.x + coordinate["X"] * scalingRatio;
                            UINT drawpoint_y = tree_Point.y + coordinate["Y"] * scalingRatio;

                            if (fruit_Bitmap)
                                m_pRenderTarget->DrawBitmap(tree_Bitmap, D2D1::RectF(drawpoint_x, drawpoint_y, drawpoint_x + scalingPx, drawpoint_y + scalingPx));
                        }
                    }
                }
            }


        }
        else {
            std::cout << "樹在 Tree_saveData 中不存在" << std::endl;
        }

        std::cout << std::endl;
    }
    // 再繪製正在當前元件
    //樹座標
    for (const POINT& tree_Point : Map_treepoints)
    {


        if (tree->treeBitmap)
        {
            // 繪製樹
            m_pRenderTarget->DrawBitmap(tree->treeBitmap, D2D1::RectF(tree_Point.x, tree_Point.y, tree_Point.x + pxSize, tree_Point.y + pxSize));
            // 水果座標
            for (const POINT& coordinate : tree->Get_fruit_Points())
            {
                UINT drawpoint_x = tree_Point.x + coordinate.x* scalingRatio;
                UINT drawpoint_y = tree_Point.y + coordinate.y* scalingRatio;
                // 繪製水果
                m_pRenderTarget->DrawBitmap(tree->fruitBitmap, D2D1::RectF(drawpoint_x, drawpoint_y, drawpoint_x + scalingPx, drawpoint_y + scalingPx));

            }
        }
    }
    m_pRenderTarget->EndDraw();

    return S_OK;
}

void Engine::ClearDraw(HWND hWnd)
{
    m_pRenderTarget->BeginDraw();
    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));  // 以白色清空背景
    m_pRenderTarget->EndDraw();
    InvalidateRect(hWnd, NULL, TRUE);
}

