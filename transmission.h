#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QDialog>

namespace Ui {
class Transmission;
}

class Transmission : public QDialog
{
    Q_OBJECT

public:
    explicit Transmission(QWidget *parent = 0);
    ~Transmission();

    quint8 Transmission_Progress(quint16 setValue,quint16 Maximum);
    void Progress_Closed();

private:
    Ui::Transmission *ui;
};

#endif // TRANSMISSION_H
