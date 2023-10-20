#pragma once
// 包含基本的Windows頭檔和Direct3D頭文件

#include <afxwin.h>  // 包含 MFC 的主要頭文件
#include <windows.h>
#include <windowsx.h>


#include <CommCtrl.h>/*
#include <commdlg.h>  */      //讀取檔案
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

#include "Common.h"             //自定義指令
#include "nlohmann/json.hpp"    //Json
#include <fstream>
#include <atlimage.h>  

#include <shobjidl.h>
#include <filesystem>

#pragma warning(disable : 4996)  //std::wstring_convert C++17中不推薦使用,並以報錯方式提醒, 以此忽略此報錯

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

