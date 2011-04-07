#ifndef RASTERIZERINTERFACE_H
#define RASTERIZERINTERFACE_H

#include <QVector3D>
#include <QImage>
#include <QColor>

class ColorVertex;
class VertexProcessor;

class RasterizerInterface : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QColor paintColor READ paintColor WRITE setPaintColor)
	Q_PROPERTY(QColor clearColor READ clearColor WRITE setClearColor)
	Q_PROPERTY(VertexProcessor *vp READ vertexProcessor WRITE setVertexProcessor)
public:
	explicit RasterizerInterface(int width, int height, QObject *parent = 0);
	virtual QImage getDepthBuffer() const;
	virtual QImage getColorBuffer() const;
	virtual QImage getNormalBuffer() const;
	virtual QColor clearColor() const;
	virtual void setClearColor(const QColor &clearColor);
	virtual QColor paintColor() const;
	virtual void setPaintColor(const QColor &paintColor);
	virtual void triangle(ColorVertex a, ColorVertex b, ColorVertex c);
	virtual void setVertexProcessor(VertexProcessor *vp);
	virtual VertexProcessor *vertexProcessor() const;

public slots:
	virtual void clear();
	virtual void clearDepth();
	virtual void clearNormal();
	virtual void vertex(QVector3D v) = 0;
	virtual void normal(QVector3D n) = 0;
	virtual void setLightPosition(const QVector3D &lightPos) = 0;

protected:
	QImage mColorBuffer, mDepthBuffer, mNormalBuffer;
	QColor mClearColor, mPaintColor;
	QVector3D mNormal, mLightPos;
	VertexProcessor *mVP;
};

#endif // RASTERIZERINTERFACE_H
