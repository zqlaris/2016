/****************************************************************************
** Meta object code from reading C++ file 'ArkivToolBox.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "ArkivToolBox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ArkivToolBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ArkivToolBox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   15,   14,   14, 0x0a,
      65,   61,   14,   14, 0x0a,
      82,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ArkivToolBox[] = {
    "ArkivToolBox\0\0isAuthenticated\0"
    "onAuthenticationChanged(bool)\0url\0"
    "loadUrl(QString)\0initJavascript()\0"
};

void ArkivToolBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ArkivToolBox *_t = static_cast<ArkivToolBox *>(_o);
        switch (_id) {
        case 0: _t->onAuthenticationChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->loadUrl((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->initJavascript(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ArkivToolBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ArkivToolBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ArkivToolBox,
      qt_meta_data_ArkivToolBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ArkivToolBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ArkivToolBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ArkivToolBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ArkivToolBox))
        return static_cast<void*>(const_cast< ArkivToolBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int ArkivToolBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
