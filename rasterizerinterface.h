#ifndef RASTERIZERINTERFACE_H
#define RASTERIZERINTERFACE_H

#include <QVector3D>
#include <QImage>
#include <QColor>

class RasterizerInterface
{
public:
	RasterizerInterface(int width, int height);
	virtual void triangle(QVector3D a, QVector3D b, QVector3D c) = 0;
	virtual QImage getColorBuffer() const;
	virtual void setClearColor(QColor clearColor);
	virtual void setPaintColor(QColor paintColor);
	virtual void clear();

protected:
	QImage mColorBuffer;
	QColor mClearColor, mPaintColor;
};

#endif // RASTERIZERINTERFACE_H
