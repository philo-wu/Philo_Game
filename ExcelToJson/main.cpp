#include "ExcelToJson.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExcelToJson w;
    w.show();
    return a.exec();
}
