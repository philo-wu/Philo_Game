#pragma once

#include "Direct2D.h"
//#include "Direct3D.h"
#include "framework.h"
#include "Engine.h"
#include "resource.h"

// �����n��
HWND hWnd; // �u�NW�j�g�קK���~�I�s
//  ���s�ŧi
HWND Load_Button;
HWND Clean_Button;
HWND Start_Button;
HWND Difficulty_Button;
HWND Score_Button;
HWND End_Button;

HWND hwndScrollBar;

//�e����s
//double targetFrameTime = 1.0 / 8; // �ؼШC�V�ɶ��]�o�̰��] �� 8 FPS�^
//double accumulatedTime = 0.0;

// �C������
Engine* engine;
Common* common;

IFileSaveDialog* pFileSaveDlg = NULL;


// ��ƭ쫬
void ShowButton(bool);
void InitButtom();
//  �ŧiWindowProc
LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam);


void ShowButton(bool show)
{
    if (show)
    {
        ShowWindow(Start_Button, SW_SHOW);
        ShowWindow(Difficulty_Button, SW_SHOW);
        ShowWindow(Score_Button, SW_SHOW);
        ShowWindow(End_Button, SW_SHOW);
        ShowWindow(Clean_Button, SW_SHOW);

    }
    else
    {
        ShowWindow(Start_Button, SW_HIDE);
        ShowWindow(Difficulty_Button, SW_HIDE);
        ShowWindow(Score_Button, SW_HIDE);
        ShowWindow(End_Button, SW_HIDE);
        ShowWindow(Clean_Button, SW_HIDE);

    }
}

void InitButtom()
{
    // �r��Τj�p
    HFONT hFont = CreateFont(
        18,                                     // �r�骺����
        0,                                      // �r�骺�e��
        0,                                      // �r�骺���ਤ��
        0,                                      // �r�骺���騤��
        FW_NORMAL,                              // �r�骺�ʲӫ�
        FALSE,                                  // �O�_�O����r��
        FALSE,                                  // �O�_�O�U���u�r��
        FALSE,                                  // �O�_�O�R���u�r��
        DEFAULT_CHARSET,                        // �r�Ŷ�
        OUT_OUTLINE_PRECIS,                     // ��X���
        CLIP_DEFAULT_PRECIS,                    // �ŵ����
        ANTIALIASED_QUALITY,                    // ��t���ƫ�
        DEFAULT_PITCH | FF_SWISS,               // �r��a�کM�r��W
        L"Verdana"                              // �r��W
    );

    SendMessage(Start_Button, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
    SendMessage(Difficulty_Button, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
    SendMessage(Score_Button, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
    SendMessage(End_Button, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
    SendMessage(Clean_Button, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

}