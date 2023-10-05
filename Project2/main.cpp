
#include "framework.h"
// #include "libxl.h"

#pragma comment(lib, "libxl.lib")

// 定義螢幕解析度
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

// 全域聲明,Direct初始化
HWND hWnd;


// 函數原型
void OpenFile(void);


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

    // libxl::Book* book;
    // book = xlCreateXMLBook();// xlCreateXMLBook() for xlsx
    // if (book)
    // {
    //     libxl::Sheet* sheet = book->addSheet(L"Sheet1");
    //     if (sheet)
    //     {
    //         sheet->writeStr(2, 1, L"Hello, World !");
    //         sheet->writeNum(3, 1, 1000);
    //     }
    //     book->save(L"example.xls");
    //     book->release();
    // }
    // return 0;

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

    // 顯示視窗
    ShowWindow(hWnd, nCmdShow);
    bool flag = 0;

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
        }

    }
    return msg.wParam;
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

            Load_Button = CreateWindow(
                L"BUTTON",             // 按鈕控制項的類別名稱
                L"選擇Excel",               // 按鈕上顯示的文字
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
                10, 10, 100, 30,        // 按鈕位置和大小 (x, y, width, height)
                hWnd,                  // 父窗口句柄
                (HMENU)1,              // 控制項 ID (可以用於識別按鈕)
                GetModuleHandle(NULL), // 模組句柄
                NULL                   // 指定為 NULL
            );
            Clean_Button = CreateWindow(
                L"BUTTON",             // 按鈕控制項的類別名稱
                L"保留",              // 按鈕上顯示的文字
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

                    break;
                }
            }
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }break;
            // 當視窗關閉時會讀取此訊息
        case WM_DESTROY:
            {
                // 完全關閉應用程式
                PostQuitMessage(0);
                return 0;
            } break;
    }

    // 處理 switch 語句未攔截訊息
    return DefWindowProc (hWnd, message, wParam, lParam);
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

    }
}





