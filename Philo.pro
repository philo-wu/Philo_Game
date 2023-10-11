QT += core gui axcontainer
greaterThan(QT_MAJOR_VERSION, 4 ): QT += widgets
CONFIG+=precompile_header

TARGET = ExcelToJson

TEMPLATE = app

SOURCES +=  main.cpp \
            ExcelToJson/mainwindow.cpp

HEADERS += \
    ExcelToJson/mainwindow.h

FORMS += \
    ExcelToJson/mainwindow.ui

msvc{
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
