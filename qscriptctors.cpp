#include "qscriptctors.h"
#include "vertexprocessor.h"
#include "box.h"
#include "rasterizerinterface.h"
#include "sphere.h"
#include "cylinder.h"

#include <QtGlobal>
#include <QScriptEngine>

#include <QDebug>

QScriptValue QColor_ctor(QScriptContext *context, QScriptEngine *engine)
{
	QColor color;
	if (context->argumentCount() != 3) {
		context->throwError(QScriptContext::SyntaxError, "QColor constructor takes 3 parameters: QColor(r ,g b)");
	}
	if (!context->argument(0).isNumber() || !context->argument(1).isNumber() || !context->argument(2).isNumber()) {
		context->throwError(QScriptContext::SyntaxError, "One of parameters is not a number");
	}
	color.setRed(context->argument(0).toInteger());
	color.setGreen(context->argument(1).toInteger());
	color.setBlue(context->argument(2).toInteger());
	return engine->toScriptValue(color);
}

QScriptValue QVector3D_ctor(QScriptContext *context, QScriptEngine *engine)
{
	QVector3D vector;
	if (context->argumentCount() != 3) {
		context->throwError(QScriptContext::SyntaxError, "QVector3D constructor takes 3 parameters: QColor(r ,g b)");
	}
	if (!context->argument(0).isNumber() || !context->argument(1).isNumber() || !context->argument(2).isNumber()) {
		context->throwError(QScriptContext::SyntaxError, "One of parameters is not a number");
	}
	vector.setX(context->argument(0).toNumber());
	vector.setY(context->argument(1).toNumber());
	vector.setZ(context->argument(2).toNumber());
	return engine->toScriptValue(vector);
}

QScriptValue Box_ctor(QScriptContext *context, QScriptEngine *engine)
{
	Box *box;
	if (context->argumentCount() != 1) {
		context->throwError(QScriptContext::SyntaxError, "Box constructor takes 1 parameter: RasterizerInterface *");
	}
	if (qobject_cast<RasterizerInterface *>(context->argument(0).toQObject()) == NULL) {
		context->throwError(QScriptContext::SyntaxError, "Invalid parameter");
	}
	box = new Box(qobject_cast<RasterizerInterface *>(context->argument(0).toQObject()));
	return engine->toScriptValue(box);
}

QScriptValue Sphere_ctor(QScriptContext *context, QScriptEngine *engine)
{
	Sphere *sphere;
	if (context->argumentCount() != 3) {
		context->throwError(QScriptContext::SyntaxError, "Sphere constructor takes 3 parameters: horizontal, vertical, RasterizerInterface *");
	}
	if (!context->argument(0).isNumber() || !context->argument(1).isNumber() || qobject_cast<RasterizerInterface *>(context->argument(2).toQObject()) == NULL) {
		context->throwError(QScriptContext::SyntaxError, "Invalid parameter");
	}
	sphere = new Sphere(context->argument(0).toNumber(), context->argument(1).toNumber(), qobject_cast<RasterizerInterface *>(context->argument(2).toQObject()));
	return engine->toScriptValue(sphere);
}

QScriptValue Cylinder_ctor(QScriptContext *context, QScriptEngine *engine)
{
	Cylinder *cylinder;
	if (context->argumentCount() != 2) {
		context->throwError(QScriptContext::SyntaxError, "Cylinder constructor takes 2 parameters: segments, RasterizerInterface *");
	}
	if (!context->argument(0).isNumber() || qobject_cast<RasterizerInterface *>(context->argument(1).toQObject()) == NULL) {
		context->throwError(QScriptContext::SyntaxError, "Invalid parameter");
	}
	cylinder = new Cylinder(context->argument(0).toNumber(), qobject_cast<RasterizerInterface *>(context->argument(1).toQObject()));
	return engine->toScriptValue(cylinder);
}

QScriptValue vertexProcessorToScriptValue(QScriptEngine *engine, VertexProcessor *const &in)
{
	return engine->newQObject(in);
}

void vertexProcessorFromScriptValue(const QScriptValue &object, VertexProcessor *&out)
{
	out = qobject_cast<VertexProcessor*>(object.toQObject());
}

QScriptValue boxToScriptValue(QScriptEngine *engine, Box *const &in)
{
	return engine->newQObject(in);
}

void boxFromScriptValue(const QScriptValue &object, Box *&out)
{
	out = qobject_cast<Box*>(object.toQObject());
}

QScriptValue sphereToScriptValue(QScriptEngine *engine, Sphere *const &in)
{
	return engine->newQObject(in);
}

void sphereFromScriptValue(const QScriptValue &object, Sphere *&out)
{
	out = qobject_cast<Sphere*>(object.toQObject());
}

QScriptValue cylinderToScriptValue(QScriptEngine *engine, Cylinder *const &in)
{
	return engine->newQObject(in);
}

void cylinderFromScriptValue(const QScriptValue &object, Cylinder *&out)
{
	out = qobject_cast<Cylinder*>(object.toQObject());
}
