#ifndef QSCRIPTCTORS_H
#define QSCRIPTCTORS_H

#include <QMetaType>
#include <QColor>
#include <QVector3D>

Q_DECLARE_METATYPE(QVector3D)
Q_DECLARE_METATYPE(QColor)

class QScriptContext;
class QScriptEngine;
class QScriptValue;

QScriptValue QColor_ctor(QScriptContext *context, QScriptEngine *engine);
QScriptValue QVector3D_ctor(QScriptContext *context, QScriptEngine *engine);

#endif // QSCRIPTCTORS_H
