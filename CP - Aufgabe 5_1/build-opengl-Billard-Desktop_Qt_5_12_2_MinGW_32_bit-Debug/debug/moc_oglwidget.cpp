/****************************************************************************
** Meta object code from reading C++ file 'oglwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Billard_Dreieck/oglwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oglwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OGLWidget_t {
    QByteArrayData data[17];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OGLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OGLWidget_t qt_meta_stringdata_OGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "OGLWidget"
QT_MOC_LITERAL(1, 10, 14), // "changeRotation"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 2), // "dx"
QT_MOC_LITERAL(4, 29, 2), // "dy"
QT_MOC_LITERAL(5, 32, 2), // "dz"
QT_MOC_LITERAL(6, 35, 7), // "setRotX"
QT_MOC_LITERAL(7, 43, 5), // "newrx"
QT_MOC_LITERAL(8, 49, 7), // "setRotY"
QT_MOC_LITERAL(9, 57, 5), // "newry"
QT_MOC_LITERAL(10, 63, 7), // "setRotZ"
QT_MOC_LITERAL(11, 71, 5), // "newrz"
QT_MOC_LITERAL(12, 77, 7), // "setZoom"
QT_MOC_LITERAL(13, 85, 7), // "newzoom"
QT_MOC_LITERAL(14, 93, 9), // "setUnfold"
QT_MOC_LITERAL(15, 103, 9), // "newunfold"
QT_MOC_LITERAL(16, 113, 13) // "stepAnimation"

    },
    "OGLWidget\0changeRotation\0\0dx\0dy\0dz\0"
    "setRotX\0newrx\0setRotY\0newry\0setRotZ\0"
    "newrz\0setZoom\0newzoom\0setUnfold\0"
    "newunfold\0stepAnimation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OGLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   56,    2, 0x0a /* Public */,
       8,    1,   59,    2, 0x0a /* Public */,
      10,    1,   62,    2, 0x0a /* Public */,
      12,    1,   65,    2, 0x0a /* Public */,
      14,    1,   68,    2, 0x0a /* Public */,
      16,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,

       0        // eod
};

void OGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OGLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeRotation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->setRotX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setRotY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setRotZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setZoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setUnfold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->stepAnimation(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OGLWidget::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OGLWidget::changeRotation)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OGLWidget::staticMetaObject = { {
    &QOpenGLWidget::staticMetaObject,
    qt_meta_stringdata_OGLWidget.data,
    qt_meta_data_OGLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OGLWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int OGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void OGLWidget::changeRotation(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
