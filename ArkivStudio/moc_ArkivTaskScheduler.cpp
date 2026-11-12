/****************************************************************************
** Meta object code from reading C++ file 'ArkivTaskScheduler.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "ArkivTaskScheduler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ArkivTaskScheduler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ArkivTaskScheduler[] = {

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
      29,   21,   20,   20, 0x0a,
      46,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ArkivTaskScheduler[] = {
    "ArkivTaskScheduler\0\0visible\0"
    "setVisible(bool)\0updateValues()\0"
};

void ArkivTaskScheduler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ArkivTaskScheduler *_t = static_cast<ArkivTaskScheduler *>(_o);
        switch (_id) {
        case 0: _t->setVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->updateValues(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ArkivTaskScheduler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ArkivTaskScheduler::staticMetaObject = {
    { &ArkivReportView::staticMetaObject, qt_meta_stringdata_ArkivTaskScheduler,
      qt_meta_data_ArkivTaskScheduler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ArkivTaskScheduler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ArkivTaskScheduler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ArkivTaskScheduler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ArkivTaskScheduler))
        return static_cast<void*>(const_cast< ArkivTaskScheduler*>(this));
    return ArkivReportView::qt_metacast(_clname);
}

int ArkivTaskScheduler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ArkivReportView::qt_metacall(_c, _id, _a);
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
