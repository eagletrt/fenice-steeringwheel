/****************************************************************************
** Meta object code from reading C++ file 'buttons_x86.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../header/buttons_x86.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buttons_x86.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Buttons_t {
    QByteArrayData data[11];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Buttons_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Buttons_t qt_meta_stringdata_Buttons = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Buttons"
QT_MOC_LITERAL(1, 8, 10), // "btnClicked"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 5), // "btnID"
QT_MOC_LITERAL(4, 26, 10), // "btnPressed"
QT_MOC_LITERAL(5, 37, 11), // "btnReleased"
QT_MOC_LITERAL(6, 49, 13), // "presetChanged"
QT_MOC_LITERAL(7, 63, 8), // "presetID"
QT_MOC_LITERAL(8, 72, 11), // "pumpChanged"
QT_MOC_LITERAL(9, 84, 6), // "pumpID"
QT_MOC_LITERAL(10, 91, 19) // "handleKeyboardPress"

    },
    "Buttons\0btnClicked\0\0btnID\0btnPressed\0"
    "btnReleased\0presetChanged\0presetID\0"
    "pumpChanged\0pumpID\0handleKeyboardPress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Buttons[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    1,   50,    2, 0x06 /* Public */,
       6,    1,   53,    2, 0x06 /* Public */,
       8,    1,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void Buttons::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Buttons *_t = static_cast<Buttons *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->btnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->btnPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->btnReleased((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->presetChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->pumpChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->handleKeyboardPress((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Buttons::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Buttons::btnClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Buttons::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Buttons::btnPressed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Buttons::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Buttons::btnReleased)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Buttons::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Buttons::presetChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Buttons::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Buttons::pumpChanged)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Buttons::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Buttons.data,
      qt_meta_data_Buttons,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Buttons::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Buttons::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Buttons.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Buttons::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Buttons::btnClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Buttons::btnPressed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Buttons::btnReleased(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Buttons::presetChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Buttons::pumpChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
