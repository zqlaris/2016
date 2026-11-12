/****************************************************************************
** Meta object code from reading C++ file 'Arkiv.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "Arkiv.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Arkiv.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Arkiv[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,    8,    7,    7, 0x05,
      75,   64,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     104,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Arkiv[] = {
    "Arkiv\0\0message,type\0"
    "newOutputMessage(QString,RBX::MessageType)\0"
    "event,wait\0marshallAppEvent(void*,bool)\0"
    "onTimeOut()\0"
};

void Arkiv::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Arkiv *_t = static_cast<Arkiv *>(_o);
        switch (_id) {
        case 0: _t->newOutputMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< RBX::MessageType(*)>(_a[2]))); break;
        case 1: _t->marshallAppEvent((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->onTimeOut(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Arkiv::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Arkiv::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Arkiv,
      qt_meta_data_Arkiv, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Arkiv::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Arkiv::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Arkiv::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Arkiv))
        return static_cast<void*>(const_cast< Arkiv*>(this));
    if (!strcmp(_clname, "RBX::TeleportCallback"))
        return static_cast< RBX::TeleportCallback*>(const_cast< Arkiv*>(this));
    return QObject::qt_metacast(_clname);
}

int Arkiv::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Arkiv::newOutputMessage(const QString _t1, RBX::MessageType _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Arkiv::marshallAppEvent(void * _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
