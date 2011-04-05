#ifndef VERTEXPROCESSOR_H
#define VERTEXPROCESSOR_H

#include <QObject>
#include <QVector3D>
#include <QMatrix4x4>

class VertexProcessor : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QMatrix4x4 mObj2world READ obj2worldMatrix WRITE setObj2worldMatrix)
	Q_PROPERTY(QMatrix4x4 mWorld2view READ world2viewMatrix WRITE setWorld2viewMatrix)
	Q_PROPERTY(QMatrix4x4 mView2projection READ view2projectionMatrix WRITE setView2projectionMatrix)
public:
	explicit VertexProcessor(QObject *parent = 0);

signals:

public slots:
	QVector3D transformVertex(const QVector3D &vertex) const;
	QMatrix4x4 obj2worldMatrix() const;
	void setObj2worldMatrix(const QMatrix4x4 &matrix);
	QMatrix4x4 world2viewMatrix() const;
	void setWorld2viewMatrix(const QMatrix4x4 &matrix);
	QMatrix4x4 view2projectionMatrix() const;
	void setView2projectionMatrix(const QMatrix4x4 &matrix);

	void rotate(qreal angle, qreal x, qreal y, qreal z);
	void rotate(qreal angle, const QVector3D &v);

protected:
	QMatrix4x4 mObj2world, mWorld2view, mView2projection;
};

//Q_DECLARE_METATYPE(VertexProcessor*)

#endif // VERTEXPROCESSOR_H
