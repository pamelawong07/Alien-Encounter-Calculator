/****************************************************************************
** Meta object code from reading C++ file 'frontend_functions.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../frontend_functions.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frontend_functions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN18Frontend_functionsE_t {};
} // unnamed namespace

template <> constexpr inline auto Frontend_functions::qt_create_metaobjectdata<qt_meta_tag_ZN18Frontend_functionsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Frontend_functions",
        "QML.Element",
        "auto",
        "toggle_city_select",
        "",
        "getData",
        "getText",
        "getTime",
        "getState",
        "toggleCounter",
        "direction",
        "toggleSplay",
        "toggleMin",
        "processClick",
        "x",
        "y",
        "setCurr_city",
        "city",
        "submitReport",
        "desc",
        "cities_select"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'toggle_city_select'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'getData'
        QtMocHelpers::MethodData<void()>(5, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'getText'
        QtMocHelpers::MethodData<QString()>(6, 4, QMC::AccessPublic, QMetaType::QString),
        // Method 'getTime'
        QtMocHelpers::MethodData<QString()>(7, 4, QMC::AccessPublic, QMetaType::QString),
        // Method 'getState'
        QtMocHelpers::MethodData<QString()>(8, 4, QMC::AccessPublic, QMetaType::QString),
        // Method 'toggleCounter'
        QtMocHelpers::MethodData<void(bool)>(9, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 10 },
        }}),
        // Method 'toggleSplay'
        QtMocHelpers::MethodData<void()>(11, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'toggleMin'
        QtMocHelpers::MethodData<void()>(12, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'processClick'
        QtMocHelpers::MethodData<void(int, int)>(13, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 14 }, { QMetaType::Int, 15 },
        }}),
        // Method 'setCurr_city'
        QtMocHelpers::MethodData<void(QString)>(16, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Method 'submitReport'
        QtMocHelpers::MethodData<void(QString, QString)>(18, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 }, { QMetaType::QString, 19 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'cities_select'
        QtMocHelpers::PropertyData<QStringList>(20, QMetaType::QStringList, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<Frontend_functions, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject Frontend_functions::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18Frontend_functionsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18Frontend_functionsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18Frontend_functionsE_t>.metaTypes,
    nullptr
} };

void Frontend_functions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Frontend_functions *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->toggle_city_select(); break;
        case 1: _t->getData(); break;
        case 2: { QString _r = _t->getText();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { QString _r = _t->getTime();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->getState();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->toggleCounter((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->toggleSplay(); break;
        case 7: _t->toggleMin(); break;
        case 8: _t->processClick((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 9: _t->setCurr_city((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->submitReport((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Frontend_functions::*)()>(_a, &Frontend_functions::toggle_city_select, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QStringList*>(_v) = _t->cities_select(); break;
        default: break;
        }
    }
}

const QMetaObject *Frontend_functions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Frontend_functions::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18Frontend_functionsE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Frontend_functions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Frontend_functions::toggle_city_select()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
