#include "TCP_Client.h"
#include "Dialog_Login.h"

#include <QtWidgets/QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCP_Client w;


    return a.exec();
}
