#ifndef RASTERIZERINTERFACE_H
#define RASTERIZERINTERFACE_H

#include <QVector3D>
#include <QImage>
#include <QColor>

class ColorVertex;

class RasterizerInterface : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QColor mPaintColor READ paintColor WRITE setPaintColor)
	Q_PROPERTY(QColor mClearColor READ clearColor WRITE setClearColor)
public:
	explicit RasterizerInterface(int width, int height, QObject *parent = 0);
	virtual QImage getColorBuffer() const;
	virtual QColor clearColor() const;
	virtual void setClearColor(const QColor &clearColor);
	virtual QColor paintColor() const;
	virtual void setPaintColor(const QColor &paintColor);
	virtual void triangle(ColorVertex a, ColorVertex b, ColorVertex c);

public slots:
	virtual void clear();
	virtual void vertex(QVector3D v) = 0;

protected:
	QImage mColorBuffer;
	QColor mClearColor, mPaintColor;
};

#endif // RASTERIZERINTERFACE_H
