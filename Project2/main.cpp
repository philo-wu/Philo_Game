
//#include <afx.h>

#include "mian.h"
#include "Dialog_LoadTree_Proc.h"
#include "Dialog_MapMenu_Proc.h"

//����Dialog�y�`
HINSTANCE HINSTANCE1;



//�J�f�I
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)   
{

    // �����y�`�A�Ѩ�ƶ�R
    // �o�ӵ��c��ΨӫO�s�������O�������T��
    WNDCLASSEX wc;

    // �M�ŵ������O�H�Ѩϥ�
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    // �b���c�餤��g�һݪ��������O�H��
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass1";

    // ���U����
    RegisterClassEx(&wc);
    //�ھګȤ�ݨ��o�����j�p�ð��B�z
    HINSTANCE1 = hInstance;
    RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };    // ?�m�ؤo�A�Ӥ��O��m
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // �վ�j�p

    // �إߵ��f�A�ñN�Ǧ^�����G�@���y�`
    hWnd = CreateWindowEx(
        NULL,
        L"WindowClass1",                 // �������O���W�r
        L"�ؾ�o��",   // ���������D
        WS_OVERLAPPEDWINDOW,             // �������˦�
        510,                             // ������x�y��
        100,                             // ������y�y��
        wr.right - wr.left,              // �������e�� //�ھګȤ�ݤj�p�ӭp��A�X�������j�p
        wr.bottom - wr.top,              // ����������
        NULL,                            // �S�������f�A�]�w��NULL
        NULL,                            // ���ϥο��A�]�w��NULL
        hInstance,                       // ���ε{���y�`
        NULL);                           // �P�h�ӵ����@�_�ϥΡA�]�w��NULL

    //���s�����˦�
    InitButtom();

    // ��ܵ���
    ShowWindow(hWnd, nCmdShow);
    // �]�w�ê�l�� Direct
    engine = new Engine();
    engine->phWnd = hWnd;
    drawTree = new Tree(L"1");
    drawFruitTree = new FruitTree(L"2",L"apple");
    engine->InitializeD2D(hWnd); //ø�s�I��
    //Common::InitD2D(hWnd , Tree_RenderTarget); //ø�s

    //   InitD3D(hWnd);
    // �i�J�D�n�j��:
    
    // �o�ӵ��c��]�tWindows�ƥ�T��
    MSG msg = { 0 };    
    // �T���j��
    while (TRUE)
    {


        // ?�d?�C���O�_���������b����
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // �N����T���ഫ�����T���榡
            TranslateMessage(&msg);
            // �N�T���ǰe��WindowProc���
            DispatchMessage(&msg);

            // �ˬd�O�_��F�h�X���ɶ�
            if (msg.message == WM_QUIT)
                break;
            // �ݨ즳�H��return 0, ���]���ڱNClean�g�b���,�G�u��break
        }
        else
        {
            // �C�����e //���������sø�s���a��
            // �]�ؾ�{�����ݭ���ø�ϬG���ϥ�
            //if (engine->playing)
            //{
            //    // Drawing
            //    engine->Draw();
            //}
        }
    }
    
    // �NWM_QUIT�T�����o�@�����Ǧ^��Windows
    return msg.wParam;
}

// �T���B�z���
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // �ƧǨç��w�ﵹ�w�T���B����ǵ{���X
    switch(message)
    {
        case WM_CREATE:
        {
            // �b WM_CREATE �������Ыث��s
            // �b��ø�s���s�|�s�b,���|�Q�л\,���i�H�I��
            // �z�L��ø�ƥ�,�|��ø�s�I���Aø�s���s
            // �]�w�r��
            int buttomnumber = 0;
            // �P�_���ݭn���ø�s���
            // Start_Button = CreateWindow(
            //    L"BUTTON",                              // ���s��������O�W��
            //    L"��ܾ��",                            // ���s�W��ܪ���r
            //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // ���s�˦�
            //    10 + (BUTTON_WIDTH+10)* buttomnumber, 10,
            //    BUTTON_WIDTH, BUTTON_HEIGHT,
            //                                            // ���s��m�M�j�p (x, y, width, height)
            //    hWnd,                                   // �����f�y�`
            //    (HMENU)1,                               // ��� ID (�i�H�Ω��ѧO���s)
            //    GetModuleHandle(NULL),                  // �Ҳեy�`
            //    NULL                                    // ���w�� NULL
            //);
            //++buttomnumber;
            Difficulty_Button = CreateWindow(
                L"BUTTON",                              // ���s��������O�W��
                L"ø�e���",                            // ���s�W��ܪ���r
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // ���s�˦�
                10 + (BUTTON_WIDTH + 10) * buttomnumber, 10,
                BUTTON_WIDTH, BUTTON_HEIGHT,
                                                        // ���s��m�M�j�p (x, y, width, height)
                hWnd,                                   // �����f�y�`
                (HMENU)2,                               // ��� ID (�i�H�Ω��ѧO���s)
                GetModuleHandle(NULL),                  // �Ҳեy�`
                NULL                                    // ���w�� NULL
            );
            ++buttomnumber;

            Score_Button = CreateWindow(
                L"BUTTON",                              // ���s��������O�W��
                L"�a�Ͽ��",                            // ���s�W��ܪ���r
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // ���s�˦�
                10 + (BUTTON_WIDTH + 10) * buttomnumber, 10,
                BUTTON_WIDTH, BUTTON_HEIGHT,
                                                        // ���s��m�M�j�p (x, y, width, height)
                hWnd,                                   // �����f�y�`
                (HMENU)3,                               // ��� ID (�i�H�Ω��ѧO���s)
                GetModuleHandle(NULL),                  // �Ҳեy�`
                NULL                                    // ���w�� NULL
            );
            ++buttomnumber;

            //End_Button = CreateWindow(
            //    L"BUTTON",                              // ���s��������O�W��
            //    L"Ū���a��",                            // ���s�W��ܪ���r
            //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // ���s�˦�
            //    10 + (BUTTON_WIDTH + 10) * buttomnumber, 10,
            //    BUTTON_WIDTH, BUTTON_HEIGHT,
            //                                            // ���s��m�M�j�p (x, y, width, height)
            //    hWnd,                                   // �����f�y�`
            //    (HMENU)4,                               // ��� ID (�i�H�Ω��ѧO���s)
            //    GetModuleHandle(NULL),                  // �Ҳեy�`
            //    NULL                                    // ���w�� NULL
            //);
            //++buttomnumber;

            //Clean_Button = CreateWindow(
            //    L"BUTTON",                              // ���s��������O�W��
            //    L"�a�ϲM��",                            // ���s�W��ܪ���r
            //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // ���s�˦�
            //    10 + (BUTTON_WIDTH + 10) * buttomnumber, 10,
            //    BUTTON_WIDTH, BUTTON_HEIGHT,
            //                                            // ���s��m�M�j�p (x, y, width, height)
            //    hWnd,                                   // �����f�y�`
            //    (HMENU)5,                               // ��� ID (�i�H�Ω��ѧO���s)
            //    GetModuleHandle(NULL),                  // �Ҳեy�`
            //    NULL                                    // ���w�� NULL
            //);
            //++buttomnumber;

        }
        break;
        case WM_COMMAND:// �ˬd���s�ƥ�
            if (HIWORD(wParam) == BN_CLICKED )
            {
                //�ˬd���s����
                switch (LOWORD(wParam))
                {

                case 1: // ��ܾ��
                {
                    if (Dialog_LoadTree_is_open)
                    {
                        MessageBox(hWnd, L"�����w���}", L"���~", MB_OK);
                        break;
                    }
                    Dialog_is_fruit = 0;
                    DialogBox(HINSTANCE1, MAKEINTRESOURCE(IDD_LOADTREE), NULL, Dialog_LoadTree_Proc);
                }
                break;

                case 2: // ��ܤ��G��
                {
                    if (Dialog_LoadTree_is_open)
                    {
                        MessageBox(hWnd, L"�����w���}", L"���~", MB_OK);
                        break;
                    }
                    Dialog_is_fruit = 1;
                    DialogBox(HINSTANCE1, MAKEINTRESOURCE(IDD_LOADTREE), NULL, Dialog_LoadTree_Proc);
                }                    
                break;

                case 3: // �x�s�a��
                {   
                    //std::wstring filePath ;
                    //Common::FileSaveDialog(filePath);
                    //// �����r��

                    //OutputDebugString(filePath.c_str());
                    //Common::SaveWindowToImage(hWnd, filePath.c_str(), { 0,FUNCTION_COLUMN_HEIGHT }, SCREEN_WIDTH,SCREEN_HEIGHT - FUNCTION_COLUMN_HEIGHT);

                    DialogBox(HINSTANCE1, MAKEINTRESOURCE(IDD_RANKLIST), NULL, Dialog_MapMenu_Proc);

                }
                break;

                case 4: // Ū���a��
                {
                    std::wstring  NULLPATH ;//���O�s�ɮ׸��|
                    std::wstring  fileName ;
                    Common::OpenFile(hWnd, engine->m_pRenderTarget, &engine->Map_Bitmap, NULLPATH, fileName);
                    if (fileName.empty())
                        break;
                    engine->do_clear = 1;
                    engine->do_drawMap = 1;
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;

                case 5: // �a�ϲM��
                {
                    Map_clickPoint.x = static_cast<FLOAT>(0);
                    Map_clickPoint.y = static_cast<FLOAT>(0);
                    engine->do_clear = 1;
                    engine->Map_Bitmap = NULL;

                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;
                case ID_CUSTOM_COMMAND: // �۩w�q�R�O���B�z
                    //�`�Ϋ��O
                    //MessageBox(hWnd, L"�C������ \n�o����X", L"����", MB_OK);
                    //SendMessage(hWnd, WM_COMMAND, ID_CUSTOM_COMMAND, 0);  //�����۩w�q�R�O
                    //SendMessage(hWnd, WM_CUSTOM_GAMEEND, 0, 0);           //�����۩w�q�ƥ�
                    //SendMessage(hWnd, WM_CLOSE, 0, 0);                      //��������
                 break;
                }
            }
        break;
        case WM_PAINT:
        {
            // �D���e��
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            //if(Dialog_is_fruit)// 1�令�P�_�n�e���٬O���G��
                //engine->Draw(Map_clickPoint, DIALOG_TREELOAD_TREE_PX, MAINDIALOG_TREE_PX, drawTree , Map_saveData , Map_treepoints);
            //else
                engine->Draw(Map_clickPoint, DIALOG_TREELOAD_TREE_PX, MAINDIALOG_TREE_PX, drawFruitTree , Map_saveData[MapName], Tree_saveData,Map_treepoints);
                
            EndPaint(hWnd, &ps);
        }
        break;
        
        case WM_LBUTTONDOWN: // �B�z�ƹ�����
        {
            int xPos = GET_X_LPARAM(lParam);
            int yPos = GET_Y_LPARAM(lParam);
            if (xPos >= 0 
                && yPos >= FUNCTION_COLUMN_HEIGHT)
            {
                if (xPos + fixed_px_fruit > SCREEN_WIDTH)
                    xPos = SCREEN_WIDTH - fixed_px_fruit;
                if (yPos + fixed_px_fruit > SCREEN_HEIGHT)
                    yPos = SCREEN_HEIGHT - fixed_px_fruit;

                Map_clickPoint.x = static_cast<FLOAT>(xPos);
                Map_clickPoint.y = static_cast<FLOAT>(yPos);
                Map_treepoints.push_back(Map_clickPoint);
                InvalidateRect(hWnd, NULL, TRUE);
            }
        }
        break;
        case WM_KEYDOWN:
        {
        }
        break;

        case WM_DESTROY: // ����������ɷ|Ū�����T��
        {
                // �����������ε{��
                PostQuitMessage(0);
                return 0;
        } 
        break;
    }

    // �B�z switch �y�y���d�I�T��
    return DefWindowProc (hWnd, message, wParam, lParam);
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


// Dialog�[�c�O�d
//INT_PTR CALLBACK Dialog_Ranklist_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    DWORD dwID = wParam;
//
//    switch (uMsg) {
//    case WM_INITDIALOG:
//        {
//            // �]�w�ƶ��d��
//            HWND hListView = GetDlgItem(hwndDlg, IDC_LIST4);
//            DWORD dwStyle = GetWindowLong(hListView, GWL_STYLE);
//            SetWindowLong(hListView, GWL_STYLE, dwStyle | LVS_REPORT | LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP);
//
//            // �K�[�T�C���D
//            LVCOLUMN lvColumn = { 0 };
//            lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
//
//            // �Ĥ@�C�G�m�W
//            const wchar_t* myConstString = L"�m�W";
//            wchar_t* myNonConstString = const_cast<wchar_t*>(myConstString);
//            lvColumn.pszText = const_cast<wchar_t*>(myConstString);
//            lvColumn.iSubItem = 0;
//            lvColumn.cx = 150;  // �]�w�C�e��
//            ListView_InsertColumn(hListView, 0, &lvColumn);
//
//            // �ĤG�C�G����
//            myConstString = L"����";
//            myNonConstString = const_cast<wchar_t*>(myConstString);
//            lvColumn.pszText = const_cast<wchar_t*>(myConstString);
//            lvColumn.iSubItem = 1;
//            lvColumn.cx = 150;
//            ListView_InsertColumn(hListView, 1, &lvColumn);
//
//            // �ĤT�C�G����
//            myConstString = L"����";
//            myNonConstString = const_cast<wchar_t*>(myConstString);
//            lvColumn.pszText = const_cast<wchar_t*>(myConstString);
//            lvColumn.iSubItem = 2;
//            lvColumn.cx = 90;
//            ListView_InsertColumn(hListView, 2, &lvColumn);
//
//
//
//            std::ifstream file("C:\\Users\\philo.wu\\Documents\\GitHub\\Philo_Snake\\Project2\\Ranklist.json", std::ifstream::binary);
//            if (file.is_open()) 
//            {
//                json j;
//                file >> j;
//
//                // �B�z�ѪR�᪺���
//                for (const auto& entry : j["Ranklist"]) {
//                    std::string name = entry["name"];
//                    int score = entry["score"];
//                    int difficulty = entry["difficulty"];
//
//                    // �b�o�̳B�z����s�X���D
//                    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//                    std::wstring nameText = converter.from_bytes(name);
//
//                    LVITEM lvi;
//                    lvi.mask = LVIF_TEXT;
//                    lvi.pszText = const_cast<wchar_t*>(nameText.c_str());
//                    lvi.iItem = ListView_GetItemCount(hListView);  // �s�W���ت�����
//                    lvi.iSubItem = 0;
//                    ListView_InsertItem(hListView, &lvi);
//
//                    // �]�m����
//                    std::wstring scoreText = std::to_wstring(score);
//                    ListView_SetItemText(hListView, lvi.iItem, 1, const_cast<wchar_t*>(scoreText.c_str()));
//
//                    // �]�m����
//                    std::wstring difficultyText = std::to_wstring(difficulty);
//                    ListView_SetItemText(hListView, lvi.iItem, 2, const_cast<wchar_t*>(difficultyText.c_str()));
//
//                }
//
//                file.close();
//            }
//            else 
//            {
//                //std::cout << "Failed to open JSON file" << std::endl;
//            }
//        }
//        break;
//
//    case WM_COMMAND:
//        switch (LOWORD(wParam))
//        {
//        case IDOK:
//            // �ϥΪ̫��U�F�T�w���s
//        {
//            EndDialog(hwndDlg, IDOK);
//        }
//        break;
//        case IDCANCEL:
//            // �ϥΪ̫��U�F�������s
//            EndDialog(hwndDlg, IDCANCEL);
//            break;
//        }
//        break;
//    }
//    return FALSE;
//}
//INT_PTR CALLBACK Dialog_GameEnd_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    DWORD dwID = wParam;
//
//    switch (uMsg) {
//    case WM_INITDIALOG:
//        return TRUE;
//
//    case WM_COMMAND:
//        switch (LOWORD(wParam))
//        {
//        case IDOK:
//            // �ϥΪ̫��U�F�T�w���s
//        {
//            // ���o���a�W��
//            int textLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_EDIT1));
//            if (textLength == 0)
//            {
//                // ��J����
//                MessageBox(hWnd, L"����J���a�W��", L"���~", MB_OK);
//                // �u�X�����e��
//                SendMessage(hWnd, WM_CUSTOM_GAMEEND, 0, 0);
//            }
//            else
//            {
//                wchar_t buffer[100]; // �n�s���ƪ��w�İ�
//                GetDlgItemText(hwndDlg, IDC_EDIT1, buffer, 100);
//                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
//                std::string newName = converter.to_bytes(buffer);
//
//                int newScore =0;
//                int newDifficulty =0;
//
//                std::ifstream file("./Ranklist.json", std::ifstream::binary);
//                json jsonData;
//                file >> jsonData;
//                file.close();
//
//                json newEntry = {
//                    {"name", newName},
//                    {"score", newScore},
//                    {"difficulty", newDifficulty}
//                };
//                jsonData["Ranklist"].push_back(newEntry);
//                std::ofstream outFile("./Ranklist.json");
//                outFile << jsonData.dump(4);  // 4 �O�Y�ƪ��ƶq
//                outFile.close();
//                
//            }
//
//            EndDialog(hwndDlg, IDOK);
//        }
//        break;
//
//        case IDCANCEL:
//            // �ϥΪ̫��U�F�������s
//            EndDialog(hwndDlg, IDCANCEL);
//            break;
//        }
//        break;
//    }
//    return FALSE;
//}
