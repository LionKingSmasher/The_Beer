/****************************************************************************
** Meta object code from reading C++ file 'clientwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../TheBeer4Qt5/clientwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientWindow_t {
    QByteArrayData data[10];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientWindow_t qt_meta_stringdata_ClientWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ClientWindow"
QT_MOC_LITERAL(1, 13, 23), // "on_Server_Start_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 28), // "on_Server_End_Button_clicked"
QT_MOC_LITERAL(4, 67, 30), // "on_Server_Start_Button_clicked"
QT_MOC_LITERAL(5, 98, 24), // "on_ConnectButton_clicked"
QT_MOC_LITERAL(6, 123, 21), // "on_sendButton_clicked"
QT_MOC_LITERAL(7, 145, 25), // "on_lineEdit_returnPressed"
QT_MOC_LITERAL(8, 171, 28), // "on_actionLoad_Chat_triggered"
QT_MOC_LITERAL(9, 200, 28) // "on_actionSave_Chat_triggered"

    },
    "ClientWindow\0on_Server_Start_clicked\0"
    "\0on_Server_End_Button_clicked\0"
    "on_Server_Start_Button_clicked\0"
    "on_ConnectButton_clicked\0on_sendButton_clicked\0"
    "on_lineEdit_returnPressed\0"
    "on_actionLoad_Chat_triggered\0"
    "on_actionSave_Chat_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientWindow[] = {

 // content:
       8,       // revision
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
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
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

void ClientWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_Server_Start_clicked(); break;
        case 1: _t->on_Server_End_Button_clicked(); break;
        case 2: _t->on_Server_Start_Button_clicked(); break;
        case 3: _t->on_ConnectButton_clicked(); break;
        case 4: _t->on_sendButton_clicked(); break;
        case 5: _t->on_lineEdit_returnPressed(); break;
        case 6: _t->on_actionLoad_Chat_triggered(); break;
        case 7: _t->on_actionSave_Chat_triggered(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject ClientWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ClientWindow.data,
    qt_meta_data_ClientWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ClientWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ClientWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
