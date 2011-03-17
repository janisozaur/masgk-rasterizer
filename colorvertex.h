#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QColor>

struct ColorVertex
{
//public:
	ColorVertex();
	ColorVertex(QVector3D pos, QColor color);
	QVector3D mPos;
	QColor mColor;
};

#endif // VERTEX_H
