/****************************************************************************
** Meta object code from reading C++ file 'ImageImprovement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GxViewer/ImageImprovement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageImprovement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CImageImprovement_t {
    QByteArrayData data[14];
    char stringdata0[302];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CImageImprovement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CImageImprovement_t qt_meta_stringdata_CImageImprovement = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CImageImprovement"
QT_MOC_LITERAL(1, 18, 27), // "SigSendColorCorrectionParam"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 7), // "int64_t"
QT_MOC_LITERAL(4, 55, 15), // "SigSendGammaLUT"
QT_MOC_LITERAL(5, 71, 14), // "unsigned char*"
QT_MOC_LITERAL(6, 86, 18), // "SigSendContrastLUT"
QT_MOC_LITERAL(7, 105, 33), // "on_ImageImprovement_Close_cli..."
QT_MOC_LITERAL(8, 139, 23), // "on_ColorCorrect_clicked"
QT_MOC_LITERAL(9, 163, 24), // "on_GammaCheckBox_clicked"
QT_MOC_LITERAL(10, 188, 27), // "on_ContrastCheckBox_clicked"
QT_MOC_LITERAL(11, 216, 25), // "on_GammaSpin_valueChanged"
QT_MOC_LITERAL(12, 242, 28), // "on_ContrastSpin_valueChanged"
QT_MOC_LITERAL(13, 271, 30) // "on_ContrastSlider_valueChanged"

    },
    "CImageImprovement\0SigSendColorCorrectionParam\0"
    "\0int64_t\0SigSendGammaLUT\0unsigned char*\0"
    "SigSendContrastLUT\0on_ImageImprovement_Close_clicked\0"
    "on_ColorCorrect_clicked\0"
    "on_GammaCheckBox_clicked\0"
    "on_ContrastCheckBox_clicked\0"
    "on_GammaSpin_valueChanged\0"
    "on_ContrastSpin_valueChanged\0"
    "on_ContrastSlider_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CImageImprovement[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       6,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   73,    2, 0x08 /* Private */,
       8,    1,   74,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      10,    1,   80,    2, 0x08 /* Private */,
      11,    1,   83,    2, 0x08 /* Private */,
      12,    1,   86,    2, 0x08 /* Private */,
      13,    1,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void CImageImprovement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CImageImprovement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigSendColorCorrectionParam((*reinterpret_cast< int64_t(*)>(_a[1]))); break;
        case 1: _t->SigSendGammaLUT((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 2: _t->SigSendContrastLUT((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 3: _t->on_ImageImprovement_Close_clicked(); break;
        case 4: _t->on_ColorCorrect_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_GammaCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_ContrastCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_GammaSpin_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->on_ContrastSpin_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_ContrastSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CImageImprovement::*)(int64_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CImageImprovement::SigSendColorCorrectionParam)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CImageImprovement::*)(unsigned char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CImageImprovement::SigSendGammaLUT)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CImageImprovement::*)(unsigned char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CImageImprovement::SigSendContrastLUT)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CImageImprovement::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_CImageImprovement.data,
    qt_meta_data_CImageImprovement,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CImageImprovement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CImageImprovement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CImageImprovement.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CImageImprovement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void CImageImprovement::SigSendColorCorrectionParam(int64_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CImageImprovement::SigSendGammaLUT(unsigned char * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CImageImprovement::SigSendContrastLUT(unsigned char * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
