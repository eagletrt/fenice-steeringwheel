/****************************************************************************
** Meta object code from reading C++ file 'canbus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../header/canbus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canbus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Canbus_t {
    QByteArrayData data[32];
    char stringdata0[438];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Canbus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Canbus_t qt_meta_stringdata_Canbus = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Canbus"
QT_MOC_LITERAL(1, 7, 19), // "controlStateChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "ctrlState"
QT_MOC_LITERAL(4, 38, 4), // "warn"
QT_MOC_LITERAL(5, 43, 3), // "err"
QT_MOC_LITERAL(6, 47, 13), // "presetChanged"
QT_MOC_LITERAL(7, 61, 8), // "presetID"
QT_MOC_LITERAL(8, 70, 11), // "pumpChanged"
QT_MOC_LITERAL(9, 82, 6), // "pumpID"
QT_MOC_LITERAL(10, 89, 31), // "actuatorRangePendingFlagCleared"
QT_MOC_LITERAL(11, 121, 12), // "speedChanged"
QT_MOC_LITERAL(12, 134, 13), // "hvTempChanged"
QT_MOC_LITERAL(13, 148, 13), // "lvTempChanged"
QT_MOC_LITERAL(14, 162, 13), // "hvVoltChanged"
QT_MOC_LITERAL(15, 176, 13), // "lvVoltChanged"
QT_MOC_LITERAL(16, 190, 16), // "invSxTempChanged"
QT_MOC_LITERAL(17, 207, 16), // "invDxTempChanged"
QT_MOC_LITERAL(18, 224, 15), // "brakeValChanged"
QT_MOC_LITERAL(19, 240, 18), // "throttleValChanged"
QT_MOC_LITERAL(20, 259, 11), // "parseSerial"
QT_MOC_LITERAL(21, 271, 9), // "toggleCar"
QT_MOC_LITERAL(22, 281, 11), // "askHVUpdate"
QT_MOC_LITERAL(23, 293, 17), // "setActuatorsRange"
QT_MOC_LITERAL(24, 311, 21), // "checkCANCommunication"
QT_MOC_LITERAL(25, 333, 17), // "checkSensorsError"
QT_MOC_LITERAL(26, 351, 14), // "steerConnected"
QT_MOC_LITERAL(27, 366, 9), // "askStatus"
QT_MOC_LITERAL(28, 376, 12), // "sendEncState"
QT_MOC_LITERAL(29, 389, 14), // "askSetupOrIdle"
QT_MOC_LITERAL(30, 404, 8), // "PWMCheck"
QT_MOC_LITERAL(31, 413, 24) // "actuatorRangePendingFlag"

    },
    "Canbus\0controlStateChanged\0\0ctrlState\0"
    "warn\0err\0presetChanged\0presetID\0"
    "pumpChanged\0pumpID\0actuatorRangePendingFlagCleared\0"
    "speedChanged\0hvTempChanged\0lvTempChanged\0"
    "hvVoltChanged\0lvVoltChanged\0"
    "invSxTempChanged\0invDxTempChanged\0"
    "brakeValChanged\0throttleValChanged\0"
    "parseSerial\0toggleCar\0askHVUpdate\0"
    "setActuatorsRange\0checkCANCommunication\0"
    "checkSensorsError\0steerConnected\0"
    "askStatus\0sendEncState\0askSetupOrIdle\0"
    "PWMCheck\0actuatorRangePendingFlag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Canbus[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       1,  178, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,  134,    2, 0x06 /* Public */,
       6,    1,  141,    2, 0x06 /* Public */,
       8,    1,  144,    2, 0x06 /* Public */,
      10,    0,  147,    2, 0x06 /* Public */,
      11,    0,  148,    2, 0x06 /* Public */,
      12,    0,  149,    2, 0x06 /* Public */,
      13,    0,  150,    2, 0x06 /* Public */,
      14,    0,  151,    2, 0x06 /* Public */,
      15,    0,  152,    2, 0x06 /* Public */,
      16,    0,  153,    2, 0x06 /* Public */,
      17,    0,  154,    2, 0x06 /* Public */,
      18,    0,  155,    2, 0x06 /* Public */,
      19,    0,  156,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    0,  157,    2, 0x0a /* Public */,
      21,    0,  158,    2, 0x0a /* Public */,
      22,    1,  159,    2, 0x0a /* Public */,
      23,    2,  162,    2, 0x0a /* Public */,
      24,    1,  167,    2, 0x0a /* Public */,
      25,    0,  170,    2, 0x0a /* Public */,
      26,    0,  171,    2, 0x0a /* Public */,
      27,    0,  172,    2, 0x0a /* Public */,
      28,    0,  173,    2, 0x0a /* Public */,
      29,    1,  174,    2, 0x0a /* Public */,
      30,    0,  177,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // properties: name, type, flags
      31, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       3,

       0        // eod
};

void Canbus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Canbus *_t = static_cast<Canbus *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->controlStateChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->presetChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->pumpChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->actuatorRangePendingFlagCleared(); break;
        case 4: _t->speedChanged(); break;
        case 5: _t->hvTempChanged(); break;
        case 6: _t->lvTempChanged(); break;
        case 7: _t->hvVoltChanged(); break;
        case 8: _t->lvVoltChanged(); break;
        case 9: _t->invSxTempChanged(); break;
        case 10: _t->invDxTempChanged(); break;
        case 11: _t->brakeValChanged(); break;
        case 12: _t->throttleValChanged(); break;
        case 13: _t->parseSerial(); break;
        case 14: _t->toggleCar(); break;
        case 15: _t->askHVUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->setActuatorsRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: _t->checkCANCommunication((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->checkSensorsError(); break;
        case 19: _t->steerConnected(); break;
        case 20: _t->askStatus(); break;
        case 21: _t->sendEncState(); break;
        case 22: _t->askSetupOrIdle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->PWMCheck(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Canbus::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::controlStateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::presetChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::pumpChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::actuatorRangePendingFlagCleared)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::speedChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::hvTempChanged)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::lvTempChanged)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::hvVoltChanged)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::lvVoltChanged)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::invSxTempChanged)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::invDxTempChanged)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::brakeValChanged)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (Canbus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Canbus::throttleValChanged)) {
                *result = 12;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Canbus *_t = static_cast<Canbus *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->actuatorRangePendingFlag(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Canbus::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Canbus.data,
      qt_meta_data_Canbus,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Canbus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Canbus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Canbus.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Canbus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Canbus::controlStateChanged(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Canbus::presetChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Canbus::pumpChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Canbus::actuatorRangePendingFlagCleared()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Canbus::speedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Canbus::hvTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Canbus::lvTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Canbus::hvVoltChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Canbus::lvVoltChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Canbus::invSxTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void Canbus::invDxTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void Canbus::brakeValChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void Canbus::throttleValChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
