#ifndef RASTERIZERINTERFACE_H
#define RASTERIZERINTERFACE_H

#include <QVector3D>
#include <QImage>

class RasterizerInterface
{
public:
	RasterizerInterface(int width, int height);
	virtual void triangle(QVector3D a, QVector3D b, QVector3D c) = 0;
	virtual QImage getColorBuffer() const;

protected:
	QImage mColorBuffer;
};

#endif // RASTERIZERINTERFACE_H
