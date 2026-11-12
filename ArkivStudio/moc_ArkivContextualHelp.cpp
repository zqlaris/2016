/****************************************************************************
** Meta object code from reading C++ file 'ArkivContextualHelp.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "ArkivContextualHelp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ArkivContextualHelp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ArkivContextualHelpService[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   55,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ArkivContextualHelpService[] = {
    "ArkivContextualHelpService\0\0"
    "helpTopicChanged(QString)\0helpTopic\0"
    "onHelpTopicChanged(QString)\0"
};

void ArkivContextualHelpService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ArkivContextualHelpService *_t = static_cast<ArkivContextualHelpService *>(_o);
        switch (_id) {
        case 0: _t->helpTopicChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->onHelpTopicChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ArkivContextualHelpService::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ArkivContextualHelpService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ArkivContextualHelpService,
      qt_meta_data_ArkivContextualHelpService, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ArkivContextualHelpService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ArkivContextualHelpService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ArkivContextualHelpService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ArkivContextualHelpService))
        return static_cast<void*>(const_cast< ArkivContextualHelpService*>(this));
    return QObject::qt_metacast(_clname);
}

int ArkivContextualHelpService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void ArkivContextualHelpService::helpTopicChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_ArkivHelpWebView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ArkivHelpWebView[] = {
    "ArkivHelpWebView\0\0loadProgress(int)\0"
};

void ArkivHelpWebView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ArkivHelpWebView *_t = static_cast<ArkivHelpWebView *>(_o);
        switch (_id) {
        case 0: _t->loadProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ArkivHelpWebView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ArkivHelpWebView::staticMetaObject = {
    { &ArkivBrowser::staticMetaObject, qt_meta_stringdata_ArkivHelpWebView,
      qt_meta_data_ArkivHelpWebView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ArkivHelpWebView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ArkivHelpWebView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ArkivHelpWebView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ArkivHelpWebView))
        return static_cast<void*>(const_cast< ArkivHelpWebView*>(this));
    return ArkivBrowser::qt_metacast(_clname);
}

int ArkivHelpWebView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ArkivBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_ArkivContextualHelp[] = {

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
      38,   22,   21,   21, 0x0a,
      78,   68,   21,   21, 0x0a,
     110,  106,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ArkivContextualHelp[] = {
    "ArkivContextualHelp\0\0isAuthenticated\0"
    "onAuthenticationChanged(bool)\0helpTopic\0"
    "onHelpTopicChanged(QString)\0url\0"
    "linkClicked(QUrl)\0"
};

void ArkivContextualHelp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ArkivContextualHelp *_t = static_cast<ArkivContextualHelp *>(_o);
        switch (_id) {
        case 0: _t->onAuthenticationChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->onHelpTopicChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->linkClicked((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ArkivContextualHelp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ArkivContextualHelp::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ArkivContextualHelp,
      qt_meta_data_ArkivContextualHelp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ArkivContextualHelp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ArkivContextualHelp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ArkivContextualHelp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ArkivContextualHelp))
        return static_cast<void*>(const_cast< ArkivContextualHelp*>(this));
    return QWidget::qt_metacast(_clname);
}

int ArkivContextualHelp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
