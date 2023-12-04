#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCP_Server.h"

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>



class TCP_Server : public QMainWindow
{
    Q_OBJECT

public:
    TCP_Server(QWidget *parent = nullptr);
    ~TCP_Server();

private:
    Ui::TCP_ServerClass ui;
};
