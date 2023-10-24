#pragma once

#include "Common.h"
#include "Direct2D.h"
#include "mian.h"
#include "resource.h"
//#include <afx.h>


//防呆
bool Dialog_LoadTree_is_open = false;
bool Dialog_Input_is_open = false;

// Dialog相關
std::vector<POINT> fruit_Points;
POINT Tree_Point = { DIALOG_TREELOAD_POINT_X,DIALOG_TREELOAD_POINT_Y }; //Dialog樹木生成座標
POINT Tree_clickPoint = { 0 }; //Dialog點擊座標
//POINT movePoint = { 0 }; //Dialog滑鼠當前座標
json Tree_saveData;   //所有元件存檔

//主視窗相關
std::vector<POINT> Map_treepoints;
POINT Map_clickPoint = { 0 }; //主視窗點擊座標
json Map_saveData;   //所有地圖存檔
json Map_saveData_using; //正在讀取的Map
std::string using_MapName; //正在讀取的存檔名稱
std::string using_Dialog_TreeName ; //正在讀取的元件名稱
std::string using_Main_TreeName ; //正在主視窗繪畫的元件名稱

//圖檔繪製大小 樹木圖檔為正方形,長寬為fixed_px, 
int fixed_px = DIALOG_TREELOAD_TREE_PX;
//圖檔繪製大小 水果圖檔為正方形,長寬為fixed_px_fruit, 
int fixed_px_fruit = DIALOG_TREELOAD_FRUIT_PX;
RECT TreeRect ;

//Dialog繪圖
bool Dialog_do_Clear = 1;
bool Dialog_do_TreeClear = 1;
bool Dialog_is_Save = 0;
bool Dialog_is_fruit;
bool Dialog_has_save_name = 0;
bool Dialog_Tree_has_newaction = 0;
ID2D1Bitmap* Tree_Bitmap;
ID2D1Bitmap* Fruit_Bitmap;
ID2D1HwndRenderTarget* Tree_RenderTarget;

//主視窗繪圖
Tree* drawTree;
FruitTree* drawFruitTree;
FruitTree* drawFruitTree2;

ID2D1Factory* pD2DFactory;

// 取得專案位置
std::filesystem::path currentPath = std::filesystem::current_path(); // C++ 17



std::wstring Load_Tree_File_Path;
std::wstring Load_Fruit_File_Path;

std::wstring Save_File_Path;
std::string Tree_File_Name;
std::string Fruit_File_Name;
std::string Save_Name; //為Dialog_Input 最後保存的名稱
std::string Save_Remarks; //為Dialog_Input 最後保存的名稱

std::string Tree_Remarks; 
std::string Map_Remarks; 

//提前宣告
INT_PTR CALLBACK Dialog_MapMenu_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK Dialog_Input_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD dwID = wParam;

    switch (uMsg) {
    case WM_INITDIALOG:
    {
        OutputDebugString(L"輸入視窗開啟\n");

        Dialog_Input_is_open = 1;
        Save_Remarks = "";
        Save_Name = "";
        return TRUE;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            // 使用者按下了確定按鈕
        case IDOK:
        {
            // 取得玩家名稱
            int textLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_EDIT1));
            if (textLength == 0)
            {
                // 輸入為空
                MessageBox(hwndDlg, L"未輸入檔案名稱", L"錯誤", MB_OK);
                break;

            }
            else
            {
                wchar_t buffer[100]; // 要存放資料的緩衝區
                // C++14
                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

                GetDlgItemText(hwndDlg, IDC_EDIT1, buffer, 100);
                Save_Name = converter.to_bytes(buffer);

                GetDlgItemText(hwndDlg, IDC_EDIT2, buffer, 100);
                Save_Remarks = converter.to_bytes(buffer);

                // C++17
                //GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT1), buffer, 100);
                //int bufferSize = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);
                //Save_Name.resize(bufferSize);
                //WideCharToMultiByte(CP_UTF8, 0, buffer, -1, &Save_Name[0], bufferSize, nullptr, nullptr);
                //OutputDebugString(buffer);
                //OutputDebugString(L"保存\n");

                //std::wstring wideSaveName(Save_Name.begin(), Save_Name.end());
                //OutputDebugString(wideSaveName.c_str());

                //OutputDebugString(L"保存\n");

                //TODO: 寫入存檔路徑以及快捷記錄檔

            }
            EndDialog(hwndDlg, IDOK);
        }
        break;
        // 使用者按下了取消按鈕
        case IDCANCEL:
        {
            EndDialog(hwndDlg, IDCANCEL);
        }
        break;
        }
        break;
    case WM_DESTROY:
    {
        OutputDebugString(L"輸入視窗關閉\n");
        Dialog_Input_is_open = 0;
    }
    break;
    }
    return FALSE;
}

//用以還原控制項
void Dialog_clear()
{
    if (!fruit_Points.empty())
        fruit_Points.clear();
    Dialog_do_Clear = 1;
    Dialog_do_TreeClear = 1;
    Tree_clickPoint = { 0 };
    Dialog_has_save_name = 0 ;

}
INT_PTR CALLBACK Dialog_LoadTree_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD dwID = wParam;
    switch (uMsg) {
    case WM_INITDIALOG:
    {
        OutputDebugString(L"繪畫選單開啟\n");

        Dialog_LoadTree_is_open = 1;
        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
        if (SUCCEEDED(hr))
        {

            OutputDebugString(L"Dialog初始化\n");
            Tree_Point.x = DIALOG_TREELOAD_POINT_X;
            Tree_Point.y = DIALOG_TREELOAD_POINT_Y;
            TreeRect = {
            static_cast<LONG>(Tree_Point.x),
            static_cast<LONG>(Tree_Point.y),
            static_cast<LONG>(Tree_Point.x + fixed_px),
            static_cast<LONG>(Tree_Point.y + fixed_px)
            };
            Dialog_is_Save = 0;
            Tree_Bitmap = NULL;
            Fruit_Bitmap = NULL;
            Common::InitD2D(hwndDlg, pD2DFactory, &Tree_RenderTarget);

            
        }
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
    {
        if (LOWORD(wParam) == IDC_COMBO1 && HIWORD(wParam) == CBN_SELCHANGE) //偵測Combobox改變
        {
            // 在這裡處理選擇改變後的邏輯
            // 直接呼叫LOADSAVE
            SendMessage(hwndDlg, WM_COMMAND, ID_DATALOAD, 0); 

        }
        switch (LOWORD(wParam))
        {
            case IDOK: //匯入主選單
            {

                //OutputDebugString(L"儲存圖片\n");
                //if (!Dialog_is_fruit)//先處理一般樹
                {
                    // 將上一份繪圖結果儲存
                    if (Dialog_Tree_has_newaction)
                    {
                        MessageBox(hwndDlg, L"請先進行存檔", L"錯誤", MB_OK);
                        break;

                    }
                    // 初始化主視窗相關
                    if (!Map_treepoints.empty())
                    {
                        json tree;
                        auto it = Map_saveData_using.find(using_Main_TreeName);

                        if (it != Map_saveData_using.end())
                            tree = Map_saveData_using[using_Main_TreeName];
                        json coordinatesArray = tree["coordinates"];
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
                        Map_saveData_using[using_Main_TreeName] = tree;

                    }

                    Map_treepoints.clear();

                    // 將地圖中符合元件拿出寫入正在繪製中
                    auto it = Map_saveData_using.find(using_Dialog_TreeName);

                    if (it != Map_saveData_using.end())
                    {
                        for (const auto& coordinate : Map_saveData_using[using_Dialog_TreeName]["coordinates"])
                        {
                            POINT tree_Point;
                            tree_Point.x = coordinate["X"];
                            tree_Point.y = coordinate["Y"];
                            Map_treepoints.push_back(tree_Point);
                        }
                        Map_saveData_using.erase(using_Dialog_TreeName);
                    }

                    Map_clickPoint = { 0 };
                    using_Main_TreeName = using_Dialog_TreeName;
                    // 帶入水果樹圖片
                    //OutputDebugString(L"匯入主選單\n");
                    //OutputDebugString(L"樹木位置\n");
                    //OutputDebugString(Load_Tree_File_Path.c_str());
                    //OutputDebugString(L"\n");

                    IWICImagingFactory* pIWICFactory = NULL;
                    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
                    drawFruitTree->Release_treeBitmap();
                    int errorcode;

                    Common::LoadBitmapFromFile(engine->m_pRenderTarget, pIWICFactory, Load_Tree_File_Path, 0, 0, &drawFruitTree->Get_treeBitmap(), hwndDlg, errorcode);
                    //OutputDebugString(L"水果位置\n");
                    //OutputDebugString(Load_Fruit_File_Path.c_str());
                    //OutputDebugString(L"\n");
                    if (!Load_Fruit_File_Path.empty()) {
                        drawFruitTree->Release_fruitBitmap();
                        Common::LoadBitmapFromFile(engine->m_pRenderTarget, pIWICFactory, Load_Fruit_File_Path, 0, 0, &drawFruitTree->Get_fruitBitmap(), hwndDlg, errorcode);
                        drawFruitTree->Set_fruit_Points(fruit_Points);
                    }

                    OutputDebugString(L"匯入結束\n");
                    pIWICFactory->Release();
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                //else
                //{
                //    if(!Dialog_is_Save)
                //    {
                //        drawFruitTree->Release();
                //        Save_File_Path = L"./tree_save/auto_save.png";
                //        Common::SaveWindowToImage(hwndDlg, Save_File_Path.c_str(), Tree_Point, fixed_px, fixed_px);
                //    }
                //    // 自動帶入水果樹圖片      
                //    IWICImagingFactory* pIWICFactory = NULL;
                //    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
                //    Common::LoadBitmapFromFile(engine->m_pRenderTarget, pIWICFactory, Save_File_Path, 0, 0, &drawFruitTree->treeBitmap);
                //    pIWICFactory->Release();
                //}
                //EndDialog(hwndDlg, IDOK);
            }
            break;

            case IDCANCEL:
            {
                // 使用者按下了取消按鈕
                Dialog_clear();
                EndDialog(hwndDlg, IDCANCEL);
            }
            break;
            case ID_LOADTREE: // 選擇樹木
            {
                std::wstring filename;
                Common::OpenFile(hwndDlg, Tree_RenderTarget, &Tree_Bitmap, Load_Tree_File_Path, filename, currentPath);
                if (!filename.empty())
                {

                    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                    Tree_File_Name = converter.to_bytes(filename);
                    //OutputDebugString(Load_File_Path.c_str());
                    Dialog_clear();
                    InvalidateRect(hwndDlg, NULL, TRUE);
                }
            }
            break;

            case ID_LOADFRUIT: // 選擇水果
            {
                if (!Tree_Bitmap)
                {
                    MessageBox(hwndDlg, L"請先選擇樹木", L"錯誤", MB_OK);
                    break;
                }
                std::wstring filename;
                Common::OpenFile(hwndDlg, Tree_RenderTarget, &Fruit_Bitmap, Load_Fruit_File_Path, filename, currentPath);
                if (!filename.empty())
                {
                    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                    Fruit_File_Name = converter.to_bytes(filename);
                    Dialog_clear();
                    InvalidateRect(hwndDlg, NULL, TRUE);
                }
            }
            break;
            case ID_DATASAVE: // 另存新檔
            {
                //OutputDebugString(L"繪畫選單_另存新檔\n");

                //if (fruit_Points.empty() || !Fruit_Bitmap)
                //{
                //    MessageBox(hwndDlg, L"無進行任何繪圖", L"錯誤", MB_OK);
                //    break;
                //}
                Dialog_is_Save = 1;
                Dialog_Tree_has_newaction = 0;

                // SAVE
                json save_tree;
                json fruit;
                // 創建一個 JSON array，用於存放 coordinates
                json coordinatesArray;
                // 將 fruit_Points 中的每個 POINT 轉換為 JSON object 並添加到 array 中
                for (const POINT& point : fruit_Points)
                {
                    json pointObject =
                    {
                        {"X", point.x},
                        {"Y", point.y}
                    };

                    coordinatesArray.push_back(pointObject);
                }

                // 將 coordinatesArray 存入 JSON 中的 "coordinates"
                fruit["coordinates"] = coordinatesArray;
                if (Fruit_File_Name != "")
                    fruit["image"] = Fruit_File_Name;

                save_tree["coordinates"] = { {"X", 0}, {"Y", 0} };
                save_tree["image"] = Tree_File_Name;

                save_tree["Fruit"] = fruit;

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

                Tree_Remarks = Save_Remarks;
                save_tree["remarks"] = Tree_Remarks;
                std::wstring widestr;
                std::string stdStr;
                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

                if (!save_tree["remarks"].empty()) {
                    stdStr = save_tree["remarks"];
                    widestr = converter.from_bytes(stdStr);
                }
                else {
                    widestr = L"";
                }
                HWND hStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
                SetWindowText(hStatic, widestr.c_str());

                using_Dialog_TreeName = Save_Name;
                //std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                //std::wstring wideName = converter.from_bytes(Save_Name);
                //OutputDebugString(L"讀取保存名稱\n");
                //std::wstring wideSaveName(Save_Name.begin(), Save_Name.end());
                //OutputDebugString(wideSaveName.c_str());

                // 將 JSON 對象轉換為字串
                Tree_saveData[using_Dialog_TreeName] = save_tree;
                std::string jsonString = Tree_saveData.dump(4);

                // 將 JSON 字串保存到文件
                std::string path = currentPath.parent_path().string() + "/種樹/Images/Tree_saveData.json";


                std::ofstream outFile(path);
                if (outFile.is_open())
                {
                    outFile << jsonString;
                    outFile.close();
                    OutputDebugString(L"JSON 已保存到 Tree_saveData.json\n");

                    CComboBox pComboBox;
                    pComboBox.Attach(GetDlgItem(hwndDlg, IDC_COMBO1));

                    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                    std::wstring wideSaveName = converter.from_bytes(using_Dialog_TreeName);
                    //判斷是否有存在同名選項
                    int index = pComboBox.FindString(-1, wideSaveName.c_str());
                    if (index == CB_ERR) {
                        // 相同的選項不存在，可以新增
                        pComboBox.AddString(wideSaveName.c_str());
                    }
                    index = pComboBox.FindString(-1, wideSaveName.c_str());
                    pComboBox.SetCurSel(index);

                    pComboBox.Detach();

                }
                else
                {
                    //OutputDebugString(widepath.c_str
                    //MessageBox(hwndDlg, path.c_str(), L"繪圖選單", MB_OK);

                    MessageBox(hwndDlg, L"無法另存新檔", L"繪圖選單", MB_OK);
                }



            }
            break;
            case ID_DATASAVE_QUICK: // 快速儲存
            {
                //if (fruit_Points.empty() || !Fruit_Bitmap)
                //{
                //    MessageBox(hwndDlg, L"無進行任何繪圖", L"錯誤", MB_OK);
                //    break;
                //}
                Dialog_is_Save = 1;
                Dialog_Tree_has_newaction = 0;
                // SAVE
                json save_tree;
                json fruit;
                // 創建一個 JSON array，用於存放 coordinates
                json coordinatesArray;
                // 將 fruit_Points 中的每個 POINT 轉換為 JSON object 並添加到 array 中
                for (const POINT& point : fruit_Points)
                {
                    json pointObject =
                    {
                        {"X", point.x},
                        {"Y", point.y}
                    };

                    coordinatesArray.push_back(pointObject);
                }

                // 將 coordinatesArray 存入 JSON 中的 "coordinates"
                fruit["coordinates"] = coordinatesArray;
                fruit["image"] = Fruit_File_Name;

                save_tree["coordinates"] = { {"X", 0}, {"Y", 0} };
                save_tree["image"] = Tree_File_Name;
                if (Fruit_File_Name != "")
                    save_tree["Fruit"] = fruit;

                //std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                //std::wstring wideName = converter.from_bytes(Save_Name);
                //OutputDebugString(L"讀取保存名稱\n");
                //std::wstring wideSaveName(Save_Name.begin(), Save_Name.end());
                //OutputDebugString(wideSaveName.c_str());

                // 將 JSON 對象轉換為字串
                if (using_Dialog_TreeName.empty()) // 檢查是否從存檔讀取
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
                    using_Dialog_TreeName = Save_Name;
                }

                Tree_Remarks = Save_Remarks;
                save_tree["remarks"] = Tree_Remarks;
                std::wstring widestr;
                std::string stdStr;
                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

                if (!save_tree["remarks"].empty()) {
                    stdStr = save_tree["remarks"];
                    widestr = converter.from_bytes(stdStr);
                }
                else {
                    widestr = L"";
                }
                HWND hStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
                SetWindowText(hStatic, widestr.c_str());

                Tree_saveData[using_Dialog_TreeName] = save_tree;
                std::string jsonString = Tree_saveData.dump(4);

                // 將 JSON 字串保存到文件
                std::string path = currentPath.parent_path().string() + "/種樹/Images/Tree_saveData.json";
                std::ofstream outFile(path);
                if (outFile.is_open())
                {
                    outFile << jsonString;
                    outFile.close();
                    OutputDebugString(L"JSON 已保存到 Tree_saveData.json\n");

                    CComboBox pComboBox;
                    pComboBox.Attach(GetDlgItem(hwndDlg, IDC_COMBO1));

                    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                    std::wstring wideSaveName = converter.from_bytes(using_Dialog_TreeName);
                    //判斷是否有存在同名選項
                    int index = pComboBox.FindString(-1, wideSaveName.c_str());
                    if (index == CB_ERR) {
                        // 相同的選項不存在，可以新增
                        pComboBox.AddString(wideSaveName.c_str());
                    }
                    index = pComboBox.FindString(-1, wideSaveName.c_str());
                    pComboBox.SetCurSel(index);

                    pComboBox.Detach();

                }
                else
                {
                    /*           OutputDebugString(L"JSON 已保存到 Map_saveData.json\n");
           OutputDebugString(widepath.c_str());*/
           //MessageBox(hwndDlg, widepath.c_str(), L"錯誤", MB_OK);
                    MessageBox(hwndDlg, L"無法快速保存JSON", L"錯誤", MB_OK);
                }



            }
            break;
            case ID_DATADELETE: //刪除存檔
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
                    Tree_saveData.erase(stdStr);
                    pComboBox.DeleteString(selectedIndex);
                    if (pComboBox.GetCount() == 0)
                        pComboBox.SetCurSel(-1);
                    else
                        pComboBox.SetCurSel(0);


                    std::string jsonString = Tree_saveData.dump(4);
                    // 將 JSON 字串保存到文件
                    std::string path = currentPath.parent_path().string() + "/種樹/Images/Tree_saveData.json";
                    std::ofstream outFile(path);
                    if (outFile.is_open())
                    {
                        outFile << jsonString;
                        outFile.close();
                        OutputDebugString(L"JSON 已保存到 Tree_saveData.json\n");
                    }
                }
                else
                {
                    // 沒有項目被選中
                    //OutputDebugString(L"沒有項目被選中\n");
                    MessageBox(hwndDlg, L"沒有項目被選中", L"錯誤", MB_OK);
                }
                pComboBox.Detach();
                InvalidateRect(hwndDlg, NULL, TRUE);

            }
            break;
            case ID_DATALOAD: // 載入存檔
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
                    json save_tree = Tree_saveData[stdStr];
                    Dialog_clear();
                    using_Dialog_TreeName = stdStr;
                    json Fruit = save_tree["Fruit"];
                    json coordinatesArray = Fruit["coordinates"];

                    // 將 JSON array 中的每個 object 轉換為 POINT 並添加到 fruit_Points 中
                    for (const auto& pointObject : coordinatesArray)
                    {
                        POINT point;
                        point.x = pointObject["X"];
                        point.y = pointObject["Y"];
                        fruit_Points.push_back(point);
                    }

                    IWICImagingFactory* pIWICFactory = NULL;
                    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);

                    // 讀取圖檔
                    stdStr = save_tree["image"];
                    Tree_File_Name = save_tree["image"];
                    std::wstring Png = converter.from_bytes(stdStr);
                    std::wstring path = currentPath.wstring() + L"\\..\\種樹\\Images\\" + Png;
                    Tree_Bitmap = NULL;
                    int errorcode;
                    Common::LoadBitmapFromFile(Tree_RenderTarget, pIWICFactory, path, 0, 0, &Tree_Bitmap, hwndDlg, errorcode);
                    Load_Tree_File_Path = path;
                    if (errorcode != 0) { //errorcode用來示警圖檔不存在的狀況
                        std::wstring str1 = path + L"\n圖檔不存在" + L"\n";
                        MessageBox(hwndDlg, str1.c_str(), L"錯誤", MB_OK);
                        Load_Tree_File_Path = L"";
                    }

                    // 顯示備註
                    if (!save_tree["remarks"].empty()) {
                        Tree_Remarks = save_tree["remarks"];
                        Png = converter.from_bytes(Tree_Remarks);
                    }
                    else {
                        Png = L"";
                    }
                    HWND hStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
                    SetWindowText(hStatic, Png.c_str());

                    // 排除存檔中無水果的狀況
                    if (Fruit["image"].empty()) { 
                        Fruit_Bitmap = NULL;
                        Load_Fruit_File_Path = L"";
                    }
                    else {
                        stdStr = Fruit["image"];
                        Fruit_File_Name = Fruit["image"];
                        Png = converter.from_bytes(stdStr);
                        path = currentPath.wstring() + L"\\..\\種樹\\Images\\" + Png;
                        Fruit_Bitmap = NULL;

                        Common::LoadBitmapFromFile(Tree_RenderTarget, pIWICFactory, path, 0, 0, &Fruit_Bitmap, hwndDlg, errorcode);
                        Load_Fruit_File_Path = path;
                        if (errorcode != 0) {
                            std::wstring str1 = path + L"\n圖檔不存在" + L"\n";
                            MessageBox(hwndDlg, str1.c_str(), L"錯誤", MB_OK);
                            Load_Fruit_File_Path = L"";
                        }
                    }
                    if (pIWICFactory)
                        pIWICFactory->Release();


                }
                else
                {
                    // 沒有項目被選中
                    //OutputDebugString(L"沒有項目被選中\n");
                    MessageBox(hwndDlg, L"沒有項目被選中", L"錯誤", MB_OK);
                }
                pComboBox.Detach();
                OutputDebugString(L"載入結束\n");

                InvalidateRect(hwndDlg, NULL, TRUE);

            }
            break;
            case ID_RETURN:
            {
                if (!fruit_Points.empty())
                    fruit_Points.pop_back();
                else
                    MessageBox(hwndDlg, L"已經沒有水果可以刪除", L"錯誤", MB_OK);
                Dialog_do_Clear = 1;
                Dialog_do_TreeClear = 1;
                Tree_clickPoint = { 0 };
                InvalidateRect(hwndDlg, NULL, FALSE);
            }
            break;
        }
    }
        break;
    case WM_LBUTTONDOWN:
        // 處理滑鼠左鍵
    {
        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);
        if (Fruit_Bitmap 
            && xPos >= Tree_Point.x 
            && yPos >= Tree_Point.y 
            && xPos <= Tree_Point.x + fixed_px 
            && yPos <= Tree_Point.y + fixed_px)
        {
            //越界判定
            if (xPos + fixed_px_fruit > Tree_Point.x + fixed_px)
                xPos = Tree_Point.x + fixed_px - fixed_px_fruit;
            if (yPos + fixed_px_fruit > Tree_Point.y + fixed_px)
                yPos = Tree_Point.y + fixed_px - fixed_px_fruit;

            Tree_clickPoint.x = static_cast<FLOAT>(xPos) - Tree_Point.x;
            Tree_clickPoint.y = static_cast<FLOAT>(yPos) - Tree_Point.y;

            fruit_Points.push_back(Tree_clickPoint);
            //using_Dialog_TreeName = "";
            Dialog_Tree_has_newaction = 1;
            InvalidateRect(hwndDlg, NULL, FALSE);
        }
    }
    break;
    case WM_MOUSEMOVE:
        // 在滑鼠指向的位置渲染圖片 TODO:
    {
        //int xPos = GET_X_LPARAM(lParam);
        //int yPos = GET_Y_LPARAM(lParam);
        //if (xPos >= Tree_Point.x && yPos >= Tree_Point.y && xPos <= Tree_Point.x + fixed_px && yPos <= Tree_Point.y + fixed_px)
        //{
        //    movePoint.x = static_cast<FLOAT>(xPos);
        //    movePoint.y = static_cast<FLOAT>(yPos);
        //    InvalidateRect(hwndDlg, NULL, FALSE);
        //}
    }    
    break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwndDlg, &ps);

            Tree_RenderTarget->BeginDraw();
            Tree_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
            //不重複清除是因為要保留繪製結果 //使用點擊陣列後即可每次清除
            if (Dialog_do_Clear)
            {

                Tree_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF(0.8f, 0.8f, 0.8f, 0.8f))); // dialog 背景色
                Dialog_do_Clear = 0;
            }

            //有讀取樹木圖片
            if (Tree_Bitmap && Dialog_do_TreeClear)
            {
                D2D1_COLOR_F white_Color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f); //繪製區域背景色
                ID2D1SolidColorBrush* pWhiteBrush;
                Tree_RenderTarget->CreateSolidColorBrush(white_Color, &pWhiteBrush);
                //m_pRenderTarget->DrawRectangle(&rectangle, pBlackBrush, 7.0f);
                Tree_RenderTarget->FillRectangle(D2D1::RectF(Tree_Point.x, Tree_Point.y, Tree_Point.x + fixed_px, Tree_Point.y + fixed_px), pWhiteBrush);
                D2D1_SIZE_U size = Tree_Bitmap->GetPixelSize();
                UINT width = size.width;
                UINT height = size.height;
                Tree_RenderTarget->DrawBitmap(Tree_Bitmap, D2D1::RectF(Tree_Point.x, Tree_Point.y, Tree_Point.x + fixed_px, Tree_Point.y + fixed_px));
                Dialog_do_TreeClear = 0;
            }
            //有讀取水果圖片並點擊在樹上
            //if (Fruit_Bitmap && Tree_clickPoint.x != 0 && Tree_clickPoint.y != 0)
            //{
            //    D2D1_SIZE_U size = Fruit_Bitmap->GetPixelSize();
            //    UINT width = size.width;
            //    UINT height = size.height;
            //    Tree_RenderTarget->DrawBitmap(Fruit_Bitmap, D2D1::RectF(Tree_clickPoint.x, Tree_clickPoint.y, Tree_clickPoint.x + fixed_px_fruit, Tree_clickPoint.y + fixed_px_fruit));
            //}
            if (Fruit_Bitmap)
            {
                Tree_RenderTarget->DrawBitmap(Fruit_Bitmap, D2D1::RectF(DIALOG_TREELOAD_FRUIT_POINT_X, DIALOG_TREELOAD_FRUIT_POINT_Y, DIALOG_TREELOAD_FRUIT_POINT_X + fixed_px_fruit, DIALOG_TREELOAD_FRUIT_POINT_Y + fixed_px_fruit));
            }

            // 讀取點擊陣列並繪圖水果
            for (const POINT& fruit_Point : fruit_Points)
            {
                if (Fruit_Bitmap)
                {
                    UINT drawpoint_x = Tree_Point.x + fruit_Point.x;
                    UINT drawpoint_y = Tree_Point.y + fruit_Point.y;

                    Tree_RenderTarget->DrawBitmap(Fruit_Bitmap, D2D1::RectF(drawpoint_x, drawpoint_y, drawpoint_x + fixed_px_fruit, drawpoint_y + fixed_px_fruit));
                }
            }
            Tree_RenderTarget->EndDraw();

            EndPaint(hwndDlg, &ps);
        }
        break;
    case WM_DESTROY:
        {
            OutputDebugString(L"繪畫選單關閉\n");
            if (Tree_Bitmap)
                Tree_Bitmap->Release();
            if (Fruit_Bitmap)
                Fruit_Bitmap->Release();
            if (!fruit_Points.empty())
                fruit_Points.clear();
            Dialog_do_Clear = 1;
            Dialog_do_TreeClear = 1;
            Tree_clickPoint = { 0 };
            Tree_RenderTarget->Release();
            Dialog_LoadTree_is_open = 0;
        }
        break;

    case WM_ERASEBKGND:
        break;

    case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC)wParam;
            SetBkColor(hdcStatic, RGB(255, 0, 0)); // 設置背景顏色
        }
        break;
    }

    return FALSE;
}

