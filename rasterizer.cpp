#include "rasterizer.h"
#include "colorvertex.h"
#include "vertexprocessor.h"

#include <cmath>

Rasterizer::Rasterizer(int width, int height, QObject *parent) :
	RasterizerInterface(width, height, parent)
{
	mTriangleVertices.reserve(3);
}

void Rasterizer::vertex(QVector3D v)
{
	QVector3D vertexPos, vertexViewPos, normal;
	if (mVP != NULL) {
		vertexPos = mVP->transformVertex(v);
		normal = mVP->transformNormal(mNormal);
		vertexViewPos = mVP->transformToView(v);
	} else {
		normal = mNormal;
		vertexPos = v;
		vertexViewPos = v;
	}
	ColorVertex cv(vertexPos, vertexViewPos, normal, mPaintColor);
	mTriangleVertices.append(cv);
	if (mTriangleVertices.count() == 3) {
		triangle(mTriangleVertices.at(0), mTriangleVertices.at(1), mTriangleVertices.at(2));
		mTriangleVertices.resize(0);
	}
}

void Rasterizer::triangle(ColorVertex a, ColorVertex b, ColorVertex c)
{
	const float y1 = (a.mPos.y() + 1) * mColorBuffer.height() / 2;
	const float y2 = (b.mPos.y() + 1) * mColorBuffer.height() / 2;
	const float y3 = (c.mPos.y() + 1) * mColorBuffer.height() / 2;

	const float x1 = (a.mPos.x() + 1) * mColorBuffer.width() / 2;
	const float x2 = (b.mPos.x() + 1) * mColorBuffer.width() / 2;
	const float x3 = (c.mPos.x() + 1) * mColorBuffer.width() / 2;

	const QVector3D na = a.mNormal.normalized();
	const QVector3D nb = b.mNormal.normalized();
	const QVector3D nc = c.mNormal.normalized();
	const QVector3D l = (mVP == NULL) ? mLightPos : mVP->transformLight(mLightPos);
	const QVector3D nl = l.normalized();

	QVector3D ca = QVector3D(a.mColor.redF(), a.mColor.greenF(), a.mColor.blueF());
	QVector3D cb = QVector3D(b.mColor.redF(), b.mColor.greenF(), b.mColor.blueF());
	QVector3D cc = QVector3D(c.mColor.redF(), c.mColor.greenF(), c.mColor.blueF());

	const qreal ambient = 0.2;
	const qreal diffuse = 0.5;
	const int specularPower = 25;

	QVector3D ra = 2 * QVector3D::dotProduct(nl, na) * na - nl;
	QVector3D rb = 2 * QVector3D::dotProduct(nl, nb) * nb - nl;
	QVector3D rc = 2 * QVector3D::dotProduct(nl, nc) * nc - nl;

	QVector3D pl = -a.mViewPos + l;
	pl.normalize();
	QVector3D da = ca * qMax(QVector3D::dotProduct(pl, na), 0.0) * diffuse;
	QVector3D sa = ca * pow(qMax(QVector3D::dotProduct(ra, pl), 0.0), specularPower);

	pl = -b.mViewPos + l;
	pl.normalize();
	QVector3D db = cb * qMax(QVector3D::dotProduct(pl, nb), 0.0) * diffuse;
	QVector3D sb = cb * pow(qMax(QVector3D::dotProduct(rb, pl), 0.0), specularPower);

	pl = -c.mViewPos + l;
	pl.normalize();
	QVector3D dc = cc * qMax(QVector3D::dotProduct(pl, nc), 0.0) * diffuse;
	QVector3D sc = cc * pow(qMax(QVector3D::dotProduct(rc, pl), 0.0), specularPower);

	QVector3D aa = ca * ambient;
	QVector3D ab = cb * ambient;
	QVector3D ac = cc * ambient;

	const int minx = qMax((int)(qMin(x1, qMin(x2, x3))), 0);
	const int maxx = qMin((int)(qMax(x1, qMax(x2, x3))), mColorBuffer.width());
	const int miny = qMax((int)(qMin(y1, qMin(y2, y3))), 0);
	const int maxy = qMin((int)(qMax(y1, qMax(y2, y3))), mColorBuffer.height());

	for (int y = miny; y < maxy; y++) {
		for (int x = minx; x < maxx; x++) {
			QPoint pos(x, mColorBuffer.height() - y - 1);
			qreal l1 = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
			qreal l2 = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / ((y3 - y1) * (x2 - x3) + (x1 - x3) * (y2 - y3));
			qreal l3 = 1 - l1 - l2;
			qreal d = a.mPos.z() * l1 + b.mPos.z() * l2 + c.mPos.z() * l3;
			int idx = pos.y() * mColorBuffer.width() + pos.x();
			if ((mDepthBuffer.at(idx) > d) &&
				//(qBound(0, d, 255) == d) &&
				(x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) >= 0 &&
				(x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) >= 0 &&
				(x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) >= 0)
			{
				QVector3D n = na * l1 + nb * l2 + nc * l3;
				n.normalize();
				//int red = l1 * a.mColor.red() + l2 * b.mColor.red() + l3 * c.mColor.red();
				//int green = l1 * a.mColor.green() + l2 * b.mColor.green() + l3 * c.mColor.green();
				//int blue = l1 * a.mColor.blue() + l2 * b.mColor.blue() + l3 * c.mColor.blue();
				QVector3D color = ((da + aa + sa) * l1 + (db + ab + sb) * l2 + (dc + ac + sc) * l3) * 255;
				color.setX(qBound(0.0, color.x(), 255.0));
				color.setY(qBound(0.0, color.y(), 255.0));
				color.setZ(qBound(0.0, color.z(), 255.0));
				mColorBuffer.setPixel(pos, qRgb(color.x(), color.y(), color.z()));
				mDepthBuffer[idx] = d;
				n /= 2;
				n += QVector3D(0.5, 0.5, 0.5);
				mNormalBuffer.setPixel(pos, qRgb(n.x() * 255, n.y() * 255, n.z() * 255));
			}
		}
	}
}

void Rasterizer::normal(QVector3D n)
{
	mNormal = n.normalized();
}

void Rasterizer::setLightPosition(const QVector3D &l)
{
	mLightPos = l;
}
