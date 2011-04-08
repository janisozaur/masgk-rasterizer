#include "vertexprocessor.h"

#include <QVector4D>

VertexProcessor::VertexProcessor(QObject *parent) :
	QObject(parent)
{
}

QVector3D VertexProcessor::transformVertex(const QVector3D &vertex) const
{
	//QVector4D result = QVector4D(vertex, 1.0) * mObj2world * mWorld2view * mView2projection;
	QVector4D result = mView2projection * mWorld2view * mObj2world * QVector4D(vertex, 1.0);
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

void VertexProcessor::translate(qreal x, qreal y, qreal z)
{
	mObj2world.translate(x, y, z);
}

void VertexProcessor::translate(const QVector3D &v)
{
	mObj2world.translate(v);
}

void VertexProcessor::setPerspective(qreal angle, qreal aspect, qreal near,
									 qreal far)
{
	mView2projection.perspective(angle, aspect, near, far);
}

void VertexProcessor::setLookAt(const QVector3D &eye, const QVector3D &center,
								const QVector3D &up)
{
	mWorld2view.lookAt(eye, center, up);
}

void VertexProcessor::setIdentity()
{
	mObj2world = QMatrix4x4();
}

void VertexProcessor::reset()
{
	mObj2world = mView2projection = mWorld2view = QMatrix4x4();
}

QMatrix4x4 VertexProcessor::normalMatrix() const
{
	return QMatrix4x4((mWorld2view * mObj2world).normalMatrix());
}

QVector3D VertexProcessor::transformNormal(const QVector3D &normal) const
{
	//QVector4D result = QVector4D(vertex, 1.0) * mObj2world * mWorld2view * mView2projection;
	QVector4D result = normalMatrix() * normal;
	return QVector3D(result);
}

QVector3D VertexProcessor::transformLight(const QVector3D &light) const
{
	return QVector3D(mWorld2view * QVector4D(light, 1.0));
}
