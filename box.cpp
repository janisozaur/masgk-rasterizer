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

	// front
	mRasterizer->normal(QVector3D(0, 0, 1));
	mRasterizer->vertex(QVector3D(-1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(-1, -1, 1) * mScale);

	mRasterizer->vertex(QVector3D(-1, -1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, -1, 1) * mScale);

	// left
	mRasterizer->normal(QVector3D(-1, 0, 0));
	mRasterizer->vertex(QVector3D(-1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(-1, -1, -1) * mScale);

	mRasterizer->vertex(QVector3D(-1, -1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(-1, -1, 1) * mScale);

	// back
	mRasterizer->normal(QVector3D(0, 0, -1));
	mRasterizer->vertex(QVector3D(1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(1, -1, -1) * mScale);

	mRasterizer->vertex(QVector3D(1, -1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, -1, -1) * mScale);

	// right
	mRasterizer->normal(QVector3D(1, 0, 0));
	mRasterizer->vertex(QVector3D(1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(1, -1, 1) * mScale);

	mRasterizer->vertex(QVector3D(1, -1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(1, -1, -1) * mScale);

	// top
	mRasterizer->normal(QVector3D(0, 1, 0));
	mRasterizer->vertex(QVector3D(-1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(-1, 1, 1) * mScale);

	mRasterizer->vertex(QVector3D(-1, 1, 1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, -1) * mScale);
	mRasterizer->vertex(QVector3D(1, 1, 1) * mScale);

	// bottom
	mRasterizer->normal(QVector3D(0, -1, 0));
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
