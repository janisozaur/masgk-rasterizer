#include "box.h"
#include "rasterizerinterface.h"

#include <QDebug>

Box::Box(RasterizerInterface *rasterizer) :
	QObject(qobject_cast<QObject *>(rasterizer)),
	mRasterizer(rasterizer),
	mScale(10)
{
}

Box::~Box()
{
	qDebug() << "box" << this << "deleted";
}

void Box::render()
{
	mRasterizer->normal(QVector3D(0, 0, 1));

	// front
	mRasterizer->vertex(QVector3D(-1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(-1, -1, 1) * mScale);

	mRasterizer->vertex(QVector3D(-1, -1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, -1, 1) * mScale);

	// left
	mRasterizer->vertex(QVector3D(-1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(-1, -1, -1) * mScale);

	mRasterizer->vertex(QVector3D(-1, -1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(-1, -1, 1) * mScale);

	// back
	mRasterizer->vertex(QVector3D(1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(1, -1, -1) * mScale);

	mRasterizer->vertex(QVector3D(1, -1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, -1, -1) * mScale);

	// right
	mRasterizer->vertex(QVector3D(1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(1, -1, 1) * mScale);

	mRasterizer->vertex(QVector3D(1, -1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(1, -1, -1) * mScale);

	// top
	mRasterizer->vertex(QVector3D(-1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, 1) * mScale);

	mRasterizer->vertex(QVector3D(-1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, 1) * mScale);

	// bottom
	mRasterizer->vertex(QVector3D(-1, -1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, -1, 1) * mScale);
	mRasterizer->vertex(QVector3D(-1, -1, -1) * mScale);

	mRasterizer->vertex(QVector3D(-1, -1, -1) * mScale);
	mRasterizer->vertex(QVector3D(1, -1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, -1, -1) * mScale);
}

void Box::scale(qreal s)
{
	mScale = s;
}
