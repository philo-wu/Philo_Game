#pragma once
// �]�t�򥻪�Windows�Y�ɩMDirect3D�Y���
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <commdlg.h>        //Ū���ɮ�
#include <wincodec.h>
#include <locale>


#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <wchar.h>
#include <math.h>
#include <vector>
#include <codecvt>


#include <dwrite.h>
#include <ctime>
#include <string>
#include <sstream>
#include <chrono>

#include "Common.h"
#include "nlohmann/json.hpp"
#include <fstream>

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

