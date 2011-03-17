#include "rasterizerinterface.h"

RasterizerInterface::RasterizerInterface(int width, int height) :
	mColorBuffer(width, height, QImage::Format_ARGB32_Premultiplied)
{
	setClearColor(Qt::black);
	setPaintColor(Qt::white);
}

QImage RasterizerInterface::getColorBuffer() const
{
	return mColorBuffer;
}

void RasterizerInterface::setClearColor(QColor clearColor)
{
	mClearColor = clearColor;
}

void RasterizerInterface::setPaintColor(QColor paintColor)
{
	mPaintColor = paintColor;
}

void RasterizerInterface::clear()
{
	mColorBuffer.fill(mClearColor.rgba());
}
