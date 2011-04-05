#include "rasterizerinterface.h"
#include "colorvertex.h"

#include <QDebug>

RasterizerInterface::RasterizerInterface(int width, int height, QObject *parent) :
	QObject(parent),
	mColorBuffer(width, height, QImage::Format_ARGB32_Premultiplied),
	mDepthBuffer(width, height, QImage::Format_Indexed8),
	mVP(NULL)
{
	setClearColor(Qt::black);
	setPaintColor(Qt::white);
	QVector<QRgb> colorTable;
	colorTable.reserve(256);
	for (int i = 0; i < 256; i++) {
		colorTable << qRgb(i, i, i);
	}
	mDepthBuffer.setColorTable(colorTable);
	clear();
	clearDepth();
}

QImage RasterizerInterface::getColorBuffer() const
{
	return mColorBuffer;
}

QImage RasterizerInterface::getDepthBuffer() const
{
	return mDepthBuffer;
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
	mDepthBuffer.fill(255);
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
