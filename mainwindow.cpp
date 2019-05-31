#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QRegExp"
#include "project_file.h"
#include "QAxObject"
#include "transmission.h"

/******************************************************************************/
RESULT_DATA_STRUCT Storage_Data;
Q_DECLARE_METATYPE(STORAGE_SINGLE_DATA_STRUCT)

/******************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SerialPort = new QSerialPort(this);
    SerialPort2 = new QSerialPort(this);

    dataModel = new QStandardItemModel();

    SerialPort->setDataBits(QSerialPort::Data8);
    SerialPort->setParity(QSerialPort::NoParity);
    SerialPort->setStopBits(QSerialPort::OneStop);
    SerialPort->setBaudRate(115200);
    connect(SerialPort,SIGNAL(readyRead()),this,SLOT(ReadData()));

    SearchPortT = new QTimer;
    SearchPortT->setInterval(200);
    connect(SearchPortT, SIGNAL(timeout()), this, SLOT(SearchPort()));
    SearchPortT->start(100);

    connect(SerialPort,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this,SLOT(Rrrorhandle(QSerialPort::SerialPortError)));

    ui->Connect_Btn->setText("Connect\r\n连接");
    ui->Read_Record->setText("Read Record\n读取记录");
    ui->Clear->setText("Clear Record\n清除记录");

    Progress = new Transmission;
}

/******************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/******************************************************************************/
void MainWindow::Rrrorhandle(QSerialPort::SerialPortError ror)
{
    qDebug()<<ror;
}

/******************************************************************************/
/*连接*/
void MainWindow::on_Connect_Btn_clicked()
{
    if(ui->Connect_Btn->text()==tr("Connect\r\n连接"))
    {
        if(ui->Connect_Btn->text()==tr("Connect\r\n连接"))
        {
            SerialPort->setPortName(ui->COMSelectcomboBox->currentText());
            SerialPort->setFlowControl(QSerialPort::NoFlowControl);
            if(SerialPort->open(QIODevice::ReadWrite))
            {
                ui->Connect_Btn->setText("Disconnected\r\n断开");
                ui->COMSelectcomboBox->setEnabled(false);
                SearchPortT->stop();
            }
            else
            {
                QMessageBox::warning(this,tr("警告"),tr("打开串口失败\r\n该串口被占用或者未选择正确的串口"));
            }
        }
    }
    else
    {
        ui->Connect_Btn->setText("Connect\r\n连接");
        ui->COMSelectcomboBox->setEnabled(true);
        SerialPort->clear();
        SerialPort->close();
        SearchPortT->start();
        ui->lineEdit->setText("0");
    }
}

/******************************************************************************/
/*串口插入添加，拔出清除*/
void MainWindow::SearchPort()
{
    QStringList ComList;
    QList<int> Index;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {

        SerialPort2->setPort(info);
        SerialPort2->open(QIODevice::ReadWrite);
        ComList += SerialPort2->portName();
        SerialPort2->clear();
        SerialPort2->close();
    }
    for(int i=0;i< ComList.length();i++)
    {
       for(int j=0;j< ui->COMSelectcomboBox->count();j++)
       {
           if(ComList.at(i) == ui->COMSelectcomboBox->itemText(j))
           {
               Index.append(i);
               break;
           }
           else
           {
           }
        }
    }
    for(int i=0;i< ComList.length();i++)
    {
        if(Index.contains(i))
        {
        }
        else
        {
          ui->COMSelectcomboBox->addItem(ComList.at(i));
         qDebug("add");
        }
    }

    //拔出清除
    for(int i=0;i<ui->COMSelectcomboBox->count();i++)
    {
        if(ComList.contains(ui->COMSelectcomboBox->itemText(i)))
        {

        }
        else
        {
            ui->COMSelectcomboBox->removeItem(i);
            qDebug("rm ");
        }
    }
}

/***********************************************************************************************
*函数名: CommandSend
*函数功能描述:串口发送函数
*函数参数:无
*函数返回值: 无
***********************************************************************************************/
int MainWindow::CommandSend(int cmdDataNum, quint8 cmdType, quint8 cmdCode, quint8* bypass)
{
    int SIZE_LEN_HEAD_CMD_CRC = 6;
    uint16 totalPackageLength = SIZE_LEN_HEAD_CMD_CRC + cmdDataNum + 2;
    uint16 packageLength = SIZE_LEN_HEAD_CMD_CRC + cmdDataNum;
    uint16 crcCal = 0;
    QString str;

    /* Head */
    cmdBuffer[OFFSET_HEADER] = (char)'$';

    /* Package length */
    cmdBuffer[OFFSET_LEN_LO] = (uint8)(packageLength & 0x00FF);
    cmdBuffer[OFFSET_LEN_HI] = (uint8)((packageLength & 0xFF00)>>8);

    /* Command type and code */
    cmdBuffer[OFFSET_CMD_TYPE] = cmdType;
    cmdBuffer[OFFSET_CMD_CODE] = cmdCode;
    memcpy(&cmdBuffer[OFFSET_CMD_DATA],bypass,cmdDataNum);

    /* Calculate CRC, exclude 2-bytes crc value */
    crcCal = CRC16_Calculate(cmdBuffer, (uint32)(packageLength - 2), 0xFFFF, 0);

    /* CRC */
    cmdBuffer[OFFSET_CMD_DATA + cmdDataNum] = crcCal& 0x00FF;
    cmdBuffer[OFFSET_CMD_DATA + cmdDataNum + 1] = (crcCal & 0xFF00)>>8;

    /* Tail */
    cmdBuffer[OFFSET_CMD_DATA + cmdDataNum + 2] = (char)'#';
    QByteArray data = QByteArray((const char*)cmdBuffer,totalPackageLength);

    QString Str;
    for(int i = 0; i < data.length(); i++)
    {
       Str.append(tr("%1").arg(data[i]&0xFF,2, 16, QLatin1Char('0')).toUpper() + QString(" "));
    }
    qDebug()<<Str;
    Str.clear();

    if(ui->Connect_Btn->text() == tr("Disconnected\r\n断开"))
    {
        if(!SerialPort->write(data))
        {
            qDebug("发送失败！");
        }
    }
    else
    {
        QMessageBox::warning(this,tr("串口问题"),tr("串口未连接，请先连接串口。"));
    }
    return 0;
}

/******************************************************************************/
void MainWindow::ReadData()
{
    static QByteArray ReadBuff;
    static QByteArray ReadBuff_All;
    quint8  stdid,RecvBuff[4096];
    quint16 Datalength = 0,Total_Length = 0,test_Total_Count = 0,strip_Count = 0,strip_All = 0;
    QString Str;
    ReadBuff_All = SerialPort->readAll();
//    ReadBuff.append(SerialPort->readAll());

    /* 先拼接数据，得到完整数据，否则就退出舍弃本次数据 */
    if(ReadBuff_All[0] != '$')
    {
        if(ReadBuff[0] != '$')
        {
            ReadBuff.clear();
            ReadBuff_All.clear();
            return;
        }
        else
        {
            ReadBuff.append(ReadBuff_All);
            if(ReadBuff[(ReadBuff.length() - 1)] != '#')
            {
                return;
            }
        }
    }
    else
    {
        ReadBuff.clear();
        if(ReadBuff_All[(ReadBuff_All.length() - 1)] != '#')
        {
            ReadBuff.append(ReadBuff_All);
            return;
        }
        else
        {
            ReadBuff.append(ReadBuff_All);
        }
    }

    /* 对符合要求的数据进行处理 */
    memset(RecvBuff,0,4096);
    memcpy(&RecvBuff[0],ReadBuff,ReadBuff.length());
    Total_Length = ReadBuff.length();
    ReadBuff.clear();

    for(int i = 0; i < Total_Length; i++)
    {
       Str.append(tr("%1").arg(RecvBuff[i]&0xFF,2, 16, QLatin1Char('0')).toUpper() + QString(" "));
    }
    qDebug()<<Str;
    Str.clear();
    memcpy(&Datalength,&RecvBuff[1],2);
    stdid = RecvBuff[4];
    switch(stdid)
    {
    case APP_RECORD_COUNT:
        memcpy(&test_Total_Count,&RecvBuff[OFFSET_CMD_DATA],2);
        memcpy(&Device_Type,&RecvBuff[OFFSET_CMD_DATA + 2],1);
        Display_StripNum(test_Total_Count);
        /* 进度条显示  */
        if((test_Total_Count != 0) &&(test_Total_Count != 65535))
        {
            Progress->Transmission_Progress(0, 500);
            Progress->exec();
        }
        break;

    case APP_SEEK_RECORD:
        memcpy(&strip_Count,&RecvBuff[5],2);
        memcpy(&strip_All,&RecvBuff[7],2);
        if(strip_Count == 1)
        {
            memset(&Storage_Data,0,sizeof(RESULT_DATA_STRUCT));
            memcpy(&Storage_Data.Result_Data[strip_Count],&RecvBuff[9],sizeof(STORAGE_SINGLE_DATA_STRUCT));
        }
        else
        {
            memcpy(&Storage_Data.Result_Data[strip_Count],&RecvBuff[9],sizeof(STORAGE_SINGLE_DATA_STRUCT));
        }

        if(Progress->Transmission_Progress(strip_Count, strip_All) == strip_All)
        {
            Progress->Progress_Closed();
        }

        if(strip_Count == strip_All)
        {
            Save_Data(strip_All);
        }
        break;

        default:
        break;
    }
    ReadBuff.clear();
    return;
}

/******************************************************************************/
void MainWindow::on_Read_Record_clicked()
{
    quint8 DATA = 0;
    if((QMessageBox::question(this,tr("警告"),tr("Please confirm that the instrument test is completed."
                                               "\nInstruments will not be operational!\n"
                                               "请确认测试已完成，且读取时仪器不可操作！"))) == QMessageBox::Yes)
    {
       CommandSend(1,CMD_TYPE_APP, APP_SEEK_RECORD,&DATA);
    }
}

/******************************************************************************/
void MainWindow::Display_StripNum(quint16 Test_Count)
{
    (Test_Count == 65535)?(ui->lineEdit->setText("0")):ui->lineEdit->setText(tr("%3").arg(Test_Count));
}

/******************************************************************************/
void MainWindow::on_Clear_clicked()
{
    quint8 DATA = 1;
    cmdBuffer[OFFSET_CMD_DATA] = 1;
    QMessageBox msg(this);                                           //对话框设置父组件
    msg.setWindowTitle("Warm reminder:");                            //对话框标题
    msg.setText("Clear all records in the instrument！\n清除仪器内所有记录！");                        //对话框提示文本
    msg.setIcon(QMessageBox::Information);                           //设置图标类型
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox:: Cancel);  //对话框上包含的按钮

    if(msg.exec() == QMessageBox::Ok)                                //模态调用
    {
       CommandSend(1,CMD_TYPE_APP,APP_CLEAR_RECORD,&DATA);           //数据处理
    }
}

/******************************************************************************/
uint8 MainWindow::Save_Data(uint16 strip_All)
{
    QFile file;
    quint16 Write_X,Write_Y,Reagent_Count;
    QString timePoint = QDateTime::currentDateTime().toString("yyyy-MM-dd HH-mm-ss");
    if(Device_Type == 1)
    {
       path = QString("Data/Record-S100-%2").arg(timePoint);
    }

    if(Device_Type == 2)
    {
       path = QString("Data/Record-C100-%2").arg(timePoint);
    }

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save File"),
            path,
            tr("Config Files (*.xlsx)"));
    QXlsx::Document xlsx;
    QDir dir;
    dir.cd(QDir::currentPath());
    if(!dir.exists("Data"))
    {
        dir.mkdir("Data");
    }

    /* 设置第一列单元格宽度 */
    xlsx.setColumnWidth(1,1,18);
    /* 设置第二列单元格宽度 */
    xlsx.setColumnWidth(2,2,14);
    /* 设置第三列单元格宽度 */
    xlsx.setColumnWidth(3,3,23);
    /* 设置第四列单元格宽度 */
    xlsx.setColumnWidth(4,4,8);
    /* 设置第五、六列单元格宽度 */
    xlsx.setColumnWidth(5,6,15);

    QXlsx::Format format1;                           /* 设置该单元的样式1 */
    format1.setFontColor(QColor(Qt::black));         /* 文字为黑色 */
    format1.setFontSize(13);                         /*设置字体大小  15*/
    format1.setFontName("Time New Roman");
    format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    format1.setVerticalAlignment(QXlsx::Format::AlignVCenter);

    QXlsx::Format format2;                           /* 设置该单元的样式2 */
    format2.setFontColor(QColor(Qt::red));           /* 文字为红色 */
    format2.setFontSize(12);                         /*设置字体大小  12*/
    format2.setFontName("Time New Roman");
    format2.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    format2.setVerticalAlignment(QXlsx::Format::AlignVCenter);

    QXlsx::Format format3;                           /* 设置该单元的样式3 */
    format3.setFontColor(QColor(Qt::black));           /* 文字为黑色 */
    format3.setFontSize(13);                         /*设置字体大小  14*/
    format3.setFontName("Time New Roman");
    format3.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    format3.setVerticalAlignment(QXlsx::Format::AlignVCenter);


    QXlsx::Format format4;                           /* 设置该单元的样式4 */
    format4.setFontColor(QColor(Qt::black));           /* 文字为黑色 */
    format4.setFontSize(15);                         /*设置字体大小*/
    format4.setFontName("Time New Roman");
    format4.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    format4.setVerticalAlignment(QXlsx::Format::AlignVCenter);

    /* 设置边框 */
    QXlsx::Format format5;
    format5.setBottomBorderStyle(QXlsx::Format::BorderThick);/*边框样式*/

    /********************************编写第一行内容*********************************/
    xlsx.write(1,1,"Test Name",format4);
    xlsx.write(1,2,"SN",format4);
    xlsx.write(1,3,"Test Time",format4);
    xlsx.write(1,4,"Count",format4);
    xlsx.write(1,5,"Item",format4);
    xlsx.write(1,6,"Result",format4);

    /*****************从结构体数组里取出相应的数据写入Excel里面************************/
    for(Reagent_Count = 1;Reagent_Count <= strip_All;Reagent_Count++)
    {
        Write_X = (Reagent_Count == 1)?2:(Write_X + 1);
        Write_Y = 1;

        /************************测试名称显示*******************************************/
        QString value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].Product_name);
        xlsx.write(Write_X,Write_Y,value,format1);

        /************************批号显示*********************************************/
        value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].Product_SN);
        Write_Y = 2;
        xlsx.write(Write_X,Write_Y,value,format1);

        /*************************测试时间显示******************************************/
        char Date[20];
        memset(Date,0,sizeof(Date));
        sprintf(Date,"%04d/%02d/%02d %02d:%02d",Storage_Data.Result_Data[Reagent_Count].Product_Time.year,
                Storage_Data.Result_Data[Reagent_Count].Product_Time.month,
                Storage_Data.Result_Data[Reagent_Count].Product_Time.day,
                Storage_Data.Result_Data[Reagent_Count].Product_Time.hour,
                Storage_Data.Result_Data[Reagent_Count].Product_Time.min);
        value = QString::fromLocal8Bit(Date);
        Write_Y = 3;
        xlsx.write(Write_X,Write_Y,value,format3);

         /************************试剂条名称与结果显示************************************/
        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[0].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[0].TName);
            Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[0].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"1",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[1].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[1].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[1].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"2",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[2].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[2].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[2].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"3",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[3].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[3].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[3].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"4",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[4].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[4].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[4].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"5",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[5].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[5].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[5].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"6",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[6].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[6].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[6].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"7",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[7].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[7].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[7].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"8",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[8].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[8].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[8].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"9",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[9].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[9].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[9].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"10",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[10].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[10].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[10].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"11",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[11].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[11].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[11].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"12",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[12].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[12].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[12].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"13",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[13].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[13].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[13].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"14",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[14].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[14].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[14].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"15",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[15].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[15].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[15].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"16",format2);
        }

        if(!(Storage_Data.Result_Data[Reagent_Count].CH_data[16].Result[0] == '\0'))
        {
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[16].TName);
            Write_X += 1;Write_Y = 5;
            xlsx.write(Write_X,Write_Y,value,format2);
            value = QString::fromLocal8Bit(Storage_Data.Result_Data[Reagent_Count].CH_data[16].Result);
            Write_Y = 6;
            xlsx.write(Write_X,Write_Y,value,format2);
            Write_Y = 4;
            xlsx.write(Write_X,Write_Y,"17",format2);
        }
        Write_X += 1;
    }
    xlsx.saveAs(fileName);
    file.close();
    return 0;
}
