#pragma once
#include <wincodec.h>
#include "Direct2D.h"

// 視窗相關
#define SCREEN_WIDTH  720  
#define SCREEN_HEIGHT 980
#define BUTTON_INTERVAL 30
#define BUTTON_WIDTH  200
#define BUTTON_HEIGHT 50

// 遊戲相關
#define CELL_SIZE 20
#define GAME_SIZE 7

// 事件或指令相關
#define ID_CUSTOM_COMMAND 1001
#define WM_CUSTOM_GAMEEND WM_USER + 1
#define WM_CUSTOM_GAMEWIN WM_USER + 2

class Common
{
public:

    // 讀取檔案並轉換成圖片
    static HRESULT LoadBitmapFromFile(
                    ID2D1RenderTarget* pRenderTarget,
                    IWICImagingFactory* pIWICFactory,
                    LPCWSTR uri,
                    UINT destinationWidth,
                    UINT destinationHeight,
                    ID2D1Bitmap** ppBitmap)
    {
        // 初始化 WIC
        IWICBitmapDecoder* pDecoder = NULL;
        IWICBitmapFrameDecode* pSource = NULL;
        IWICStream* pStream = NULL;
        IWICFormatConverter* pConverter = NULL;

        HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
            uri,
            NULL,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
        );

        if (SUCCEEDED(hr))
        {
            hr = pDecoder->GetFrame(0, &pSource);
            // 初始化 WIC 轉換器
            hr = pIWICFactory->CreateFormatConverter(&pConverter);
            // 設定轉換器屬性
            hr = pConverter->Initialize(
                pSource,
                GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                NULL,
                0.0,
                WICBitmapPaletteTypeMedianCut
            );
            // 創建 D2D 位圖
            hr = pRenderTarget->CreateBitmapFromWicBitmap(
                pConverter,
                NULL,
                ppBitmap
            );
        }

        // 釋放 WIC 資源
        if (pDecoder != NULL)
            pDecoder->Release();
        if (pSource != NULL)
            pSource->Release();
        if (pStream != NULL)
            pStream->Release();
        if (pConverter != NULL)
            pConverter->Release();

        return hr;
    }

};