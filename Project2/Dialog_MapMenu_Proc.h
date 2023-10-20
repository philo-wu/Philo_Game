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
            //std::cerr << "�L�k���} JSON ���" << std::endl;
            //OutputDebugString(L"JSON�}�Ҧ��\\n");
            MessageBox(hWnd, L"JSON�s��Ū������", L"���~", MB_OK);

            return 1;
        }
        //else
            //OutputDebugString(L"JSON�}�Ҧ��\\n");
        json Data;
        inFile >> Data;
        inFile.close();
        Map_saveData = Data;
        std::vector<std::string> items;

        for (auto it = Data.begin(); it != Data.end(); ++it)
        {
            items.push_back(it.key());
        }
        //OutputDebugString(L"items����\n");

        CComboBox pComboBox;
        pComboBox.Attach(GetDlgItem(hwndDlg, IDC_COMBO1));
        CFont font;
        font.CreatePointFont(120, _T("Verdana"));  // 120 �O�r��j�p�A"Verdana" �O�r��W��
        pComboBox.SetFont(&font);

        for (const auto& item : items) {
            //�Nstring�ഫ��wstring //Cstring�襤��䴩���n
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring wideSaveName = converter.from_bytes(item);
            pComboBox.AddString(wideSaveName.c_str());
            //OutputDebugString(wideSaveName.c_str());
            //OutputDebugString(L"\n");

        }

        pComboBox.Detach();
        //OutputDebugString(L"JSONŪ�����\\n");


    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            // �ϥΪ̫��U�F�T�w���s
        {

        }
        break;

        case IDCANCEL:
        {
            // �ϥΪ̫��U�F�������s
            EndDialog(hwndDlg, IDCANCEL);
        }
        break;
        case ID_DATASAVE: // �x�s�ɮ�
        {
            // SAVE
            json save_map;
            json tree;
            // �Ыؤ@�� JSON array�A�Ω�s�� coordinates
            json coordinatesArray;
            // �N fruit_Points �����C�� POINT �ഫ�� JSON object �òK�[�� array ��
            for (const POINT& point : Map_treepoints)
            {
                json pointObject =
                {
                    {"X", point.x},
                    {"Y", point.y}
                };

                coordinatesArray.push_back(pointObject);
            }

            // �N coordinatesArray �s�J JSON ���� "coordinates"
            tree["coordinates"] = coordinatesArray;

            save_map[TreeName] = tree;
            int result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INPUT), NULL, Dialog_Input_Proc);
            if (result == -1)
            {
                // ��ܮسЫإ���
                MessageBox(NULL, L"��ܮسЫإ���", L"���~", MB_OK | MB_ICONERROR);
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
            //OutputDebugString(L"Ū���O�s�W��\n");
            //std::wstring wideSaveName(Save_Name.begin(), Save_Name.end());
            //OutputDebugString(wideSaveName.c_str());

            // �N JSON ��H�ഫ���r��
            Map_saveData[Save_Name] = save_map;
            std::string jsonString = Map_saveData.dump(4);

            // �N JSON �r��O�s����
            std::string path = currentPath.string() + "/Images/Map_saveData.json";
            std::ofstream outFile(path);
            if (outFile.is_open())
            {
                outFile << jsonString;
                outFile.close();
                OutputDebugString(L"JSON �w�O�s�� Map_saveData.json\n");

                CComboBox pComboBox;
                pComboBox.Attach(GetDlgItem(hwndDlg, IDC_COMBO1));

                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                std::wstring wideSaveName = converter.from_bytes(Save_Name);
                //�P�_�O�_���s�b�P�W�ﶵ
                int index = pComboBox.FindString(-1, wideSaveName.c_str());
                if (index == CB_ERR) {
                    // �ۦP���ﶵ���s�b�A�i�H�s�W
                    pComboBox.AddString(wideSaveName.c_str());
                }
                pComboBox.Detach();

            }
            else
            {
                MessageBox(hwndDlg, L"�L�k���}���O�sJSON", L"���~", MB_OK);
            }



        }
        break;
        case ID_DATADELETE:  //�R���s��
        {
            OutputDebugString(L"�R���s��\n");

            CComboBox pComboBox;
            pComboBox.Attach(GetDlgItem(hwndDlg, IDC_COMBO1));

            int selectedIndex = pComboBox.GetCurSel();

            if (selectedIndex != CB_ERR)
            {
                // �����سQ�襤

                CString selectedText;
                pComboBox.GetLBText(selectedIndex, selectedText);
                OutputDebugString(selectedText);
                OutputDebugString(L"\n");
                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                std::wstring wideselectedText(selectedText);
                std::string stdStr = converter.to_bytes(wideselectedText);

                //OutputDebugString(selectedText);
                // 
                //�R���s��
                Map_saveData.erase(stdStr);
                pComboBox.DeleteString(selectedIndex);
                if (pComboBox.GetCount() == 0)
                    pComboBox.SetCurSel(-1);
                else
                    pComboBox.SetCurSel(0);


                std::string jsonString = Map_saveData.dump(4);
                // �N JSON �r��O�s����
                std::string path = currentPath.string() + "/Images/Map_saveData.json";
                std::ofstream outFile(path);
                if (outFile.is_open())
                {
                    outFile << jsonString;
                    outFile.close();
                    OutputDebugString(L"JSON �w�O�s�� Map_saveData.json\n");
                }
            }
            else
            {
                // �S�����سQ�襤
                //OutputDebugString(L"�S�����سQ�襤\n");
                MessageBox(hwndDlg, L"�S�����سQ�襤", L"���~", MB_OK);
            }
            pComboBox.Detach();
            InvalidateRect(hWnd, NULL, TRUE);

        }
        break;
        case ID_DATALOAD: //���J�s��
        {
            OutputDebugString(L"���J�s��\n");

            CComboBox pComboBox;
            pComboBox.Attach(GetDlgItem(hwndDlg, IDC_COMBO1));

            int selectedIndex = pComboBox.GetCurSel();

            if (selectedIndex != CB_ERR)
            {
                // �����سQ�襤

                CString selectedText;
                pComboBox.GetLBText(selectedIndex, selectedText);
                OutputDebugString(selectedText);
                OutputDebugString(L"\n");


                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                std::wstring wideselectedText(selectedText);
                std::string stdStr = converter.to_bytes(wideselectedText);

                //OutputDebugString(selectedText);
                // 
                //Ū���s��
                MapName = stdStr;
                Map_saveData_using = Map_saveData[MapName];

            }
            else
            {
                // �S�����سQ�襤
                //OutputDebugString(L"�S�����سQ�襤\n");
                MessageBox(hwndDlg, L"�S�����سQ�襤", L"���~", MB_OK);
            }
            pComboBox.Detach();
            InvalidateRect(hWnd, NULL, TRUE);

        }
        break;
        case ID_RETURN: //�R���̫�ø�ϸ��
        {
            if (!Map_treepoints.empty())
                Map_treepoints.pop_back();
            else
                MessageBox(hwndDlg, L"������w�g�L����i�R��", L"���~", MB_OK);
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
        //�����ƲM���O�]���n�O�dø�s���G //�ϥΰ}�C�x�s�y�Ы� ��^�C���M��
        MapMenu_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF(0.8f, 0.8f, 0.8f, 0.8f))); // dialog �I����
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
