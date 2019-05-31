#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <QStandardItem>
#include <QDateTime>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QVector>
#include <QPen>
#include <QTimer>
#include <QMessageBox>
#include <command.h>
#include "common/CRC16.h"
#include "QFile"

#include "xlsxformat.h"
#include "xlsxformat_p.h"
#include "transmission.h"

//#include "project_file.h"
namespace Ui {
class MainWindow;
}

/******************************************************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int CommandSend(int cmdDataNum, quint8 cmdType, quint8 cmdCode, quint8* bypass);

private slots:
    void on_Connect_Btn_clicked();
    void ReadData();
    void SearchPort();
    void Rrrorhandle(QSerialPort::SerialPortError a);
    uint8 Save_Data(uint16 strip_All);

    void on_Read_Record_clicked();

    void Display_StripNum(quint16 Test_Count);

    void on_Clear_clicked();

private:
    Ui::MainWindow *ui;
    QString path;

    QTimer *SearchPortT;                    //刷新端口定时器

    QStandardItemModel *dataModel;

    QSerialPort *SerialPort;                //传输绑定的端口
    QSerialPort *SerialPort2;               //刷新端口绑定的端口
    quint8 cmdBuffer[200];
    quint8 Result[300000];
    quint8 Device_Type;
    Transmission *Progress;

    uint8 commandType;
    uint8 commandCode;

    int contReceive = 0;
    int respLength = 0;
    int bytesReceived = 0;
    int getResponse = 0;

    int OFFSET_HEADER = 0;
    int OFFSET_LEN_LO = 1;
    int OFFSET_LEN_HI = 2;
    int OFFSET_CMD_TYPE = 3;
    int OFFSET_CMD_CODE = 4;
    int OFFSET_CMD_DATA = 5;

    int LEN_HEAD_LENGTH = 3;
    int LEN_HEAD_TAIL = 2;
};

/******************************************************************************/
typedef struct {
    uint16 year;
    uint8 month;
    uint8 day;
    uint8 hour;
    uint8 min;
} STORAGE_TIME;

/******************************************************************************/
typedef struct {
   char TName[8];
   uint8 Switch_Bool;
   float threshold1;
   float threshold2;
   float threshold3;
   char Result[6];
} STORAGE_SINGLE_LINE;

/******************************************************************************/
typedef struct {
    char Product_name[20];
    char Product_SN[10];
    uint8 StripNum;
    STORAGE_TIME Product_Time;
    STORAGE_SINGLE_LINE CH_data[17];
} STORAGE_SINGLE_DATA_STRUCT;

/******************************************************************************/
typedef struct {
    STORAGE_SINGLE_DATA_STRUCT Result_Data[501];

} RESULT_DATA_STRUCT;

extern RESULT_DATA_STRUCT Storage_Data;


#endif // MAINWINDOW_H
