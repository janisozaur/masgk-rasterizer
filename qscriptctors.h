#ifndef QSCRIPTCTORS_H
#define QSCRIPTCTORS_H

#include <QMetaType>
#include <QColor>
#include <QVector3D>

class QScriptContext;
class QScriptEngine;
class QScriptValue;
class VertexProcessor;
class Box;
class RasterizerInterface;
class Sphere;

Q_DECLARE_METATYPE(QVector3D)
Q_DECLARE_METATYPE(QColor)
Q_DECLARE_METATYPE(VertexProcessor*)
Q_DECLARE_METATYPE(RasterizerInterface*)
Q_DECLARE_METATYPE(Box*)
Q_DECLARE_METATYPE(Sphere*)

QScriptValue QColor_ctor(QScriptContext *context, QScriptEngine *engine);
QScriptValue QVector3D_ctor(QScriptContext *context, QScriptEngine *engine);
QScriptValue Box_ctor(QScriptContext *context, QScriptEngine *engine);
QScriptValue Sphere_ctor(QScriptContext *context, QScriptEngine *engine);

QScriptValue vertexProcessorToScriptValue(QScriptEngine *engine, VertexProcessor *const &in);
void vertexProcessorFromScriptValue(const QScriptValue &object, VertexProcessor *&out);
QScriptValue boxToScriptValue(QScriptEngine *engine, Box *const &in);
void boxFromScriptValue(const QScriptValue &object, Box *&out);
QScriptValue sphereToScriptValue(QScriptEngine *engine, Sphere *const &in);
void sphereFromScriptValue(const QScriptValue &object, Sphere *&out);

#endif // QSCRIPTCTORS_H
