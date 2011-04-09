#include "sphere.h"
#include "rasterizerinterface.h"

#include <cmath>
#include <QMatrix4x4>

Sphere::Sphere(int horizontal, int vertical, RasterizerInterface *rasterizer) :
	QObject(qobject_cast<QObject *>(rasterizer)),
	mRasterizer(rasterizer),
	mScale(10)
{
	horizontal *= 2;
	for (int i = 0; i < horizontal; i++) {
		for (int j = 0; j < vertical + 1; j++) {
			{
				// upper left
				QMatrix4x4 m;
				m.rotate(360.0 / horizontal * i, 0, 0, 1);
				QVector3D axis = m * QVector3D(1, 0, 0);
				m.rotate(180.0 / vertical * j, axis);
				mVertices << m * QVector3D(0, 0, -1);
			}
			{
				// upper right
				QMatrix4x4 m;
				m.rotate(360.0 / horizontal * ((i + 1) % horizontal), 0, 0, 1);
				QVector3D axis = m * QVector3D(1, 0, 0);
				m.rotate(180.0 / vertical * j, axis);
				mVertices << m * QVector3D(0, 0, -1);
			}
			{
				// lower left
				QMatrix4x4 m;
				m.rotate(360.0 / horizontal * i, 0, 0, 1);
				QVector3D axis = m * QVector3D(1, 0, 0);
				m.rotate(180.0 / vertical * (j - 1), axis);
				mVertices << m * QVector3D(0, 0, -1);
			}
			{
				// lower left
				QMatrix4x4 m;
				m.rotate(360.0 / horizontal * i, 0, 0, 1);
				QVector3D axis = m * QVector3D(1, 0, 0);
				m.rotate(180.0 / vertical * (j - 1), axis);
				mVertices << m * QVector3D(0, 0, -1);
			}
			{
				// upper right
				QMatrix4x4 m;
				m.rotate(360.0 / horizontal * ((i + 1) % horizontal), 0, 0, 1);
				QVector3D axis = m * QVector3D(1, 0, 0);
				m.rotate(180.0 / vertical * j, axis);
				mVertices << m * QVector3D(0, 0, -1);
			}
			{
				// lower right
				QMatrix4x4 m;
				m.rotate(360.0 / horizontal * ((i + 1) % horizontal), 0, 0, 1);
				QVector3D axis = m * QVector3D(1, 0, 0);
				m.rotate(180.0 / vertical * (j - 1), axis);
				mVertices << m * QVector3D(0, 0, -1);
			}
		}
	}
}

void Sphere::render()
{
	bool restore = mRasterizer->normalize();
	mRasterizer->enableNormalization(false);

	for (int i = 0; i < mVertices.count(); i++) {
		mRasterizer->normal(mVertices.at(i));
		mRasterizer->vertex(mVertices.at(i) * mScale);
	}

	mRasterizer->enableNormalization(restore);
}

void Sphere::scale(qreal s)
{
	mScale = s;
}
