#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qstringliteral.h"

#define HEADER_ROW 1 //為excel標頭檔第一列

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
void MainWindow::loadExcelToTableWidget(QTableWidget *tableWidget, const QString &filePath)
{
    // 用以紀錄這份檔案不符合資料型別的地方
    int error_time = 0;
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
    QJsonObject header_type;
    QJsonObject header_en;
    QJsonObject header_showkey;

    for (int colIndex = 1; colIndex <= columnCount; ++colIndex)
    {
        QAxObject* cell_header  = usedRange->querySubObject("Cells(int,int)", HEADER_ROW   , colIndex);
        QAxObject* cell_type    = usedRange->querySubObject("Cells(int,int)", HEADER_ROW +1, colIndex);
        QAxObject* cell_en      = usedRange->querySubObject("Cells(int,int)", HEADER_ROW +2, colIndex);
        QAxObject* cell_showkey = usedRange->querySubObject("Cells(int,int)", HEADER_ROW +3, colIndex);

        QVariant cell_header_Value  = cell_header->property("Value");
        QVariant cell_type_Value    = cell_type->property("Value");
        QVariant cell_en_Value      = cell_en->property("Value");
        QVariant cell_showkey_Value = cell_showkey->property("Value");

        // 如果儲存格有值
        if (!cell_header_Value.toString().isEmpty())
        {
            QString name = QString::number(colIndex);
            header[name] = cell_header_Value.toString();
        }
        // 先進行型別判斷
        if (!cell_en_Value.toString().isEmpty())
        {
            QString name = QString::number(colIndex);
            header_type[name] = cell_en_Value.toString();
        }

        if (!cell_type_Value.toString().isEmpty())
        {
            QString name = QString::number(colIndex);
            header_en[name] = cell_type_Value.toString();
        }
        // 如果為"開關功能"的英文,預設為空,在此也輸入為"open"
        //else if (header_type[QString::number(colIndex)] == "open")
        else if (cell_en_Value.toString() == "open")
        {
            QString name = QString::number(colIndex);
            header_en[name] = "open";
        }
        if (!cell_showkey_Value.toString().isEmpty())
        {
            QString name = QString::number(colIndex);
            header_showkey[name] = cell_showkey_Value.toString();
        }
    }

    // 顯示資料
    QJsonDocument doc1(header);
    QJsonDocument doc2(header_type);
    QJsonDocument doc3(header_en);
    QJsonDocument doc4(header_showkey);

    qDebug() << doc1.toJson(QJsonDocument::Indented);
    qDebug() << doc2.toJson(QJsonDocument::Indented);
    qDebug() << doc3.toJson(QJsonDocument::Indented);
    qDebug() << doc4.toJson(QJsonDocument::Indented);

    QJsonArray dataArray_CS;
    QJsonArray dataArray_C;
    QJsonArray dataArray_S;

    for (int rowumnIndex = HEADER_ROW+4; rowumnIndex <= rowCount; ++rowumnIndex)
    {
        QJsonObject row_data_CS;
        QJsonObject row_data_C;
        QJsonObject row_data_S;

        for (int colIndex = columnCount; colIndex >= 1; --colIndex)
        {
            QAxObject* cell = usedRange->querySubObject("Cells(int,int)", rowumnIndex, colIndex);
            QVariant cellValue = cell->property("Value");

            // 如果儲存格有值，則將資料加入到 Json 中
            if (!cellValue.toString().isEmpty())
            {
                QString key = QString::number(colIndex);
                QString showkey = header_showkey[key].toString();
                QString name = header_en[key].toString();

                if (showkey == "CS" || showkey == "SC")
                {
                    // 顯示在Client與Server
                    row_data_CS[name] = cellValue.toString();
                    row_data_C[name] = cellValue.toString();
                    row_data_S[name] = cellValue.toString();
                }
                else if (showkey == "C")
                {
                    // 只顯示在Client
                    row_data_CS[name] = cellValue.toString();
                    row_data_C[name] = cellValue.toString();
                }
                else if (showkey == "S")
                {
                    // 只顯示在Server
                    row_data_CS[name] = cellValue.toString();
                    row_data_S[name] = cellValue.toString();
                }
                else if (showkey == "PS")
                {
                    // PS為資料不顯示
                }
            }
        }
        dataArray_CS.append(row_data_CS);
        dataArray_C.append(row_data_C);
        dataArray_S.append(row_data_S);
    }

    //data["data"] = dataArray;
    //QJsonArray sortedArray;
    //for (const QJsonValue& value : dataArray)
    //{
    //    QJsonObject sortedObject;
    //    sortedObject["taskid"] = value.toObject()["taskid"];
    //    sortedObject["reward"] = value.toObject()["reward"];
    //    sortedObject["open"] = value.toObject()["open"];
    //    sortedObject["content"] = value.toObject()["content"];
    //    sortedObject["condparm2"] = value.toObject()["condparm2"];
    //    sortedObject["condparm1"] = value.toObject()["condparm1"];
    //    sortedObject["condition"] = value.toObject()["condition"];
    //    sortedObject["condcnt"] = value.toObject()["condcnt"];
    //    sortedArray.append(sortedObject);
    //}

    QJsonDocument jsonDoc_CS(dataArray_CS);
    QJsonDocument jsonDoc_C(dataArray_C);
    QJsonDocument jsonDoc_S(dataArray_S);

    //在資料夾中存成Json
    QString JsonPath = out_folderPath + "Client_Server.json";
        //"./Json/Client_Server.json";
    saveJson(jsonDoc_CS, JsonPath);
    JsonPath = out_folderPath + "Client.json";
    saveJson(jsonDoc_C, JsonPath);
    JsonPath = out_folderPath + "Server.json";
    saveJson(jsonDoc_S, JsonPath);

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
                if (rowumnIndex >= 5 &&
                    !isValid(cellValue.toString(), header_type[QString::number(colIndex)].toString())
                    )
                {
                    item->setForeground(QBrush(QColor(Qt::red)));
                    ++error_time;
                }
                tableWidget->setItem(rowumnIndex - 1, colIndex - 1, item);

            }
        }
    }

    // 設置水平標題 //水平標題暫不使用
    //QStringList headers;
    //for (int i = 1; i <= columnCount; ++i)
    //{
    //    QAxObject *headerCell = usedRange->querySubObject("Cells(int,int)", 1, i);
    //    QVariant headerValue = headerCell->property("Value");
    //    headers << headerValue.toString();
    //}
    //tableWidget->setHorizontalHeaderLabels(headers);

    // 設置垂直標題
    QStringList verticalHeaders = {"中文名稱","英文名稱","資料型別","顯示縮寫"};
    for (int i = 5; i <= rowCount; ++i)
    {
        // 不以資料內容作為標題
        //QAxObject* headerCell = usedRange->querySubObject("Cells(int,int)", i, 1);
        //QVariant headerValue = headerCell->property("Value");
        verticalHeaders << QString::number(i-4);
    }
    tableWidget->setVerticalHeaderLabels(verticalHeaders);

    // 調整列寬以確保資料正確顯示
    tableWidget->resizeColumnsToContents();
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 设置水平头部为拉伸模式

    // 關閉工作簿和退出 Excel
    workbook->dynamicCall("Close()");
    excel.dynamicCall("Quit()");

    if (error_time > 0)
    {
        QString text = "有 " + QString::number(error_time) + " 個單元格不符合資料型別";
        QMessageBox::information(this, "錯誤", text);
    }
}


void MainWindow::on_pushButton_change_clicked()
{
    out_folderPath = QFileDialog::getExistingDirectory(NULL, QStringLiteral("選擇資料夾"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString showtext = "輸出路徑為:" + out_folderPath;
    ui->label_out_folderPath->setText(showtext);
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



void MainWindow::saveJson(QJsonDocument jsonDoc, QString filepath) 
{
    QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // 將 JSON 字串寫入檔案
        qDebug() << "打開檔案進行寫入";

        QTextStream out(&file);
        out << jsonString;

        // 關閉檔案
        file.close();
    }
    else
    {
        qDebug() << "無法打開檔案進行寫入";
    }
}
//檢查單元格內資料是否符合資料型別
bool MainWindow::isValid(QString qstr ,QString type)
{
    bool ok = false;
    int typekey;
    if (type == "uint") // 整數
    {
        qstr.toUInt(&ok);
    }
    else if (type == "open") // 0與1
    {
        if (qstr.toInt() == 1 || qstr.toInt() == 0)
            ok = true;
    }
    else if (type == "string")
    {
        ok = true;//string不用判斷
    }
    else if (type == "char")
    {
        QByteArray byteArray = qstr.toUtf8();
        const char* Char = byteArray.constData();
        if (Char) {
            ok = true;
        }
        else {
            ok = false;
        }
    }
    return ok;  

    
}