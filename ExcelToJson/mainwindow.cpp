#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qstringliteral.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 將 Excel 資料載入到 QTableWidget 的函數
void loadExcelToTableWidget(QTableWidget *tableWidget, const QString &filePath)
{
    // 創建 Excel 物件
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false); // 不顯示 Excel 界面

    // 打開 Excel 檔案
    QAxObject *workbooks = excel.querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", filePath);

    if (!workbook)
    {
        qDebug() << "打開工作簿失敗";
        return;
    }

    // 獲取工作表
    QAxObject *worksheets = workbook->querySubObject("Worksheets");
    int sheetCount = worksheets->property("Count").toInt();

    // 假設只有一個工作表
    QAxObject *worksheet = worksheets->querySubObject("Item(int)", 1);

    if (!worksheet)
    {
        qDebug() << "打開工作表失敗";
        workbook->dynamicCall("Close()");
        excel.dynamicCall("Quit()");
        return;
    }

    // 獲取使用範圍
    QAxObject *usedRange = worksheet->querySubObject("UsedRange");
    QAxObject *rows = usedRange->querySubObject("Rows");
    QAxObject *columns = usedRange->querySubObject("Columns");

    // 獲取行數和列數
    int rowCount = rows->property("Count").toInt();
    int columnCount = columns->property("Count").toInt();
    //qDebug() << "rowCount" << rowCount ; //992
    //qDebug() << "columnCount" << columnCount ; //24

    // 取得實際row以及col
    for (int rowIndex = rowCount; rowIndex >= 1; --rowIndex)
    {
        QAxObject* cell = usedRange->querySubObject("Cells(int,int)", rowIndex, 1);
        QVariant cellValue = cell->property("Value");

        // 如果儲存格有值，那麼這就是最後一行
        if (!cellValue.toString().isEmpty())
        {
            qDebug() << "Last row with data: " << rowIndex;
            rowCount = rowIndex;
            break;
        }
    }
    for (int colIndex = columnCount; colIndex >= 1; --colIndex)
    {
        QAxObject* cell = usedRange->querySubObject("Cells(int,int)", 1, colIndex);
        QVariant cellValue = cell->property("Value");

        // 如果儲存格有值，那麼這就是最後一列
        if (!cellValue.toString().isEmpty())
        {
            qDebug() << "Last row with data: " << colIndex;
            columnCount = colIndex;
            break;
        }
    }
    qDebug() << "rowCount" << rowCount;
    qDebug() << "columnCount" << columnCount;

    // 包成Json
    QJsonObject header;
    for (int colIndex = columnCount; colIndex >= 1; --colIndex)
    {
        QAxObject* cell = usedRange->querySubObject("Cells(int,int)", 1, colIndex);
        QVariant cellValue = cell->property("Value");

        // 如果儲存格有值
        if (!cellValue.toString().isEmpty())
        {
            //qDebug() << "Last row with data: " << rowIndex;
            //rowCount = rowIndex;
            QString name = QString::number(colIndex);
            header[name] = cellValue.toString();
        }
    }
    QJsonDocument doc(header);
    qDebug() << doc.toJson(QJsonDocument::Indented);

    //newEntry["name"] = newName;
    //newEntry["score"] = newScore;
    //newEntry["difficulty"] = newDifficulty;
    // 
    // 設置表格的行數和列數
    tableWidget->setRowCount(rowCount);
    tableWidget->setColumnCount(columnCount);

    // 迭代每個單元格，將其值設置到表格的相應位置
    for (int rowumnIndex = 1; rowumnIndex <= rowCount; ++rowumnIndex)
    {
        for (int colIndex = 1; colIndex <= columnCount; ++colIndex)
        {
            QAxObject *cell = usedRange->querySubObject("Cells(int,int)", rowumnIndex, colIndex);
            QVariant cellValue = cell->property("Value");

            // 如果儲存格有值，則將資料加入到 QTableWidget 中
            if (!cellValue.toString().isEmpty())
            {
                // 創建 QTableWidgetItem 並設置值
                QTableWidgetItem *item = new QTableWidgetItem(cellValue.toString());
                tableWidget->setItem(rowumnIndex - 1, colIndex - 1, item);
            }
        }

    }

    // 設置水平標題
    QStringList headers;
    for (int i = 1; i <= columnCount; ++i)
    {
        QAxObject *headerCell = usedRange->querySubObject("Cells(int,int)", 1, i);
        QVariant headerValue = headerCell->property("Value");
        headers << headerValue.toString();
    }
    tableWidget->setHorizontalHeaderLabels(headers);

    // 調整列寬以確保資料正確顯示
    tableWidget->resizeColumnsToContents();
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 设置水平头部为拉伸模式

    // 關閉工作簿和退出 Excel
    workbook->dynamicCall("Close()");
    excel.dynamicCall("Quit()");
}


void MainWindow::on_pushButton_change_clicked()
{

}


void MainWindow::on_pushButton_select_clicked()
{
    //使用檔案總管選取文件
    QString readFile = QFileDialog::getOpenFileName(NULL, QStringLiteral("選擇Excel"), "", tr("Exel file(*.xls *.xlsx)"));


    loadExcelToTableWidget(ui->tableWidget_show,readFile);

}


void MainWindow::on_pushButton_show_clicked()
{

}



