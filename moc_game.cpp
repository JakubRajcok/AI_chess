/****************************************************************************
** Meta object code from reading C++ file 'game.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "game.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Game_t {
    QByteArrayData data[15];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Game_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Game_t qt_meta_stringdata_Game = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Game"
QT_MOC_LITERAL(1, 5, 9), // "appendLog"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 1), // "s"
QT_MOC_LITERAL(4, 18, 20), // "QList<BoardPosition>"
QT_MOC_LITERAL(5, 39, 9), // "appendFen"
QT_MOC_LITERAL(6, 49, 3), // "fen"
QT_MOC_LITERAL(7, 53, 10), // "validMoves"
QT_MOC_LITERAL(8, 64, 22), // "updateChessboardSignal"
QT_MOC_LITERAL(9, 87, 24), // "std::vector<ChessPiece*>"
QT_MOC_LITERAL(10, 112, 1), // "b"
QT_MOC_LITERAL(11, 114, 1), // "w"
QT_MOC_LITERAL(12, 116, 24), // "updateKickedPiecesSignal"
QT_MOC_LITERAL(13, 141, 10), // "solveClick"
QT_MOC_LITERAL(14, 152, 21) // "deadPieceSelectedSlot"

    },
    "Game\0appendLog\0\0s\0QList<BoardPosition>\0"
    "appendFen\0fen\0validMoves\0"
    "updateChessboardSignal\0std::vector<ChessPiece*>\0"
    "b\0w\0updateKickedPiecesSignal\0solveClick\0"
    "deadPieceSelectedSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Game[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       1,    1,   57,    2, 0x06 /* Public */,
       5,    1,   60,    2, 0x06 /* Public */,
       7,    1,   63,    2, 0x06 /* Public */,
       8,    2,   66,    2, 0x06 /* Public */,
      12,    2,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    2,   76,    2, 0x0a /* Public */,
      14,    1,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9,   10,   11,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9,   10,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Game *_t = static_cast<Game *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->appendLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->appendLog((*reinterpret_cast< const QList<BoardPosition>(*)>(_a[1]))); break;
        case 2: _t->appendFen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->validMoves((*reinterpret_cast< const QList<BoardPosition>(*)>(_a[1]))); break;
        case 4: _t->updateChessboardSignal((*reinterpret_cast< const std::vector<ChessPiece*>(*)>(_a[1])),(*reinterpret_cast< const std::vector<ChessPiece*>(*)>(_a[2]))); break;
        case 5: _t->updateKickedPiecesSignal((*reinterpret_cast< const std::vector<ChessPiece*>(*)>(_a[1])),(*reinterpret_cast< const std::vector<ChessPiece*>(*)>(_a[2]))); break;
        case 6: _t->solveClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->deadPieceSelectedSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Game::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Game::appendLog)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Game::*)(const QList<BoardPosition> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Game::appendLog)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Game::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Game::appendFen)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Game::*)(const QList<BoardPosition> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Game::validMoves)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Game::*)(const std::vector<ChessPiece*> & , const std::vector<ChessPiece*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Game::updateChessboardSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Game::*)(const std::vector<ChessPiece*> & , const std::vector<ChessPiece*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Game::updateKickedPiecesSignal)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Game::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Game.data,
      qt_meta_data_Game,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Game.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Game::appendLog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Game::appendLog(const QList<BoardPosition> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Game::appendFen(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Game::validMoves(const QList<BoardPosition> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Game::updateChessboardSignal(const std::vector<ChessPiece*> & _t1, const std::vector<ChessPiece*> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Game::updateKickedPiecesSignal(const std::vector<ChessPiece*> & _t1, const std::vector<ChessPiece*> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
