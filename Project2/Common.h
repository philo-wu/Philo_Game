#pragma once
#include <wincodec.h>
#include "Direct2D.h"
// 從framework.h拿出來
#include <atlimage.h>  
#include <shobjidl.h>
#include <filesystem>

// 視窗相關
#define SCREEN_WIDTH  720  
#define SCREEN_HEIGHT 980
#define BUTTON_INTERVAL 30
#define BUTTON_WIDTH  200
#define BUTTON_HEIGHT 50

// 遊戲視窗相關
#define GRID_NUMBER     0
#define FUNCTION_BET_NUMBER      1 
#define FUNCTION_NUMBER 2

#define GRID_X      (SCREEN_WIDTH/3 - 125) //遊戲區域左上角位置
#define GRID_Y      150
#define GRID_WIDTH  (SCREEN_WIDTH / 3 + 250) / 7
#define GRID_HEIGHT 490 / 7

#define BET_X       SCREEN_WIDTH / 3 - 176
#define BET_Y       GRID_Y + GRID_HEIGHT*7 +10
#define BET_WIDTH  (SCREEN_WIDTH / 3 + 352) / 8
#define BET_HEIGHT  200
#define BET_RATIO   0.515



#define FUNCTION_X      BET_X
#define FUNCTION_Y      BET_Y + BET_HEIGHT
#define FUNCTION_WIDTH  BET_WIDTH
#define FUNCTION_HEIGHT 125




// 遊戲相關
#define LIGHT_SIZE 6 //燈號大小 
#define CELL_SIZE 20
#define GAME_SIZE 7 //遊戲區域分成7*7 但只用邊界格
#define GAME_TOTAL GAME_SIZE*4-4 // 遊戲區域格子數

#define BET_SIZE  8 //下注區域分成8*1
#define BET_TOTAL  8 //下注區域格子數

#define STATE_IDLE              0
#define STATE_BET_BEFORE        1 //無法操作
#define STATE_BET_GAMING        2 //無法操作
#define STATE_BET_SETTLING      3 
#define STATE_COMPARE_BEFORE    4 //無法操作
#define STATE_COMPARE_GAMING    5 //無法操作
#define STATE_COMPARE_SETTLING  6


// 事件或指令相關
#define ID_CUSTOM_COMMAND 1001
#define WM_CUSTOM_GAMEEND WM_USER + 1
#define WM_CUSTOM_GAMEWIN WM_USER + 2

// CELL依據代表分數降序排列

#define BAR_NUMBER              0
#define SEVEN_NUMBER            BAR_NUMBER + 1
#define STAR_NUMBER             BAR_NUMBER + 2
#define WATERMELOM_NUMBER       BAR_NUMBER + 3
#define BELL_NUMBER             BAR_NUMBER + 4
#define LEMON_NUMBER            BAR_NUMBER + 5
#define ORANGE_NUMBER           BAR_NUMBER + 6
#define APPLE_NUMBER            BAR_NUMBER + 7

#define RED_ONCEMORE_NUMBER     BAR_NUMBER + 100
#define BLUE_ONCEMORE_NUMBER    BAR_NUMBER + 101

#define SMALL_NUMBER     0
#define BIG_NUMBER       1


#define CELL_TOTAL              APPLE_NUMBER+1 //紀錄總共有幾個CELL

#define IDLETIME 5000 //閒置多久進入idle,單位為ms
#define AUTOTIME 2000 //間隔多久自動下一輪,單位為ms
class BitmapManager;
class ScoreManager;
class EngineStateManager;

class Common
{
public:
    // 依據uri路徑讀取檔案並轉換成圖片
    std::filesystem::path currentPath = std::filesystem::current_path(); // C++ 17
    BitmapManager* BM;
    ScoreManager* SM;
    EngineStateManager* ESM;
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
            std::wstring path = uri;
            path += L"\n圖檔不存在\n";
            std::wstring path1 =  L"圖檔不存在" ;
            wprintf(L"%s", path1.c_str());
            OutputDebugString(path1.c_str());

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
        ID2D1Bitmap** ppBitmap,
        std::wstring& ploadPath,
        std::wstring& filename)
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
        ofn.lpstrFilter = L"All Files\0*.*\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
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
        POINT point,
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

};


class BitmapManager {
public:
    BitmapManager(Common* pcommon,
    ID2D1Factory* p_pDirect2dFactory,
    ID2D1HwndRenderTarget* p_pRenderTarget,
    IDWriteFactory* p_pDWriteFactory,
    IDWriteTextFormat* p_pTextFormat,
    ID2D1SolidColorBrush* p_pWhiteBrush
    ) {
        common = pcommon;
        m_pDirect2dFactory = p_pDirect2dFactory;
        m_pRenderTarget = p_pRenderTarget;
        m_pDWriteFactory = p_pDWriteFactory;
        m_pTextFormat = p_pTextFormat;
        m_pWhiteBrush = p_pWhiteBrush;
    }


    Common* common;

    ID2D1Factory* m_pDirect2dFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    IDWriteFactory* m_pDWriteFactory;
    IDWriteTextFormat* m_pTextFormat;
    ID2D1SolidColorBrush* m_pWhiteBrush;

    ID2D1Bitmap* AppleBitmap;
    ID2D1Bitmap* BarBitmap;
    ID2D1Bitmap* BellBitmap;
    ID2D1Bitmap* LemonBitmap;
    ID2D1Bitmap* OrangeBitmap;
    ID2D1Bitmap* SevenBitmap;
    ID2D1Bitmap* StarBitmap;
    ID2D1Bitmap* WatermelonBitmap;

    ID2D1Bitmap* BackgroundBitmap;
    ID2D1Bitmap* Mid_BackgroundBitmap;

    void init(HWND m_hwnd) {

        IWICImagingFactory* pIWICFactory = NULL;
        CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
        int errorcode = 0;

        // 將讀取所有圖檔
        std::wstring path = common->currentPath.wstring() + L"\\Images\\Apple.png";
        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &AppleBitmap, m_hwnd, errorcode);
        if (errorcode != 0) { //TODO::error處理
            ;
        }
        path = common->currentPath.wstring() + L"\\Images\\Bar.png";
        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &BarBitmap, m_hwnd, errorcode);
        if (errorcode != 0) {
            ;
        }
        path = common->currentPath.wstring() + L"\\Images\\Bell.png";
        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &BellBitmap, m_hwnd, errorcode);
        if (errorcode != 0) {
            ;
        }
        path = common->currentPath.wstring() + L"\\Images\\Lemon.png";
        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &LemonBitmap, m_hwnd, errorcode);
        if (errorcode != 0) {
            ;
        }
        path = common->currentPath.wstring() + L"\\Images\\Orange.png";
        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &OrangeBitmap, m_hwnd, errorcode);
        if (errorcode != 0) {
            ;
        }
        path = common->currentPath.wstring() + L"\\Images\\Seven.png";
        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &SevenBitmap, m_hwnd, errorcode);
        if (errorcode != 0) {
            ;
        }
        path = common->currentPath.wstring() + L"\\Images\\Star.png";
        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &StarBitmap, m_hwnd, errorcode);
        if (errorcode != 0) {
            ;
        }
        path = common->currentPath.wstring() + L"\\Images\\Watermelon.png";
        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &WatermelonBitmap, m_hwnd, errorcode);
        if (errorcode != 0) {
            ;
        }
        path = common->currentPath.wstring() + L"\\Images\\Background.png";
        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &BackgroundBitmap, m_hwnd, errorcode);
        if (errorcode != 0) {
            ;
        }
        path = common->currentPath.wstring() + L"\\Images\\Mid_Background.png";
        Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, path, 0, 0, &Mid_BackgroundBitmap, m_hwnd, errorcode);
        if (errorcode != 0) {
            ;
        }
        pIWICFactory->Release();
    }


};

class ScoreManager
{
public:
    ScoreManager() {
        WinScore = 0;
        Score = 15000;
    }
    void AddWinScore(int cost) {
        WinScore += cost;
        return;
    }
    bool CostWinScore(int cost) {
        WinScore -= cost;
        if (Score >= 0)
            return true;
        else
            WinScore += cost;
        return false;
    }
    // 結算WinScore 到Score
    void WinToScore() {
        Score += WinScore;
        WinScore = 0;
    }
    bool CostScore(int cost) {
        Score -= cost;
        if (Score >= 0)
            return true;
        else
            Score += cost;
        return false;
    }
    void AddScore(int score) { Score += score; }
    int GetWinScore() { return WinScore; }
    int GetScore() { return Score; }

private:
    int WinScore;
    int Score;

public:
    int Get_CellScore(int number) {
        switch (number)
        {
        case APPLE_NUMBER: {
            return 5;
        }
                         break;
        case BAR_NUMBER: {
            return 100;
        }
                       break;
        case BELL_NUMBER: {
            return 20;
        }
                        break;
        case LEMON_NUMBER: {
            return 15;
        }
                         break;
        case ORANGE_NUMBER: {
            return 10;
        }
                          break;
        case SEVEN_NUMBER: {
            return 40;
        }
                         break;
        case STAR_NUMBER: {
            return 30;
        }
                        break;
        case WATERMELOM_NUMBER: {
            return 20;
        }
                              break;

        default:
            break;
        }
    }
};

class EngineStateManager
{
public:
    int state = 0;
    bool playing = 0; //位於遊戲畫面中
    bool bet_starting = 0; //按下開始遊戲
    bool bet_started = 0; //有開始過遊戲 //
    bool bet_settling = 0; //等待結算

    bool compare_starting = 0; //按下大小
    bool compare_SmallOrBig = 0; // 0=小 1=大
    bool compare_settling = 0; //等待結算


    bool idleing = 0; //閒置中
    bool autoing = 0; //自動執行
    int position = 0; //起點位置
    int endPosition = 0; //終點位置
    int endCompare = 0;
    int Comparenumber = 0; //比大小的結果數字

    long long currentTime;
    long long endTime;

    void SetBigOrSmall(bool number) {
        if (number == 0)
            compare_SmallOrBig = 0;
        else if (number == 1)
            compare_SmallOrBig = 1;
    }
};