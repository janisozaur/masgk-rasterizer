#ifndef QSCRIPTCTORS_H
#define QSCRIPTCTORS_H

#include <QMetaType>
#include <QColor>

Q_DECLARE_METATYPE(QColor)

class QScriptContext;
class QScriptEngine;
class QScriptValue;

QScriptValue QColor_ctor(QScriptContext *context, QScriptEngine *engine);

#endif // QSCRIPTCTORS_H
