#pragma once

#include "Direct2D.h"
//#include "framework.h"
#include "Engine.h"
#include "resource.h"


// 以下為原複製圖片宣告,但經思考後,決定學習網路上宣告在引擎內
// 原本想宣告在Direct2D.h ,但發現會重複宣告,應包成 Class處理,
//ID2D1Factory* pD2DFactory;
//ID2D1HwndRenderTarget* pRT;
//ID2D1Bitmap* pBitmap;
//IWICBitmapDecoder* pDecoder;
//IWICBitmapFrameDecode* pSource;
//IWICStream* pStream;
//IWICFormatConverter* pConverter;
//D2D1_POINT_2F clickPoint = { 0 };
//HRESULT InitD2D(HWND hwnd)
//{
//    // 建立D2D工廠
//    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
//
//    if (SUCCEEDED(hr))
//    {
//        RECT rc;
//        GetClientRect(hwnd, &rc);
//
//
//        hr = pD2DFactory->CreateHwndRenderTarget(
//            D2D1::RenderTargetProperties(),
//            D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
//            &pRT
//        );
//    }
//
//    return hr;
//};

// 全域聲明
HWND hWnd; // 只將W大寫避免錯誤呼叫
bool GameRunning = 0;
//  按鈕宣告
HWND Load_Button;
HWND Clean_Button;
HWND Start_Button;
HWND Difficulty_Button;
HWND Score_Button;
HWND End_Button;
HWND hwndScrollBar;

HINSTANCE HINSTANCE1;

//畫面更新
double secFrameTime = 1.0 / 120; // 目標每幀時間（這裡假設 為 8 FPS）
double secTime = 0.0;

double targetFrameTime = 1000 / 120; // 目標每幀時間（這裡假設 為 8 FPS）
double accumulatedTime = 0.0;

double logicFrameTime = 1000 / 240; // 目標每幀時間（這裡假設 為 8 FPS）
double logicAccumulatedTime = 0.0;

int deltaTime = 0;
// 遊戲引擎
     Engine* engine;
     Common* common;
// 函數原型
// void OpenFile(void);
// void DrawBitmap();
// void ClearDraw();
// void OnClick(int mouseX, int mouseY); 
// void OnPaint(HWND hWnd);
// 以上貪吃蛇使用不到, 並轉移給引擎宣告

void ShowButton(bool);
void init(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow);
    
//  宣告WindowProc
LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam);


// 
#ifdef NOUSE
INT_PTR CALLBACK Dialog_Difficulty_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD dwID = wParam;

    switch (uMsg) {
    case WM_INITDIALOG:

        // 設定滑塊範圍
        SendDlgItemMessage(hwndDlg, IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG(1, 9));
        // 設定滑塊初始值
        SendDlgItemMessage(hwndDlg, IDC_SLIDER1, TBM_SETPOS, TRUE, 5);

        // 設定 "食物生成於邊界" 勾選框的初始狀態
        //if(engine->isFoodOnBorderChecked)
        //    CheckDlgButton(hwndDlg, IDC_CHECK1, BST_CHECKED);
        //else
        //    CheckDlgButton(hwndDlg, IDC_CHECK1, BST_UNCHECKED);

        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            // 使用者按下了確定按鈕
        {
            // 取得設定頁面的資料
            int sliderValue = SendDlgItemMessage(hwndDlg, IDC_SLIDER1, TBM_GETPOS, 0, 0);
            BOOL isFoodOnBorderChecked = IsDlgButtonChecked(hwndDlg, IDC_CHECK1) == BST_CHECKED;
            // 將資料存入引擎
            //engine->difficulty = sliderValue;
            //targetFrameTime = engine->UpdateFrameSleep(engine->difficulty);
            //engine->isFoodOnBorderChecked = isFoodOnBorderChecked;

            EndDialog(hwndDlg, IDOK);
        }
        break;

        case IDCANCEL:
            // 使用者按下了取消按鈕
            EndDialog(hwndDlg, IDCANCEL);
            break;
        }
        break;
    }
    return FALSE;
}
INT_PTR CALLBACK Dialog_Ranklist_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD dwID = wParam;

    switch (uMsg) {
    case WM_INITDIALOG:
    {
        // 設定滑塊範圍
        HWND hListView = GetDlgItem(hwndDlg, IDC_LIST4);
        DWORD dwStyle = GetWindowLong(hListView, GWL_STYLE);
        SetWindowLong(hListView, GWL_STYLE, dwStyle | LVS_REPORT | LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP);

        // 添加三列標題
        LVCOLUMN lvColumn = { 0 };
        lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

        // 第一列：姓名
        const wchar_t* myConstString = L"姓名";
        wchar_t* myNonConstString = const_cast<wchar_t*>(myConstString);
        lvColumn.pszText = const_cast<wchar_t*>(myConstString);
        lvColumn.iSubItem = 0;
        lvColumn.cx = 150;  // 設定列寬度
        ListView_InsertColumn(hListView, 0, &lvColumn);

        // 第二列：分數
        myConstString = L"分數";
        myNonConstString = const_cast<wchar_t*>(myConstString);
        lvColumn.pszText = const_cast<wchar_t*>(myConstString);
        lvColumn.iSubItem = 1;
        lvColumn.cx = 150;
        ListView_InsertColumn(hListView, 1, &lvColumn);

        // 第三列：難度
        myConstString = L"難度";
        myNonConstString = const_cast<wchar_t*>(myConstString);
        lvColumn.pszText = const_cast<wchar_t*>(myConstString);
        lvColumn.iSubItem = 2;
        lvColumn.cx = 90;
        ListView_InsertColumn(hListView, 2, &lvColumn);



        std::ifstream file("./Ranklist.json", std::ifstream::binary);
        if (file.is_open())
        {
            json j;
            file >> j;

            // 處理解析後的資料
            for (const auto& entry : j["Ranklist"]) {
                std::string name = entry["name"];
                int score = entry["score"];
                int difficulty = entry["difficulty"];

                // 在這裡處理中文編碼問題
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                std::wstring nameText = converter.from_bytes(name);

                LVITEM lvi;
                lvi.mask = LVIF_TEXT;
                lvi.pszText = const_cast<wchar_t*>(nameText.c_str());
                lvi.iItem = ListView_GetItemCount(hListView);  // 新增項目的索引
                lvi.iSubItem = 0;
                ListView_InsertItem(hListView, &lvi);

                // 設置分數
                std::wstring scoreText = std::to_wstring(score);
                ListView_SetItemText(hListView, lvi.iItem, 1, const_cast<wchar_t*>(scoreText.c_str()));

                // 設置難度
                std::wstring difficultyText = std::to_wstring(difficulty);
                ListView_SetItemText(hListView, lvi.iItem, 2, const_cast<wchar_t*>(difficultyText.c_str()));

            }

            file.close();
        }
        else
        {
            //std::cout << "Failed to open JSON file" << std::endl;
        }
    }
    break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            // 使用者按下了確定按鈕
        {
            EndDialog(hwndDlg, IDOK);
        }
        break;
        case IDCANCEL:
            // 使用者按下了取消按鈕
            EndDialog(hwndDlg, IDCANCEL);
            break;
        }
        break;
    }
    return FALSE;
}
INT_PTR CALLBACK Dialog_GameEnd_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD dwID = wParam;

    switch (uMsg) {
    case WM_INITDIALOG:

        // 將實際分數設定到對應的靜態文字控制項上
        //SetDlgItemInt(hwndDlg, IDC_STATIC_SCORE, engine->GetWindScore(), FALSE);
        // 將實際難度設定到對應的靜態文字控制項上
        //SetDlgItemInt(hwndDlg, IDC_STATIC_DIFFICULTY, engine->difficulty, FALSE);

        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            // 使用者按下了確定按鈕
        {
            // 取得玩家名稱
            int textLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_EDIT1));
            if (textLength == 0)
            {
                // 輸入為空
                MessageBox(hWnd, L"未輸入玩家名稱", L"錯誤", MB_OK);
                // 彈出結束畫面
                SendMessage(hWnd, WM_CUSTOM_GAMEEND, 0, 0);
            }
            else
            {
                wchar_t buffer[100]; // 要存放資料的緩衝區
                GetDlgItemText(hwndDlg, IDC_EDIT1, buffer, 100);
                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                std::string newName = converter.to_bytes(buffer);

                //int newScore = engine->getscore();
                //int newDifficulty = engine->difficulty;

                std::ifstream file("./Ranklist.json", std::ifstream::binary);
                json jsonData;
                if (file.is_open())
                {
                    file >> jsonData;
                    file.close();
                }
                json newEntry = {
                    {"name", newName},
                    //{"score", newScore},
                    //{"difficulty", newDifficulty}
                };
                jsonData["Ranklist"].push_back(newEntry);
                std::ofstream outFile("./Ranklist.json");
                outFile << jsonData.dump(4);  // 4 是縮排的數量
                outFile.close();

            }

            EndDialog(hwndDlg, IDOK);
        }
        break;

        case IDCANCEL:
            // 使用者按下了取消按鈕
            EndDialog(hwndDlg, IDCANCEL);
            break;
        }
        break;
    }
    return FALSE;
}

#endif