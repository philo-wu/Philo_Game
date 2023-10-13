#pragma once

#include "Direct2D.h"
//#include "Direct3D.h"
#include "framework.h"
#include "Engine.h"


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

//畫面更新
double targetFrameTime = 1.0 / 8; // 目標每幀時間（這裡假設 為 8 FPS）
double accumulatedTime = 0.0;
bool dialog_isfruit;
// 遊戲引擎
Engine* engine;
// 函數原型
// void OpenFile(void);
// void DrawBitmap();
// void ClearDraw();
// void OnClick(int mouseX, int mouseY); 
// void OnPaint(HWND hWnd);
// 以上貪吃蛇使用不到, 並轉移給引擎宣告

ID2D1Bitmap* Tree_Bitmap;
ID2D1Bitmap* Fruit_Bitmap;
ID2D1HwndRenderTarget* Tree_RenderTarget;

ID2D1Factory* pD2DFactory;
HBITMAP finish_Tree;

void ShowButton(bool);

//  宣告WindowProc
LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam);


HRESULT InitD2D(HWND hwnd , ID2D1HwndRenderTarget* RenderTarget)
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
            &RenderTarget
        );
    }

    return hr;
}