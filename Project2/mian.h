#pragma once

#include "Direct2D.h"
//#include "Direct3D.h"
#include "framework.h"
#include "Engine.h"


// �H�U����ƻs�Ϥ��ŧi,���g��ҫ�,�M�w�ǲߺ����W�ŧi�b������
// �쥻�Q�ŧi�bDirect2D.h ,���o�{�|���ƫŧi,���]�� Class�B�z,
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
//    // �إ�D2D�u�t
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

// �����n��
HWND hWnd; // �u�NW�j�g�קK���~�I�s
bool GameRunning = 0;
//  ���s�ŧi
HWND Load_Button;
HWND Clean_Button;
HWND Start_Button;
HWND Difficulty_Button;
HWND Score_Button;
HWND End_Button;
HWND hwndScrollBar;

//�e����s
double targetFrameTime = 1.0 / 8; // �ؼШC�V�ɶ��]�o�̰��] �� 8 FPS�^
double accumulatedTime = 0.0;
int deltaTime = 0;
// �C������
     Engine* engine;
// ��ƭ쫬
// void OpenFile(void);
// void DrawBitmap();
// void ClearDraw();
// void OnClick(int mouseX, int mouseY); 
// void OnPaint(HWND hWnd);
// �H�W�g�Y�D�ϥΤ���, ���ಾ�������ŧi

void ShowButton(bool);

//  �ŧiWindowProc
LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam);


