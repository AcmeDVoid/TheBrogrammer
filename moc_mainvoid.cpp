/****************************************************************************
** Meta object code from reading C++ file 'mainvoid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainvoid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainvoid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainVoid_t {
    QByteArrayData data[13];
    char stringdata[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainVoid_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainVoid_t qt_meta_stringdata_MainVoid = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 21),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 22),
QT_MOC_LITERAL(4, 55, 25),
QT_MOC_LITERAL(5, 81, 22),
QT_MOC_LITERAL(6, 104, 23),
QT_MOC_LITERAL(7, 128, 21),
QT_MOC_LITERAL(8, 150, 27),
QT_MOC_LITERAL(9, 178, 23),
QT_MOC_LITERAL(10, 202, 23),
QT_MOC_LITERAL(11, 226, 24),
QT_MOC_LITERAL(12, 251, 23)
    },
    "MainVoid\0on_userButton_clicked\0\0"
    "on_closeButton_clicked\0on_viewListButton_clicked\0"
    "on_adminButton_clicked\0on_pushButton_4_clicked\0"
    "on_pushButton_clicked\0on_importFileButton_clicked\0"
    "on_goBackButton_clicked\0on_selectButton_clicked\0"
    "on_aboutUsButton_clicked\0"
    "on_pushButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainVoid[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainVoid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainVoid *_t = static_cast<MainVoid *>(_o);
        switch (_id) {
        case 0: _t->on_userButton_clicked(); break;
        case 1: _t->on_closeButton_clicked(); break;
        case 2: _t->on_viewListButton_clicked(); break;
        case 3: _t->on_adminButton_clicked(); break;
        case 4: _t->on_pushButton_4_clicked(); break;
        case 5: _t->on_pushButton_clicked(); break;
        case 6: _t->on_importFileButton_clicked(); break;
        case 7: _t->on_goBackButton_clicked(); break;
        case 8: _t->on_selectButton_clicked(); break;
        case 9: _t->on_aboutUsButton_clicked(); break;
        case 10: _t->on_pushButton_2_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainVoid::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainVoid.data,
      qt_meta_data_MainVoid,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainVoid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainVoid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainVoid.stringdata))
        return static_cast<void*>(const_cast< MainVoid*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainVoid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
