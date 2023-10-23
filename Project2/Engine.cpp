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

HRESULT Engine::Draw(HWND hWnd, POINT point, int OriginalSize, int pxSize,
    FruitTree* tree, json Map_saveData, json Tree_saveData,
    std::vector<POINT> Map_treepoints,
    std::string using_MapName, std::string using_Main_TreeName)
{

    // This is the drawing method of the engine.
    // It simply draws all the elements in the game using Direct2D
    //HRESULT hr;

    //OutputDebugString(L"開始繪製\n");.
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
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    IWICImagingFactory* pIWICFactory = NULL;
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);

    //OutputDebugString(L"繪製已儲存元件\n");
    for (auto& tree : Map_saveData.items()) {
        //OutputDebugString(L"迴圈開始\n");
        std::string treeName = tree.key();

        //std::wstring wideTreeName(treeName.begin(), treeName.end());
        //LPCWSTR treeNameCStr = wideTreeName.c_str();
        //OutputDebugString(treeNameCStr);
        // 在 Tree_saveData 中查找對應樹的資料
        if (Tree_saveData.contains(treeName)) {
            ID2D1Bitmap* tree_Bitmap;
            //樹圖片: Tree_saveData[treeName]["image"]
            std::wstring image = converter.from_bytes(Tree_saveData[treeName]["image"]);
            std::wstring path = currentPath.wstring() + L"\\Images\\" + image;
            int errorcode;
            Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &tree_Bitmap, phWnd , errorcode);
            if (errorcode != 0) {
                std::wstring str1 = path + L"圖檔不存在" + L"\n";
                OutputDebugString(path.c_str());
            }
            //樹座標:  Tree_saveData[treeName]["coordinates"]
            for (const auto& coordinate : Map_saveData[treeName]["coordinates"])
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
                        image = converter.from_bytes(Tree_saveData[treeName]["Fruit"]["image"]);
                        path = currentPath.wstring() + L"\\Images\\" + image;
                        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &fruit_Bitmap, phWnd , errorcode);
                        if (errorcode != 0) {
                            std::wstring str1 = path + L"圖檔不存在" + L"\n";
                            OutputDebugString(path.c_str());
                        }
                        //水果座標:  Tree_saveData[treeName]["Fruit"]["coordinates"]
                        for (auto& coordinate : Tree_saveData[treeName]["Fruit"]["coordinates"]) {
                            UINT drawpoint_x = tree_Point.x + coordinate["X"] * scalingRatio;
                            UINT drawpoint_y = tree_Point.y + coordinate["Y"] * scalingRatio;

                            if (fruit_Bitmap)
                                m_pRenderTarget->DrawBitmap(fruit_Bitmap, D2D1::RectF(drawpoint_x, drawpoint_y, drawpoint_x + scalingPx, drawpoint_y + scalingPx));
                        }
                        fruit_Bitmap->Release();
                    }

                }
            }
            tree_Bitmap->Release();
        }
        else {
            std::wstring str = converter.from_bytes(treeName);
            std::wstring str1 = L"無法在元件存檔找到" + str + L"\n";
            OutputDebugString(str1.c_str());
        }

    }
    pIWICFactory->Release();

    ID2D1SolidColorBrush* pBlackBrush = nullptr;
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBlackBrush);
    std::wstring p_using_MapName;
    std::wstring p_using_Main_TreeName;

    if (using_MapName.empty())
        p_using_MapName = L"地圖未存檔";
    else
        p_using_MapName = converter.from_bytes(using_MapName);
    if (using_Main_TreeName.empty())
        p_using_Main_TreeName = L"未選擇元件";
    else
        p_using_Main_TreeName = converter.from_bytes(using_Main_TreeName);

    D2D1_RECT_F rectangle3 = D2D1::RectF(230, 5, 1000, 45);
    WCHAR scoreStr[256];
    D2D1_COLOR_F white_Color = D2D1::ColorF(0.8f, 0.8f, 0.8f, 1.0f);
    ID2D1SolidColorBrush* pWhiteBrush;
    m_pRenderTarget->CreateSolidColorBrush(white_Color, &pWhiteBrush);
    //m_pRenderTarget->DrawRectangle(&rectangle, pBlackBrush, 7.0f);
    m_pRenderTarget->FillRectangle(&Rect_functionColumn_right, pWhiteBrush);


    swprintf_s(scoreStr, L"地圖名稱: %s\n元件名稱: %s                    ", 
        p_using_MapName.c_str(), p_using_Main_TreeName.c_str());
    m_pRenderTarget->DrawText(
        scoreStr,
        35,
        m_pTextFormat,
        rectangle3,
        pBlackBrush
    );
    // 再繪製正在當前元件
    //OutputDebugString(L"繪製未儲存元件\n");
    if (tree->treeBitmap) {
        for (const POINT& tree_Point : Map_treepoints){
            // 繪製樹
            if (tree->treeBitmap)
                m_pRenderTarget->DrawBitmap(tree->treeBitmap, D2D1::RectF(tree_Point.x, tree_Point.y, tree_Point.x + pxSize, tree_Point.y + pxSize));
            // 水果座標
            for (const POINT& coordinate : tree->Get_fruit_Points())
            {
                UINT drawpoint_x = tree_Point.x + coordinate.x* scalingRatio;
                UINT drawpoint_y = tree_Point.y + coordinate.y* scalingRatio;
                // 繪製水果
                if(tree->fruitBitmap)
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

