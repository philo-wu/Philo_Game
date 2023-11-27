
#include "mian.h"
#include "nlohmann/json.hpp"
#include <thread>

// 計時器 //單位為毫秒
int time_start = GetTickCount();
int time_end = GetTickCount();


//入口點
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)   
{
    init(hInstance,
        hPrevInstance,
        lpCmdLine,
        nCmdShow);

    // 設定並初始化 Direct
    common = new Common();
    engine = new Engine(common, hWnd);
    // 進入主要迴圈:    
    // 這個結構體包含Windows事件訊息
    MSG msg = { 0 };
    
    // 訊息迴圈
    while (TRUE)
    {
        time_end = GetTickCount();
        int elapsed_sec = time_end - time_start;
        logicAccumulatedTime += elapsed_sec; //邏輯間隔時間
        accumulatedTime += elapsed_sec; //繪圖間隔時間
        secTime += elapsed_sec;

        if (secTime >= 1000)
        {
            //OutputDebugString(L"1秒=================================\n");
            time_t now = time(0);
            char* dt = ctime(&now);
            //OutputDebugStringA(dt);
            secTime -= 1000;
        }

        if (logicAccumulatedTime >= logicFrameTime)
        {


            // Game logic
            if (engine->playing)
            {
                //OutputDebugString(L"邏輯\n");
                engine->Logic();
                if (!engine->playing)
                {
                    SendMessage(hWnd, WM_CUSTOM_GAMEEND, 0, 0);
                    engine->Reset();
                    engine->ClearDraw();
                }
            }
            logicAccumulatedTime -= logicFrameTime;

        }

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
            if (accumulatedTime >= targetFrameTime)
            {

                if (engine->playing)
                {
                    // Drawing
                    //OutputDebugString(L"繪圖\n");
                    engine->Draw();
                }
                accumulatedTime -= targetFrameTime;

            }
        }
        time_start = time_end;
    }
    
    // 將WM_QUIT訊息的這一部分傳回給Windows
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
            // 在此繪製按鈕會存在,但會被覆蓋,仍可以點選
            // 透過重繪事件,會先繪製背景再繪製按鈕
            // 設定字體

            Start_Button = CreateWindow(
                L"BUTTON",                              // 按鈕控制項的類別名稱
                L"開始遊戲",                            // 按鈕上顯示的文字
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
                SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 -160,
                BUTTON_WIDTH, BUTTON_HEIGHT,
                                                        // 按鈕位置和大小 (x, y, width, height)
                hWnd,                                   // 父窗口句柄
                (HMENU)1,                               // 控制項 ID (可以用於識別按鈕)
                GetModuleHandle(NULL),                  // 模組句柄
                NULL                                    // 指定為 NULL
            );
            //Difficulty_Button = CreateWindow(
            //    L"BUTTON",                              // 按鈕控制項的類別名稱
            //    L"難度選擇",                            // 按鈕上顯示的文字
            //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
            //    SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 -80,
            //    BUTTON_WIDTH, BUTTON_HEIGHT,
            //                                            // 按鈕位置和大小 (x, y, width, height)
            //    hWnd,                                   // 父窗口句柄
            //    (HMENU)2,                               // 控制項 ID (可以用於識別按鈕)
            //    GetModuleHandle(NULL),                  // 模組句柄
            //    NULL                                    // 指定為 NULL
            //);
            //Score_Button = CreateWindow(
            //    L"BUTTON",                              // 按鈕控制項的類別名稱
            //    L"排行榜",                            // 按鈕上顯示的文字
            //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
            //    SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 ,
            //    BUTTON_WIDTH, BUTTON_HEIGHT,
            //                                            // 按鈕位置和大小 (x, y, width, height)
            //    hWnd,                                   // 父窗口句柄
            //    (HMENU)3,                               // 控制項 ID (可以用於識別按鈕)
            //    GetModuleHandle(NULL),                  // 模組句柄
            //    NULL                                    // 指定為 NULL
            //);
            End_Button = CreateWindow(
                L"BUTTON",                              // 按鈕控制項的類別名稱
                L"離開遊戲",                            // 按鈕上顯示的文字
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
                SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 -80, //+80
                BUTTON_WIDTH, BUTTON_HEIGHT,
                                                        // 按鈕位置和大小 (x, y, width, height)
                hWnd,                                   // 父窗口句柄
                (HMENU)4,                               // 控制項 ID (可以用於識別按鈕)
                GetModuleHandle(NULL),                  // 模組句柄
                NULL                                    // 指定為 NULL
            );
            //hwndScrollBar = CreateWindowEx(
            //    NULL,                                        // window styles
            //    TRACKBAR_CLASS,                               // 視窗類別的名字
            //    L"難易度選擇",                               // 視窗的標題
            //    WS_CHILD | WS_VISIBLE | TBS_HORZ,         // 視窗的樣式
            //    10, 10, 200, 30,                          // 按鈕位置和大小 (x, y, width, height)
            //    hWnd,                                     // Parent window
            //    (HMENU)2001,                                 // Unique ID
            //    GetModuleHandle(NULL),                    // Instance handle
            //    NULL                                      // Additional application data
            //);
            //ShowWindow(hwndScrollBar, SW_HIDE);

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
                case 1: // 開始遊戲
                    ShowButton(0);
                    //OnPaint(hWnd);
                    engine->playing = 1;
                    common->ESM->autoing = 0;

                    break;

                case 2: // 難度選擇
                    //DialogBox(HINSTANCE1, MAKEINTRESOURCE(IDD_DIFFICULTY), NULL, Dialog_Difficulty_Proc);

                    break;

                case 3: //TODO:: 最高分數
                    //MessageBox(hWnd, L"此功能尚未實作", L"錯誤", MB_OK | MB_ICONINFORMATION);
                    //DialogBox(HINSTANCE1, MAKEINTRESOURCE(IDD_RANKLIST), NULL, Dialog_Ranklist_Proc);

                    break;

                case 4: //離開遊戲
                    //SendMessage(hWnd, WM_COMMAND, ID_CUSTOM_COMMAND, 0);  //此為自定義命令
                    //SendMessage(hWnd, WM_CUSTOM_GAMEEND, 0, 0);           //此為自定義事件
                    SendMessage(hWnd, WM_CLOSE, 0, 0);                      //視窗關閉
                    break;
                case ID_CUSTOM_COMMAND: // 自定義命令的處理
                    //MessageBox(hWnd, L"遊戲結束 \n得分為X", L"結算", MB_OK);
                    return 0;
                }
            }
            break;

        case WM_PAINT:
        {
            //繪製遊戲選單
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            HFONT hFont = CreateFont(72, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
            SelectObject(hdc, hFont);
            SetTextColor(hdc, RGB(0, 0, 0));
            SetBkColor(hdc, RGB(240, 240, 240));

            WCHAR Str[64];
            swprintf_s(Str, L"%s", L"超級小瑪莉777");
            TextOut(hdc, SCREEN_WIDTH/2 -210, 100, Str, wcslen(Str));

            // 釋放字體資源
            DeleteObject(hFont);


            EndPaint(hWnd, &ps);
        }break;
        case WM_LBUTTONDOWN:
            // 處理滑鼠左鍵
            {
                int xPos = GET_X_LPARAM(lParam);
                int yPos = GET_Y_LPARAM(lParam);
                if (engine->playing)
                {
                    engine->m_area_Function->ClickFunction(xPos, yPos, hWnd);
                }
            }break;
        case WM_KEYDOWN:
        {
            engine->KeyUp(wParam);
        }
        break;

        case WM_CUSTOM_GAMEEND:
            // 處理遊戲結束
            engine->playing = 0;
            engine->ClearDraw();
            //MessageBox(hWnd, L"自動", L"測試", MB_OK);
            //WCHAR scoreStr[64];
            //swprintf_s(scoreStr, L"遊戲結束 \n得分為%d     ", engine->getscore());
            //MessageBox(hWnd, scoreStr, L"結算", MB_OK);
            //DialogBox(HINSTANCE1, MAKEINTRESOURCE(IDD_GAMEEND), NULL, Dialog_GameEnd_Proc);
            ShowButton(1);
            break;

        case WM_CUSTOM_GAMEWIN:

            break;

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

void init(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow) {
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
    //根據客戶端取得視窗大小並做處理
    HINSTANCE1 = hInstance;
    RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };    // 设置尺寸，而不是位置
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // 調整大小

    // 建立窗口，並將傳回的結果作為句柄
    hWnd = CreateWindowEx(
        NULL,
        L"WindowClass1",                 // 視窗類別的名字
        L"超級小瑪莉777",   // 視窗的標題
        WS_OVERLAPPEDWINDOW,             // 視窗的樣式
        1980 / 2 - SCREEN_WIDTH / 2,         // 視窗的x座標 //畫面置中 = 1980/2 - SCREEN_WIDTH-2
        0,                               // 視窗的y座標
        wr.right - wr.left,              // 視窗的寬度 //根據客戶端大小來計算適合的視窗大小
        wr.bottom - wr.top,              // 視窗的高度
        NULL,                            // 沒有父窗口，設定為NULL
        NULL,                            // 不使用選單，設定為NULL
        hInstance,                       // 應用程式句柄
        NULL);                           // 與多個視窗一起使用，設定為NULL

    // 主選單的字體及大小
    HFONT hFont = CreateFont(
        28,                                     // 字體的高度
        0,                                      // 字體的寬度
        0,                                      // 字體的旋轉角度
        0,                                      // 字體的斜體角度
        FW_NORMAL,                              // 字體的粗細度
        FALSE,                                  // 是否是斜體字體
        FALSE,                                  // 是否是下劃線字體
        FALSE,                                  // 是否是刪除線字體
        DEFAULT_CHARSET,                        // 字符集
        OUT_OUTLINE_PRECIS,                     // 輸出精度
        CLIP_DEFAULT_PRECIS,                    // 剪裁精度
        ANTIALIASED_QUALITY,                    // 邊緣平滑度
        DEFAULT_PITCH | FF_SWISS,               // 字體家族和字體名
        L"Verdana"                              // 字體名
    );
    SendMessage(Start_Button, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
    SendMessage(Difficulty_Button, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
    SendMessage(Score_Button, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
    SendMessage(End_Button, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

    // 顯示視窗
    ShowWindow(hWnd, nCmdShow);
}

void ShowButton(bool show)
{
    if(show)
    { 
        ShowWindow(Start_Button, SW_SHOW);
        ShowWindow(Difficulty_Button, SW_SHOW);
        ShowWindow(Score_Button, SW_SHOW);
        ShowWindow(End_Button, SW_SHOW);
    }
    else
    {
        ShowWindow(Start_Button, SW_HIDE);
        ShowWindow(Difficulty_Button, SW_HIDE);
        ShowWindow(Score_Button, SW_HIDE);
        ShowWindow(End_Button, SW_HIDE);
    }
}