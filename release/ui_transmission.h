/********************************************************************************
** Form generated from reading UI file 'transmission.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSMISSION_H
#define UI_TRANSMISSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_Transmission
{
public:
    QProgressBar *progressBar;
    QLabel *Transmission_Count;

    void setupUi(QDialog *Transmission)
    {
        if (Transmission->objectName().isEmpty())
            Transmission->setObjectName(QStringLiteral("Transmission"));
        Transmission->resize(950, 520);
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        Transmission->setFont(font);
        Transmission->setModal(false);
        progressBar = new QProgressBar(Transmission);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(410, 230, 521, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(18);
        progressBar->setFont(font1);
        progressBar->setValue(24);
        Transmission_Count = new QLabel(Transmission);
        Transmission_Count->setObjectName(QStringLiteral("Transmission_Count"));
        Transmission_Count->setEnabled(true);
        Transmission_Count->setGeometry(QRect(440, 260, 471, 41));
        QFont font2;
        font2.setFamily(QStringLiteral("Times New Roman"));
        font2.setPointSize(16);
        font2.setBold(false);
        font2.setWeight(50);
        Transmission_Count->setFont(font2);

        retranslateUi(Transmission);

        QMetaObject::connectSlotsByName(Transmission);
    } // setupUi

    void retranslateUi(QDialog *Transmission)
    {
        Transmission->setWindowTitle(QApplication::translate("Transmission", "Dialog", Q_NULLPTR));
        Transmission_Count->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Transmission: public Ui_Transmission {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSMISSION_H
