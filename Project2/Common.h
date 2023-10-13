#pragma once
#include <wincodec.h>
#include "Direct2D.h"

// ��������
#define SCREEN_WIDTH  1024  
#define SCREEN_HEIGHT 768
#define BUTTON_INTERVAL 30
#define BUTTON_WIDTH  100
#define BUTTON_HEIGHT 30
#define FUNCTION_COLUMN_HEIGHT 50

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
    static void OpenFile(HWND hWnd,ID2D1RenderTarget* pRenderTarget, ID2D1Bitmap** ppBitmap)
    {
        OPENFILENAME ofn;
        wchar_t szFile[MAX_PATH] = L"";

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = hWnd;  // �������� handle
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
        ofn.lpstrFilter = L"All Files\0*.*\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        // TODO:�P�_���ɦW
        if (GetOpenFileName(&ofn) == TRUE)
        {
            IWICImagingFactory* pIWICFactory = NULL;
            CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
            LoadBitmapFromFile(pRenderTarget, pIWICFactory, szFile, 0, 0, ppBitmap);
            pIWICFactory->Release();
        }
    }
    static HBITMAP CreateDIBSectionBitmap(int width, int height) 
    {
        BITMAPINFO bmi;
        ZeroMemory(&bmi, sizeof(BITMAPINFO));
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = width;
        bmi.bmiHeader.biHeight = -height;  // �t�Ȫ�ܳ����V�U
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;  // 32 ���m
        bmi.bmiHeader.biCompression = BI_RGB;

        void* pBits; // �Ω�s�x�Ϲ��ƾڪ����w
        HBITMAP hBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
        return hBitmap;
    }
};