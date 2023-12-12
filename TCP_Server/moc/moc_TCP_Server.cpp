/****************************************************************************
** Meta object code from reading C++ file 'TCP_Server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../TCP_Server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TCP_Server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TCP_Server_t {
    QByteArrayData data[14];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TCP_Server_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TCP_Server_t qt_meta_stringdata_TCP_Server = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TCP_Server"
QT_MOC_LITERAL(1, 11, 20), // "on_Btn_Start_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 20), // "on_Btn_Pause_clicked"
QT_MOC_LITERAL(4, 54, 18), // "slot_newConnection"
QT_MOC_LITERAL(5, 73, 17), // "slot_disConnected"
QT_MOC_LITERAL(6, 91, 16), // "Client_to_Server"
QT_MOC_LITERAL(7, 108, 16), // "Server_to_Client"
QT_MOC_LITERAL(8, 125, 7), // "Command"
QT_MOC_LITERAL(9, 133, 7), // "command"
QT_MOC_LITERAL(10, 141, 11), // "QTcpSocket*"
QT_MOC_LITERAL(11, 153, 6), // "socket"
QT_MOC_LITERAL(12, 160, 8), // "MyPacket"
QT_MOC_LITERAL(13, 169, 6) // "Packet"

    },
    "TCP_Server\0on_Btn_Start_clicked\0\0"
    "on_Btn_Pause_clicked\0slot_newConnection\0"
    "slot_disConnected\0Client_to_Server\0"
    "Server_to_Client\0Command\0command\0"
    "QTcpSocket*\0socket\0MyPacket\0Packet"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TCP_Server[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    3,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10, 0x80000000 | 12,    9,   11,   13,

       0        // eod
};

void TCP_Server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TCP_Server *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Btn_Start_clicked(); break;
        case 1: _t->on_Btn_Pause_clicked(); break;
        case 2: _t->slot_newConnection(); break;
        case 3: _t->slot_disConnected(); break;
        case 4: _t->Client_to_Server(); break;
        case 5: _t->Server_to_Client((*reinterpret_cast< Command(*)>(_a[1])),(*reinterpret_cast< QTcpSocket*(*)>(_a[2])),(*reinterpret_cast< MyPacket(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TCP_Server::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_TCP_Server.data,
    qt_meta_data_TCP_Server,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TCP_Server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TCP_Server::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TCP_Server.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TCP_Server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
