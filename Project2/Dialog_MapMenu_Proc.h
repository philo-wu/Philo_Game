#pragma once
#include "Dialog_LoadTree_Proc.h"

ID2D1HwndRenderTarget* MapMenu_RenderTarget;


INT_PTR CALLBACK Dialog_MapMenu_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD dwID = wParam;
    switch (uMsg) {
    case WM_INITDIALOG:
    {
        Common::InitD2D(hwndDlg, pD2DFactory, &MapMenu_RenderTarget);

        std::string path = currentPath.string() + "/Images/Map_saveData.json";
        std::ifstream inFile(path);
        if (!inFile.is_open()) {
            //std::cerr << "無法打開 JSON 文件" << std::endl;
            //OutputDebugString(L"JSON開啟成功\n");
            MessageBox(hWnd, L"JSON存檔讀取失敗", L"錯誤", MB_OK);

            return 1;
        }
        //else
            //OutputDebugString(L"JSON開啟成功\n");
        json Data;
        inFile >> Data;
        inFile.close();
        Map_saveData = Data;
        std::vector<std::string> items;

        for (auto it = Data.begin(); it != Data.end(); ++it)
        {
            items.push_back(it.key());
        }
        //OutputDebugString(L"items完成\n");

        CComboBox pComboBox;
        pComboBox.Attach(GetDlgItem(hwndDlg, IDC_COMBO1));
        CFont font;
        font.CreatePointFont(120, _T("Verdana"));  // 120 是字體大小，"Verdana" 是字體名稱
        pComboBox.SetFont(&font);

        for (const auto& item : items) {
            //將string轉換到wstring //Cstring對中文支援不好
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring wideSaveName = converter.from_bytes(item);
            pComboBox.AddString(wideSaveName.c_str());
            //OutputDebugString(wideSaveName.c_str());
            //OutputDebugString(L"\n");

        }

        pComboBox.Detach();
        //OutputDebugString(L"JSON讀取成功\n");


    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            // 使用者按下了確定按鈕
        {

        }
        break;

        case IDCANCEL:
        {
            // 使用者按下了取消按鈕
            EndDialog(hwndDlg, IDCANCEL);
        }
        break;
        case ID_DATASAVE: // 儲存檔案
        {
            // SAVE
            json save_map;
            json tree;
            // 創建一個 JSON array，用於存放 coordinates
            json coordinatesArray;
            // 將 fruit_Points 中的每個 POINT 轉換為 JSON object 並添加到 array 中
            for (const POINT& point : Map_treepoints)
            {
                json pointObject =
                {
                    {"X", point.x},
                    {"Y", point.y}
                };

                coordinatesArray.push_back(pointObject);
            }

            // 將 coordinatesArray 存入 JSON 中的 "coordinates"
            tree["coordinates"] = coordinatesArray;

            save_map[TreeName] = tree;
            int result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INPUT), NULL, Dialog_Input_Proc);
            if (result == -1)
            {
                // 對話框創建失敗
                MessageBox(NULL, L"對話框創建失敗", L"錯誤", MB_OK | MB_ICONERROR);
            }
            else
            {
                if (result == IDCANCEL)
                {
                    break;
                }
            }
            //std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            //std::wstring wideName = converter.from_bytes(Save_Name);
            //OutputDebugString(L"讀取保存名稱\n");
            //std::wstring wideSaveName(Save_Name.begin(), Save_Name.end());
            //OutputDebugString(wideSaveName.c_str());

            // 將 JSON 對象轉換為字串
            Map_saveData[Save_Name] = save_map;
            std::string jsonString = Map_saveData.dump(4);

            // 將 JSON 字串保存到文件
            std::string path = currentPath.string() + "/Images/Map_saveData.json";
            std::ofstream outFile(path);
            if (outFile.is_open())
            {
                outFile << jsonString;
                outFile.close();
                OutputDebugString(L"JSON 已保存到 Map_saveData.json\n");

                CComboBox pComboBox;
                pComboBox.Attach(GetDlgItem(hwndDlg, IDC_COMBO1));

                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                std::wstring wideSaveName = converter.from_bytes(Save_Name);
                //判斷是否有存在同名選項
                int index = pComboBox.FindString(-1, wideSaveName.c_str());
                if (index == CB_ERR) {
                    // 相同的選項不存在，可以新增
                    pComboBox.AddString(wideSaveName.c_str());
                }
                pComboBox.Detach();

            }
            else
            {
                MessageBox(hwndDlg, L"無法打開文件保存JSON", L"錯誤", MB_OK);
            }



        }
        break;
        case ID_DATADELETE:  //刪除存檔
        {
            OutputDebugString(L"刪除存檔\n");

            CComboBox pComboBox;
            pComboBox.Attach(GetDlgItem(hwndDlg, IDC_COMBO1));

            int selectedIndex = pComboBox.GetCurSel();

            if (selectedIndex != CB_ERR)
            {
                // 有項目被選中

                CString selectedText;
                pComboBox.GetLBText(selectedIndex, selectedText);
                OutputDebugString(selectedText);
                OutputDebugString(L"\n");
                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                std::wstring wideselectedText(selectedText);
                std::string stdStr = converter.to_bytes(wideselectedText);

                //OutputDebugString(selectedText);
                // 
                //刪除存檔
                Map_saveData.erase(stdStr);
                pComboBox.DeleteString(selectedIndex);
                if (pComboBox.GetCount() == 0)
                    pComboBox.SetCurSel(-1);
                else
                    pComboBox.SetCurSel(0);


                std::string jsonString = Map_saveData.dump(4);
                // 將 JSON 字串保存到文件
                std::string path = currentPath.string() + "/Images/Map_saveData.json";
                std::ofstream outFile(path);
                if (outFile.is_open())
                {
                    outFile << jsonString;
                    outFile.close();
                    OutputDebugString(L"JSON 已保存到 Map_saveData.json\n");
                }
            }
            else
            {
                // 沒有項目被選中
                //OutputDebugString(L"沒有項目被選中\n");
                MessageBox(hwndDlg, L"沒有項目被選中", L"錯誤", MB_OK);
            }
            pComboBox.Detach();
            InvalidateRect(hWnd, NULL, TRUE);

        }
        break;
        case ID_DATALOAD: //載入存檔
        {
            OutputDebugString(L"載入存檔\n");

            CComboBox pComboBox;
            pComboBox.Attach(GetDlgItem(hwndDlg, IDC_COMBO1));

            int selectedIndex = pComboBox.GetCurSel();

            if (selectedIndex != CB_ERR)
            {
                // 有項目被選中

                CString selectedText;
                pComboBox.GetLBText(selectedIndex, selectedText);
                OutputDebugString(selectedText);
                OutputDebugString(L"\n");


                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                std::wstring wideselectedText(selectedText);
                std::string stdStr = converter.to_bytes(wideselectedText);

                //OutputDebugString(selectedText);
                // 
                //讀取存檔
                MapName = stdStr;
                Map_saveData_using = Map_saveData[MapName];

            }
            else
            {
                // 沒有項目被選中
                //OutputDebugString(L"沒有項目被選中\n");
                MessageBox(hwndDlg, L"沒有項目被選中", L"錯誤", MB_OK);
            }
            pComboBox.Detach();
            InvalidateRect(hWnd, NULL, TRUE);

        }
        break;
        case ID_RETURN: //刪除最後繪圖資料
        {
            if (!Map_treepoints.empty())
                Map_treepoints.pop_back();
            else
                MessageBox(hwndDlg, L"此元件已經無物件可刪除", L"錯誤", MB_OK);
            Map_clickPoint = { 0 };
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwndDlg, &ps);

        MapMenu_RenderTarget->BeginDraw();
        MapMenu_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        //不重複清除是因為要保留繪製結果 //使用陣列儲存座標後 改回每次清除
        MapMenu_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF(0.8f, 0.8f, 0.8f, 0.8f))); // dialog 背景色
        MapMenu_RenderTarget->EndDraw();

        EndPaint(hwndDlg, &ps);
    }
    break;
    case WM_DESTROY:
    {

    }
    break;
    case WM_ERASEBKGND:
        break;
    }

    return FALSE;
}
