#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QColor>

struct ColorVertex
{
//public:
	ColorVertex();
	ColorVertex(QVector3D pos, QVector3D viewPos, QVector3D normal, QColor color);
	QVector3D mPos, mViewPos, mNormal;
	QColor mColor;
};

#endif // VERTEX_H
