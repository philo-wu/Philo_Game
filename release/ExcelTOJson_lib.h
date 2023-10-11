#pragma once

# if defined ExcelTOJson_lib
#  define ExcelTOJson_lib_EXPORT Q_DECL_EXPORT
# else
#  define ExcelTOJson_lib_EXPORT Q_DECL_IMPORT
# endif

#include "exceltojson_lib_global.h"

class EXCELTOJSON_LIB_EXPORT ExcelTOJson_lib
{
public:
    ExcelTOJson_lib();
};
