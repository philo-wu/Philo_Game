#include "TCP_Client.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCP_Client w;
    w.show();
    return a.exec();
}
