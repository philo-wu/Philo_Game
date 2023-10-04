
#include "mian.h"
#include "resource.h"


// 定義螢幕解析度


//HINSTANCE HINSTANCE1;
//INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    switch (uMsg)
//    {
//    case WM_INITDIALOG:
//        // 初始化對話框
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        // 處理命令消息，例如按鈕點擊
//        switch (LOWORD(wParam))
//        {
//        case IDOK:
//            // OK 按鈕被點擊
//            EndDialog(hwndDlg, IDOK);
//            return (INT_PTR)TRUE;
//
//        case IDCANCEL:
//            // 取消按鈕被點擊
//            EndDialog(hwndDlg, IDCANCEL);
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//
//    return (INT_PTR)FALSE;
//}


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
    //根據客戶端取得視窗大小並做處理
    //HINSTANCE1 = hInstance;
    RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };    // 设置尺寸，而不是位置
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // 調整大小

    // 建立窗口，並將傳回的結果作為句柄
    hWnd = CreateWindowEx(
        NULL,
        L"WindowClass1",                 // 視窗類別的名字
        L"Our First Windowed Program",   // 視窗的標題
        WS_OVERLAPPEDWINDOW,             // 視窗的樣式
        300,                             // 視窗的x座標
        100,                             // 視窗的y座標
        wr.right - wr.left,              // 視窗的寬度 //根據客戶端大小來計算適合的視窗大小
        wr.bottom - wr.top,              // 視窗的高度
        NULL,                            // 沒有父窗口，設定為NULL
        NULL,                            // 不使用選單，設定為NULL
        hInstance,                       // 應用程式句柄
        NULL);                           // 與多個視窗一起使用，設定為NULL
    
    //也可以在這裡創建按
    // 顯示視窗
    ShowWindow(hWnd, nCmdShow);
    // 設定並初始化 Direct
    engine = new Engine();

    engine->InitializeD2D(hWnd);
    //InitD2D(hWnd);

    //   InitD3D(hWnd);
    // 進入主要迴圈:
    
    // 這個結構體包含Windows事件訊息
    MSG msg = { 0 };
    // 計時器
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    int frames = 0;
    double framesTime = 0;

    // 訊息迴圈
    while (TRUE)
    {
        end = std::chrono::steady_clock::now();
        double elapsed_secs = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
        begin = end;

        // 顯示 FPS
        //framesTime += elapsed_secs;
        //frames++;
        //if (framesTime > 1) {
        //    WCHAR fpsText[32];
        //    swprintf(fpsText, 32, L"Game: %d FPS", frames);
        //    SetWindowText(hWnd, fpsText);
        //    frames = 0;
        //    framesTime = 0;
        //}

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
            // 看到有人用return 0, 但因為我將Clean寫在後方,故只用break
        }
        else
        {
            // 遊戲內容 //為不停重新繪製的地方
            if(engine->playing)
            { 
                // Game logic
                engine->Logic(elapsed_secs);

                // Drawing
                engine->Draw();
                if (!engine->playing)
                {
                    SendMessage(hWnd, WM_CUSTOM_GAMEEND, 0, 0);
                    engine->Reset();
                    engine->ClearDraw(hWnd);
                }
            }

        }

    }

    // 清理 DirectX 和 COM
    // CleanD3D();
    // TODO: CleanD2D
    
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
             
            Start_Button = CreateWindow(
                L"BUTTON",                              // 按鈕控制項的類別名稱
                L"開始遊戲",                            // 按鈕上顯示的文字
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
                SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 -80,
                BUTTON_WIDTH, BUTTON_HEIGHT,
                                                        // 按鈕位置和大小 (x, y, width, height)
                hWnd,                                   // 父窗口句柄
                (HMENU)1,                               // 控制項 ID (可以用於識別按鈕)
                GetModuleHandle(NULL),                  // 模組句柄
                NULL                                    // 指定為 NULL
            );
            Difficulty_Button = CreateWindow(
                L"BUTTON",                              // 按鈕控制項的類別名稱
                L"難度選擇",                            // 按鈕上顯示的文字
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
                SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 -40,
                BUTTON_WIDTH, BUTTON_HEIGHT,
                                                        // 按鈕位置和大小 (x, y, width, height)
                hWnd,                                   // 父窗口句柄
                (HMENU)2,                               // 控制項 ID (可以用於識別按鈕)
                GetModuleHandle(NULL),                  // 模組句柄
                NULL                                    // 指定為 NULL
            );
            Score_Button = CreateWindow(
                L"BUTTON",                              // 按鈕控制項的類別名稱
                L"歷史分數",                            // 按鈕上顯示的文字
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
                SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 ,
                BUTTON_WIDTH, BUTTON_HEIGHT,
                                                        // 按鈕位置和大小 (x, y, width, height)
                hWnd,                                   // 父窗口句柄
                (HMENU)3,                               // 控制項 ID (可以用於識別按鈕)
                GetModuleHandle(NULL),                  // 模組句柄
                NULL                                    // 指定為 NULL
            );
            End_Button = CreateWindow(
                L"BUTTON",                              // 按鈕控制項的類別名稱
                L"離開遊戲",                            // 按鈕上顯示的文字
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
                SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 +40,
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
                case 1: //TODO:: 開始遊戲
                    ShowButton(0);
                    //OnPaint(hWnd);
                    engine->playing = 1;
                    break;

                case 2: //TODO:: 難度選擇
                    MessageBox(hWnd, L"此功能尚未實作", L"錯誤", MB_OK | MB_ICONINFORMATION);
                    //hwndScrollBar = CreateWindowEx(
                    //    NULL,                                        // window styles
                    //    L"難易度選擇",                               // 視窗類別的名字
                    //    L"難易度選擇",                               // 視窗的標題
                    //    WS_CHILD | WS_VISIBLE | TBS_HORZ,         // 視窗的樣式
                    //    10, 10, 200, 30,                          // 按鈕位置和大小 (x, y, width, height)
                    //    hWnd,                                     // Parent window
                    //    (HMENU)2001,                                 // Unique ID
                    //    GetModuleHandle(NULL),                    // Instance handle
                    //    NULL                                      // Additional application data
                    //);
                    //ShowWindow(hwndScrollBar, SW_SHOW);
                    //DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOGBAR), hWnd, DialogProc);

                    break;

                case 3: //TODO:: 最高分數
                    MessageBox(hWnd, L"此功能尚未實作", L"錯誤", MB_OK | MB_ICONINFORMATION);
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // 繪製圖片
            //DrawBitmap();
            EndPaint(hWnd, &ps);
        }break;
        //貪吃蛇不使用
        //case WM_LBUTTONDOWN:
        //    // 處理滑鼠左鍵
        //    {
        //        int xPos = GET_X_LPARAM(lParam);
        //        int yPos = GET_Y_LPARAM(lParam);
        //        OnClick(xPos, yPos);
        //    }break;
        case WM_KEYDOWN:
        {
            engine->KeyUp(wParam);
        }
        break;

        case WM_CUSTOM_GAMEEND:
            // 處理遊戲結束
            engine->playing = 0;
            WCHAR scoreStr[64];
            swprintf_s(scoreStr, L"遊戲結束 \n得分為%d     ", engine->getscore());
            MessageBox(hWnd, scoreStr, L"結算", MB_OK);
            ShowButton(1);
            //ClearDraw();
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


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////



// 開啟檔案
//void OpenFile()
//{
//    OPENFILENAME ofn;
//    wchar_t szFile[MAX_PATH] = L"";
//
//    ZeroMemory(&ofn, sizeof(ofn));
//    ofn.lStructSize = sizeof(ofn);
//    ofn.hwndOwner = hWnd;  // 父視窗的 handle
//    ofn.lpstrFile = szFile;
//    ofn.lpstrFile[0] = '\0';
//    ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
//    ofn.lpstrFilter = L"All Files\0*.*\0";
//    ofn.nFilterIndex = 1;
//    ofn.lpstrFileTitle = NULL;
//    ofn.nMaxFileTitle = 0;
//    ofn.lpstrInitialDir = NULL;
//    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
//    // TODO:判斷副檔名
//    if (GetOpenFileName(&ofn) == TRUE)
//    {
//        IWICImagingFactory* pIWICFactory = NULL;
//        CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
        //LoadBitmapFromFile(pRT, pIWICFactory, szFile, 0, 0, &pBitmap);
//        pIWICFactory->Release();
//    }
//}
//
//// 繪圖
//void DrawBitmap()
//{
//    if (pRT && pBitmap)
//    {
//        D2D1_SIZE_U size = pBitmap->GetPixelSize();
//        UINT width = size.width;
//        UINT height = size.height;
//        pRT->BeginDraw();
//        pRT->DrawBitmap(pBitmap, D2D1::RectF(clickPoint.x, clickPoint.y, clickPoint.x + width, clickPoint.y + height));
//        pRT->EndDraw();
//    }
//}
//
// 
//void OnClick(int mouseX, int mouseY)
//{
//    // 更新點擊位置
//    clickPoint.x = static_cast<FLOAT>(mouseX);
//    clickPoint.y = static_cast<FLOAT>(mouseY);
//    // 通知系統進行重繪
//    InvalidateRect(hWnd, NULL, TRUE);
//
//}
//
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

