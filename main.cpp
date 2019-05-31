#include "mainwindow.h"
#include <QApplication>
//#include <Log/Log.h>
#include <QApplication>
#include <QTranslator>
#include <QLabel>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    LogInit();
    MainWindow w;
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    w.setSizePolicy(sizePolicy);
    w.setWindowOpacity(1);
//    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setMinimumSize(QSize(950, 520));
    w.setMaximumSize(QSize(950, 520));
    w.setWindowTitle("S100 - C100 Record Management");
    w.setWindowIcon(QIcon("Realy.ico"));
    w.show();

    return a.exec();
}
