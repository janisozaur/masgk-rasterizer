#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "rasterizerinterface.h"

class Rasterizer : public RasterizerInterface
{
public:
	explicit Rasterizer(int width, int height, QObject *parent = 0);
	void triangle(ColorVertex a, ColorVertex b, ColorVertex c);

public slots:
	virtual void vertex(QVector3D v);
	virtual void normal(QVector3D n);
	virtual void setLightPosition(const QVector3D &lightPos);

protected:
	QVector<ColorVertex> mTriangleVertices;
};

#endif // RASTERIZER_H
