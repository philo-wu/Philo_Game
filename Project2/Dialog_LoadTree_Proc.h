#pragma once

#include "framework.h"
#include "Common.h"
#include "Direct2D.h"
#include "mian.h"
#include "resource.h"

// Dialog相關
POINT clickPoint = { 0 }; //主視窗點擊座標
POINT treePoint = { 0 }; //Dialog樹木生成座標
POINT treeclickPoint = { 0 }; //Dialog點擊座標
//判斷是否重繪
bool Diglog_doClear = 1; 
bool Diglog_do_TreeClear = 1;
//圖檔繪製大小 樹木圖檔為正方形,長寬為fixed_px, 
int fixed_px = 200;
//圖檔繪製大小 水果圖檔為正方形,長寬為fixed_px_fruit, 
int fixed_px_fruit = 30;

INT_PTR CALLBACK Dialog_LoadTree_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD dwID = wParam;

    treePoint.x = 130;
    treePoint.y = 10;


    switch (uMsg) {
    case WM_INITDIALOG:
    {
        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
        if (SUCCEEDED(hr))
        {
            RECT rc;
            GetClientRect(hwndDlg, &rc);
            // 創建 D2D 渲染目標
            hr = pD2DFactory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(hwndDlg, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
                &Tree_RenderTarget
            );
        }
        if (dialog_isfruit) {
            // 顯示水果圖片按鈕
            ShowWindow(GetDlgItem(hwndDlg, ID_LOADFRUIT), SW_SHOW);
        }
        else {
            // 隱藏水果圖片按鈕
            ShowWindow(GetDlgItem(hwndDlg, ID_LOADFRUIT), SW_HIDE);
        }
    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            // 使用者按下了確定按鈕
        {
            HWND hwnd = hwndDlg;
            HDC hDC = GetDC(hwnd);//獲取屏幕DC

            RECT rect;
            //GetClientRect(hwnd, &rect);//获取屏幕大小  
            rect.left = treePoint.x;
            rect.top = treePoint.y;
            rect.right = treePoint.x + fixed_px;
            rect.bottom = treePoint.y + fixed_px;
            HDC hDCMem = CreateCompatibleDC(hDC);//創建兼容DC 

            //HBITMAP hBitMap = CreateCompatibleBitmap(hDC, fixed_px, fixed_px);//創建兼容位圖
            //HBITMAP hBitMap = CreateBitmap(fixed_px, fixed_px, 1, 32, NULL);
            HBITMAP hBitMap = Common::CreateDIBSectionBitmap(fixed_px, fixed_px);
            HBITMAP hOldMap = (HBITMAP)::SelectObject(hDCMem, hBitMap);//選入位圖到兼容DC。并保存返回值  

            SetBkColor(hDCMem, RGB(255, 255, 255));  // 將白色視為透明色

            BitBlt(hDCMem, 0, 0, fixed_px, fixed_px, hDC, treePoint.x, treePoint.y, SRCCOPY);//將指定區域的屏幕DC圖象拷貝到兼容DC中

            CImage image;
            image.Attach(hBitMap);
            image.Save(_T("./B.png"));//假设文件后缀为.bmp，则保存为为bmp格式  
            image.Detach();

            SelectObject(hDCMem, hOldMap);//釋放選入的位圖

            //释放  
            DeleteObject(hBitMap);
            DeleteDC(hDCMem);
            DeleteDC(hDC);
            Diglog_doClear = 1;
            Diglog_do_TreeClear = 1;
            treeclickPoint = { 0 };
            EndDialog(hwndDlg, IDOK);
        }
        break;

        case IDCANCEL:
            // 使用者按下了取消按鈕
            Diglog_doClear = 1;
            Diglog_do_TreeClear = 1;
            EndDialog(hwndDlg, IDCANCEL);
            break;
        case ID_LOADTREE: // 選擇樹木
        {
            Common::OpenFile(hwndDlg, Tree_RenderTarget, &Tree_Bitmap);
            Diglog_doClear = 1;
            Diglog_do_TreeClear = 1;
            treeclickPoint = { 0 };
            InvalidateRect(hwndDlg, NULL, TRUE);

        }
        break;

        case ID_LOADFRUIT: // 選擇水果
        {
            Common::OpenFile(hwndDlg, Tree_RenderTarget, &Fruit_Bitmap);
            Diglog_doClear = 1;
            Diglog_do_TreeClear = 1;
            treeclickPoint = { 0 };
            InvalidateRect(hwndDlg, NULL, TRUE);
        }
        break;
        }
        break;
    case WM_LBUTTONDOWN:
        // 處理滑鼠左鍵
    {
        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);
        if (xPos >= treePoint.x && yPos >= treePoint.y && xPos <= treePoint.x + fixed_px && yPos <= treePoint.y + fixed_px)
        {
            treeclickPoint.x = static_cast<FLOAT>(xPos);
            treeclickPoint.y = static_cast<FLOAT>(yPos);
            InvalidateRect(hwndDlg, NULL, TRUE);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwndDlg, &ps);

        Tree_RenderTarget->BeginDraw();
        Tree_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        //不重複清除是因為要保留繪製結果
        if (Diglog_doClear)
        {
            Tree_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
            Diglog_doClear = 0;
        }

        //有讀取樹木圖片
        if (Tree_Bitmap && Diglog_do_TreeClear)
        {
            D2D1_SIZE_U size = Tree_Bitmap->GetPixelSize();
            UINT width = size.width;
            UINT height = size.height;
            Tree_RenderTarget->DrawBitmap(Tree_Bitmap, D2D1::RectF(treePoint.x, treePoint.y, treePoint.x + fixed_px, treePoint.y + fixed_px));
            Diglog_do_TreeClear = 0;
        }
        //有讀取水果圖片並點擊在樹上
        if (Fruit_Bitmap && treeclickPoint.x != 0 && treeclickPoint.y != 0)
        {
            D2D1_SIZE_U size = Fruit_Bitmap->GetPixelSize();
            UINT width = size.width;
            UINT height = size.height;
            Tree_RenderTarget->DrawBitmap(Fruit_Bitmap, D2D1::RectF(treeclickPoint.x, treeclickPoint.y, treeclickPoint.x + fixed_px_fruit, treeclickPoint.y + fixed_px_fruit));
        }
        //if (Tree_Bitmap)
        //    Tree_RenderTarget->DrawBitmap(Fruit_Bitmap, D2D1::RectF(treeclickPoint.x, treeclickPoint.y, treeclickPoint.x + width, treeclickPoint.y + height));

        Tree_RenderTarget->EndDraw();

        EndPaint(hwndDlg, &ps);
    }
    break;

    }
    return FALSE;
}