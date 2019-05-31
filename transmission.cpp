#include "transmission.h"
#include "ui_transmission.h"
#include "QProgressBar"

Transmission::Transmission(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transmission)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);
}

Transmission::~Transmission()
{
    delete ui;
}

quint8 Transmission::Transmission_Progress(quint16 setValue,quint16 Maximum)
{
    char Buffer[50] = {0};
    ui->progressBar->setOrientation(Qt::Horizontal);               // 水平方向
    ui->progressBar->setMinimum(0);                                // 最小值
    ui->progressBar->setMaximum(Maximum);                          // 最大值
    ui->progressBar->setValue(setValue);                           // 当前进度
    sprintf(Buffer,"正在传送......               当前进度%03d/总条数%03d",setValue,Maximum);
    ui->Transmission_Count->setText(Buffer);
    return setValue;
}

void Transmission::Progress_Closed()
{
    this->close();
}
