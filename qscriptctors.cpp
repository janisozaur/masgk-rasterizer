#include "qscriptctors.h"

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
