#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ExcelToJson.h"

class ExcelToJson : public QMainWindow
{
    Q_OBJECT

public:
    ExcelToJson(QWidget *parent = nullptr);
    ~ExcelToJson();

private:
    Ui::ExcelToJsonClass ui;
};
