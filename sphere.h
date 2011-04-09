#ifndef SPHERE_H
#define SPHERE_H

#include <QObject>
#include <QVector>
#include <QVector3D>

class RasterizerInterface;

class Sphere : public QObject
{
	Q_OBJECT
public:
	explicit Sphere(int horizontal, int vertical, RasterizerInterface *rasterizer);

signals:

public slots:
	void render();
	void scale(qreal s);

private:
	QVector<QVector3D> mVertices;
	RasterizerInterface *mRasterizer;
	qreal mScale;
};

#endif // SPHERE_H
