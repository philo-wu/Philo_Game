#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qfiledialog.h>
#include <ActiveQt/qaxobject.h>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTranslator>
#include <QTextCodec>
#include <QApplication>
#include <QLocale>
#include <QTableWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString out_folderPath = "./Json/";
    void loadExcelToTableWidget(QTableWidget* tableWidget, const QString& filePath);
    void saveJson(QJsonDocument jsonDoc , QString filepath);
    bool isValid(QString qstr, QString type);

private slots:

    void on_pushButton_change_clicked();

    void on_pushButton_select_clicked();

    void on_pushButton_show_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
