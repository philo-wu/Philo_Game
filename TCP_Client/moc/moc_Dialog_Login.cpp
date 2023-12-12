/****************************************************************************
** Meta object code from reading C++ file 'Dialog_Login.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Dialog_Login.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Dialog_Login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_Login_t {
    QByteArrayData data[17];
    char stringdata0[290];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_Login_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_Login_t qt_meta_stringdata_Dialog_Login = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Dialog_Login"
QT_MOC_LITERAL(1, 13, 6), // "ToRoom"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 16), // "Server_to_Client"
QT_MOC_LITERAL(4, 38, 16), // "Client_to_Server"
QT_MOC_LITERAL(5, 55, 7), // "Command"
QT_MOC_LITERAL(6, 63, 7), // "command"
QT_MOC_LITERAL(7, 71, 23), // "on_Btn_ToSignup_clicked"
QT_MOC_LITERAL(8, 95, 20), // "on_Btn_Login_clicked"
QT_MOC_LITERAL(9, 116, 22), // "on_Btn_Setting_clicked"
QT_MOC_LITERAL(10, 139, 21), // "on_Btn_return_clicked"
QT_MOC_LITERAL(11, 161, 19), // "on_Btn_quit_clicked"
QT_MOC_LITERAL(12, 181, 25), // "on_Btn_Setting_OK_clicked"
QT_MOC_LITERAL(13, 207, 21), // "on_Btn_Signup_clicked"
QT_MOC_LITERAL(14, 229, 27), // "on_CB_Showpass_stateChanged"
QT_MOC_LITERAL(15, 257, 4), // "arg1"
QT_MOC_LITERAL(16, 262, 27) // "on_CB_Keeppass_stateChanged"

    },
    "Dialog_Login\0ToRoom\0\0Server_to_Client\0"
    "Client_to_Server\0Command\0command\0"
    "on_Btn_ToSignup_clicked\0on_Btn_Login_clicked\0"
    "on_Btn_Setting_clicked\0on_Btn_return_clicked\0"
    "on_Btn_quit_clicked\0on_Btn_Setting_OK_clicked\0"
    "on_Btn_Signup_clicked\0on_CB_Showpass_stateChanged\0"
    "arg1\0on_CB_Keeppass_stateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_Login[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   75,    2, 0x08 /* Private */,
       4,    1,   76,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,
      14,    1,   86,    2, 0x08 /* Private */,
      16,    1,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void Dialog_Login::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dialog_Login *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ToRoom(); break;
        case 1: _t->Server_to_Client(); break;
        case 2: _t->Client_to_Server((*reinterpret_cast< Command(*)>(_a[1]))); break;
        case 3: _t->on_Btn_ToSignup_clicked(); break;
        case 4: _t->on_Btn_Login_clicked(); break;
        case 5: _t->on_Btn_Setting_clicked(); break;
        case 6: _t->on_Btn_return_clicked(); break;
        case 7: _t->on_Btn_quit_clicked(); break;
        case 8: _t->on_Btn_Setting_OK_clicked(); break;
        case 9: _t->on_Btn_Signup_clicked(); break;
        case 10: _t->on_CB_Showpass_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_CB_Keeppass_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dialog_Login::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_Login::ToRoom)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog_Login::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Dialog_Login.data,
    qt_meta_data_Dialog_Login,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Dialog_Login::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_Login::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_Login.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog_Login::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Dialog_Login::ToRoom()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
