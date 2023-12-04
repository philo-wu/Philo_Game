#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCP_Client.h"

class TCP_Client : public QMainWindow
{
    Q_OBJECT

public:
    TCP_Client(QWidget *parent = nullptr);
    ~TCP_Client();

private:
    Ui::TCP_ClientClass ui;
};
