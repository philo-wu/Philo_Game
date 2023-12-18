#pragma once

#include <QDialog>
#include "ui_Dialog_face.h"

class Dialog_face : public QDialog
{
	Q_OBJECT

public:
	Dialog_face(QWidget *parent = nullptr);
	~Dialog_face();


protected:
    void changeEvent(QEvent* e);

private:
    Ui::Dialog_faceClass *ui;

private slots:
    void on_faceTable_2_cellClicked(int row, int column);
    void on_faceTable_1_cellClicked(int row, int column);
    void on_backButton_clicked();
    void on_foreButton_clicked();
    void on_faceTable_2_cellDoubleClicked(int row, int column);
    void on_faceTable_1_cellDoubleClicked(int row, int column);

signals:
    void catchFace(int row, int column, int page);
};
