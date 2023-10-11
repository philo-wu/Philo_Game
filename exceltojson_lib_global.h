#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(EXCELTOJSON_LIB_LIB)
#  define EXCELTOJSON_LIB_EXPORT Q_DECL_EXPORT
# else
#  define EXCELTOJSON_LIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define EXCELTOJSON_LIB_EXPORT
#endif
