#pragma once
#include "Dialog_LoadTree_Proc.h"

ID2D1HwndRenderTarget* MapMenu_RenderTarget;
std::string AnsiToUtf8(const std::string& ansiStr)
{
    int wstrLen = MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, nullptr, 0);
    if (wstrLen == 0) {
        // Handle error
        return std::string();
    }

    std::wstring wstr(wstrLen, L'\0');
    MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, &wstr[0], wstrLen);

    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8Len == 0) {
        // Handle error
        return std::string();
    }

    std::string utf8Str(utf8Len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &utf8Str[0], utf8Len, nullptr, nullptr);

    return utf8Str;
}

INT_PTR CALLBACK Dialog_MapMenu_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD dwID = wParam;
    switch (uMsg) {
    case WM_INITDIALOG:
    {
        Common::InitD2D(hwndDlg, pD2DFactory, &MapMenu_RenderTarget);
        if (Tree_saveData.empty()) {
            std::string path = currentPath.string() + "/Images/Tree_saveData.json";
            std::ifstream inFile(path);
            if (!inFile.is_open()) {
                //std::cerr << "無法打開 JSON 文件" << std::endl;
                //OutputDebugString(L"JSON開啟成功\n");
                MessageBox(hWnd, L"存檔讀取失敗", L"錯誤", MB_OK);

                return 1;
            }
            //else
                //OutputDebugString(L"JSON開啟成功\n");
            json Data;
            inFile >> Data;
            inFile.close();
            Tree_saveData = Data;
        }

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
        case ID_DATASAVE: // 另存新檔
        {

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

            // 將 JSON 對象轉換為字串
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
            Map_treepoints.clear();
            // 將 coordinatesArray 存入 JSON 中的 "coordinates"
            tree["coordinates"] = coordinatesArray;
            // 將未儲存元件使用中地圖
            Map_saveData_using[using_Dialog_TreeName] = tree;
            // 將使用中地圖寫入存檔
            Map_saveData[Save_Name] = Map_saveData_using;
            using_MapName = Save_Name;
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
        case ID_DATASAVE_QUICK: // 快速存檔
        {
            if (using_MapName.empty()) {
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
                using_MapName = Save_Name;
            }
            // 將 JSON 對象轉換為字串
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
            Map_treepoints.clear();

            // 將 coordinatesArray 存入 JSON 中的 "coordinates"
            tree["coordinates"] = coordinatesArray;
            // 將未儲存元件使用中地圖
            Map_saveData_using[using_Dialog_TreeName] = tree;
            // 將使用中地圖寫入存檔
            Map_saveData[using_MapName] = Map_saveData_using;
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
                std::wstring wideSaveName = converter.from_bytes(using_MapName);
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
                using_MapName = stdStr;
                Map_saveData_using = Map_saveData[using_MapName];

                //清理陣列
                Map_treepoints.clear();
                auto it = Map_saveData_using.find(using_Main_TreeName);
                // 將地圖中符合元件拿出寫入正在繪製中
                if (it != Map_saveData_using.end()) { 
                    for (const auto& coordinate : Map_saveData_using[using_Main_TreeName]["coordinates"]) {
                        POINT tree_Point;
                        tree_Point.x = coordinate["X"];
                        tree_Point.y = coordinate["Y"];
                        Map_treepoints.push_back(tree_Point);
                    }
                    Map_saveData_using.erase(using_Main_TreeName);
                }
                OutputDebugString(L"檢查樹木\n");
                if (Tree_saveData.empty()) {
                    ;
                }
                else {
                    //for (const auto& tree : Map_saveData_using.items()) {// 檢查所有種類的樹
                    //    std::string key = tree.key();
                    //    auto it = Tree_saveData.find(key);
                    //    if (it == Tree_saveData.end()) {
                    //        std::wstring str = converter.from_bytes(key);
                    //        std::wstring str1 = L"無法在元件存檔找到" + str;
                    //        MessageBox(hwndDlg, str1.c_str(), L"錯誤", MB_OK);
                    //        Map_saveData_using.erase(key);
                    //    }
                    //} 
                    // 上面 erase以後 會超出容範圍
                    for (auto it = Map_saveData_using.begin(); it != Map_saveData_using.end();) {
                        std::string key = it.key();
                        auto treeIt = Tree_saveData.find(key);
                        if (treeIt == Tree_saveData.end()) {
                            std::wstring str = converter.from_bytes(key);
                            std::wstring str1 = L"無法在元件存檔找到" + str;
                            MessageBox(hwndDlg, str1.c_str(), L"錯誤", MB_OK);
                            it = Map_saveData_using.erase(it); // 更新迭代器
                        }
                        else {
                            ++it; // 移到下一個元素
                        }
                    }
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
        case ID_RETURN: //刪除最後繪圖資料
        {
            if (!Map_treepoints.empty())
                Map_treepoints.pop_back();
            else if (using_Main_TreeName.empty())
                MessageBox(hwndDlg, L"未選擇元件", L"錯誤", MB_OK);
            else
                MessageBox(hwndDlg, L"此元件已經無物件可刪除", L"錯誤", MB_OK);
            Map_clickPoint = { 0 };
            InvalidateRect(hWnd, NULL, FALSE);
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

