#include "TCP_Client.h"
#include "Dialog_Login.h"

#include <QtWidgets/QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Dialog_Login login (&w);

    //login.show();
    QTimer::singleShot(0, &a, [&]() {
        //qDebug() << "Qt 初始化完成，現在執行程式碼";
        TCP_Client w;    
        w.show();
        });


    return a.exec();
}
