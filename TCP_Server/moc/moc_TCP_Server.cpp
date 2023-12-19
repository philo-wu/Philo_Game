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
    QByteArrayData data[16];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TCP_Server_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TCP_Server_t qt_meta_stringdata_TCP_Server = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TCP_Server"
QT_MOC_LITERAL(1, 11, 10), // "SendFinish"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 20), // "on_Btn_Start_clicked"
QT_MOC_LITERAL(4, 44, 18), // "slot_newConnection"
QT_MOC_LITERAL(5, 63, 17), // "slot_disConnected"
QT_MOC_LITERAL(6, 81, 16), // "Client_to_Server"
QT_MOC_LITERAL(7, 98, 16), // "Server_to_Client"
QT_MOC_LITERAL(8, 115, 7), // "Command"
QT_MOC_LITERAL(9, 123, 7), // "command"
QT_MOC_LITERAL(10, 131, 11), // "QTcpSocket*"
QT_MOC_LITERAL(11, 143, 6), // "socket"
QT_MOC_LITERAL(12, 150, 8), // "MyPacket"
QT_MOC_LITERAL(13, 159, 6), // "Packet"
QT_MOC_LITERAL(14, 166, 11), // "Send_Packet"
QT_MOC_LITERAL(15, 178, 11) // "QByteArray&"

    },
    "TCP_Server\0SendFinish\0\0on_Btn_Start_clicked\0"
    "slot_newConnection\0slot_disConnected\0"
    "Client_to_Server\0Server_to_Client\0"
    "Command\0command\0QTcpSocket*\0socket\0"
    "MyPacket\0Packet\0Send_Packet\0QByteArray&"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TCP_Server[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    3,   54,    2, 0x0a /* Public */,
      14,    2,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10, 0x80000000 | 12,    9,   11,   13,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 15,   11,   13,

       0        // eod
};

void TCP_Server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TCP_Server *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendFinish(); break;
        case 1: _t->on_Btn_Start_clicked(); break;
        case 2: _t->slot_newConnection(); break;
        case 3: _t->slot_disConnected(); break;
        case 4: _t->Client_to_Server(); break;
        case 5: _t->Server_to_Client((*reinterpret_cast< Command(*)>(_a[1])),(*reinterpret_cast< QTcpSocket*(*)>(_a[2])),(*reinterpret_cast< MyPacket(*)>(_a[3]))); break;
        case 6: _t->Send_Packet((*reinterpret_cast< QTcpSocket*(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
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
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TCP_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCP_Server::SendFinish)) {
                *result = 0;
                return;
            }
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
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TCP_Server::SendFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
