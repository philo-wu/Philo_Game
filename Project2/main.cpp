
//#include <afx.h>

#include "mian.h"
#include "Dialog_LoadTree_Proc.h"
#include "Dialog_MapMenu_Proc.h"

//提供Dialog句柄
HINSTANCE HINSTANCE1;



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
    HINSTANCE1 = hInstance;
    RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };    // ?置尺寸，而不是位置
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // 調整大小

    // 建立窗口，並將傳回的結果作為句柄
    hWnd = CreateWindowEx(
        NULL,
        L"WindowClass1",                 // 視窗類別的名字
        L"種樹得樹",   // 視窗的標題
        WS_OVERLAPPEDWINDOW,             // 視窗的樣式
        510,                             // 視窗的x座標
        100,                             // 視窗的y座標
        wr.right - wr.left,              // 視窗的寬度 //根據客戶端大小來計算適合的視窗大小
        wr.bottom - wr.top,              // 視窗的高度
        NULL,                            // 沒有父窗口，設定為NULL
        NULL,                            // 不使用選單，設定為NULL
        hInstance,                       // 應用程式句柄
        NULL);                           // 與多個視窗一起使用，設定為NULL

    //按鈕相關樣式
    InitButtom();

    // 顯示視窗
    ShowWindow(hWnd, nCmdShow);
    // 設定並初始化 Direct
    engine = new Engine();
    engine->phWnd = hWnd;
    drawTree = new Tree(L"1");
    drawFruitTree = new FruitTree(L"2",L"apple");
    engine->InitializeD2D(hWnd); //繪製背景
    //Common::InitD2D(hWnd , Tree_RenderTarget); //繪製

    //   InitD3D(hWnd);
    // 進入主要迴圈:
    
    // 這個結構體包含Windows事件訊息
    MSG msg = { 0 };    
    // 訊息迴圈
    while (TRUE)
    {


        // ?查?列中是否有消息正在等待
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
            // 因種樹程式不需重複繪圖故不使用
            //if (engine->playing)
            //{
            //    // Drawing
            //engine->Draw(Map_clickPoint, DIALOG_TREELOAD_TREE_PX, MAINDIALOG_TREE_PX, drawFruitTree, Map_saveData_using, Tree_saveData, Map_treepoints);
            //}
        }
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
            int buttomnumber = 0;
            // 判斷不需要單純繪製樹木
            // Start_Button = CreateWindow(
            //    L"BUTTON",                              // 按鈕控制項的類別名稱
            //    L"選擇樹木",                            // 按鈕上顯示的文字
            //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
            //    10 + (BUTTON_WIDTH+10)* buttomnumber, 10,
            //    BUTTON_WIDTH, BUTTON_HEIGHT,
            //                                            // 按鈕位置和大小 (x, y, width, height)
            //    hWnd,                                   // 父窗口句柄
            //    (HMENU)1,                               // 控制項 ID (可以用於識別按鈕)
            //    GetModuleHandle(NULL),                  // 模組句柄
            //    NULL                                    // 指定為 NULL
            //);
            //++buttomnumber;
            Difficulty_Button = CreateWindow(
                L"BUTTON",                              // 按鈕控制項的類別名稱
                L"繪畫選單",                            // 按鈕上顯示的文字
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
                10 + (BUTTON_WIDTH + 10) * buttomnumber, 10,
                BUTTON_WIDTH, BUTTON_HEIGHT,
                                                        // 按鈕位置和大小 (x, y, width, height)
                hWnd,                                   // 父窗口句柄
                (HMENU)2,                               // 控制項 ID (可以用於識別按鈕)
                GetModuleHandle(NULL),                  // 模組句柄
                NULL                                    // 指定為 NULL
            );
            ++buttomnumber;

            Score_Button = CreateWindow(
                L"BUTTON",                              // 按鈕控制項的類別名稱
                L"地圖選單",                            // 按鈕上顯示的文字
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
                10 + (BUTTON_WIDTH + 10) * buttomnumber, 10,
                BUTTON_WIDTH, BUTTON_HEIGHT,
                                                        // 按鈕位置和大小 (x, y, width, height)
                hWnd,                                   // 父窗口句柄
                (HMENU)3,                               // 控制項 ID (可以用於識別按鈕)
                GetModuleHandle(NULL),                  // 模組句柄
                NULL                                    // 指定為 NULL
            );
            ++buttomnumber;

            //End_Button = CreateWindow(
            //    L"BUTTON",                              // 按鈕控制項的類別名稱
            //    L"讀取地圖",                            // 按鈕上顯示的文字
            //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
            //    10 + (BUTTON_WIDTH + 10) * buttomnumber, 10,
            //    BUTTON_WIDTH, BUTTON_HEIGHT,
            //                                            // 按鈕位置和大小 (x, y, width, height)
            //    hWnd,                                   // 父窗口句柄
            //    (HMENU)4,                               // 控制項 ID (可以用於識別按鈕)
            //    GetModuleHandle(NULL),                  // 模組句柄
            //    NULL                                    // 指定為 NULL
            //);
            //++buttomnumber;

            //Clean_Button = CreateWindow(
            //    L"BUTTON",                              // 按鈕控制項的類別名稱
            //    L"地圖清空",                            // 按鈕上顯示的文字
            //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // 按鈕樣式
            //    10 + (BUTTON_WIDTH + 10) * buttomnumber, 10,
            //    BUTTON_WIDTH, BUTTON_HEIGHT,
            //                                            // 按鈕位置和大小 (x, y, width, height)
            //    hWnd,                                   // 父窗口句柄
            //    (HMENU)5,                               // 控制項 ID (可以用於識別按鈕)
            //    GetModuleHandle(NULL),                  // 模組句柄
            //    NULL                                    // 指定為 NULL
            //);
            //++buttomnumber;

        }
        break;
        case WM_COMMAND:// 檢查按鈕事件
            if (HIWORD(wParam) == BN_CLICKED )
            {
                //檢查按鈕身分
                switch (LOWORD(wParam))
                {

                case 1: // 選擇樹木
                {
                    if (Dialog_LoadTree_is_open)
                    {
                        MessageBox(hWnd, L"視窗已打開", L"錯誤", MB_OK);
                        break;
                    }
                    Dialog_is_fruit = 0;
                    DialogBox(HINSTANCE1, MAKEINTRESOURCE(IDD_LOADTREE), NULL, Dialog_LoadTree_Proc);
                }
                break;

                case 2: // 選擇水果樹
                {
                    if (Dialog_LoadTree_is_open)
                    {
                        MessageBox(hWnd, L"視窗已打開", L"錯誤", MB_OK);
                        break;
                    }
                    Dialog_is_fruit = 1;
                    DialogBox(HINSTANCE1, MAKEINTRESOURCE(IDD_LOADTREE), NULL, Dialog_LoadTree_Proc);
                }                    
                break;

                case 3: // 儲存地圖
                {   
                    //std::wstring filePath ;
                    //Common::FileSaveDialog(filePath);
                    //// 拼接字串

                    //OutputDebugString(filePath.c_str());
                    //Common::SaveWindowToImage(hWnd, filePath.c_str(), { 0,FUNCTION_COLUMN_HEIGHT }, SCREEN_WIDTH,SCREEN_HEIGHT - FUNCTION_COLUMN_HEIGHT);

                    DialogBox(HINSTANCE1, MAKEINTRESOURCE(IDD_RANKLIST), NULL, Dialog_MapMenu_Proc);

                }
                break;

                case 4: // 讀取地圖
                {
                    std::wstring  NULLPATH ;//不保存檔案路徑
                    std::wstring  fileName ;
                    Common::OpenFile(hWnd, engine->m_pRenderTarget, &engine->Map_Bitmap, NULLPATH, fileName , currentPath);
                    if (fileName.empty())
                        break;
                    engine->do_clear = 1;
                    engine->do_drawMap = 1;
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;

                case 5: // 地圖清空
                {
                    Map_clickPoint.x = static_cast<FLOAT>(0);
                    Map_clickPoint.y = static_cast<FLOAT>(0);
                    engine->do_clear = 1;
                    engine->Map_Bitmap = NULL;

                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;
                case ID_CUSTOM_COMMAND: // 自定義命令的處理
                    //常用指令
                    //MessageBox(hWnd, L"遊戲結束 \n得分為X", L"結算", MB_OK);
                    //SendMessage(hWnd, WM_COMMAND, ID_CUSTOM_COMMAND, 0);  //此為自定義命令
                    //SendMessage(hWnd, WM_CUSTOM_GAMEEND, 0, 0);           //此為自定義事件
                    //SendMessage(hWnd, WM_CLOSE, 0, 0);                      //視窗關閉
                 break;
                }
            }
        break;
        case WM_PAINT:
        {
            // 主選單畫面
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            //if(Dialog_is_fruit)// 1改成判斷要畫樹還是水果樹
                //engine->Draw(Map_clickPoint, DIALOG_TREELOAD_TREE_PX, MAINDIALOG_TREE_PX, drawTree , Map_saveData , Map_treepoints);
            //else
            //std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            //std::wstring wstr = converter.from_bytes(using_MapName);
            //OutputDebugString(L"測試\n");

            //OutputDebugString(wstr.c_str());
            //OutputDebugString(L"\n");

            //wstr = converter.from_bytes(using_Main_TreeName);
            //OutputDebugString(wstr.c_str());
            //OutputDebugString(L"\n");

                engine->Draw(hWnd, Map_clickPoint, DIALOG_TREELOAD_TREE_PX, MAINDIALOG_TREE_PX, drawFruitTree ,
                    Map_saveData_using, Tree_saveData , Map_treepoints ,
                    using_MapName , using_Main_TreeName);
                
            EndPaint(hWnd, &ps);
        }
        break;
        
        case WM_LBUTTONDOWN: // 處理滑鼠左鍵
        {
            int xPos = GET_X_LPARAM(lParam);
            int yPos = GET_Y_LPARAM(lParam);
            if (xPos >= 0 
                && yPos >= FUNCTION_COLUMN_HEIGHT
                && drawFruitTree->treeBitmap)
            {
                if (xPos + fixed_px_fruit > SCREEN_WIDTH)
                    xPos = SCREEN_WIDTH - fixed_px_fruit;
                if (yPos + fixed_px_fruit > SCREEN_HEIGHT)
                    yPos = SCREEN_HEIGHT - fixed_px_fruit;

                Map_clickPoint.x = static_cast<FLOAT>(xPos);
                Map_clickPoint.y = static_cast<FLOAT>(yPos);
                Map_treepoints.push_back(Map_clickPoint);
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        break;
        case WM_KEYDOWN:
        {
        }
        break;

        case WM_DESTROY: // 當視窗關閉時會讀取此訊息
        {
                // 完全關閉應用程式
                PostQuitMessage(0);
                return 0;
        } 
        break;
    }

    // 處理 switch 語句未攔截訊息
    return DefWindowProc (hWnd, message, wParam, lParam);
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


// Dialog架構保留
//INT_PTR CALLBACK Dialog_Ranklist_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    DWORD dwID = wParam;
//
//    switch (uMsg) {
//    case WM_INITDIALOG:
//        {
//            // 設定滑塊範圍
//            HWND hListView = GetDlgItem(hwndDlg, IDC_LIST4);
//            DWORD dwStyle = GetWindowLong(hListView, GWL_STYLE);
//            SetWindowLong(hListView, GWL_STYLE, dwStyle | LVS_REPORT | LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP);
//
//            // 添加三列標題
//            LVCOLUMN lvColumn = { 0 };
//            lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
//
//            // 第一列：姓名
//            const wchar_t* myConstString = L"姓名";
//            wchar_t* myNonConstString = const_cast<wchar_t*>(myConstString);
//            lvColumn.pszText = const_cast<wchar_t*>(myConstString);
//            lvColumn.iSubItem = 0;
//            lvColumn.cx = 150;  // 設定列寬度
//            ListView_InsertColumn(hListView, 0, &lvColumn);
//
//            // 第二列：分數
//            myConstString = L"分數";
//            myNonConstString = const_cast<wchar_t*>(myConstString);
//            lvColumn.pszText = const_cast<wchar_t*>(myConstString);
//            lvColumn.iSubItem = 1;
//            lvColumn.cx = 150;
//            ListView_InsertColumn(hListView, 1, &lvColumn);
//
//            // 第三列：難度
//            myConstString = L"難度";
//            myNonConstString = const_cast<wchar_t*>(myConstString);
//            lvColumn.pszText = const_cast<wchar_t*>(myConstString);
//            lvColumn.iSubItem = 2;
//            lvColumn.cx = 90;
//            ListView_InsertColumn(hListView, 2, &lvColumn);
//
//
//
//            std::ifstream file("C:\\Users\\philo.wu\\Documents\\GitHub\\Philo_Snake\\Project2\\Ranklist.json", std::ifstream::binary);
//            if (file.is_open()) 
//            {
//                json j;
//                file >> j;
//
//                // 處理解析後的資料
//                for (const auto& entry : j["Ranklist"]) {
//                    std::string name = entry["name"];
//                    int score = entry["score"];
//                    int difficulty = entry["difficulty"];
//
//                    // 在這裡處理中文編碼問題
//                    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//                    std::wstring nameText = converter.from_bytes(name);
//
//                    LVITEM lvi;
//                    lvi.mask = LVIF_TEXT;
//                    lvi.pszText = const_cast<wchar_t*>(nameText.c_str());
//                    lvi.iItem = ListView_GetItemCount(hListView);  // 新增項目的索引
//                    lvi.iSubItem = 0;
//                    ListView_InsertItem(hListView, &lvi);
//
//                    // 設置分數
//                    std::wstring scoreText = std::to_wstring(score);
//                    ListView_SetItemText(hListView, lvi.iItem, 1, const_cast<wchar_t*>(scoreText.c_str()));
//
//                    // 設置難度
//                    std::wstring difficultyText = std::to_wstring(difficulty);
//                    ListView_SetItemText(hListView, lvi.iItem, 2, const_cast<wchar_t*>(difficultyText.c_str()));
//
//                }
//
//                file.close();
//            }
//            else 
//            {
//                //std::cout << "Failed to open JSON file" << std::endl;
//            }
//        }
//        break;
//
//    case WM_COMMAND:
//        switch (LOWORD(wParam))
//        {
//        case IDOK:
//            // 使用者按下了確定按鈕
//        {
//            EndDialog(hwndDlg, IDOK);
//        }
//        break;
//        case IDCANCEL:
//            // 使用者按下了取消按鈕
//            EndDialog(hwndDlg, IDCANCEL);
//            break;
//        }
//        break;
//    }
//    return FALSE;
//}
//INT_PTR CALLBACK Dialog_GameEnd_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    DWORD dwID = wParam;
//
//    switch (uMsg) {
//    case WM_INITDIALOG:
//        return TRUE;
//
//    case WM_COMMAND:
//        switch (LOWORD(wParam))
//        {
//        case IDOK:
//            // 使用者按下了確定按鈕
//        {
//            // 取得玩家名稱
//            int textLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_EDIT1));
//            if (textLength == 0)
//            {
//                // 輸入為空
//                MessageBox(hWnd, L"未輸入玩家名稱", L"錯誤", MB_OK);
//                // 彈出結束畫面
//                SendMessage(hWnd, WM_CUSTOM_GAMEEND, 0, 0);
//            }
//            else
//            {
//                wchar_t buffer[100]; // 要存放資料的緩衝區
//                GetDlgItemText(hwndDlg, IDC_EDIT1, buffer, 100);
//                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
//                std::string newName = converter.to_bytes(buffer);
//
//                int newScore =0;
//                int newDifficulty =0;
//
//                std::ifstream file("./Ranklist.json", std::ifstream::binary);
//                json jsonData;
//                file >> jsonData;
//                file.close();
//
//                json newEntry = {
//                    {"name", newName},
//                    {"score", newScore},
//                    {"difficulty", newDifficulty}
//                };
//                jsonData["Ranklist"].push_back(newEntry);
//                std::ofstream outFile("./Ranklist.json");
//                outFile << jsonData.dump(4);  // 4 是縮排的數量
//                outFile.close();
//                
//            }
//
//            EndDialog(hwndDlg, IDOK);
//        }
//        break;
//
//        case IDCANCEL:
//            // 使用者按下了取消按鈕
//            EndDialog(hwndDlg, IDCANCEL);
//            break;
//        }
//        break;
//    }
//    return FALSE;
//}
