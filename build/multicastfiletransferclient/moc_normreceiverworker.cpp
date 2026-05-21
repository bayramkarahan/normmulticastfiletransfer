/****************************************************************************
** Meta object code from reading C++ file 'normreceiverworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../multicastfiletransferclient/normreceiverworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'normreceiverworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NormReceiverWorker_t {
    QByteArrayData data[20];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NormReceiverWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NormReceiverWorker_t qt_meta_stringdata_NormReceiverWorker = {
    {
QT_MOC_LITERAL(0, 0, 18), // "NormReceiverWorker"
QT_MOC_LITERAL(1, 19, 3), // "log"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "text"
QT_MOC_LITERAL(4, 29, 8), // "progress"
QT_MOC_LITERAL(5, 38, 8), // "fileName"
QT_MOC_LITERAL(6, 47, 7), // "current"
QT_MOC_LITERAL(7, 55, 5), // "total"
QT_MOC_LITERAL(8, 61, 7), // "percent"
QT_MOC_LITERAL(9, 69, 12), // "fileReceived"
QT_MOC_LITERAL(10, 82, 8), // "filePath"
QT_MOC_LITERAL(11, 91, 12), // "senderActive"
QT_MOC_LITERAL(12, 104, 14), // "senderInactive"
QT_MOC_LITERAL(13, 119, 5), // "error"
QT_MOC_LITERAL(14, 125, 13), // "startReceiver"
QT_MOC_LITERAL(15, 139, 8), // "cacheDir"
QT_MOC_LITERAL(16, 148, 11), // "multicastIp"
QT_MOC_LITERAL(17, 160, 4), // "port"
QT_MOC_LITERAL(18, 165, 4), // "stop"
QT_MOC_LITERAL(19, 170, 17) // "detectNetworkType"

    },
    "NormReceiverWorker\0log\0\0text\0progress\0"
    "fileName\0current\0total\0percent\0"
    "fileReceived\0filePath\0senderActive\0"
    "senderInactive\0error\0startReceiver\0"
    "cacheDir\0multicastIp\0port\0stop\0"
    "detectNetworkType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NormReceiverWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    4,   62,    2, 0x06 /* Public */,
       9,    1,   71,    2, 0x06 /* Public */,
      11,    0,   74,    2, 0x06 /* Public */,
      12,    0,   75,    2, 0x06 /* Public */,
      13,    1,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    3,   79,    2, 0x0a /* Public */,
      18,    0,   86,    2, 0x0a /* Public */,
      19,    0,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong, QMetaType::LongLong, QMetaType::Double,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::UShort,   15,   16,   17,
    QMetaType::Void,
    QMetaType::QString,

       0        // eod
};

void NormReceiverWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NormReceiverWorker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->progress((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 2: _t->fileReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->senderActive(); break;
        case 4: _t->senderInactive(); break;
        case 5: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->startReceiver((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 7: _t->stop(); break;
        case 8: { QString _r = _t->detectNetworkType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NormReceiverWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiverWorker::log)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NormReceiverWorker::*)(QString , qint64 , qint64 , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiverWorker::progress)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NormReceiverWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiverWorker::fileReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NormReceiverWorker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiverWorker::senderActive)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NormReceiverWorker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiverWorker::senderInactive)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (NormReceiverWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiverWorker::error)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NormReceiverWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NormReceiverWorker.data,
    qt_meta_data_NormReceiverWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NormReceiverWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NormReceiverWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NormReceiverWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NormReceiverWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void NormReceiverWorker::log(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NormReceiverWorker::progress(QString _t1, qint64 _t2, qint64 _t3, double _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NormReceiverWorker::fileReceived(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NormReceiverWorker::senderActive()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void NormReceiverWorker::senderInactive()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void NormReceiverWorker::error(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
