#pragma once
#include "Dialog_LoadTree_Proc.h"

ID2D1HwndRenderTarget* MapMenu_RenderTarget;
bool Dialog_MapMenu_is_open = false;
bool Dialog_MapMenu_is_Create = 1;//控制創造或刪除模式 

INT_PTR CALLBACK Dialog_MapMenu_Proc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD dwID = wParam;
    switch (uMsg) {
    case WM_INITDIALOG:
    {
        OutputDebugString(L"地圖選單開啟\n");
        MapMenu_hWnd = hwndDig;
        Dialog_MapMenu_is_open = 1;

        if (Dialog_MapMenu_is_Create) {
            CheckDlgButton(hwndDig, IDC_CHECK1, BST_CHECKED);   // 勾選 IDC_CHECK1
            CheckDlgButton(hwndDig, IDC_CHECK2, BST_UNCHECKED); // 取消 IDC_CHECK2 勾選
        }
        else {
            CheckDlgButton(hwndDig, IDC_CHECK1, BST_UNCHECKED); // 取消 IDC_CHECK1
            CheckDlgButton(hwndDig, IDC_CHECK2, BST_CHECKED);   // 勾選 IDC_CHECK2
        }
        ShowWindow(GetDlgItem(hwndDig, ID_RETURN), SW_HIDE);
        EnableWindow(GetDlgItem(hWnd, 3), FALSE);

        if (Dialog_Input_is_open) {
            EnableWindow(GetDlgItem(hwndDig, ID_DATASAVE), FALSE);
            EnableWindow(GetDlgItem(hwndDig, ID_DATASAVE_QUICK), FALSE);
        }   

        Common::InitD2D(hwndDig, pD2DFactory, &MapMenu_RenderTarget);
        if (Tree_saveData.empty()) {
            std::string path = currentPath.parent_path().string() + "/種樹/Images/Tree_saveData.json";
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
        std::string path = currentPath.parent_path().string() + "/種樹/Images/Map_saveData.json";

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
        pComboBox.Attach(GetDlgItem(hwndDig, IDC_COMBO1));
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

        if (LOWORD(wParam) == IDC_CHECK1 && HIWORD(wParam) == BN_CLICKED) {
            // IDC_CHECK1 被點擊
            CheckDlgButton(hwndDig, IDC_CHECK2, BST_UNCHECKED); // 取消 IDC_CHECK2 的勾選
            Dialog_MapMenu_is_Create = 1;
        }
        else if (LOWORD(wParam) == IDC_CHECK2 && HIWORD(wParam) == BN_CLICKED) {
            CheckDlgButton(hwndDig, IDC_CHECK1, BST_UNCHECKED); // 取消 IDC_CHECK1 的勾選
            Dialog_MapMenu_is_Create = 0;
        }
        switch (LOWORD(wParam))
        {
        case IDOK:            // 使用者按下了確定按鈕
        {

        }
        break;

        case IDCANCEL:       // 使用者按下了取消按鈕
        {

            DestroyWindow(hwndDig);

            //EndDialog(hwndDig, IDCANCEL);
        }
        break;
        case ID_DATASAVE: // 另存新檔
        {
            if (Dialog_Input_is_open)
            {
                MessageBox(hwndDig, L"輸入框已開啟", L"錯誤", MB_OK);
                break;
            }
            int result = DialogBoxParam(InPut_hInstance, MAKEINTRESOURCE(IDD_INPUT), hwndDig, Dialog_Input_Proc, 0);
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
            json coordinatesArray = g_FruitTreeManager->PointsToJson();
            g_FruitTreeManager->ClearPoints();
            // 將 coordinatesArray 存入 JSON 中的 "coordinates"
            tree["coordinates"] = coordinatesArray;

            // 將未儲存元件使用中地圖
            Map_saveData_using[using_Dialog_TreeName] = tree;
            // 將使用中地圖寫入存檔
            Map_saveData[Save_Name] = Map_saveData_using;

            Map_Remarks = Save_Remarks;
            Map_saveData_using["remarks"] = Map_Remarks;
            std::wstring widestr;
            std::string stdStr;
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

            if (!Map_saveData_using["remarks"].empty()) {
                stdStr = Map_saveData_using["remarks"];
                widestr = converter.from_bytes(stdStr);
            }
            else {
                widestr = L"";
            }
            HWND hStatic = GetDlgItem(hwndDig, IDC_STATIC1);
            SetWindowText(hStatic, widestr.c_str());

            using_MapName = Save_Name;
            std::string jsonString = Map_saveData.dump(4);

            // 將 JSON 字串保存到文件
            std::string path = currentPath.parent_path().string() + "/種樹/Images/Map_saveData.json";
            //std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            //std::wstring widepath = converter.from_bytes(path);
            //OutputDebugString(widepath.c_str());

            std::ofstream outFile(path);
            if (outFile.is_open())
            {
                outFile << jsonString;
                outFile.close();
                OutputDebugString(L"JSON 已保存到 Map_saveData.json\n");
                ComboBoxAdd(hwndDig, IDC_COMBO1, Save_Name);
            }
            else
            {


                MessageBox(hwndDig, L"無法另存新檔案", L"地圖選單", MB_OK);
            }



        }
        break;
        case ID_DATASAVE_QUICK: // 快速存檔
        {

            if (Dialog_Input_is_open) {
            MessageBox(hwndDig, L"輸入框已開啟", L"錯誤", MB_OK);
            break;
            }
            if (using_MapName.empty()) {
                int result = DialogBoxParam(InPut_hInstance, MAKEINTRESOURCE(IDD_INPUT), hwndDig, Dialog_Input_Proc, 0);
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
                Map_Remarks = Save_Remarks;
            }
            // 將 JSON 對象轉換為字串
            json tree;
            json coordinatesArray = g_FruitTreeManager->PointsToJson();
            //g_FruitTreeManager->ClearPoints();
            tree["coordinates"] = coordinatesArray;
            // 將未儲存元件使用中地圖
            Map_saveData_using[using_Dialog_TreeName] = tree;
            // 將使用中地圖寫入存檔

            Map_saveData_using["remarks"] = Map_Remarks;

            std::wstring widestr;
            std::string stdStr;
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

            if (!Map_saveData_using["remarks"].empty()) {
                stdStr = Map_saveData_using["remarks"];
                widestr = converter.from_bytes(stdStr);
            }
            else {
                widestr = L"";
            }
            HWND hStatic = GetDlgItem(hwndDig, IDC_STATIC1);
            SetWindowText(hStatic, widestr.c_str());

            Map_saveData[using_MapName] = Map_saveData_using;
            std::string jsonString = Map_saveData.dump(4);

            // 將 JSON 字串保存到文件
            std::string path = currentPath.parent_path().string() + "/種樹/Images/Map_saveData.json";
            std::ofstream outFile(path);
            if (outFile.is_open())
            {
                outFile << jsonString;
                outFile.close();
                OutputDebugString(L"JSON 已保存到 Map_saveData.json\n");
                ComboBoxAdd(hwndDig, IDC_COMBO1, using_MapName);
            }
            else
            {
                MessageBox(hwndDig, L"無法打開文件保存JSON", L"錯誤", MB_OK);
            }

        }
        break;
        case ID_DATADELETE:  //刪除存檔
        {
            OutputDebugString(L"刪除存檔\n");

            CComboBox pComboBox;
            pComboBox.Attach(GetDlgItem(hwndDig, IDC_COMBO1));

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
                std::string path = currentPath.parent_path().string() + "/種樹/Images/Map_saveData.json";
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
                MessageBox(hwndDig, L"沒有項目被選中", L"錯誤", MB_OK);
            }
            pComboBox.Detach();

        }
        break;
        case ID_DATALOAD: //載入存檔
        {
            OutputDebugString(L"載入存檔\n");

            CComboBox pComboBox;
            pComboBox.Attach(GetDlgItem(hwndDig, IDC_COMBO1));

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
                std::wstring widestr;

                //OutputDebugString(selectedText);
                // 
                //讀取存檔
                using_MapName = stdStr;
                Map_saveData_using = Map_saveData[using_MapName];


                //清理陣列
                g_FruitTreeManager->ClearPoints();

                auto it = Map_saveData_using.find(using_Main_TreeName);
                // 將地圖中符合元件拿出寫入正在繪製中
                if (it != Map_saveData_using.end()) {
                    for (const auto& coordinate : Map_saveData_using[using_Main_TreeName]["coordinates"]) {
                        drawPoint tree_Point;
                        tree_Point.x = coordinate["X"];
                        tree_Point.y = coordinate["Y"];
                        g_FruitTreeManager->Add_points(tree_Point);
                    }
                    Map_saveData_using.erase(using_Main_TreeName);
                }
                // 顯示備註
                if (!Map_saveData_using["remarks"].empty()) {
                    Map_Remarks = Map_saveData_using["remarks"];
                    widestr = converter.from_bytes(Map_Remarks);

                }
                else {
                    Map_Remarks = "";
                    widestr = L"";
                }
                HWND hStatic = GetDlgItem(hwndDig, IDC_STATIC1);
                SetWindowText(hStatic, widestr.c_str());


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
                    //        MessageBox(hwndDig, str1.c_str(), L"錯誤", MB_OK);
                    //        Map_saveData_using.erase(key);
                    //    }
                    //} 
                    // 上面 erase以後 會超出容範圍
                    for (auto it = Map_saveData_using.begin(); it != Map_saveData_using.end();) {
                        std::string key = it.key();
                        if (key == "remarks") {
                            ++it;
                            continue;
                        }
                        auto treeIt = Tree_saveData.find(key);
                        if (treeIt == Tree_saveData.end()) {
                            std::wstring str = converter.from_bytes(key);
                            std::wstring str1 = L"無法在元件存檔找到" + str + L"\n請到元件存檔重建," + str + L"\n再讀取一次地圖存檔即可.";
                            str1 += L"\n若無重建元件,直接存檔地圖,\n則會將" + str + L"從地圖存檔中刪除";
                            MessageBox(hwndDig, str1.c_str(), L"錯誤", MB_OK);
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
                MessageBox(hwndDig, L"沒有項目被選中", L"錯誤", MB_OK);

            }
            pComboBox.Detach();
            InvalidateRect(hWnd, NULL, TRUE);

        }
        break;
        case ID_RETURN: //刪除最後繪圖資料
        {
            //if (Map_treepoints.empty())
            //    MessageBox(hwndDig, L"此元件已經無物件可刪除", L"錯誤", MB_OK);
            //else if (using_Main_TreeName.empty())
            //    MessageBox(hwndDig, L"未選擇元件", L"錯誤", MB_OK);
            //else {
            //    Map_treepoints.pop_back();
            //    Map_clickPoint = { 0 };
            //    InvalidateRect(hWnd, NULL, FALSE);
            //}

        }
        break;
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwndDig, &ps);

        MapMenu_RenderTarget->BeginDraw();
        MapMenu_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        //不重複清除是因為要保留繪製結果 //使用陣列儲存座標後 改回每次清除
        MapMenu_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF(0.8f, 0.8f, 0.8f, 0.8f))); // dialog 背景色
        MapMenu_RenderTarget->EndDraw();

        EndPaint(hwndDig, &ps);
    }
    break;
    case WM_DESTROY:
    {
        EnableWindow(GetDlgItem(hWnd, 3), TRUE);
        Map_Remarks = "";
        Dialog_MapMenu_is_open = 0;
        MapMenu_RenderTarget->Release();
        MapMenu_hWnd = NULL;
        OutputDebugString(L"地圖選單關閉\n");
    }
    break;
    case WM_ERASEBKGND:
        break;
    case WM_CLOSE:
    {

        DestroyWindow(hwndDig);
    }
        break;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetBkColor(hdcStatic, RGB(204, 204, 204)); // 設定靜態控制項的背景色
        return (INT_PTR)CreateSolidBrush(RGB(204, 204, 204)); // 返回背景刷
    }
    break;
    }

    
    return FALSE;
}

