/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "on_Connect_Btn_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 8), // "ReadData"
QT_MOC_LITERAL(4, 44, 10), // "SearchPort"
QT_MOC_LITERAL(5, 55, 11), // "Rrrorhandle"
QT_MOC_LITERAL(6, 67, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(7, 96, 1), // "a"
QT_MOC_LITERAL(8, 98, 9), // "Save_Data"
QT_MOC_LITERAL(9, 108, 5), // "uint8"
QT_MOC_LITERAL(10, 114, 6), // "uint16"
QT_MOC_LITERAL(11, 121, 9), // "strip_All"
QT_MOC_LITERAL(12, 131, 22), // "on_Read_Record_clicked"
QT_MOC_LITERAL(13, 154, 16), // "Display_StripNum"
QT_MOC_LITERAL(14, 171, 10), // "Test_Count"
QT_MOC_LITERAL(15, 182, 16) // "on_Clear_clicked"

    },
    "MainWindow\0on_Connect_Btn_clicked\0\0"
    "ReadData\0SearchPort\0Rrrorhandle\0"
    "QSerialPort::SerialPortError\0a\0Save_Data\0"
    "uint8\0uint16\0strip_All\0on_Read_Record_clicked\0"
    "Display_StripNum\0Test_Count\0"
    "on_Clear_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    1,   57,    2, 0x08 /* Private */,
       8,    1,   60,    2, 0x08 /* Private */,
      12,    0,   63,    2, 0x08 /* Private */,
      13,    1,   64,    2, 0x08 /* Private */,
      15,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    0x80000000 | 9, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort,   14,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Connect_Btn_clicked(); break;
        case 1: _t->ReadData(); break;
        case 2: _t->SearchPort(); break;
        case 3: _t->Rrrorhandle((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 4: { uint8 _r = _t->Save_Data((*reinterpret_cast< uint16(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint8*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->on_Read_Record_clicked(); break;
        case 6: _t->Display_StripNum((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 7: _t->on_Clear_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
