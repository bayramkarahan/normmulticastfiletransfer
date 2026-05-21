/****************************************************************************
** Meta object code from reading C++ file 'normreceiver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../multicastfiletransferclient/normreceiver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'normreceiver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NormReceiver_t {
    QByteArrayData data[14];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NormReceiver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NormReceiver_t qt_meta_stringdata_NormReceiver = {
    {
QT_MOC_LITERAL(0, 0, 12), // "NormReceiver"
QT_MOC_LITERAL(1, 13, 3), // "log"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 4), // "text"
QT_MOC_LITERAL(4, 23, 8), // "progress"
QT_MOC_LITERAL(5, 32, 8), // "fileName"
QT_MOC_LITERAL(6, 41, 7), // "current"
QT_MOC_LITERAL(7, 49, 5), // "total"
QT_MOC_LITERAL(8, 55, 7), // "percent"
QT_MOC_LITERAL(9, 63, 12), // "fileReceived"
QT_MOC_LITERAL(10, 76, 8), // "filePath"
QT_MOC_LITERAL(11, 85, 12), // "senderActive"
QT_MOC_LITERAL(12, 98, 14), // "senderInactive"
QT_MOC_LITERAL(13, 113, 5) // "error"

    },
    "NormReceiver\0log\0\0text\0progress\0"
    "fileName\0current\0total\0percent\0"
    "fileReceived\0filePath\0senderActive\0"
    "senderInactive\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NormReceiver[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    4,   47,    2, 0x06 /* Public */,
       9,    1,   56,    2, 0x06 /* Public */,
      11,    0,   59,    2, 0x06 /* Public */,
      12,    0,   60,    2, 0x06 /* Public */,
      13,    1,   61,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong, QMetaType::LongLong, QMetaType::Double,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void NormReceiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NormReceiver *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->progress((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 2: _t->fileReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->senderActive(); break;
        case 4: _t->senderInactive(); break;
        case 5: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NormReceiver::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiver::log)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NormReceiver::*)(QString , qint64 , qint64 , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiver::progress)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NormReceiver::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiver::fileReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NormReceiver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiver::senderActive)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NormReceiver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiver::senderInactive)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (NormReceiver::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NormReceiver::error)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NormReceiver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NormReceiver.data,
    qt_meta_data_NormReceiver,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NormReceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NormReceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NormReceiver.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NormReceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void NormReceiver::log(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NormReceiver::progress(QString _t1, qint64 _t2, qint64 _t3, double _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NormReceiver::fileReceived(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NormReceiver::senderActive()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void NormReceiver::senderInactive()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void NormReceiver::error(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
