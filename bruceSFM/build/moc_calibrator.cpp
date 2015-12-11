/****************************************************************************
** Meta object code from reading C++ file 'calibrator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../calibrator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calibrator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Calibrator_t {
    QByteArrayData data[16];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Calibrator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Calibrator_t qt_meta_stringdata_Calibrator = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Calibrator"
QT_MOC_LITERAL(1, 11, 10), // "calibrated"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "Mat"
QT_MOC_LITERAL(4, 27, 1), // "k"
QT_MOC_LITERAL(5, 29, 1), // "d"
QT_MOC_LITERAL(6, 31, 9), // "calibrate"
QT_MOC_LITERAL(7, 41, 12), // "QVector<Mat>"
QT_MOC_LITERAL(8, 54, 6), // "images"
QT_MOC_LITERAL(9, 61, 4), // "Size"
QT_MOC_LITERAL(10, 66, 14), // "chessboardSize"
QT_MOC_LITERAL(11, 81, 4), // "load"
QT_MOC_LITERAL(12, 86, 18), // "calibParamFilePath"
QT_MOC_LITERAL(13, 105, 4), // "save"
QT_MOC_LITERAL(14, 110, 3), // "get"
QT_MOC_LITERAL(15, 114, 4) // "Mat&"

    },
    "Calibrator\0calibrated\0\0Mat\0k\0d\0calibrate\0"
    "QVector<Mat>\0images\0Size\0chessboardSize\0"
    "load\0calibParamFilePath\0save\0get\0Mat&"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Calibrator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   44,    2, 0x0a /* Public */,
      11,    1,   49,    2, 0x0a /* Public */,
      13,    1,   52,    2, 0x0a /* Public */,
      14,    2,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    8,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15,    4,    5,

       0        // eod
};

void Calibrator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Calibrator *_t = static_cast<Calibrator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->calibrated((*reinterpret_cast< const Mat(*)>(_a[1])),(*reinterpret_cast< const Mat(*)>(_a[2]))); break;
        case 1: _t->calibrate((*reinterpret_cast< const QVector<Mat>(*)>(_a[1])),(*reinterpret_cast< Size(*)>(_a[2]))); break;
        case 2: _t->load((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->save((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->get((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Calibrator::*_t)(const Mat & , const Mat & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Calibrator::calibrated)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Calibrator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Calibrator.data,
      qt_meta_data_Calibrator,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Calibrator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Calibrator::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Calibrator.stringdata0))
        return static_cast<void*>(const_cast< Calibrator*>(this));
    return QObject::qt_metacast(_clname);
}

int Calibrator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void Calibrator::calibrated(const Mat & _t1, const Mat & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
