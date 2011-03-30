#include "rasterizer.h"

#include "colorvertex.h"

Rasterizer::Rasterizer(int width, int height, QObject *parent) :
	RasterizerInterface(width, height, parent)
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
	const float y1 = a.mPos.y();
	const float y2 = b.mPos.y();
	const float y3 = c.mPos.y();

	const float x1 = a.mPos.x();
	const float x2 = b.mPos.x();
	const float x3 = c.mPos.x();

	const int minx = (qMin(x1, qMin(x2, x3)));
	const int maxx = (qMax(x1, qMax(x2, x3)));
	const int miny = (qMin(y1, qMin(y2, y3)));
	const int maxy = (qMax(y1, qMax(y2, y3)));

	for (int y = miny; y < maxy; y++) {
		for (int x = minx; x < maxx; x++) {
			if ((x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0 &&
				(x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0 &&
				(x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0)
			{
				float l1 = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
				float l2 = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / ((y3 - y1) * (x2 - x3) + (x1 - x3) * (y2 - y3));
				float l3 = 1 - l1 - l2;
				int red = l1 * a.mColor.red() + l2 * b.mColor.red() + l3 * c.mColor.red();
				int green = l1 * a.mColor.green() + l2 * b.mColor.green() + l3 * c.mColor.green();
				int blue = l1 * a.mColor.blue() + l2 * b.mColor.blue() + l3 * c.mColor.blue();
				mColorBuffer.setPixel(y, x, QColor(red, green, blue).rgb());
			}
		}
	}
}
