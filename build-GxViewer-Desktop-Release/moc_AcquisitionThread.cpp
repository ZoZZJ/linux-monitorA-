/****************************************************************************
** Meta object code from reading C++ file 'AcquisitionThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GxViewer/AcquisitionThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AcquisitionThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CAcquisitionThread_t {
    QByteArrayData data[10];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CAcquisitionThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CAcquisitionThread_t qt_meta_stringdata_CAcquisitionThread = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CAcquisitionThread"
QT_MOC_LITERAL(1, 19, 19), // "SigAcquisitionError"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 17), // "SigImageProcError"
QT_MOC_LITERAL(4, 58, 7), // "VxInt32"
QT_MOC_LITERAL(5, 66, 27), // "SlotGetColorCorrectionParam"
QT_MOC_LITERAL(6, 94, 7), // "int64_t"
QT_MOC_LITERAL(7, 102, 15), // "SlotGetGammaLUT"
QT_MOC_LITERAL(8, 118, 14), // "unsigned char*"
QT_MOC_LITERAL(9, 133, 18) // "SlotGetContrastLUT"

    },
    "CAcquisitionThread\0SigAcquisitionError\0"
    "\0SigImageProcError\0VxInt32\0"
    "SlotGetColorCorrectionParam\0int64_t\0"
    "SlotGetGammaLUT\0unsigned char*\0"
    "SlotGetContrastLUT"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CAcquisitionThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   45,    2, 0x0a /* Public */,
       7,    1,   48,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 8,    2,

       0        // eod
};

void CAcquisitionThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CAcquisitionThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigAcquisitionError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->SigImageProcError((*reinterpret_cast< VxInt32(*)>(_a[1]))); break;
        case 2: _t->SlotGetColorCorrectionParam((*reinterpret_cast< int64_t(*)>(_a[1]))); break;
        case 3: _t->SlotGetGammaLUT((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 4: _t->SlotGetContrastLUT((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CAcquisitionThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CAcquisitionThread::SigAcquisitionError)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CAcquisitionThread::*)(VxInt32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CAcquisitionThread::SigImageProcError)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CAcquisitionThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_CAcquisitionThread.data,
    qt_meta_data_CAcquisitionThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CAcquisitionThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CAcquisitionThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CAcquisitionThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int CAcquisitionThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CAcquisitionThread::SigAcquisitionError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CAcquisitionThread::SigImageProcError(VxInt32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
