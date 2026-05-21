/****************************************************************************
** Meta object code from reading C++ file 'multicastfileclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "multicastfileclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multicastfileclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MulticastClient_t {
    QByteArrayData data[30];
    char stringdata0[330];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MulticastClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MulticastClient_t qt_meta_stringdata_MulticastClient = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MulticastClient"
QT_MOC_LITERAL(1, 16, 12), // "fileReceived"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "tmpPath"
QT_MOC_LITERAL(4, 38, 8), // "destPath"
QT_MOC_LITERAL(5, 47, 8), // "fileName"
QT_MOC_LITERAL(6, 56, 10), // "transferId"
QT_MOC_LITERAL(7, 67, 12), // "TransferType"
QT_MOC_LITERAL(8, 80, 12), // "transferType"
QT_MOC_LITERAL(9, 93, 17), // "transferOverwrite"
QT_MOC_LITERAL(10, 111, 16), // "transferProgress"
QT_MOC_LITERAL(11, 128, 7), // "percent"
QT_MOC_LITERAL(12, 136, 3), // "log"
QT_MOC_LITERAL(13, 140, 3), // "msg"
QT_MOC_LITERAL(14, 144, 15), // "processDatagram"
QT_MOC_LITERAL(15, 160, 8), // "datagram"
QT_MOC_LITERAL(16, 169, 12), // "QHostAddress"
QT_MOC_LITERAL(17, 182, 6), // "sender"
QT_MOC_LITERAL(18, 189, 8), // "sendNack"
QT_MOC_LITERAL(19, 198, 16), // "QVector<quint32>"
QT_MOC_LITERAL(20, 215, 7), // "missing"
QT_MOC_LITERAL(21, 223, 8), // "saveFile"
QT_MOC_LITERAL(22, 232, 10), // "resetState"
QT_MOC_LITERAL(23, 243, 8), // "sendDone"
QT_MOC_LITERAL(24, 252, 23), // "processPendingDatagrams"
QT_MOC_LITERAL(25, 276, 16), // "generateFileName"
QT_MOC_LITERAL(26, 293, 3), // "dir"
QT_MOC_LITERAL(27, 297, 8), // "baseName"
QT_MOC_LITERAL(28, 306, 12), // "sendProgress"
QT_MOC_LITERAL(29, 319, 10) // "getLocalIp"

    },
    "MulticastClient\0fileReceived\0\0tmpPath\0"
    "destPath\0fileName\0transferId\0TransferType\0"
    "transferType\0transferOverwrite\0"
    "transferProgress\0percent\0log\0msg\0"
    "processDatagram\0datagram\0QHostAddress\0"
    "sender\0sendNack\0QVector<quint32>\0"
    "missing\0saveFile\0resetState\0sendDone\0"
    "processPendingDatagrams\0generateFileName\0"
    "dir\0baseName\0sendProgress\0getLocalIp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MulticastClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    6,   74,    2, 0x06 /* Public */,
      10,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   90,    2, 0x08 /* Private */,
      14,    2,   93,    2, 0x08 /* Private */,
      18,    2,   98,    2, 0x08 /* Private */,
      21,    0,  103,    2, 0x08 /* Private */,
      22,    0,  104,    2, 0x08 /* Private */,
      23,    0,  105,    2, 0x08 /* Private */,
      24,    0,  106,    2, 0x08 /* Private */,
      25,    2,  107,    2, 0x08 /* Private */,
      28,    1,  112,    2, 0x08 /* Private */,
      29,    0,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, 0x80000000 | 7, QMetaType::Bool,    3,    4,    5,    6,    8,    9,
    QMetaType::Void, QMetaType::Int,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 16,   15,   17,
    QMetaType::Void, 0x80000000 | 19, 0x80000000 | 16,   20,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   26,   27,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::QString,

       0        // eod
};

void MulticastClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MulticastClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fileReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< TransferType(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 1: _t->transferProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->log((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->processDatagram((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QHostAddress(*)>(_a[2]))); break;
        case 4: _t->sendNack((*reinterpret_cast< const QVector<quint32>(*)>(_a[1])),(*reinterpret_cast< const QHostAddress(*)>(_a[2]))); break;
        case 5: _t->saveFile(); break;
        case 6: _t->resetState(); break;
        case 7: _t->sendDone(); break;
        case 8: _t->processPendingDatagrams(); break;
        case 9: { QString _r = _t->generateFileName((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->sendProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: { QString _r = _t->getLocalIp();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<quint32> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MulticastClient::*)(QString , QString , QString , QString , TransferType , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MulticastClient::fileReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MulticastClient::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MulticastClient::transferProgress)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MulticastClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MulticastClient.data,
    qt_meta_data_MulticastClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MulticastClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MulticastClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MulticastClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MulticastClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MulticastClient::fileReceived(QString _t1, QString _t2, QString _t3, QString _t4, TransferType _t5, bool _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MulticastClient::transferProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
