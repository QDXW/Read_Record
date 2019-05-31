/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *Connect_Btn;
    QComboBox *COMSelectcomboBox;
    QPushButton *Clear;
    QGroupBox *groupBox;
    QPushButton *Read_Record;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(950, 520);
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Connect_Btn = new QPushButton(centralWidget);
        Connect_Btn->setObjectName(QStringLiteral("Connect_Btn"));
        Connect_Btn->setGeometry(QRect(260, 10, 181, 51));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Connect_Btn->sizePolicy().hasHeightForWidth());
        Connect_Btn->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        Connect_Btn->setFont(font);
        Connect_Btn->setStyleSheet(QStringLiteral(""));
        COMSelectcomboBox = new QComboBox(centralWidget);
        COMSelectcomboBox->setObjectName(QStringLiteral("COMSelectcomboBox"));
        COMSelectcomboBox->setGeometry(QRect(20, 10, 191, 51));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(20);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(COMSelectcomboBox->sizePolicy().hasHeightForWidth());
        COMSelectcomboBox->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(30);
        COMSelectcomboBox->setFont(font1);
        COMSelectcomboBox->setStyleSheet(QStringLiteral(""));
        COMSelectcomboBox->setIconSize(QSize(50, 50));
        Clear = new QPushButton(centralWidget);
        Clear->setObjectName(QStringLiteral("Clear"));
        Clear->setGeometry(QRect(590, 350, 221, 101));
        QFont font2;
        font2.setFamily(QStringLiteral("Times New Roman"));
        font2.setPointSize(20);
        Clear->setFont(font2);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 140, 491, 321));
        Read_Record = new QPushButton(groupBox);
        Read_Record->setObjectName(QStringLiteral("Read_Record"));
        Read_Record->setGeometry(QRect(140, 40, 221, 101));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Read_Record->sizePolicy().hasHeightForWidth());
        Read_Record->setSizePolicy(sizePolicy2);
        Read_Record->setFont(font2);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 210, 211, 91));
        QFont font3;
        font3.setFamily(QStringLiteral("Times New Roman"));
        font3.setPointSize(20);
        font3.setBold(false);
        font3.setWeight(50);
        label->setFont(font3);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Raised);
        label->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(270, 210, 191, 91));
        QFont font4;
        font4.setFamily(QStringLiteral("Times New Roman"));
        font4.setPointSize(26);
        lineEdit->setFont(font4);
        lineEdit->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Connect_Btn->setText(QApplication::translate("MainWindow", "Connect\n"
"\350\277\236\346\216\245", Q_NULLPTR));
        Clear->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        groupBox->setTitle(QString());
        Read_Record->setText(QApplication::translate("MainWindow", "Read ", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Total record times\n"
"\346\200\273\350\256\260\345\275\225\346\254\241\346\225\260", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
