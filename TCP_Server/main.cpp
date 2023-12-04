#include "TCP_Server.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCP_Server w;
    w.show();
    return a.exec();
}
