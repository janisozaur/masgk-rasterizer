#include "rasterizerinterface.h"
#include "colorvertex.h"

#include <QDebug>

RasterizerInterface::RasterizerInterface(int width, int height, QObject *parent) :
	QObject(parent),
	mColorBuffer(width, height, QImage::Format_ARGB32_Premultiplied),
	mNormalBuffer(width, height, QImage::Format_RGB32),
	mDepthBuffer(width * height, 255.0),
	mVP(NULL)
{
	setClearColor(Qt::black);
	setPaintColor(Qt::white);
	clear();
	clearDepth();
}

QImage RasterizerInterface::getColorBuffer() const
{
	return mColorBuffer;
}

QImage RasterizerInterface::getDepthBuffer() const
{
	QImage result(mColorBuffer.size(), QImage::Format_RGB32);
	for (int y = 0; y < mColorBuffer.height(); y++) {
		for (int x = 0; x < mColorBuffer.width(); x++) {
			//qreal val = qBound(0.0, mDepthBuffer.at(y * mColorBuffer.width() + x), 1.0);
			qreal val = mDepthBuffer.at(y * mColorBuffer.width() + x);
			QRgb color = qRgb(val, val, val);
			result.setPixel(x, y, color);
		}
	}
	return result;
}

QImage RasterizerInterface::getNormalBuffer() const
{
	return mNormalBuffer;
}

void RasterizerInterface::setClearColor(const QColor &clearColor)
{
	mClearColor = clearColor;
}

void RasterizerInterface::setPaintColor(const QColor &paintColor)
{
	mPaintColor = paintColor;
}

QColor RasterizerInterface::paintColor() const
{
	return mPaintColor;
}

QColor RasterizerInterface::clearColor() const
{
	return mClearColor;
}

void RasterizerInterface::clear()
{
	mColorBuffer.fill(mClearColor.rgba());
}

void RasterizerInterface::clearDepth()
{
	mDepthBuffer.fill(255.0);
}

void RasterizerInterface::clearNormal()
{
	mNormalBuffer.fill(Qt::black);
}

void RasterizerInterface::triangle(ColorVertex /*a*/, ColorVertex /*b*/, ColorVertex /*c*/)
{
	qDebug() << "This rasterizer does not support triangles";
}

void RasterizerInterface::setVertexProcessor(VertexProcessor *vp)
{
	mVP = vp;
}

VertexProcessor *RasterizerInterface::vertexProcessor() const
{
	return mVP;
}
