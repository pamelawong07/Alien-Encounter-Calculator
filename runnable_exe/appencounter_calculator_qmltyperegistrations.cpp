/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<frontend_functions.h>)
#  include <frontend_functions.h>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_encounter_calculator()
{
    qmlRegisterModule("encounter_calculator", 254, 0);
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<Frontend_functions>("encounter_calculator", 254);
    QT_WARNING_POP
    qmlRegisterModule("encounter_calculator", 254, 254);
}

static const QQmlModuleRegistration encountercalculatorRegistration("encounter_calculator", qml_register_types_encounter_calculator);
