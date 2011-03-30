#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "rasterizerinterface.h"

class ColorVertex;

class Rasterizer : public RasterizerInterface
{
public:
	explicit Rasterizer(int width, int height, QObject *parent = 0);
	virtual void vertex(QVector3D v);
	void triangle(ColorVertex a, ColorVertex b, ColorVertex c);

protected:
	QVector<ColorVertex> mTriangleVertices;
};

#endif // RASTERIZER_H
