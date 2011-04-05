#include "vertexprocessor.h"

#include <QVector4D>

VertexProcessor::VertexProcessor(QObject *parent) :
	QObject(parent)
{
}

QVector3D VertexProcessor::transformVertex(const QVector3D &vertex) const
{
	QVector4D result = QVector4D(vertex, 1.0) * mObj2world * mWorld2view * mView2projection;
	qreal w = result.w();
	return QVector3D(result.x() / w, result.y() / w, result.z() / w);
}

QMatrix4x4 VertexProcessor::obj2worldMatrix() const
{
	return mObj2world;
}

void VertexProcessor::setObj2worldMatrix(const QMatrix4x4 &matrix)
{
	mObj2world = matrix;
}

QMatrix4x4 VertexProcessor::world2viewMatrix() const
{
	return mWorld2view;
}

void VertexProcessor::setWorld2viewMatrix(const QMatrix4x4 &matrix)
{
	mWorld2view = matrix;
}

QMatrix4x4 VertexProcessor::view2projectionMatrix() const
{
	return mView2projection;
}

void VertexProcessor::setView2projectionMatrix(const QMatrix4x4 &matrix)
{
	mView2projection = matrix;
}

void VertexProcessor::rotate(qreal angle, qreal x, qreal y, qreal z)
{
	mObj2world.rotate(angle, x, y, z);
}

void VertexProcessor::rotate(qreal angle, const QVector3D &v)
{
	mObj2world.rotate(angle, v);
}
