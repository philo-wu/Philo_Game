// 包含基本的Windows頭檔和Direct3D頭文件
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

// 包含Direct3D庫文件
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")


// 定義螢幕解析度
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600



// 全域聲明Direct初始化
HWND hWnd;
IDXGISwapChain* swapchain; // 指向交換連結口的指針
ID3D11Device* dev; // 指向Direct3D裝置介面的指針
ID3D11DeviceContext* devcon; // 指向Direct3D裝置上下文的指針
ID3D11RenderTargetView* backbuffer;

//繪圖相關
ID3D11InputLayout* pLayout;            // 指向輸入佈局的指針
ID3D11VertexShader* pVS;               // 指向頂點著色器的指針
ID3D11PixelShader* pPS;                // 指向像素著色器的指針
ID3D11Buffer* pVBuffer;                // 指向頂點緩衝區的指針

//測試深度繪圖
ID3D11Texture2D* depthStencilBuffer ;
ID3D11DepthStencilView* depthStencilView ;
ID3D11DepthStencilState* depthStencilState ;


struct VERTEX { FLOAT X, Y, Z; D3DXCOLOR Color; };//定義單一頂點的結構體

// 函數原型
void InitD3D(HWND hWnd); // 設定並初始化Direct3D
void RenderFrame(void);
void CleanD3D(void); // 關閉Direct3D並釋放內存
void InitGraphics(void);    // 建立要渲染的形狀
void InitPipeline(void);    // 載入並準備著色器

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
    // the handle for the window, filled by a function
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

    // register the window class
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

    // set up and initialize Direct3D
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
            // 遊戲內容
            //RenderFrame();

        }

    }

    // clean up DirectX and COM
    CleanD3D();

    // return this part of the WM_QUIT message to Windows
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
    // sort through and find what code to run for the message given
    switch(message)
    {
        case WM_CREATE:
        {
            // 在 WM_CREATE 消息中創建按鈕
            // 在此繪製按鈕會存在,但會被覆蓋,仍可以點選
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
            SetWindowPos(Load_Button, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
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
            SetWindowPos(Clean_Button, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            //if (Load_Button != NULL)
            //{
            //    //SetWindowLongPtr(hButton, GWLP_USERDATA, (LONG_PTR)SubclassProc);
            //    //SubclassWindow(hButton, SubclassProc, 0, 0);
            //}
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
                    MessageBox(hWnd, L"Load Clicked!", L"Load Click", MB_OK);
                    break;

                case 2:
                    MessageBox(hWnd, L"Clean Clicked!", L"Clean Click", MB_OK);
                    break;
                }
            }
            break;
        // this message is read when the window is closed
        case WM_DESTROY:
            {
                // close the application entirely
                PostQuitMessage(0);
                return 0;
            } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}
// 這個函數初始化並準備Direct3D以供使用
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

    // get the address of the back buffer
    ID3D11Texture2D* pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();

    // set the render target as the back buffer
    devcon->OMSetRenderTargets(1, &backbuffer, NULL);


    // Set the viewport
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

// 這是用於渲染單一幀的函數
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
    //深度繪圖
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

// 這個函數是為了清理Direct3D和COM
void CleanD3D()
{
    // 關閉並釋放所有的COM對象
    //Direct初始
    swapchain->Release();
    dev->Release();
    devcon->Release();
    //緩衝區
    backbuffer->Release();
    //頂點以及像素著色器
    //pLayout->Release();
    //pVS->Release();
    //pPS->Release();
    //pVBuffer->Release();
    //depthStencilBuffer->Release();
    //depthStencilState->Release();

}

// 這是創建要渲染的形狀的函數
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
    memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // 複製數據
    devcon->Unmap(pVBuffer, NULL);                                      // 取消映射緩衝區
    
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
    depthStencilDesc.DepthEnable = TRUE;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    dev->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
    devcon->OMSetDepthStencilState(depthStencilState, 1);

}


// 函數載入並準備著色器
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
