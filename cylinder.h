#ifndef CYLINDER_H
#define CYLINDER_H

#include <QObject>
#include <QVector>
#include <QVector3D>

class RasterizerInterface;

class Cylinder : public QObject
{
	Q_OBJECT
public:
	explicit Cylinder(int segments, RasterizerInterface *rasterizer);

signals:

public slots:
	void render();
	void scale(qreal s);

private:
	QVector<QVector3D> mVertices, mNormals;
	RasterizerInterface *mRasterizer;
	qreal mScale;
};

#endif // CYLINDER_H
