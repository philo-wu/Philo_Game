// 包含基本的Windows頭檔和Direct3D頭文件
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <commdlg.h>        //讀取檔案
#include <d2d1.h>
#include <wincodec.h>


// 包含Direct3D庫文件
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "windowscodecs.lib")


// 定義螢幕解析度
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600



// 全域聲明,Direct初始化
HWND hWnd;
IDXGISwapChain* swapchain; // 指向交換連結口的指針
ID3D11Device* dev; // 指向Direct3D裝置介面的指針
ID3D11DeviceContext* devcon; // 指向Direct3D裝置上下文的指針
ID3D11RenderTargetView* backbuffer;

// 繪圖相關
ID3D11InputLayout* pLayout;            // 指向輸入佈局的指針
ID3D11VertexShader* pVS;               // 指向頂點著色器的指針
ID3D11PixelShader* pPS;                // 指向像素著色器的指針
ID3D11Buffer* pVBuffer;                // 指向頂點緩衝區的指針

// 測試深度繪圖 
// 深度繪圖
// 原因是 已創造的按鈕在3D繪圖後會被覆蓋,仍存在但不會顯示,
// 可能是沒有再次呼叫WM_PAINT,但由於已使用2D繪圖完成目的,故3D繪圖以及深度繪圖暫不使用.
ID3D11Texture2D* depthStencilBuffer ;  // 緩衝區
ID3D11DepthStencilView* depthStencilView ;
ID3D11DepthStencilState* depthStencilState ;

// 複製圖片
ID2D1Factory* pD2DFactory ;
ID2D1HwndRenderTarget* pRT ;
ID2D1Bitmap* pBitmap ;
IWICBitmapDecoder* pDecoder ;
IWICBitmapFrameDecode* pSource ;
IWICStream* pStream ;
IWICFormatConverter* pConverter ;
D2D1_POINT_2F clickPoint = { 0 };
HRESULT InitD2D(HWND hwnd);

struct VERTEX { FLOAT X, Y, Z; D3DXCOLOR Color; };//定義單一頂點的結構體

// 函數原型
void InitD3D(HWND hWnd); // 設定並初始化Direct3D
void RenderFrame(void);
void CleanD3D(void); // 關閉Direct3D並釋放內存
void InitGraphics(void);    // 建立要渲染的形狀
void InitPipeline(void);    // 載入並準備著色器
void OpenFile(void);
void DrawBitmap();
void ClearDraw();
void OnClick(int mouseX, int mouseY);

//  按鈕宣告
HWND Load_Button;
HWND Clean_Button;
//  宣告WindowProc
LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);

//入口點
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    // 視窗句柄，由函數填充
    // 這個結構體用來保存視窗類別相關的訊息
    WNDCLASSEX wc;

    // 清空視窗類別以供使用
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // 在結構體中填寫所需的視窗類別信息
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass1";

    // 註冊視窗
    RegisterClassEx(&wc);

    RECT wr = { 0, 0, 500, 400 };    // 设置尺寸，而不是位置
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // 調整大小

// 建立窗口，並將傳回的結果作為句柄
    hWnd = CreateWindowEx(NULL,
        L"WindowClass1",                 // 視窗類別的名字
        L"Our First Windowed Program",   // 視窗的標題
        WS_OVERLAPPEDWINDOW,             // 視窗的樣式
        300,                             // 視窗的x座標
        300,                             // 視窗的y座標
        wr.right - wr.left,              // 視窗的寬度 //根據客戶端大小來計算適合的視窗大小
        wr.bottom - wr.top,              // 視窗的高度
        NULL,                            // 沒有父窗口，設定為NULL
        NULL,                            // 不使用選單，設定為NULL
        hInstance,                       // 應用程式句柄
        NULL);                           // 與多個視窗一起使用，設定為NULL

    //也可以在這裡創建按鈕
    //HWND hwndButton = CreateWindow(
    //    L"BUTTON",             // 按鈕控制項的類別名稱
    //    L"Click Me",           // 按鈕上顯示的文字
    //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
    //    10, 10, 100, 30,       // 按鈕位置和大小 (x, y, width, height)
    //    hWnd,                  // 父窗口句柄
    //    (HMENU)1,              // 控制項 ID (可以用於識別按鈕)
    //    GetModuleHandle(NULL), // 模組句柄
    //    NULL                   // 指定為 NULL
    //);
// 顯示視窗
    ShowWindow(hWnd, nCmdShow);

    // 設定並初始化 Direct
    InitD2D(hWnd);
    InitD3D(hWnd);
    // 進入主要迴圈:
    
// 這個結構體包含Windows事件訊息
    MSG msg = { 0 };

    // 訊息迴圈
    while (TRUE)
    {
        // 检查队列中是否有消息正在等待
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // 將按鍵訊息轉換為正確的格式
            TranslateMessage(&msg);

            // 將訊息傳送到WindowProc函數
            DispatchMessage(&msg);

            // 檢查是否到了退出的時間
            if (msg.message == WM_QUIT)
                break;
        }
        else
        {
            // 遊戲內容 //為不停重新繪製的地方
            //RenderFrame(); //3D繪圖

        }

    }

    // 清理 DirectX 和 COM
    CleanD3D();
    // TODO: CleanD2D
    // 將WM_QUIT訊息的這一部分傳回給Windows
    return msg.wParam;
}
//按鈕點擊事件
void OnButtonClick(HWND hWnd)
{
    MessageBox(hWnd, L"Button Clicked!", L"Button Click", MB_OK);
}

// 訊息處理函數
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 排序並找到針對給定訊息運行哪些程式碼
    switch(message)
    {
        case WM_CREATE:
        {
            // 在 WM_CREATE 消息中創建按鈕
            // 在此繪製按鈕會存在,但會被覆蓋,仍可以點選
            // 透過重繪事件,會先繪製背景再繪製按鈕


            Load_Button = CreateWindow(
                L"BUTTON",             // 按鈕控制項的類別名稱
                L"Load",               // 按鈕上顯示的文字
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
                10, 10, 100, 30,        // 按鈕位置和大小 (x, y, width, height)
                hWnd,                  // 父窗口句柄
                (HMENU)1,              // 控制項 ID (可以用於識別按鈕)
                GetModuleHandle(NULL), // 模組句柄
                NULL                   // 指定為 NULL
            );
            Clean_Button = CreateWindow(
                L"BUTTON",             // 按鈕控制項的類別名稱
                L"Clean",              // 按鈕上顯示的文字
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
                120, 10, 100, 30,        // 按鈕位置和大小 (x, y, width, height)
                hWnd,                  // 父窗口句柄
                (HMENU)2,              // 控制項 ID (可以用於識別按鈕)
                GetModuleHandle(NULL), // 模組句柄
                NULL                   // 指定為 NULL
            );
            // 使用2D繪圖 並觸發WM_PAINT後,按鈕即可正常顯示,故先不使用置頂設置
            // 猜測若使用置頂,但無觸發WM_PAINT,仍會發生按鈕被覆蓋的問題
            //SetWindowPos(Load_Button, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); //使按鈕置頂
            //SetWindowPos(Clean_Button, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            break;
        }
        case WM_COMMAND:
            // 檢查按鈕事件
            if (HIWORD(wParam) == BN_CLICKED )
            {
                //檢查按鈕身分
                switch (LOWORD(wParam))
                {
                case 1:
                    OpenFile();
                    break;

                case 2:
                    MessageBox(hWnd, L"Clean Clicked!", L"Clean Click", MB_OK);
                    ClearDraw();
                    break;
                }
            }
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // 繪製圖片
            DrawBitmap();
            EndPaint(hWnd, &ps);
        }break;
        case WM_LBUTTONDOWN:
            // 處理滑鼠左鍵
            {
                int xPos = GET_X_LPARAM(lParam);
                int yPos = GET_Y_LPARAM(lParam);
                OnClick(xPos, yPos);
            }break;

            // 當視窗關閉時會讀取此訊息
        case WM_DESTROY:
            {
                if(pRT!=NULL)
                    pRT->Release();
                if (pD2DFactory != NULL)
                    pD2DFactory->Release();
                if (pBitmap != NULL)
                    pBitmap->Release();
                // 完全關閉應用程式
                PostQuitMessage(0);
                return 0;
            } break;
    }

    // 處理 switch 語句未攔截訊息
    return DefWindowProc (hWnd, message, wParam, lParam);
}
// 初始化並準備Direct3D以供使用
void InitD3D(HWND hWnd)
{
    // 建立一個結構體來保存有關交換鏈的信息
    DXGI_SWAP_CHAIN_DESC scd;


    // 清空這個結構體以供使用
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // 填寫交換鏈描述結構
    scd.BufferCount = 1; // 一個後緩衝區
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // 使用32位元色
    scd.BufferDesc.Width = SCREEN_WIDTH;                 // 設定後緩衝區寬度
    scd.BufferDesc.Height = SCREEN_HEIGHT;               // 設定後緩衝區高度
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // 交換鏈如何使用
    scd.OutputWindow = hWnd;                             // 要使用的視窗
    scd.SampleDesc.Count = 4;                            // 多重取樣的數量
//    scd.SampleDesc.Quality = 0;                          // 多樣本品質水平
    scd.Windowed = TRUE; // 視窗全螢幕模式
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // 允許全螢幕切換

    // 使用scd結構中的資訊來建立裝置、裝置上下文和交換鏈
    D3D11CreateDeviceAndSwapChain(NULL,
                                  D3D_DRIVER_TYPE_HARDWARE,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  D3D11_SDK_VERSION,
                                  &scd,
                                  &swapchain,
                                  &dev,
                                  NULL,
                                  &devcon);

    // 取得後台緩衝區的位址
    ID3D11Texture2D* pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // 使用後台緩衝區位址建立渲染目標
    dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();

    // 將渲染目標設定為後台緩衝區
    devcon->OMSetRenderTargets(1, &backbuffer, NULL);


    // 設定視口
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = SCREEN_WIDTH;
    viewport.Height = SCREEN_HEIGHT;

    devcon->RSSetViewports(1, &viewport);

    D3D11_TEXTURE2D_DESC depthStencilDesc;
    depthStencilDesc.Width = SCREEN_WIDTH;
    depthStencilDesc.Height = SCREEN_HEIGHT;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    dev->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
    dev->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
    devcon->OMSetRenderTargets(1, &backbuffer, depthStencilView);

    InitPipeline();
    InitGraphics();
}

//渲染單一幀
void RenderFrame(void)
{
    // 將後緩衝區清除為深藍色
    devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

    // 在這裡進行後緩衝區上的3D渲染
    // 選擇要顯示的頂點緩衝區
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

    // 選擇我們正在使用的原始類型
    devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 將頂點緩衝區繪製到後台緩衝區
    devcon->Draw(3, 0);
    // 切換後緩衝區與前緩衝區
    swapchain->Present(0, 0);
    // 深度繪圖
    devcon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

    //在此繪製按鈕可以顯示,但會過度浪費效能
    //Load_Button = CreateWindow(
    //    L"BUTTON",             // 按鈕控制項的類別名稱
    //    L"Load",               // 按鈕上顯示的文字
    //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
    //    10, 10, 100, 30,        // 按鈕位置和大小 (x, y, width, height)
    //    hWnd,                  // 父窗口句柄
    //    (HMENU)1,              // 控制項 ID (可以用於識別按鈕)
    //    GetModuleHandle(NULL), // 模組句柄
    //    NULL                   // 指定為 NULL
    //);
    //SetWindowPos(Load_Button, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    //Clean_Button = CreateWindow(
    //    L"BUTTON",             // 按鈕控制項的類別名稱
    //    L"Clean",              // 按鈕上顯示的文字
    //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
    //    120, 10, 100, 30,        // 按鈕位置和大小 (x, y, width, height)
    //    hWnd,                  // 父窗口句柄
    //    (HMENU)2,              // 控制項 ID (可以用於識別按鈕)
    //    GetModuleHandle(NULL), // 模組句柄
    //    NULL                   // 指定為 NULL
    //);
}

// 清理Direct3D和COM
void CleanD3D()
{
    // 關閉並釋放所有的COM對象
    //Direct初始
    if (swapchain)
        swapchain->Release();
    if (dev)
        dev->Release();
    if (devcon)
        devcon->Release();
    //緩衝區
    if (backbuffer)
        backbuffer->Release();
    //頂點以及像素著色器
    if (pLayout)
        pLayout->Release();
    if (pVS)
        pVS->Release();
    if (pPS)
        pPS->Release();
    if (pVBuffer)
        pVBuffer->Release();
    if (depthStencilBuffer)
        depthStencilBuffer->Release();
    if (depthStencilState)
        depthStencilState->Release();

}

// 創建要渲染形狀
void InitGraphics()
{
    // 使用 VERTEX 結構建立一個三角形
    VERTEX OurVertices[] =
    {
        {0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
        {0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
        {-0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)}
    };


    //建立頂點緩衝區
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;                  // CPU和GPU的寫入存取權限
    bd.ByteWidth = sizeof(VERTEX) * 3;               // size是VERTEX結構的大小* 3
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;         // 用作頂點緩衝區
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;      // 允許CPU寫入緩衝區

    dev->CreateBuffer(&bd, NULL, &pVBuffer);       // 建立緩衝區


    // 將頂點複製到緩衝區中
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // 映射緩衝區
    //memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // 複製數據
    devcon->Unmap(pVBuffer, NULL);                                      // 取消映射緩衝區
    
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
    depthStencilDesc.DepthEnable = TRUE;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    dev->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
    devcon->OMSetDepthStencilState(depthStencilState, 1);

}

// 載入並準備著色器
void InitPipeline()
{

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
    depthStencilDesc.DepthEnable = TRUE;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    dev->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
    devcon->OMSetDepthStencilState(depthStencilState, 1);
    // 載入並編譯兩個著色器
    ID3D10Blob* VS, * PS;
    D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
    D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

    // 將兩個著色器封裝到著色器物件中
    dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
    dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

    //設定著色器對象
    devcon->VSSetShader(pVS, 0, 0);
    devcon->PSSetShader(pPS, 0, 0);

    // 建立輸入佈局對象
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
    devcon->IASetInputLayout(pLayout);
}




//以上為DirectX 3D
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////



HRESULT InitD2D(HWND hwnd)
{
    // 創建 D2D 工廠
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

    if (SUCCEEDED(hr))
    {
        RECT rc;
        GetClientRect(hwnd, &rc);

        // 創建 D2D 渲染目標
        hr = pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
            &pRT
        );
    }

    return hr;
}
HRESULT LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, LPCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
    // 初始化 WIC
    IWICBitmapDecoder* pDecoder = NULL;
    IWICBitmapFrameDecode* pSource = NULL;
    IWICStream* pStream = NULL;
    IWICFormatConverter* pConverter = NULL;

    HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
        uri,
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
    );

    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pSource);
        // 初始化 WIC 轉換器
        hr = pIWICFactory->CreateFormatConverter(&pConverter);
        // 設定轉換器屬性
        hr = pConverter->Initialize(
            pSource,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.0,
            WICBitmapPaletteTypeMedianCut
        );
        // 創建 D2D 位圖
        hr = pRenderTarget->CreateBitmapFromWicBitmap(
            pConverter,
            NULL,
            ppBitmap
        );
    }

    // 釋放 WIC 資源
    if (pDecoder != NULL)
        pDecoder->Release();
    if (pSource != NULL)
        pSource->Release();
    if (pStream != NULL)
        pStream->Release();
    if (pConverter != NULL)
        pConverter->Release();

    return hr;
}

void OpenFile()
{
    OPENFILENAME ofn;
    wchar_t szFile[MAX_PATH] = L"";

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;  // 父視窗的 handle
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
    ofn.lpstrFilter = L"All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    //TODO:判斷副檔名
    if (GetOpenFileName(&ofn) == TRUE)
    {
        IWICImagingFactory* pIWICFactory = NULL;
        CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
        LoadBitmapFromFile(pRT, pIWICFactory, szFile, 0, 0, &pBitmap);
        pIWICFactory->Release();
    }
}


void DrawBitmap()
{
    if (pRT && pBitmap)
    {
        D2D1_SIZE_U size = pBitmap->GetPixelSize();
        UINT width = size.width;
        UINT height = size.height;
        pRT->BeginDraw();
        pRT->DrawBitmap(pBitmap, D2D1::RectF(clickPoint.x, clickPoint.y, clickPoint.x + width, clickPoint.y + height));
        pRT->EndDraw();
    }
}
void ClearDraw()
{
    pRT->BeginDraw();
    pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));  // 以白色清空背景
    if (pBitmap)
        pBitmap= nullptr;
    pRT->EndDraw();
    InvalidateRect(hWnd, NULL, TRUE);
}
// 釋放 Direct2D 資源
template <class T>  //此無法使用,改為個別release
void SafeRelease(T** ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();
        *ppInterfaceToRelease = NULL;
    }
}

void OnClick(int mouseX, int mouseY)
{
    // 更新點擊位置
    clickPoint.x = static_cast<FLOAT>(mouseX);
    clickPoint.y = static_cast<FLOAT>(mouseY);
    // 通知系統進行重繪
    InvalidateRect(hWnd, NULL, TRUE);

}