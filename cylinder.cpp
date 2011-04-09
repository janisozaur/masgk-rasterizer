#include "cylinder.h"
#include "rasterizerinterface.h"

#include <QMatrix4x4>

Cylinder::Cylinder(int segments, RasterizerInterface *rasterizer) :
	QObject(qobject_cast<QObject *>(rasterizer)),
	mRasterizer(rasterizer),
	mScale(10)
{
	for (int i = 0; i < segments; i++) {
		QVector3D base(1, 0, 0);
		QVector3D axis(0, 1, 0);
		QVector3D normalUpperCover(0, 1, 0);
		{
			// upper left
			QMatrix4x4 m;
			m.rotate(360.0 / segments * i, axis);
			mNormals << m * base;
			m.translate(0, 1, 0);
			mVertices << m * base;
		}
		{
			// upper right
			QMatrix4x4 m;
			m.rotate(360.0 / segments * ((i + 1) % segments), axis);
			mNormals << m * base;
			m.translate(0, 1, 0);
			mVertices << m * base;
		}
		{
			// lower left
			QMatrix4x4 m;
			m.rotate(360.0 / segments * i, axis);
			mNormals << m * base;
			m.translate(0, -1, 0);
			mVertices << m * base;
		}
		{
			// lower left
			QMatrix4x4 m;
			m.rotate(360.0 / segments * i, axis);
			mNormals << m * base;
			m.translate(0, -1, 0);
			mVertices << m * base;
		}
		{
			// upper right
			QMatrix4x4 m;
			m.rotate(360.0 / segments * ((i + 1) % segments), axis);
			mNormals << m * base;
			m.translate(0, 1, 0);
			mVertices << m * base;
		}
		{
			// lower right
			QMatrix4x4 m;
			m.rotate(360.0 / segments * ((i + 1) % segments), axis);
			mNormals << m * base;
			m.translate(0, -1, 0);
			mVertices << m * base;
		}
		{
			// upper right cover
			QMatrix4x4 m;
			m.rotate(360.0 / segments * ((i + 1) % segments), axis);
			mNormals << normalUpperCover;
			m.translate(0, 1, 0);
			mVertices << m * base;
		}
		{
			// upper left cover
			QMatrix4x4 m;
			m.rotate(360.0 / segments * i, axis);
			mNormals << normalUpperCover;
			m.translate(0, 1, 0);
			mVertices << m * base;
		}
		{
			// upper center cover
			mNormals << normalUpperCover;
			mVertices << normalUpperCover;
		}
		{
			// lower left cover
			QMatrix4x4 m;
			m.rotate(360.0 / segments * i, axis);
			mNormals << -normalUpperCover;
			m.translate(0, -1, 0);
			mVertices << m * base;
		}
		{
			// lower right cover
			QMatrix4x4 m;
			m.rotate(360.0 / segments * ((i + 1) % segments), axis);
			mNormals << -normalUpperCover;
			m.translate(0, -1, 0);
			mVertices << m * base;
		}
		{
			// lower center cover
			mNormals << -normalUpperCover;
			mVertices << -normalUpperCover;
		}
	}
}

void Cylinder::render()
{
	bool restore = mRasterizer->normalize();
	mRasterizer->enableNormalization(false);

	for (int i = 0; i < mVertices.count(); i++) {
		mRasterizer->normal(mNormals.at(i));
		mRasterizer->vertex(mVertices.at(i) * mScale);
	}

	mRasterizer->enableNormalization(restore);
}

void Cylinder::scale(qreal s)
{
	mScale = s;
}
