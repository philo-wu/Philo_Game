#pragma once

#include "Direct2D.h"
//#include "Direct3D.h"
#include "framework.h"
#include "Food.h"
#include "Snake.h"

#ifndef MIAN
#define MIAN
// �����n��
HWND hWnd; // �u�NW�j�g�קK���~�I�s
//  ���s�ŧi
HWND Load_Button;
HWND Clean_Button;
HWND Start_Button;
HWND Difficulty_Button;
HWND Score_Button;
HWND End_Button;

// ��ƭ쫬
void OpenFile(void);
void DrawBitmap();
void ClearDraw();
void OnClick(int mouseX, int mouseY); //�g�Y�D�ϥΤ���
void OnPaint(HWND hWnd);
void ShowButton(bool);

//  �ŧiWindowProc
LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam);


#endif // MIAN