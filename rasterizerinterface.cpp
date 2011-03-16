#include "rasterizerinterface.h"

RasterizerInterface::RasterizerInterface(int width, int height) :
	mColorBuffer(width, height, QImage::Format_ARGB32_Premultiplied)
{
}

QImage RasterizerInterface::getColorBuffer() const
{
	return mColorBuffer;
}
