﻿#pragma once
#include <wincodec.h>
#include "Direct2D.h"
//#include <Shlobj.h>
#include <filesystem> //讀取專案位置
#include <regex> //中文判定

// UI相關
#define SCREEN_WIDTH  1024  
#define SCREEN_HEIGHT 768
#define BUTTON_INTERVAL 30
#define BUTTON_WIDTH  100
#define BUTTON_HEIGHT 30
#define FUNCTION_COLUMN_HEIGHT 50 //主視窗上方功能列
//TreeLoad的樹木圖片繪製地點
#define DIALOG_TREELOAD_POINT_X 130 
#define DIALOG_TREELOAD_POINT_Y 10
//TreeLoad的水果圖片繪製地點
#define DIALOG_TREELOAD_FRUIT_POINT_X 90
#define DIALOG_TREELOAD_FRUIT_POINT_Y 125

#define DIALOG_TREELOAD_TREE_PX 200 //TreeLoad的樹木圖片繪製大小
#define DIALOG_TREELOAD_FRUIT_PX 30 //TreeLoad的水果圖片繪製大小
#define MAINDIALOG_TREE_PX 50 //主視窗的元件繪製大小


// 遊戲相關
#define CELL_SIZE 20

// 事件或指令相關
#define ID_CUSTOM_COMMAND 1001
#define WM_CUSTOM_GAMEEND WM_USER + 1
#define WM_CUSTOM_GAMEWIN WM_USER + 2

struct dtawPoint {
    int x;
    int y;

    // 自定義的比較函數
    bool operator<(const dtawPoint& other) const {
        // 首先按照 y 坐標升序排列
        if (y != other.y) {
            return y < other.y;
        }
        // 如果 y 相同，則按照 x 坐標升序排列
        return x < other.x;
    }
}; 

class Common
{
public:
    // 依據uri路徑讀取檔案並轉換成圖片
    Common() {
    }
    ~Common();
    static HRESULT LoadBitmapFromFile(
        ID2D1RenderTarget* pRenderTarget,
        IWICImagingFactory* pIWICFactory,
        std::wstring uri,
        UINT destinationWidth,
        UINT destinationHeight,
        ID2D1Bitmap** ppBitmap,
        HWND hwnd,
        int& result)
    {
        // 初始化 WIC
        result = 0;
        IWICBitmapDecoder* pDecoder = NULL;
        IWICBitmapFrameDecode* pSource = NULL;
        //IWICStream* pStream = NULL;
        IWICFormatConverter* pConverter = NULL;

        HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
            uri.c_str(),
            NULL,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
        );

        if (SUCCEEDED(hr))
        {
            hr = pDecoder->GetFrame(0, &pSource);
            UINT width, height;
            pSource->GetSize(&width, &height);
            UINT32* pixels = (UINT32*)malloc(width * height * 4);

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

            //創建 D2D 位圖
            hr = pRenderTarget->CreateBitmapFromWicBitmap(
                pConverter,
                NULL,
                ppBitmap
            );
        }
        else
        {
            std::wstring path = (uri.c_str());
            path += L"\n圖檔不存在\n";
            OutputDebugString(path.c_str());
            MessageBox(hwnd, path.c_str(), L"錯誤", MB_OK);
            result = 1;
        }

        // 釋放 WIC 資源
        if (pDecoder)
            pDecoder->Release();
        if (pSource)
            pSource->Release();
        //if (pStream)
        //    pStream->Release();
        if (pConverter)
            pConverter->Release();

        return hr;
    }

    //初始化RenderTarget
    static HRESULT InitD2D(HWND hwnd, ID2D1Factory* D2DFactory, ID2D1HwndRenderTarget** RenderTarget)
    {
        // 創建 D2D 工廠
        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory);

        if (SUCCEEDED(hr))
        {
            RECT rc;
            GetClientRect(hwnd, &rc);

            // 創建 D2D 渲染目標
            hr = D2DFactory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
                RenderTarget
            );
            OutputDebugString(L"RenderTarget初始化完成\n");
        }

        return hr;
    }

    // 以檔案總管取得檔案路徑,並寫入Bitmap
    static void OpenFile(HWND hWnd,
        ID2D1RenderTarget* pRenderTarget, 
        ID2D1Bitmap** ppBitmap, //輸出的圖檔
        std::wstring& ploadPath,  
        std::wstring& filename, 
        std::filesystem::path currentPath)
    {
        //OutputDebugString(L"讀取檔案\n");

        OPENFILENAME ofn;
        wchar_t szFile[MAX_PATH] = L"";

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = hWnd;  // 父視窗的 handle
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
        ofn.lpstrFilter = L"Image Files\0*.bmp;*.jpg;*.png\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        std::wstring str = currentPath.parent_path().wstring() + L"\\種樹\\Images\\";
        //OutputDebugString(L"\n檔案讀取預設路徑\n");
        //OutputDebugString(str.c_str());
        ofn.lpstrInitialDir = str.c_str();
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        // TODO:判斷副檔名

        if (GetOpenFileName(&ofn) == TRUE)
        {
            // 檔案是可寫的
            IWICImagingFactory* pIWICFactory = NULL;
            CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
            int errorcode;
            LoadBitmapFromFile(pRenderTarget, pIWICFactory, szFile, 0, 0, ppBitmap, hWnd, errorcode);
            if (errorcode != 0) {
                if (pIWICFactory)
                    pIWICFactory->Release();
                return;
            }
            OutputDebugString(szFile);
            //將讀取路徑儲存
            ploadPath = szFile;
            filename = PathFindFileName(szFile);

            if (pIWICFactory)
                pIWICFactory->Release();
        }
        else
        {
            filename.erase();
        }
    }
    //用以製作32位元bitmap
    static HBITMAP CreateDIBSectionBitmap(int width, int height)
    {
        BITMAPINFO bmi;
        ZeroMemory(&bmi, sizeof(BITMAPINFO));
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = width;
        bmi.bmiHeader.biHeight = -height;  // 負值表示頂部向下
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;  // 32 位色彩
        bmi.bmiHeader.biCompression = BI_RGB;

        void* pBits; // 用於存儲圖像數據的指針
        HBITMAP hBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
        return hBitmap;
    }

    //截圖視窗畫面到檔案中
    static void SaveWindowToImage(
        HWND hwnd,
        const wchar_t* filePath,
        dtawPoint point,
        int RECTwidth,
        int RECTheight
    )
    {
        if (filePath == nullptr || wcslen(filePath) == 0)
            return;

        // 初始化 WIC
        CoInitialize(nullptr);
        IWICImagingFactory* pWICFactory = nullptr;
        IWICBitmapEncoder* pEncoder = nullptr;
        IWICBitmapFrameEncode* pFrame = nullptr;
        IWICStream* pStream = nullptr;

        // 設定轉換器屬性



        if (SUCCEEDED(CoCreateInstance(
            CLSID_WICImagingFactory,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_IWICImagingFactory,
            reinterpret_cast<void**>(&pWICFactory))))
        {
            // 創建編碼器
            if (SUCCEEDED(pWICFactory->CreateEncoder(
                GUID_ContainerFormatPng,  // 或者其他支援的格式
                nullptr,
                &pEncoder)))
            {
                // 創建位圖流
                if (SUCCEEDED(pWICFactory->CreateStream(&pStream)))
                {
                    // 初始化位圖流
                    if (SUCCEEDED(pStream->InitializeFromFilename(filePath, GENERIC_WRITE)))
                    {
                        // 初始化編碼器與位圖流
                        if (SUCCEEDED(pEncoder->Initialize(pStream, WICBitmapEncoderNoCache)))
                        {
                            // 創建位圖編碼幀
                            if (SUCCEEDED(pEncoder->CreateNewFrame(&pFrame, nullptr)))
                            {
                                // 初始化位圖編碼幀
                                if (SUCCEEDED(pFrame->Initialize(nullptr)))
                                {
                                    // 獲取視窗大小
                                    // 創建兼容的 DC
                                    HDC hMemDC = CreateCompatibleDC(nullptr);
                                    HBITMAP hBitmap;
                                    // 創建位圖
                                    hBitmap = CreateDIBSectionBitmap(RECTwidth, RECTheight);

                                    // 選入位圖到兼容 DC
                                    SelectObject(hMemDC, hBitmap);

                                    // 複製視窗內容到兼容 DC
                                    PrintWindow(hwnd, hMemDC, PW_CLIENTONLY);
                                    // 複製指定區域內容到兼容 DC
                                    BitBlt(hMemDC, 0, 0, RECTwidth, RECTheight, GetDC(hwnd), point.x, point.y, SRCCOPY);

                                    // 使用 WIC 創建位圖源
                                    IWICBitmap* pWICBitmap = nullptr;

                                    if (SUCCEEDED(pWICFactory->CreateBitmapFromHBITMAP(
                                        hBitmap,
                                        nullptr,
                                        WICBitmapIgnoreAlpha,
                                        &pWICBitmap)))
                                    {

                                        GUID format = GUID_WICPixelFormat32bppPBGRA;
                                        pFrame->SetPixelFormat(&format);
                                        // 目前不需要去背 20231019
                                        //if (IsEqualGUID(format, GUID_WICPixelFormat32bppBGRA))
                                        //{
                                        //    //如果格式是 32bppBGRA，將白色視為透明
                                        //    UINT width, height;
                                        //    pWICBitmap->GetSize(&width, &height);
                                        //    //UINT32 pixelCount = width * height;  //錯誤範例 * sizeof(UINT32)才為正確記憶體儲存空間
                                        //    UINT32* pixelCount = (UINT32*)malloc(width * height * sizeof(UINT32));

                                        //    pWICBitmap->CopyPixels(NULL, width * sizeof(UINT32), width * height * sizeof(UINT32), reinterpret_cast<BYTE*>(pixelCount));

                                        //    for (int y = 0; y < height; ++y)
                                        //    {
                                        //        for (int x = 0; x < width; ++x)
                                        //        {
                                        //            UINT32* pixelsize = pixelCount + y * width + x;
                                        //            BYTE* pixel = reinterpret_cast<BYTE*>(pixelsize);

                                        //            //wchar_t buffer[20];
                                        //            //swprintf_s(buffer, L"R=%d,G=%d B=%d\n", pixel[0], pixel[1] , pixel[2]);
                                        //            //OutputDebugString(buffer);

                                        //            if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255)
                                        //            {
                                        //                // 白色視為透明
                                        //                pixel[3] = 0;
                                        //                //OutputDebugString(L"將像素透明\n");
                                        //            }
                                        //        }
                                        //    }
                                        //    pWICFactory->CreateBitmapFromMemory(width, height, format, width * 4, width * height * 4, reinterpret_cast<BYTE*>(pixelCount), &pWICBitmap);
                                        //    //OutputDebugString(L"開始編碼\n");

                                        //}
                                        // 將位圖源編碼到編碼幀
                                        if (SUCCEEDED(pFrame->WriteSource(pWICBitmap, nullptr)))
                                        {
                                            // 完成編碼
                                            //OutputDebugString(filePath);

                                            pFrame->Commit();
                                            pEncoder->Commit();
                                            //OutputDebugString(L"完成編碼\n");

                                        }

                                        // 釋放 WIC 資源
                                        pWICBitmap->Release();

                                    }

                                    // 釋放 GDI 資源
                                    DeleteObject(hBitmap);
                                    DeleteDC(hMemDC);
                                }
                                pFrame->Release();
                            }
                        }
                        pStream->Release();
                    }
                    pEncoder->Release();
                }
                pWICFactory->Release();
            }
        }

        // 釋放 WIC 相關資源
        CoUninitialize();
    }

    //只選擇資料夾
    static void OpenFolder(HWND hWnd, std::wstring& folderPath)
    {
        // 初始化 COM
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

        IFileOpenDialog* pFileOpen;

        // 創建 FileOpenDialog 對象
        if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen))))
        {
            // 設置選項，允許選擇資料夾
            DWORD dwOptions;
            if (SUCCEEDED(pFileOpen->GetOptions(&dwOptions)))
            {
                pFileOpen->SetOptions(dwOptions | FOS_PICKFOLDERS);
            }

            // 顯示對話框
            if (SUCCEEDED(pFileOpen->Show(hWnd)))
            {
                // 獲取選擇的項目
                IShellItem* pItem;
                if (SUCCEEDED(pFileOpen->GetResult(&pItem)))
                {
                    // 獲取項目的顯示名稱
                    LPWSTR pszFolderPath;
                    if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFolderPath)))
                    {
                        folderPath = pszFolderPath;
                        CoTaskMemFree(pszFolderPath);
                    }

                    pItem->Release();
                }
            }

            pFileOpen->Release();
        }

        // 釋放 COM
        CoUninitialize();
    }
    //選擇資料夾及檔案名稱
    static void FileSaveDialog(std::wstring& filename)
    {
        IFileSaveDialog* pFileSaveDlg = NULL;

        // 初始化 COM
        CoInitialize(NULL);

        // 創建 File Save Dialog
        HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileSaveDlg));

        if (SUCCEEDED(hr))
        {
            // 設置 File Save Dialog 的屬性
            COMDLG_FILTERSPEC fileTypes[] = { { L"PNG Files", L"*.png" } };
            pFileSaveDlg->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);

            // 顯示 File Save Dialog
            hr = pFileSaveDlg->Show(NULL);

            if (SUCCEEDED(hr))
            {
                // 獲取選擇的文件名
                IShellItem* pItem;
                hr = pFileSaveDlg->GetResult(&pItem);

                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    if (SUCCEEDED(hr))
                    {
                        filename = pszFilePath;
                        CoTaskMemFree(pszFilePath);
                        if (filename.find(L".png") == std::wstring::npos)
                        {
                            filename += L".png";
                        }
                    }

                    pItem->Release();
                }
            }

            pFileSaveDlg->Release();
        }

        // 釋放 COM
        CoUninitialize();
    }

    static std::wstring string2wstring(std::string str)
    {
        std::wstring result;

        //製作緩衝區
        int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
        TCHAR* buffer = new TCHAR[len + 1];

        //多字節編碼轉換寬字節編碼
        MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
        //添加字符串结尾  
        buffer[len] = '\0';

        result.append(buffer);
        //删除緩衝區  
        delete[] buffer;
        return result;

        //另一個方法
        //#include <comutil.h>  
        //#pragma comment(lib, "comsuppw.lib")


        //_bstr_t t = str.c_str();
        //wchar_t* pwchar = (wchar_t*)t;
        //result = pwchar;
        //return result;

    }

    //void 截圖(); //另一種截圖方式但未使用
    //{
    //HWND hwnd = hwndDig;
    //HDC hDC = GetDC(hwnd);//獲取屏幕DC

    //HDC hDCMem = CreateCompatibleDC(hDC);//創建兼容DC 

    ////HBITMAP hBitMap = CreateCompatibleBitmap(hDC, fixed_px, fixed_px);//創建兼容位圖
    ////HBITMAP hBitMap = CreateBitmap(fixed_px, fixed_px, 1, 32, NULL);
    //HBITMAP hBitMap = Common::CreateDIBSectionBitmap(fixed_px, fixed_px);
    //HBITMAP hOldMap = (HBITMAP)::SelectObject(hDCMem, hBitMap);//選入位圖到兼容DC。并保存返回值  


    //TransparentBlt(hDCMem, 0, 0, fixed_px, fixed_px,
    //    hDC, Tree_Point.x, Tree_Point.y, fixed_px, fixed_px, RGB(255, 255, 255)); // 將白色視為透明色 
    ////BitBlt(hDCMem, 0, 0, fixed_px, fixed_px, 
    ////        hDC, Tree_Point.x, Tree_Point.y, SRCCOPY);//將指定區域的屏幕DC圖象拷貝到兼容DC中
    ////SetBkColor(hDCMem, RGB(255, 255, 255));  // 將白色視為透明色

    //CImage image;
    //image.Attach(hBitMap);
    //image.Save(_T("./MyCapture.png"));//假设文件后缀为.bmp，则保存为为bmp格式  
    //image.Detach(); 

    //SelectObject(hDCMem, hOldMap);//釋放選入的位圖

    ////释放  
    //DeleteObject(hBitMap);
    //DeleteDC(hDCMem);
    //DeleteDC(hDC);
    //}

    // 用以判斷字串有無中文
    bool containsChinese(const std::string& str) {
        // 定義中文字符範圍（Unicode 範圍）
        std::regex chineseRegex("[\\u4e00-\\u9fa5]+");

        // 使用正則表達式進行匹配
        return std::regex_search(str, chineseRegex);
    }
};