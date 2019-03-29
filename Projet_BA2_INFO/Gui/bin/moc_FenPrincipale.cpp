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
<<<<<<< HEAD
    QByteArrayData data[35];
    char stringdata0[350];
=======
    QByteArrayData data[40];
    char stringdata0[400];
>>>>>>> f483a9a35ebd2a72d6def6f8e7e4ae89eb702146
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
QT_MOC_LITERAL(8, 85, 12), // "goToTrappist"
QT_MOC_LITERAL(9, 98, 8), // "goToMenu"
<<<<<<< HEAD
QT_MOC_LITERAL(10, 107, 11), // "sendMessage"
QT_MOC_LITERAL(11, 119, 14), // "showFriendList"
QT_MOC_LITERAL(12, 134, 8), // "setTheme"
QT_MOC_LITERAL(13, 143, 11), // "std::string"
QT_MOC_LITERAL(14, 155, 4), // "pool"
QT_MOC_LITERAL(15, 160, 9), // "addFriend"
QT_MOC_LITERAL(16, 170, 12), // "removeFriend"
QT_MOC_LITERAL(17, 183, 13), // "setFriendMenu"
QT_MOC_LITERAL(18, 197, 12), // "setThemeMenu"
QT_MOC_LITERAL(19, 210, 8), // "setPool0"
QT_MOC_LITERAL(20, 219, 8), // "setPool1"
QT_MOC_LITERAL(21, 228, 8), // "setPool2"
QT_MOC_LITERAL(22, 237, 8), // "setPool3"
QT_MOC_LITERAL(23, 246, 8), // "setPool4"
QT_MOC_LITERAL(24, 255, 6), // "myShow"
QT_MOC_LITERAL(25, 262, 9), // "gameStart"
QT_MOC_LITERAL(26, 272, 8), // "opponent"
QT_MOC_LITERAL(27, 281, 16), // "AbstractPlateau*"
QT_MOC_LITERAL(28, 298, 5), // "board"
QT_MOC_LITERAL(29, 304, 15), // "connectionError"
QT_MOC_LITERAL(30, 320, 3), // "win"
QT_MOC_LITERAL(31, 324, 4), // "lose"
QT_MOC_LITERAL(32, 329, 11), // "recvMessage"
QT_MOC_LITERAL(33, 341, 4), // "name"
QT_MOC_LITERAL(34, 346, 3) // "mov"
=======
QT_MOC_LITERAL(10, 107, 8), // "goToStat"
QT_MOC_LITERAL(11, 116, 11), // "sendMessage"
QT_MOC_LITERAL(12, 128, 14), // "showFriendList"
QT_MOC_LITERAL(13, 143, 8), // "setTheme"
QT_MOC_LITERAL(14, 152, 11), // "std::string"
QT_MOC_LITERAL(15, 164, 4), // "pool"
QT_MOC_LITERAL(16, 169, 9), // "addFriend"
QT_MOC_LITERAL(17, 179, 12), // "removeFriend"
QT_MOC_LITERAL(18, 192, 10), // "showFriend"
QT_MOC_LITERAL(19, 203, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(20, 220, 4), // "item"
QT_MOC_LITERAL(21, 225, 13), // "setFriendMenu"
QT_MOC_LITERAL(22, 239, 12), // "setThemeMenu"
QT_MOC_LITERAL(23, 252, 8), // "setPool0"
QT_MOC_LITERAL(24, 261, 8), // "setPool1"
QT_MOC_LITERAL(25, 270, 8), // "setPool2"
QT_MOC_LITERAL(26, 279, 8), // "setPool3"
QT_MOC_LITERAL(27, 288, 8), // "setPool4"
QT_MOC_LITERAL(28, 297, 12), // "sendPosition"
QT_MOC_LITERAL(29, 310, 3), // "pos"
QT_MOC_LITERAL(30, 314, 6), // "myShow"
QT_MOC_LITERAL(31, 321, 9), // "gameStart"
QT_MOC_LITERAL(32, 331, 8), // "opponent"
QT_MOC_LITERAL(33, 340, 15), // "connectionError"
QT_MOC_LITERAL(34, 356, 3), // "win"
QT_MOC_LITERAL(35, 360, 4), // "lose"
QT_MOC_LITERAL(36, 365, 11), // "recvMessage"
QT_MOC_LITERAL(37, 377, 4), // "name"
QT_MOC_LITERAL(38, 382, 3), // "mov"
QT_MOC_LITERAL(39, 386, 13) // "pingForUpdate"
>>>>>>> f483a9a35ebd2a72d6def6f8e7e4ae89eb702146

    },
    "FenPrincipale\0checkSignIn\0\0checkRegister\0"
    "goToRegister\0goToLogIn\0goToGame\0"
    "goToClassic\0goToTrappist\0goToMenu\0"
<<<<<<< HEAD
    "sendMessage\0showFriendList\0setTheme\0"
    "std::string\0pool\0addFriend\0removeFriend\0"
    "setFriendMenu\0setThemeMenu\0setPool0\0"
    "setPool1\0setPool2\0setPool3\0setPool4\0"
    "myShow\0gameStart\0opponent\0AbstractPlateau*\0"
    "board\0connectionError\0win\0lose\0"
    "recvMessage\0name\0mov"
=======
    "goToStat\0sendMessage\0showFriendList\0"
    "setTheme\0std::string\0pool\0addFriend\0"
    "removeFriend\0showFriend\0QListWidgetItem*\0"
    "item\0setFriendMenu\0setThemeMenu\0"
    "setPool0\0setPool1\0setPool2\0setPool3\0"
    "setPool4\0sendPosition\0pos\0myShow\0"
    "gameStart\0opponent\0connectionError\0"
    "win\0lose\0recvMessage\0name\0mov\0"
    "pingForUpdate"
>>>>>>> f483a9a35ebd2a72d6def6f8e7e4ae89eb702146
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FenPrincipale[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
<<<<<<< HEAD
      26,   14, // methods
=======
      30,   14, // methods
>>>>>>> f483a9a35ebd2a72d6def6f8e7e4ae89eb702146
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
<<<<<<< HEAD
       1,    0,  144,    2, 0x0a /* Public */,
       3,    0,  145,    2, 0x0a /* Public */,
       4,    0,  146,    2, 0x0a /* Public */,
       5,    0,  147,    2, 0x0a /* Public */,
       6,    0,  148,    2, 0x0a /* Public */,
       7,    0,  149,    2, 0x0a /* Public */,
       8,    0,  150,    2, 0x0a /* Public */,
       9,    0,  151,    2, 0x0a /* Public */,
      10,    0,  152,    2, 0x0a /* Public */,
      11,    0,  153,    2, 0x0a /* Public */,
      12,    1,  154,    2, 0x0a /* Public */,
      15,    0,  157,    2, 0x0a /* Public */,
      16,    0,  158,    2, 0x0a /* Public */,
      17,    0,  159,    2, 0x0a /* Public */,
      18,    0,  160,    2, 0x0a /* Public */,
      19,    0,  161,    2, 0x0a /* Public */,
      20,    0,  162,    2, 0x0a /* Public */,
      21,    0,  163,    2, 0x0a /* Public */,
      22,    0,  164,    2, 0x0a /* Public */,
      23,    0,  165,    2, 0x0a /* Public */,
      24,    0,  166,    2, 0x0a /* Public */,
      25,    2,  167,    2, 0x0a /* Public */,
      29,    0,  172,    2, 0x0a /* Public */,
      30,    0,  173,    2, 0x0a /* Public */,
      31,    0,  174,    2, 0x0a /* Public */,
      32,    2,  175,    2, 0x0a /* Public */,
=======
       1,    0,  164,    2, 0x0a /* Public */,
       3,    0,  165,    2, 0x0a /* Public */,
       4,    0,  166,    2, 0x0a /* Public */,
       5,    0,  167,    2, 0x0a /* Public */,
       6,    0,  168,    2, 0x0a /* Public */,
       7,    0,  169,    2, 0x0a /* Public */,
       8,    0,  170,    2, 0x0a /* Public */,
       9,    0,  171,    2, 0x0a /* Public */,
      10,    0,  172,    2, 0x0a /* Public */,
      11,    0,  173,    2, 0x0a /* Public */,
      12,    0,  174,    2, 0x0a /* Public */,
      13,    1,  175,    2, 0x0a /* Public */,
      16,    0,  178,    2, 0x0a /* Public */,
      17,    0,  179,    2, 0x0a /* Public */,
      18,    1,  180,    2, 0x0a /* Public */,
      21,    0,  183,    2, 0x0a /* Public */,
      22,    0,  184,    2, 0x0a /* Public */,
      23,    0,  185,    2, 0x0a /* Public */,
      24,    0,  186,    2, 0x0a /* Public */,
      25,    0,  187,    2, 0x0a /* Public */,
      26,    0,  188,    2, 0x0a /* Public */,
      27,    0,  189,    2, 0x0a /* Public */,
      28,    1,  190,    2, 0x0a /* Public */,
      30,    0,  193,    2, 0x0a /* Public */,
      31,    1,  194,    2, 0x0a /* Public */,
      33,    0,  197,    2, 0x0a /* Public */,
      34,    0,  198,    2, 0x0a /* Public */,
      35,    0,  199,    2, 0x0a /* Public */,
      36,    2,  200,    2, 0x0a /* Public */,
      39,    0,  205,    2, 0x0a /* Public */,
>>>>>>> f483a9a35ebd2a72d6def6f8e7e4ae89eb702146

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
<<<<<<< HEAD
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 27,   26,   28,
=======
    QMetaType::Void, 0x80000000 | 14,   29,
>>>>>>> f483a9a35ebd2a72d6def6f8e7e4ae89eb702146
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   32,
    QMetaType::Void,
    QMetaType::Void,
<<<<<<< HEAD
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13,   33,   34,
=======
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 14,   37,   38,
    QMetaType::Void,
>>>>>>> f483a9a35ebd2a72d6def6f8e7e4ae89eb702146

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
        case 6: _t->goToTrappist(); break;
        case 7: _t->goToMenu(); break;
<<<<<<< HEAD
        case 8: _t->sendMessage(); break;
        case 9: _t->showFriendList(); break;
        case 10: _t->setTheme((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 11: _t->addFriend(); break;
        case 12: _t->removeFriend(); break;
        case 13: _t->setFriendMenu(); break;
        case 14: _t->setThemeMenu(); break;
        case 15: _t->setPool0(); break;
        case 16: _t->setPool1(); break;
        case 17: _t->setPool2(); break;
        case 18: _t->setPool3(); break;
        case 19: _t->setPool4(); break;
        case 20: _t->myShow(); break;
        case 21: _t->gameStart((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< AbstractPlateau*(*)>(_a[2]))); break;
        case 22: _t->connectionError(); break;
        case 23: _t->win(); break;
        case 24: _t->lose(); break;
        case 25: _t->recvMessage((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
=======
        case 8: _t->goToStat(); break;
        case 9: _t->sendMessage(); break;
        case 10: _t->showFriendList(); break;
        case 11: _t->setTheme((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 12: _t->addFriend(); break;
        case 13: _t->removeFriend(); break;
        case 14: _t->showFriend((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 15: _t->setFriendMenu(); break;
        case 16: _t->setThemeMenu(); break;
        case 17: _t->setPool0(); break;
        case 18: _t->setPool1(); break;
        case 19: _t->setPool2(); break;
        case 20: _t->setPool3(); break;
        case 21: _t->setPool4(); break;
        case 22: _t->sendPosition((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 23: _t->myShow(); break;
        case 24: _t->gameStart((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 25: _t->connectionError(); break;
        case 26: _t->win(); break;
        case 27: _t->lose(); break;
        case 28: _t->recvMessage((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 29: _t->pingForUpdate(); break;
>>>>>>> f483a9a35ebd2a72d6def6f8e7e4ae89eb702146
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
<<<<<<< HEAD
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 26;
=======
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 30;
>>>>>>> f483a9a35ebd2a72d6def6f8e7e4ae89eb702146
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
