#include "rasterizerinterface.h"
#include "colorvertex.h"

#include <QDebug>

RasterizerInterface::RasterizerInterface(int width, int height, QObject *parent) :
	QObject(parent),
	mColorBuffer(width, height, QImage::Format_ARGB32_Premultiplied)
{
	setClearColor(Qt::black);
	setPaintColor(Qt::white);
	clear();
}

QImage RasterizerInterface::getColorBuffer() const
{
	return mColorBuffer;
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

void RasterizerInterface::triangle(ColorVertex /*a*/, ColorVertex /*b*/, ColorVertex /*c*/)
{
	qDebug() << "This rasterizer does not support triangles";
}
