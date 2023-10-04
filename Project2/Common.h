#pragma once
#include <wincodec.h>
#include "Direct2D.h"

// ��������
#define SCREEN_WIDTH  1024  
#define SCREEN_HEIGHT 768
#define BUTTON_INTERVAL 30
#define BUTTON_WIDTH  200
#define BUTTON_HEIGHT 50

// �C������
#define CELL_SIZE 20

// �ƥ�Ϋ��O����
#define ID_CUSTOM_COMMAND 1001
#define WM_CUSTOM_GAMEEND WM_USER + 1
#define WM_CUSTOM_GAMEWIN WM_USER + 2

class Common
{
public:

    // Ū���ɮר��ഫ���Ϥ�
    static HRESULT LoadBitmapFromFile(
                    ID2D1RenderTarget* pRenderTarget,
                    IWICImagingFactory* pIWICFactory,
                    LPCWSTR uri,
                    UINT destinationWidth,
                    UINT destinationHeight,
                    ID2D1Bitmap** ppBitmap)
    {
        // ��l�� WIC
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
            // ��l�� WIC �ഫ��
            hr = pIWICFactory->CreateFormatConverter(&pConverter);
            // �]�w�ഫ���ݩ�
            hr = pConverter->Initialize(
                pSource,
                GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                NULL,
                0.0,
                WICBitmapPaletteTypeMedianCut
            );
            // �Ы� D2D ���
            hr = pRenderTarget->CreateBitmapFromWicBitmap(
                pConverter,
                NULL,
                ppBitmap
            );
        }

        // ���� WIC �귽
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