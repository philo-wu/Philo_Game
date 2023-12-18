#include "Dialog_face.h"
#include <QtGui>

Dialog_face::Dialog_face(QWidget *parent): 
    QDialog(parent),
    ui(new Ui::Dialog_faceClass())

{
	ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    int rowSize = 11;
    int colSize = 12;
    ui->faceTable_1->setColumnCount(rowSize);
    ui->faceTable_1->setRowCount(colSize);

    char32_t  t[] = { 0x1F601,0x0 };	//加上0x00是为了防止表情后面跟随乱码
    for (int i = 0; i < colSize; i++)
    {
        for (int j = 0; j < rowSize; j++)
        {
            t[0] = 0x1F601 + i * rowSize + j;
            QTableWidgetItem* faceItem = new QTableWidgetItem(QString::fromUcs4(t));
            ui->faceTable_1->setItem(i, j, faceItem);
        }
    }

    ui->faceTable_2->setColumnCount(rowSize);
    ui->faceTable_2->setRowCount(colSize);
    for (int i = 0; i < colSize; i++)
    {
        for (int j = 0; j < rowSize; j++)
        {
            t[0] = 0x1F601 + i * rowSize + j +132;
            QTableWidgetItem* faceItem = new QTableWidgetItem(QString::fromUcs4(t));
            ui->faceTable_2->setItem(i, j, faceItem);
        }
    }
    ui->stackedWidget->setCurrentIndex(0);

}

Dialog_face::~Dialog_face()
{
    delete ui;
}


void Dialog_face::changeEvent(QEvent* e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Dialog_face::on_foreButton_clicked()
{
    ui->stackedWidget->setCurrentIndex((ui->stackedWidget->currentIndex() - 1 + ui->stackedWidget->count()) % ui->stackedWidget->count());
}

void Dialog_face::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex((ui->stackedWidget->currentIndex() + 1) % ui->stackedWidget->count());
}

void Dialog_face::on_faceTable_1_cellClicked(int row, int column)
{
    emit catchFace(row, column, 0);
}

void Dialog_face::on_faceTable_2_cellClicked(int row, int column)
{
    emit catchFace(row, column, 1);
}

void Dialog_face::on_faceTable_2_cellDoubleClicked(int row, int column)
{
    //emit catchFace(row, column, 0);

}
void Dialog_face::on_faceTable_1_cellDoubleClicked(int row, int column)
{
    //emit catchFace(row, column, 1);
}

