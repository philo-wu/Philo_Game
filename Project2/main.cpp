// 包含基本的Windows頭檔和Direct3D頭文件
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

// 包含Direct3D庫文件
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

// 全域聲明
IDXGISwapChain* swapchain; // 指向交換連結口的指針
ID3D11Device* dev; // 指向Direct3D裝置介面的指針
ID3D11DeviceContext* devcon; // 指向Direct3D裝置上下文的指針
ID3D11RenderTargetView* backbuffer;

// 函數原型
void InitD3D(HWND hWnd); // 設定並初始化Direct3D
void RenderFrame(void);
void CleanD3D(void); // 關閉Direct3D並釋放內存

//  宣告WindowProc
LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    // the handle for the window, filled by a function
    HWND hWnd;
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
        L"WindowClass1", // 視窗類別的名字
        L"Our First Windowed Program", // 視窗的標題
        WS_OVERLAPPEDWINDOW, // 視窗的樣式
        300, // 視窗的x座標
        300, // 視窗的y座標
        wr.right - wr.left, // 視窗的寬度 //根據客戶端大小來計算適合的視窗大小
        wr.bottom - wr.top, // 視窗的高度
        NULL, // 沒有父窗口，設定為NULL
        NULL, // 不使用選單，設定為NULL
        hInstance, // 應用程式句柄
        NULL); // 與多個視窗一起使用，設定為NULL

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
            RenderFrame();

        }

    }

    // clean up DirectX and COM
    CleanD3D();

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}
// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
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
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 使用32位元色
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 交換鏈如何使用
    scd.OutputWindow = hWnd; // 要使用的視窗
    scd.SampleDesc.Count = 4; // 多重取樣的數量
    scd.Windowed = TRUE; // 視窗全螢幕模式

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
    viewport.Width = 800;
    viewport.Height = 600;

    devcon->RSSetViewports(1, &viewport);
}

// 這是用於渲染單一幀的函數
void RenderFrame(void)
{
    // 將後緩衝區清除為深藍色
    devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

    // 在這裡進行後緩衝區上的3D渲染

    // 切換後緩衝區與前緩衝區
    swapchain->Present(0, 0);
}

// 這個函數是為了清理Direct3D和COM
void CleanD3D()
{
    // 關閉並釋放所有的COM對象
    swapchain->Release();
    dev->Release();
    devcon->Release();

    backbuffer->Release();

}