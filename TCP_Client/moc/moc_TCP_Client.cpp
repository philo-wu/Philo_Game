/****************************************************************************
** Meta object code from reading C++ file 'TCP_Client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../TCP_Client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TCP_Client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TCP_Client_t {
    QByteArrayData data[11];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TCP_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TCP_Client_t qt_meta_stringdata_TCP_Client = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TCP_Client"
QT_MOC_LITERAL(1, 11, 16), // "Server_to_Client"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "Client_to_Server"
QT_MOC_LITERAL(4, 46, 7), // "Command"
QT_MOC_LITERAL(5, 54, 7), // "command"
QT_MOC_LITERAL(6, 62, 22), // "on_Btn_Signout_clicked"
QT_MOC_LITERAL(7, 85, 19), // "on_Btn_Send_clicked"
QT_MOC_LITERAL(8, 105, 18), // "socketStateChanged"
QT_MOC_LITERAL(9, 124, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(10, 153, 5) // "state"

    },
    "TCP_Client\0Server_to_Client\0\0"
    "Client_to_Server\0Command\0command\0"
    "on_Btn_Signout_clicked\0on_Btn_Send_clicked\0"
    "socketStateChanged\0QAbstractSocket::SocketState\0"
    "state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TCP_Client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    1,   40,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,
       7,    0,   44,    2, 0x08 /* Private */,
       8,    1,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void TCP_Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TCP_Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Server_to_Client(); break;
        case 1: _t->Client_to_Server((*reinterpret_cast< Command(*)>(_a[1]))); break;
        case 2: _t->on_Btn_Signout_clicked(); break;
        case 3: _t->on_Btn_Send_clicked(); break;
        case 4: _t->socketStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TCP_Client::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_TCP_Client.data,
    qt_meta_data_TCP_Client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TCP_Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TCP_Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TCP_Client.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TCP_Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
