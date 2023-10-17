#pragma once

#include "Direct2D.h"
//#include "Direct3D.h"
#include "framework.h"
#include "Engine.h"
#include "resource.h"

// 全域聲明
HWND hWnd; // 只將W大寫避免錯誤呼叫
//  按鈕宣告
HWND Load_Button;
HWND Clean_Button;
HWND Start_Button;
HWND Difficulty_Button;
HWND Score_Button;
HWND End_Button;

HWND hwndScrollBar;

//畫面更新
//double targetFrameTime = 1.0 / 8; // 目標每幀時間（這裡假設 為 8 FPS）
//double accumulatedTime = 0.0;

// 遊戲引擎
Engine* engine;
Common* common;

IFileSaveDialog* pFileSaveDlg = NULL;


// 函數原型
void ShowButton(bool);
void InitButtom();
//  宣告WindowProc
LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam);


void ShowButton(bool show)
{
    if (show)
    {
        ShowWindow(Start_Button, SW_SHOW);
        ShowWindow(Difficulty_Button, SW_SHOW);
        ShowWindow(Score_Button, SW_SHOW);
        ShowWindow(End_Button, SW_SHOW);
        ShowWindow(Clean_Button, SW_SHOW);

    }
    else
    {
        ShowWindow(Start_Button, SW_HIDE);
        ShowWindow(Difficulty_Button, SW_HIDE);
        ShowWindow(Score_Button, SW_HIDE);
        ShowWindow(End_Button, SW_HIDE);
        ShowWindow(Clean_Button, SW_HIDE);

    }
}

void InitButtom()
{
    // 字體及大小
    HFONT hFont = CreateFont(
        18,                                     // 字體的高度
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
    SendMessage(Clean_Button, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

}