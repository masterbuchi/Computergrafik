/****************************************************************************
** Meta object code from reading C++ file 'oglwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../opengl/oglwidget.h"
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
    QByteArrayData data[24];
    char stringdata0[201];
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
QT_MOC_LITERAL(6, 35, 11), // "changePlace"
QT_MOC_LITERAL(7, 47, 7), // "setRotX"
QT_MOC_LITERAL(8, 55, 5), // "newrx"
QT_MOC_LITERAL(9, 61, 7), // "setRotY"
QT_MOC_LITERAL(10, 69, 5), // "newry"
QT_MOC_LITERAL(11, 75, 7), // "setRotZ"
QT_MOC_LITERAL(12, 83, 5), // "newrz"
QT_MOC_LITERAL(13, 89, 9), // "setPlaceX"
QT_MOC_LITERAL(14, 99, 9), // "newPlaceX"
QT_MOC_LITERAL(15, 109, 9), // "setPlaceY"
QT_MOC_LITERAL(16, 119, 11), // "setCubeRotX"
QT_MOC_LITERAL(17, 131, 11), // "setCubeRotY"
QT_MOC_LITERAL(18, 143, 11), // "setCubeRotZ"
QT_MOC_LITERAL(19, 155, 11), // "setCubeSize"
QT_MOC_LITERAL(20, 167, 7), // "setZoom"
QT_MOC_LITERAL(21, 175, 7), // "newzoom"
QT_MOC_LITERAL(22, 183, 8), // "setLight"
QT_MOC_LITERAL(23, 192, 8) // "newlight"

    },
    "OGLWidget\0changeRotation\0\0dx\0dy\0dz\0"
    "changePlace\0setRotX\0newrx\0setRotY\0"
    "newry\0setRotZ\0newrz\0setPlaceX\0newPlaceX\0"
    "setPlaceY\0setCubeRotX\0setCubeRotY\0"
    "setCubeRotZ\0setCubeSize\0setZoom\0newzoom\0"
    "setLight\0newlight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OGLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   79,    2, 0x06 /* Public */,
       6,    3,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   93,    2, 0x0a /* Public */,
       9,    1,   96,    2, 0x0a /* Public */,
      11,    1,   99,    2, 0x0a /* Public */,
      13,    1,  102,    2, 0x0a /* Public */,
      15,    1,  105,    2, 0x0a /* Public */,
      16,    1,  108,    2, 0x0a /* Public */,
      17,    1,  111,    2, 0x0a /* Public */,
      18,    1,  114,    2, 0x0a /* Public */,
      19,    1,  117,    2, 0x0a /* Public */,
      20,    1,  120,    2, 0x0a /* Public */,
      22,    1,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   23,

       0        // eod
};

void OGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OGLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeRotation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->changePlace((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->setRotX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setRotY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setRotZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setPlaceX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setPlaceY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setCubeRotX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setCubeRotY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setCubeRotZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->setCubeSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setZoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setLight((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        {
            using _t = void (OGLWidget::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OGLWidget::changePlace)) {
                *result = 1;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void OGLWidget::changeRotation(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OGLWidget::changePlace(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
