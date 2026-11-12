/****************************************************************************
** Meta object code from reading C++ file 'ArkivPrizeAwarder.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "ArkivPrizeAwarder.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ArkivPrizeAwarder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ArkivPrizeAwarder[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      54,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ArkivPrizeAwarder[] = {
    "ArkivPrizeAwarder\0\0"
    "handlePrizeAwardRequestFinished()\0"
    "handleImageRequestFinished()\0"
};

void ArkivPrizeAwarder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ArkivPrizeAwarder *_t = static_cast<ArkivPrizeAwarder *>(_o);
        switch (_id) {
        case 0: _t->handlePrizeAwardRequestFinished(); break;
        case 1: _t->handleImageRequestFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ArkivPrizeAwarder::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ArkivPrizeAwarder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ArkivPrizeAwarder,
      qt_meta_data_ArkivPrizeAwarder, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ArkivPrizeAwarder::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ArkivPrizeAwarder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ArkivPrizeAwarder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ArkivPrizeAwarder))
        return static_cast<void*>(const_cast< ArkivPrizeAwarder*>(this));
    return QObject::qt_metacast(_clname);
}

int ArkivPrizeAwarder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
