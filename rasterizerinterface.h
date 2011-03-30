#ifndef RASTERIZERINTERFACE_H
#define RASTERIZERINTERFACE_H

#include <QVector3D>
#include <QImage>
#include <QColor>

class RasterizerInterface : public QObject
{
	Q_OBJECT
public:
	explicit RasterizerInterface(int width, int height, QObject *parent = 0);
	virtual void vertex(QVector3D v) = 0;
	virtual QImage getColorBuffer() const;
	virtual void setClearColor(QColor clearColor);
	virtual void setPaintColor(QColor paintColor);
	virtual void clear();

protected:
	QImage mColorBuffer;
	QColor mClearColor, mPaintColor;
};

#endif // RASTERIZERINTERFACE_H
