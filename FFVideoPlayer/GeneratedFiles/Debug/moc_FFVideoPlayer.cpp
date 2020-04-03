/****************************************************************************
** Meta object code from reading C++ file 'FFVideoPlayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FFVideoPlayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FFVideoPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FFVideoPlayer_t {
    QByteArrayData data[22];
    char stringdata0[293];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FFVideoPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FFVideoPlayer_t qt_meta_stringdata_FFVideoPlayer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FFVideoPlayer"
QT_MOC_LITERAL(1, 14, 8), // "slotPlay"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 17), // "slotSliderPressed"
QT_MOC_LITERAL(4, 42, 18), // "soltSliderReleased"
QT_MOC_LITERAL(5, 61, 24), // "on_btnFullScreen_clicked"
QT_MOC_LITERAL(6, 86, 7), // "setMute"
QT_MOC_LITERAL(7, 94, 8), // "fastPlay"
QT_MOC_LITERAL(8, 103, 13), // "fastPlayReset"
QT_MOC_LITERAL(9, 117, 14), // "OpenLocalVideo"
QT_MOC_LITERAL(10, 132, 14), // "PlayLocalVideo"
QT_MOC_LITERAL(11, 147, 8), // "filename"
QT_MOC_LITERAL(12, 156, 16), // "OpenNetStreamDlg"
QT_MOC_LITERAL(13, 173, 11), // "PopAboutDlg"
QT_MOC_LITERAL(14, 185, 13), // "GetSourceCode"
QT_MOC_LITERAL(15, 199, 12), // "volumeAdjust"
QT_MOC_LITERAL(16, 212, 14), // "slotPushStream"
QT_MOC_LITERAL(17, 227, 7), // "address"
QT_MOC_LITERAL(18, 235, 14), // "DecryptionFile"
QT_MOC_LITERAL(19, 250, 11), // "const char*"
QT_MOC_LITERAL(20, 262, 15), // "EncryptionCheck"
QT_MOC_LITERAL(21, 278, 14) // "EncryptionFile"

    },
    "FFVideoPlayer\0slotPlay\0\0slotSliderPressed\0"
    "soltSliderReleased\0on_btnFullScreen_clicked\0"
    "setMute\0fastPlay\0fastPlayReset\0"
    "OpenLocalVideo\0PlayLocalVideo\0filename\0"
    "OpenNetStreamDlg\0PopAboutDlg\0GetSourceCode\0"
    "volumeAdjust\0slotPushStream\0address\0"
    "DecryptionFile\0const char*\0EncryptionCheck\0"
    "EncryptionFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FFVideoPlayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    1,  107,    2, 0x08 /* Private */,
      12,    0,  110,    2, 0x08 /* Private */,
      13,    0,  111,    2, 0x08 /* Private */,
      14,    0,  112,    2, 0x08 /* Private */,
      15,    0,  113,    2, 0x08 /* Private */,
      16,    1,  114,    2, 0x08 /* Private */,
      18,    1,  117,    2, 0x08 /* Private */,
      20,    1,  120,    2, 0x08 /* Private */,
      21,    1,  123,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Bool, 0x80000000 | 19,   11,
    QMetaType::Bool, 0x80000000 | 19,   11,
    QMetaType::Bool, 0x80000000 | 19,   11,

       0        // eod
};

void FFVideoPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FFVideoPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPlay(); break;
        case 1: _t->slotSliderPressed(); break;
        case 2: _t->soltSliderReleased(); break;
        case 3: _t->on_btnFullScreen_clicked(); break;
        case 4: _t->setMute(); break;
        case 5: _t->fastPlay(); break;
        case 6: _t->fastPlayReset(); break;
        case 7: _t->OpenLocalVideo(); break;
        case 8: _t->PlayLocalVideo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->OpenNetStreamDlg(); break;
        case 10: _t->PopAboutDlg(); break;
        case 11: _t->GetSourceCode(); break;
        case 12: _t->volumeAdjust(); break;
        case 13: _t->slotPushStream((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: { bool _r = _t->DecryptionFile((*reinterpret_cast< const char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 15: { bool _r = _t->EncryptionCheck((*reinterpret_cast< const char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 16: { bool _r = _t->EncryptionFile((*reinterpret_cast< const char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FFVideoPlayer::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_FFVideoPlayer.data,
    qt_meta_data_FFVideoPlayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FFVideoPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FFVideoPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FFVideoPlayer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int FFVideoPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
