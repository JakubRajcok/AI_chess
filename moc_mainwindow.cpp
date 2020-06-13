/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 23), // "deadPieceSelectedSignal"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 9), // "appendLog"
QT_MOC_LITERAL(4, 46, 20), // "QList<BoardPosition>"
QT_MOC_LITERAL(5, 67, 9), // "appendFen"
QT_MOC_LITERAL(6, 77, 3), // "fen"
QT_MOC_LITERAL(7, 81, 14), // "drawValidMoves"
QT_MOC_LITERAL(8, 96, 20), // "updateChessboardSlot"
QT_MOC_LITERAL(9, 117, 24), // "std::vector<ChessPiece*>"
QT_MOC_LITERAL(10, 142, 1), // "b"
QT_MOC_LITERAL(11, 144, 1), // "w"
QT_MOC_LITERAL(12, 146, 22), // "updateKickedPiecesSlot"
QT_MOC_LITERAL(13, 169, 33), // "on_list_white_kickout_itemCli..."
QT_MOC_LITERAL(14, 203, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(15, 220, 4), // "item"
QT_MOC_LITERAL(16, 225, 33), // "on_list_black_kickout_itemCli..."
QT_MOC_LITERAL(17, 259, 21) // "on_pushButton_clicked"

    },
    "MainWindow\0deadPieceSelectedSignal\0\0"
    "appendLog\0QList<BoardPosition>\0appendFen\0"
    "fen\0drawValidMoves\0updateChessboardSlot\0"
    "std::vector<ChessPiece*>\0b\0w\0"
    "updateKickedPiecesSlot\0"
    "on_list_white_kickout_itemClicked\0"
    "QListWidgetItem*\0item\0"
    "on_list_black_kickout_itemClicked\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   72,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       3,    2,   78,    2, 0x08 /* Private */,
       5,    1,   83,    2, 0x08 /* Private */,
       7,    1,   86,    2, 0x08 /* Private */,
       8,    2,   89,    2, 0x08 /* Private */,
      12,    2,   94,    2, 0x08 /* Private */,
      13,    1,   99,    2, 0x08 /* Private */,
      16,    1,  102,    2, 0x08 /* Private */,
      17,    0,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9,   10,   11,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9,   10,   11,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deadPieceSelectedSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->appendLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->appendLog((*reinterpret_cast< const QList<BoardPosition>(*)>(_a[1]))); break;
        case 3: _t->appendLog((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->appendFen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->drawValidMoves((*reinterpret_cast< const QList<BoardPosition>(*)>(_a[1]))); break;
        case 6: _t->updateChessboardSlot((*reinterpret_cast< const std::vector<ChessPiece*>(*)>(_a[1])),(*reinterpret_cast< const std::vector<ChessPiece*>(*)>(_a[2]))); break;
        case 7: _t->updateKickedPiecesSlot((*reinterpret_cast< const std::vector<ChessPiece*>(*)>(_a[1])),(*reinterpret_cast< const std::vector<ChessPiece*>(*)>(_a[2]))); break;
        case 8: _t->on_list_white_kickout_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->on_list_black_kickout_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 10: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::deadPieceSelectedSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::deadPieceSelectedSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
