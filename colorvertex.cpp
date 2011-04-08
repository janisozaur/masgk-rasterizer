#include "colorvertex.h"

ColorVertex::ColorVertex()
{

}

ColorVertex::ColorVertex(QVector3D pos, QVector3D viewPos, QVector3D normal,
						 QColor color) :
	mPos(pos),
	mViewPos(viewPos),
	mNormal(normal),
	mColor(color)
{
}
