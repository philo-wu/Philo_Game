#pragma once
// �]�t�򥻪�Windows�Y�ɩMDirect3D�Y���

#include <afxwin.h>  // �]�t MFC ���D�n�Y���
#include <windows.h>
#include <windowsx.h>


#include <CommCtrl.h>/*
#include <commdlg.h>  */      //Ū���ɮ�
//#include <wincodec.h>
//#include <locale>
#include <iostream>/*
#include <shobjidl.h>*/


//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
//#include <wchar.h>
//#include <math.h>
//#include <vector>
#include <codecvt>


#include <ctime>
#include <string>
#include <sstream>
#include <chrono>

#include "Common.h"             //�۩w�q���O
#include "nlohmann/json.hpp"    //Json
#include <fstream>
#include <atlimage.h>  

#include <shobjidl.h>
#include <filesystem>

using json = nlohmann::json;

template<class Interface>
// ����귽
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = NULL;
    }
}

