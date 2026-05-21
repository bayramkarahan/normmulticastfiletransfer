/****************************************************************************
** Meta object code from reading C++ file 'multicastfileserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../multicastfiletransferserver/multicastfileserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multicastfileserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MulticastServer_t {
    QByteArrayData data[21];
    char stringdata0[318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MulticastServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MulticastServer_t qt_meta_stringdata_MulticastServer = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MulticastServer"
QT_MOC_LITERAL(1, 16, 22), // "clientAllProgressStart"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 21), // "clientProgressChanged"
QT_MOC_LITERAL(4, 62, 6), // "client"
QT_MOC_LITERAL(5, 69, 7), // "percent"
QT_MOC_LITERAL(6, 77, 14), // "clientHostName"
QT_MOC_LITERAL(7, 92, 21), // "clientDebInstallStart"
QT_MOC_LITERAL(8, 114, 20), // "clientDebInstallDone"
QT_MOC_LITERAL(9, 135, 6), // "status"
QT_MOC_LITERAL(10, 142, 24), // "clientScriptInstallStart"
QT_MOC_LITERAL(11, 167, 23), // "clientScriptInstallDone"
QT_MOC_LITERAL(12, 191, 19), // "allTransferFinished"
QT_MOC_LITERAL(13, 211, 16), // "transferFinished"
QT_MOC_LITERAL(14, 228, 6), // "sender"
QT_MOC_LITERAL(15, 235, 8), // "receiver"
QT_MOC_LITERAL(16, 244, 4), // "file"
QT_MOC_LITERAL(17, 249, 2), // "id"
QT_MOC_LITERAL(18, 252, 23), // "processPendingDatagrams"
QT_MOC_LITERAL(19, 276, 23), // "calculateNextJobTimeout"
QT_MOC_LITERAL(20, 300, 17) // "detectNetworkType"

    },
    "MulticastServer\0clientAllProgressStart\0"
    "\0clientProgressChanged\0client\0percent\0"
    "clientHostName\0clientDebInstallStart\0"
    "clientDebInstallDone\0status\0"
    "clientScriptInstallStart\0"
    "clientScriptInstallDone\0allTransferFinished\0"
    "transferFinished\0sender\0receiver\0file\0"
    "id\0processPendingDatagrams\0"
    "calculateNextJobTimeout\0detectNetworkType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MulticastServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    3,   70,    2, 0x06 /* Public */,
       7,    1,   77,    2, 0x06 /* Public */,
       8,    2,   80,    2, 0x06 /* Public */,
      10,    1,   85,    2, 0x06 /* Public */,
      11,    2,   88,    2, 0x06 /* Public */,
      12,    0,   93,    2, 0x06 /* Public */,
      13,    4,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    0,  103,    2, 0x08 /* Private */,
      19,    0,  104,    2, 0x08 /* Private */,
      20,    0,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,    4,    5,    6,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    9,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   14,   15,   16,   17,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,

       0        // eod
};

void MulticastServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MulticastServer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clientAllProgressStart(); break;
        case 1: _t->clientProgressChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->clientDebInstallStart((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->clientDebInstallDone((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->clientScriptInstallStart((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->clientScriptInstallDone((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->allTransferFinished(); break;
        case 7: _t->transferFinished((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 8: _t->processPendingDatagrams(); break;
        case 9: _t->calculateNextJobTimeout(); break;
        case 10: { QString _r = _t->detectNetworkType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MulticastServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MulticastServer::clientAllProgressStart)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MulticastServer::*)(QString , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MulticastServer::clientProgressChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MulticastServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MulticastServer::clientDebInstallStart)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MulticastServer::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MulticastServer::clientDebInstallDone)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MulticastServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MulticastServer::clientScriptInstallStart)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MulticastServer::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MulticastServer::clientScriptInstallDone)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MulticastServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MulticastServer::allTransferFinished)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MulticastServer::*)(QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MulticastServer::transferFinished)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MulticastServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MulticastServer.data,
    qt_meta_data_MulticastServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MulticastServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MulticastServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MulticastServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MulticastServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MulticastServer::clientAllProgressStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MulticastServer::clientProgressChanged(QString _t1, int _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MulticastServer::clientDebInstallStart(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MulticastServer::clientDebInstallDone(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MulticastServer::clientScriptInstallStart(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MulticastServer::clientScriptInstallDone(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MulticastServer::allTransferFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MulticastServer::transferFinished(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
