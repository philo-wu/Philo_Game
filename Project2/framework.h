#pragma once
// 包含基本的Windows頭檔和Direct3D頭文件
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <commdlg.h>        //讀取檔案
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
// 釋放資源
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = NULL;
    }
}

