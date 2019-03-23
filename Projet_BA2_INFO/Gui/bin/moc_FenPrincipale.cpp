/****************************************************************************
** Meta object code from reading C++ file 'FenPrincipale.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../incl/FenPrincipale.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FenPrincipale.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FenPrincipale_t {
    QByteArrayData data[21];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FenPrincipale_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FenPrincipale_t qt_meta_stringdata_FenPrincipale = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FenPrincipale"
QT_MOC_LITERAL(1, 14, 11), // "checkSignIn"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "checkRegister"
QT_MOC_LITERAL(4, 41, 12), // "goToRegister"
QT_MOC_LITERAL(5, 54, 9), // "goToLogIn"
QT_MOC_LITERAL(6, 64, 8), // "goToGame"
QT_MOC_LITERAL(7, 73, 11), // "goToClassic"
QT_MOC_LITERAL(8, 85, 8), // "goToMenu"
QT_MOC_LITERAL(9, 94, 11), // "sendMessage"
QT_MOC_LITERAL(10, 106, 6), // "myShow"
QT_MOC_LITERAL(11, 113, 9), // "gameStart"
QT_MOC_LITERAL(12, 123, 11), // "std::string"
QT_MOC_LITERAL(13, 135, 8), // "opponent"
QT_MOC_LITERAL(14, 144, 15), // "connectionError"
QT_MOC_LITERAL(15, 160, 3), // "win"
QT_MOC_LITERAL(16, 164, 4), // "lose"
QT_MOC_LITERAL(17, 169, 11), // "recvMessage"
QT_MOC_LITERAL(18, 181, 4), // "name"
QT_MOC_LITERAL(19, 186, 3), // "mov"
QT_MOC_LITERAL(20, 190, 13) // "pingForUpdate"

    },
    "FenPrincipale\0checkSignIn\0\0checkRegister\0"
    "goToRegister\0goToLogIn\0goToGame\0"
    "goToClassic\0goToMenu\0sendMessage\0"
    "myShow\0gameStart\0std::string\0opponent\0"
    "connectionError\0win\0lose\0recvMessage\0"
    "name\0mov\0pingForUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FenPrincipale[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x0a /* Public */,
       3,    0,   90,    2, 0x0a /* Public */,
       4,    0,   91,    2, 0x0a /* Public */,
       5,    0,   92,    2, 0x0a /* Public */,
       6,    0,   93,    2, 0x0a /* Public */,
       7,    0,   94,    2, 0x0a /* Public */,
       8,    0,   95,    2, 0x0a /* Public */,
       9,    0,   96,    2, 0x0a /* Public */,
      10,    0,   97,    2, 0x0a /* Public */,
      11,    1,   98,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,
      17,    2,  104,    2, 0x0a /* Public */,
      20,    0,  109,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 12,   18,   19,
    QMetaType::Void,

       0        // eod
};

void FenPrincipale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FenPrincipale *_t = static_cast<FenPrincipale *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->checkSignIn(); break;
        case 1: _t->checkRegister(); break;
        case 2: _t->goToRegister(); break;
        case 3: _t->goToLogIn(); break;
        case 4: _t->goToGame(); break;
        case 5: _t->goToClassic(); break;
        case 6: _t->goToMenu(); break;
        case 7: _t->sendMessage(); break;
        case 8: _t->myShow(); break;
        case 9: _t->gameStart((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 10: _t->connectionError(); break;
        case 11: _t->win(); break;
        case 12: _t->lose(); break;
        case 13: _t->recvMessage((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 14: _t->pingForUpdate(); break;
        default: ;
        }
    }
}

const QMetaObject FenPrincipale::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FenPrincipale.data,
      qt_meta_data_FenPrincipale,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FenPrincipale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FenPrincipale::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FenPrincipale.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "AbstractInterface"))
        return static_cast< AbstractInterface*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int FenPrincipale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
