#pragma once

#include "Direct2D.h"
//#include "Direct3D.h"
#include "framework.h"
#include "Food.h"
#include "Snake.h"

#ifndef MIAN
#define MIAN
// 全域聲明
HWND hWnd; // 只將W大寫避免錯誤呼叫
//  按鈕宣告
HWND Load_Button;
HWND Clean_Button;
HWND Start_Button;
HWND Difficulty_Button;
HWND Score_Button;
HWND End_Button;

// 函數原型
void OpenFile(void);
void DrawBitmap();
void ClearDraw();
void OnClick(int mouseX, int mouseY); //貪吃蛇使用不到
void OnPaint(HWND hWnd);
void ShowButton(bool);

//  宣告WindowProc
LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam);


#endif // MIAN