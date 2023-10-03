#pragma once

#include <d2d1.h>
#include "framework.h"

// �]�tDirect2D�w���
#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "windowscodecs.lib")

// �ƻs�Ϥ�
ID2D1Factory* pD2DFactory;
ID2D1HwndRenderTarget* pRT;
ID2D1Bitmap* pBitmap;
IWICBitmapDecoder* pDecoder;
IWICBitmapFrameDecode* pSource;
IWICStream* pStream;
IWICFormatConverter* pConverter;
D2D1_POINT_2F clickPoint = { 0 };

HRESULT InitD2D(HWND hwnd);

HRESULT InitD2D(HWND hwnd)
{
    // �Ы� D2D �u�t
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

    if (SUCCEEDED(hr))
    {
        RECT rc;
        GetClientRect(hwnd, &rc);

        // �Ы� D2D ��V�ؼ�
        hr = pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
            &pRT
        );
    }

    return hr;
}
