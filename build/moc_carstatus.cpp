/****************************************************************************
** Meta object code from reading C++ file 'carstatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../header/carstatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'carstatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CarStatus_t {
    QByteArrayData data[82];
    char stringdata0[940];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CarStatus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CarStatus_t qt_meta_stringdata_CarStatus = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CarStatus"
QT_MOC_LITERAL(1, 10, 11), // "tempChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "temperature"
QT_MOC_LITERAL(4, 35, 10), // "socChanged"
QT_MOC_LITERAL(5, 46, 3), // "soc"
QT_MOC_LITERAL(6, 50, 15), // "execModeChanged"
QT_MOC_LITERAL(7, 66, 13), // "ctrlIsEnabled"
QT_MOC_LITERAL(8, 80, 8), // "ctrlIsOn"
QT_MOC_LITERAL(9, 89, 7), // "warning"
QT_MOC_LITERAL(10, 97, 5), // "error"
QT_MOC_LITERAL(11, 103, 16), // "carStatusChanged"
QT_MOC_LITERAL(12, 120, 14), // "warningChanged"
QT_MOC_LITERAL(13, 135, 12), // "errorChanged"
QT_MOC_LITERAL(14, 148, 9), // "toggleCar"
QT_MOC_LITERAL(15, 158, 15), // "HVStatusChanged"
QT_MOC_LITERAL(16, 174, 16), // "CANStatusChanged"
QT_MOC_LITERAL(17, 191, 16), // "ERRStatusChanged"
QT_MOC_LITERAL(18, 208, 17), // "APPSStatusChanged"
QT_MOC_LITERAL(19, 226, 16), // "BSEStatusChanged"
QT_MOC_LITERAL(20, 243, 18), // "STEERStatusChanged"
QT_MOC_LITERAL(21, 262, 18), // "CTRLEnabledChanged"
QT_MOC_LITERAL(22, 281, 15), // "velocityChanged"
QT_MOC_LITERAL(23, 297, 13), // "presetChanged"
QT_MOC_LITERAL(24, 311, 11), // "pumpChanged"
QT_MOC_LITERAL(25, 323, 12), // "speedChanged"
QT_MOC_LITERAL(26, 336, 13), // "hvTempChanged"
QT_MOC_LITERAL(27, 350, 13), // "lvTempChanged"
QT_MOC_LITERAL(28, 364, 13), // "hvVoltChanged"
QT_MOC_LITERAL(29, 378, 13), // "lvVoltChanged"
QT_MOC_LITERAL(30, 392, 16), // "invSxTempChanged"
QT_MOC_LITERAL(31, 409, 16), // "invDxTempChanged"
QT_MOC_LITERAL(32, 426, 15), // "brakeValChanged"
QT_MOC_LITERAL(33, 442, 18), // "throttleValChanged"
QT_MOC_LITERAL(34, 461, 10), // "toggleCtrl"
QT_MOC_LITERAL(35, 472, 15), // "toggleCarStatus"
QT_MOC_LITERAL(36, 488, 7), // "stopCar"
QT_MOC_LITERAL(37, 496, 12), // "changePreset"
QT_MOC_LITERAL(38, 509, 8), // "presetID"
QT_MOC_LITERAL(39, 518, 10), // "changePump"
QT_MOC_LITERAL(40, 529, 6), // "pumpID"
QT_MOC_LITERAL(41, 536, 26), // "setLeftInverterTemperature"
QT_MOC_LITERAL(42, 563, 7), // "uint8_t"
QT_MOC_LITERAL(43, 571, 4), // "val1"
QT_MOC_LITERAL(44, 576, 4), // "val2"
QT_MOC_LITERAL(45, 581, 27), // "setRightInverterTemperature"
QT_MOC_LITERAL(46, 609, 8), // "setSpeed"
QT_MOC_LITERAL(47, 618, 2), // "id"
QT_MOC_LITERAL(48, 621, 9), // "prescaler"
QT_MOC_LITERAL(49, 631, 18), // "setPedalsPrescaler"
QT_MOC_LITERAL(50, 650, 11), // "setThrottle"
QT_MOC_LITERAL(51, 662, 3), // "val"
QT_MOC_LITERAL(52, 666, 8), // "setBrake"
QT_MOC_LITERAL(53, 675, 11), // "setHVStatus"
QT_MOC_LITERAL(54, 687, 8), // "valVolt1"
QT_MOC_LITERAL(55, 696, 8), // "valVolt2"
QT_MOC_LITERAL(56, 705, 8), // "valVolt3"
QT_MOC_LITERAL(57, 714, 8), // "valTemp1"
QT_MOC_LITERAL(58, 723, 8), // "valTemp2"
QT_MOC_LITERAL(59, 732, 11), // "setLVStatus"
QT_MOC_LITERAL(60, 744, 4), // "val3"
QT_MOC_LITERAL(61, 749, 9), // "CANStatus"
QT_MOC_LITERAL(62, 759, 8), // "HVStatus"
QT_MOC_LITERAL(63, 768, 9), // "ERRStatus"
QT_MOC_LITERAL(64, 778, 11), // "CTRLEnabled"
QT_MOC_LITERAL(65, 790, 10), // "APPSStatus"
QT_MOC_LITERAL(66, 801, 10), // "QList<int>"
QT_MOC_LITERAL(67, 812, 9), // "BSEStatus"
QT_MOC_LITERAL(68, 822, 11), // "STEERStatus"
QT_MOC_LITERAL(69, 834, 8), // "velocity"
QT_MOC_LITERAL(70, 843, 6), // "preset"
QT_MOC_LITERAL(71, 850, 4), // "pump"
QT_MOC_LITERAL(72, 855, 9), // "carStatus"
QT_MOC_LITERAL(73, 865, 9), // "invSxTemp"
QT_MOC_LITERAL(74, 875, 9), // "invDxTemp"
QT_MOC_LITERAL(75, 885, 6), // "hvTemp"
QT_MOC_LITERAL(76, 892, 6), // "lvTemp"
QT_MOC_LITERAL(77, 899, 6), // "hvVolt"
QT_MOC_LITERAL(78, 906, 6), // "lvVolt"
QT_MOC_LITERAL(79, 913, 5), // "speed"
QT_MOC_LITERAL(80, 919, 8), // "brakeVal"
QT_MOC_LITERAL(81, 928, 11) // "throttleVal"

    },
    "CarStatus\0tempChanged\0\0temperature\0"
    "socChanged\0soc\0execModeChanged\0"
    "ctrlIsEnabled\0ctrlIsOn\0warning\0error\0"
    "carStatusChanged\0warningChanged\0"
    "errorChanged\0toggleCar\0HVStatusChanged\0"
    "CANStatusChanged\0ERRStatusChanged\0"
    "APPSStatusChanged\0BSEStatusChanged\0"
    "STEERStatusChanged\0CTRLEnabledChanged\0"
    "velocityChanged\0presetChanged\0pumpChanged\0"
    "speedChanged\0hvTempChanged\0lvTempChanged\0"
    "hvVoltChanged\0lvVoltChanged\0"
    "invSxTempChanged\0invDxTempChanged\0"
    "brakeValChanged\0throttleValChanged\0"
    "toggleCtrl\0toggleCarStatus\0stopCar\0"
    "changePreset\0presetID\0changePump\0"
    "pumpID\0setLeftInverterTemperature\0"
    "uint8_t\0val1\0val2\0setRightInverterTemperature\0"
    "setSpeed\0id\0prescaler\0setPedalsPrescaler\0"
    "setThrottle\0val\0setBrake\0setHVStatus\0"
    "valVolt1\0valVolt2\0valVolt3\0valTemp1\0"
    "valTemp2\0setLVStatus\0val3\0CANStatus\0"
    "HVStatus\0ERRStatus\0CTRLEnabled\0"
    "APPSStatus\0QList<int>\0BSEStatus\0"
    "STEERStatus\0velocity\0preset\0pump\0"
    "carStatus\0invSxTemp\0invDxTemp\0hvTemp\0"
    "lvTemp\0hvVolt\0lvVolt\0speed\0brakeVal\0"
    "throttleVal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CarStatus[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
      22,  304, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      26,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  209,    2, 0x06 /* Public */,
       4,    1,  212,    2, 0x06 /* Public */,
       6,    4,  215,    2, 0x06 /* Public */,
      11,    0,  224,    2, 0x06 /* Public */,
      12,    0,  225,    2, 0x06 /* Public */,
      13,    0,  226,    2, 0x06 /* Public */,
      14,    0,  227,    2, 0x06 /* Public */,
      15,    0,  228,    2, 0x06 /* Public */,
      16,    0,  229,    2, 0x06 /* Public */,
      17,    0,  230,    2, 0x06 /* Public */,
      18,    0,  231,    2, 0x06 /* Public */,
      19,    0,  232,    2, 0x06 /* Public */,
      20,    0,  233,    2, 0x06 /* Public */,
      21,    0,  234,    2, 0x06 /* Public */,
      22,    0,  235,    2, 0x06 /* Public */,
      23,    0,  236,    2, 0x06 /* Public */,
      24,    0,  237,    2, 0x06 /* Public */,
      25,    0,  238,    2, 0x06 /* Public */,
      26,    0,  239,    2, 0x06 /* Public */,
      27,    0,  240,    2, 0x06 /* Public */,
      28,    0,  241,    2, 0x06 /* Public */,
      29,    0,  242,    2, 0x06 /* Public */,
      30,    0,  243,    2, 0x06 /* Public */,
      31,    0,  244,    2, 0x06 /* Public */,
      32,    0,  245,    2, 0x06 /* Public */,
      33,    0,  246,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      34,    0,  247,    2, 0x0a /* Public */,
      35,    0,  248,    2, 0x0a /* Public */,
      36,    0,  249,    2, 0x0a /* Public */,
      37,    1,  250,    2, 0x0a /* Public */,
      39,    1,  253,    2, 0x0a /* Public */,
      41,    2,  256,    2, 0x0a /* Public */,
      45,    2,  261,    2, 0x0a /* Public */,
      46,    4,  266,    2, 0x0a /* Public */,
      49,    1,  275,    2, 0x0a /* Public */,
      50,    1,  278,    2, 0x0a /* Public */,
      52,    1,  281,    2, 0x0a /* Public */,
      53,    6,  284,    2, 0x0a /* Public */,
      59,    3,  297,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,   10,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::Void, 0x80000000 | 42, 0x80000000 | 42,   43,   44,
    QMetaType::Void, 0x80000000 | 42, 0x80000000 | 42,   43,   44,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   47,   43,   44,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   51,
    QMetaType::Void, QMetaType::Int,   51,
    QMetaType::Void, 0x80000000 | 42, 0x80000000 | 42, 0x80000000 | 42, 0x80000000 | 42, 0x80000000 | 42, 0x80000000 | 42,   47,   54,   55,   56,   57,   58,
    QMetaType::Void, 0x80000000 | 42, 0x80000000 | 42, 0x80000000 | 42,   43,   44,   60,

 // properties: name, type, flags
      61, QMetaType::QString, 0x00495001,
      62, QMetaType::QString, 0x00495001,
      63, QMetaType::QString, 0x00495001,
      64, QMetaType::QString, 0x00495001,
      65, 0x80000000 | 66, 0x00495009,
      67, 0x80000000 | 66, 0x00495009,
      68, 0x80000000 | 66, 0x00495009,
      69, QMetaType::Int, 0x00495001,
      70, QMetaType::Int, 0x00495001,
      71, QMetaType::Int, 0x00495001,
       9, QMetaType::Int, 0x00495001,
      10, QMetaType::Int, 0x00495001,
      72, QMetaType::Int, 0x00495001,
      73, QMetaType::Int, 0x00495001,
      74, QMetaType::Int, 0x00495001,
      75, QMetaType::Int, 0x00495001,
      76, QMetaType::Int, 0x00495001,
      77, QMetaType::Int, 0x00495001,
      78, QMetaType::Int, 0x00495001,
      79, QMetaType::Int, 0x00495001,
      80, QMetaType::Int, 0x00495001,
      81, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       8,
       7,
       9,
      13,
      10,
      11,
      12,
      14,
      15,
      16,
       4,
       5,
       3,
      22,
      23,
      18,
      19,
      20,
      21,
      17,
      24,
      25,

       0        // eod
};

void CarStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CarStatus *_t = static_cast<CarStatus *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tempChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->socChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->execModeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 3: _t->carStatusChanged(); break;
        case 4: _t->warningChanged(); break;
        case 5: _t->errorChanged(); break;
        case 6: _t->toggleCar(); break;
        case 7: _t->HVStatusChanged(); break;
        case 8: _t->CANStatusChanged(); break;
        case 9: _t->ERRStatusChanged(); break;
        case 10: _t->APPSStatusChanged(); break;
        case 11: _t->BSEStatusChanged(); break;
        case 12: _t->STEERStatusChanged(); break;
        case 13: _t->CTRLEnabledChanged(); break;
        case 14: _t->velocityChanged(); break;
        case 15: _t->presetChanged(); break;
        case 16: _t->pumpChanged(); break;
        case 17: _t->speedChanged(); break;
        case 18: _t->hvTempChanged(); break;
        case 19: _t->lvTempChanged(); break;
        case 20: _t->hvVoltChanged(); break;
        case 21: _t->lvVoltChanged(); break;
        case 22: _t->invSxTempChanged(); break;
        case 23: _t->invDxTempChanged(); break;
        case 24: _t->brakeValChanged(); break;
        case 25: _t->throttleValChanged(); break;
        case 26: { int _r = _t->toggleCtrl();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 27: { int _r = _t->toggleCarStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 28: { int _r = _t->stopCar();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 29: _t->changePreset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->changePump((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->setLeftInverterTemperature((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 32: _t->setRightInverterTemperature((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 33: _t->setSpeed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 34: _t->setPedalsPrescaler((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->setThrottle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->setBrake((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->setHVStatus((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])),(*reinterpret_cast< uint8_t(*)>(_a[4])),(*reinterpret_cast< uint8_t(*)>(_a[5])),(*reinterpret_cast< uint8_t(*)>(_a[6]))); break;
        case 38: _t->setLVStatus((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CarStatus::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::tempChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::socChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::execModeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::carStatusChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::warningChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::errorChanged)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::toggleCar)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::HVStatusChanged)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::CANStatusChanged)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::ERRStatusChanged)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::APPSStatusChanged)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::BSEStatusChanged)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::STEERStatusChanged)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::CTRLEnabledChanged)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::velocityChanged)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::presetChanged)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::pumpChanged)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::speedChanged)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::hvTempChanged)) {
                *result = 18;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::lvTempChanged)) {
                *result = 19;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::hvVoltChanged)) {
                *result = 20;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::lvVoltChanged)) {
                *result = 21;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::invSxTempChanged)) {
                *result = 22;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::invDxTempChanged)) {
                *result = 23;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::brakeValChanged)) {
                *result = 24;
                return;
            }
        }
        {
            typedef void (CarStatus::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarStatus::throttleValChanged)) {
                *result = 25;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
        case 5:
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        CarStatus *_t = static_cast<CarStatus *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->CANStatus(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->HVStatus(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->ERRStatus(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->CTRLEnabled(); break;
        case 4: *reinterpret_cast< QList<int>*>(_v) = _t->APPSStatus(); break;
        case 5: *reinterpret_cast< QList<int>*>(_v) = _t->BSEStatus(); break;
        case 6: *reinterpret_cast< QList<int>*>(_v) = _t->STEERStatus(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->velocity(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->preset(); break;
        case 9: *reinterpret_cast< int*>(_v) = _t->pump(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->warning(); break;
        case 11: *reinterpret_cast< int*>(_v) = _t->error(); break;
        case 12: *reinterpret_cast< int*>(_v) = _t->carStatus(); break;
        case 13: *reinterpret_cast< int*>(_v) = _t->invSxTemp(); break;
        case 14: *reinterpret_cast< int*>(_v) = _t->invDxTemp(); break;
        case 15: *reinterpret_cast< int*>(_v) = _t->hvTemp(); break;
        case 16: *reinterpret_cast< int*>(_v) = _t->lvTemp(); break;
        case 17: *reinterpret_cast< int*>(_v) = _t->hvVolt(); break;
        case 18: *reinterpret_cast< int*>(_v) = _t->lvVolt(); break;
        case 19: *reinterpret_cast< int*>(_v) = _t->speed(); break;
        case 20: *reinterpret_cast< int*>(_v) = _t->brakeVal(); break;
        case 21: *reinterpret_cast< int*>(_v) = _t->throttleVal(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject CarStatus::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CarStatus.data,
      qt_meta_data_CarStatus,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CarStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CarStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CarStatus.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CarStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 39;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 22;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CarStatus::tempChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CarStatus::socChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CarStatus::execModeChanged(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CarStatus::carStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CarStatus::warningChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CarStatus::errorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CarStatus::toggleCar()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void CarStatus::HVStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void CarStatus::CANStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void CarStatus::ERRStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void CarStatus::APPSStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void CarStatus::BSEStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void CarStatus::STEERStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void CarStatus::CTRLEnabledChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void CarStatus::velocityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void CarStatus::presetChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void CarStatus::pumpChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void CarStatus::speedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void CarStatus::hvTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}

// SIGNAL 19
void CarStatus::lvTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void CarStatus::hvVoltChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void CarStatus::lvVoltChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}

// SIGNAL 22
void CarStatus::invSxTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 22, nullptr);
}

// SIGNAL 23
void CarStatus::invDxTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 23, nullptr);
}

// SIGNAL 24
void CarStatus::brakeValChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 24, nullptr);
}

// SIGNAL 25
void CarStatus::throttleValChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 25, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
