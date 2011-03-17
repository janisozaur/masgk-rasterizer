#include "rasterizer.h"

#include "colorvertex.h"

Rasterizer::Rasterizer(int width, int height) :
	RasterizerInterface(width, height)
{
	mTriangleVertices.reserve(3);
}

void Rasterizer::vertex(QVector3D v)
{
	ColorVertex cv(v, mPaintColor);
	mTriangleVertices.append(cv);
	if (mTriangleVertices.count() == 3) {
		triangle(mTriangleVertices.at(0), mTriangleVertices.at(1), mTriangleVertices.at(2));
		mTriangleVertices.resize(0);
	}
}

void Rasterizer::triangle(ColorVertex a, ColorVertex b, ColorVertex c)
{
	const int y1 = a.mPos.y();
	const int y2 = b.mPos.y();
	const int y3 = c.mPos.y();

	const int x1 = a.mPos.x();
	const int x2 = b.mPos.x();
	const int x3 = c.mPos.x();

	const int minx = qMin(x1, qMin(x2, x3));
	const int maxx = qMax(x1, qMax(x2, x3));
	const int miny = qMin(y1, qMin(y2, y3));
	const int maxy = qMax(y1, qMax(y2, y3));

	for (int i = miny; i < maxy; i++) {
		for (int j = minx; j < maxx; j++) {
			if ((x1 - x2) * (i - y1) - (y1 - y2) * (j - x1) > 0 &&
				(x2 - x3) * (i - y2) - (y2 - y3) * (j - x2) > 0 &&
				(x3 - x1) * (i - y3) - (y3 - y1) * (j - x3) > 0)
			{
				mColorBuffer.setPixel(i, j, mPaintColor.rgba());
			}
		}
	}
}
