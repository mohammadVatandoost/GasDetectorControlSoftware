/****************************************************************************
** Meta object code from reading C++ file 'backend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "backend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Backend_t {
    QByteArrayData data[41];
    char stringdata0[575];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Backend_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Backend_t qt_meta_stringdata_Backend = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Backend"
QT_MOC_LITERAL(1, 8, 21), // "notifyInfoDataChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 11), // "updateChart"
QT_MOC_LITERAL(4, 43, 16), // "QAbstractSeries*"
QT_MOC_LITERAL(5, 60, 11), // "chartSeries"
QT_MOC_LITERAL(6, 72, 8), // "sensorId"
QT_MOC_LITERAL(7, 81, 12), // "setAxisXTime"
QT_MOC_LITERAL(8, 94, 14), // "QDateTimeAxis*"
QT_MOC_LITERAL(9, 109, 4), // "axis"
QT_MOC_LITERAL(10, 114, 17), // "recieveSerialPort"
QT_MOC_LITERAL(11, 132, 9), // "timerSlot"
QT_MOC_LITERAL(12, 142, 14), // "setSensorsList"
QT_MOC_LITERAL(13, 157, 12), // "SensorsList*"
QT_MOC_LITERAL(14, 170, 11), // "sensorsList"
QT_MOC_LITERAL(15, 182, 11), // "setDataBase"
QT_MOC_LITERAL(16, 194, 9), // "DataBase*"
QT_MOC_LITERAL(17, 204, 8), // "dataBase"
QT_MOC_LITERAL(18, 213, 11), // "startSensor"
QT_MOC_LITERAL(19, 225, 14), // "startAllSensor"
QT_MOC_LITERAL(20, 240, 12), // "setPumpValue"
QT_MOC_LITERAL(21, 253, 11), // "configValue"
QT_MOC_LITERAL(22, 265, 12), // "getPumpValue"
QT_MOC_LITERAL(23, 278, 13), // "getPumpStatus"
QT_MOC_LITERAL(24, 292, 13), // "getHumidityIn"
QT_MOC_LITERAL(25, 306, 14), // "getHumidityOut"
QT_MOC_LITERAL(26, 321, 15), // "getHumidityArea"
QT_MOC_LITERAL(27, 337, 11), // "getTempArea"
QT_MOC_LITERAL(28, 349, 14), // "getPresureArea"
QT_MOC_LITERAL(29, 364, 18), // "getFlowErrorStatus"
QT_MOC_LITERAL(30, 383, 24), // "getElectricalErrorStatus"
QT_MOC_LITERAL(31, 408, 17), // "getChargingStatus"
QT_MOC_LITERAL(32, 426, 16), // "getBatteryCharge"
QT_MOC_LITERAL(33, 443, 20), // "sendSensorDataHeater"
QT_MOC_LITERAL(34, 464, 17), // "sendSensorDataRec"
QT_MOC_LITERAL(35, 482, 13), // "turnOffHeater"
QT_MOC_LITERAL(36, 496, 16), // "getSensorTempMin"
QT_MOC_LITERAL(37, 513, 16), // "getSensorTempMax"
QT_MOC_LITERAL(38, 530, 15), // "getSensorResMin"
QT_MOC_LITERAL(39, 546, 15), // "getSensorResMax"
QT_MOC_LITERAL(40, 562, 12) // "openKeyboard"

    },
    "Backend\0notifyInfoDataChanged\0\0"
    "updateChart\0QAbstractSeries*\0chartSeries\0"
    "sensorId\0setAxisXTime\0QDateTimeAxis*\0"
    "axis\0recieveSerialPort\0timerSlot\0"
    "setSensorsList\0SensorsList*\0sensorsList\0"
    "setDataBase\0DataBase*\0dataBase\0"
    "startSensor\0startAllSensor\0setPumpValue\0"
    "configValue\0getPumpValue\0getPumpStatus\0"
    "getHumidityIn\0getHumidityOut\0"
    "getHumidityArea\0getTempArea\0getPresureArea\0"
    "getFlowErrorStatus\0getElectricalErrorStatus\0"
    "getChargingStatus\0getBatteryCharge\0"
    "sendSensorDataHeater\0sendSensorDataRec\0"
    "turnOffHeater\0getSensorTempMin\0"
    "getSensorTempMax\0getSensorResMin\0"
    "getSensorResMax\0openKeyboard"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Backend[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  159,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,  160,    2, 0x0a /* Public */,
       7,    1,  165,    2, 0x0a /* Public */,
      10,    0,  168,    2, 0x08 /* Private */,
      11,    0,  169,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      12,    1,  170,    2, 0x02 /* Public */,
      15,    1,  173,    2, 0x02 /* Public */,
      18,    1,  176,    2, 0x02 /* Public */,
      19,    0,  179,    2, 0x02 /* Public */,
      20,    1,  180,    2, 0x02 /* Public */,
      22,    0,  183,    2, 0x02 /* Public */,
      23,    0,  184,    2, 0x02 /* Public */,
      24,    0,  185,    2, 0x02 /* Public */,
      25,    0,  186,    2, 0x02 /* Public */,
      26,    0,  187,    2, 0x02 /* Public */,
      27,    0,  188,    2, 0x02 /* Public */,
      28,    0,  189,    2, 0x02 /* Public */,
      29,    0,  190,    2, 0x02 /* Public */,
      30,    0,  191,    2, 0x02 /* Public */,
      31,    0,  192,    2, 0x02 /* Public */,
      32,    0,  193,    2, 0x02 /* Public */,
      33,    1,  194,    2, 0x02 /* Public */,
      34,    1,  197,    2, 0x02 /* Public */,
      35,    1,  200,    2, 0x02 /* Public */,
      36,    0,  203,    2, 0x02 /* Public */,
      37,    0,  204,    2, 0x02 /* Public */,
      38,    0,  205,    2, 0x02 /* Public */,
      39,    0,  206,    2, 0x02 /* Public */,
      40,    0,  207,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Int,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,

       0        // eod
};

void Backend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Backend *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->notifyInfoDataChanged(); break;
        case 1: _t->updateChart((*reinterpret_cast< QAbstractSeries*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->setAxisXTime((*reinterpret_cast< QDateTimeAxis*(*)>(_a[1]))); break;
        case 3: _t->recieveSerialPort(); break;
        case 4: _t->timerSlot(); break;
        case 5: _t->setSensorsList((*reinterpret_cast< SensorsList*(*)>(_a[1]))); break;
        case 6: _t->setDataBase((*reinterpret_cast< DataBase*(*)>(_a[1]))); break;
        case 7: _t->startSensor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->startAllSensor(); break;
        case 9: _t->setPumpValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: { int _r = _t->getPumpValue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->getPumpStatus();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { int _r = _t->getHumidityIn();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 13: { int _r = _t->getHumidityOut();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 14: { int _r = _t->getHumidityArea();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 15: { double _r = _t->getTempArea();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 16: { double _r = _t->getPresureArea();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 17: { bool _r = _t->getFlowErrorStatus();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 18: { bool _r = _t->getElectricalErrorStatus();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: { bool _r = _t->getChargingStatus();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 20: { QString _r = _t->getBatteryCharge();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->sendSensorDataHeater((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->sendSensorDataRec((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->turnOffHeater((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: { int _r = _t->getSensorTempMin();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 25: { int _r = _t->getSensorTempMax();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 26: { int _r = _t->getSensorResMin();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 27: { int _r = _t->getSensorResMax();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->openKeyboard(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSeries* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QDateTimeAxis* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SensorsList* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Backend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Backend::notifyInfoDataChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Backend::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Backend.data,
    qt_meta_data_Backend,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Backend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Backend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Backend.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Backend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void Backend::notifyInfoDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE