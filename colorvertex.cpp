#include "colorvertex.h"

ColorVertex::ColorVertex()
{

}

ColorVertex::ColorVertex(QVector3D pos, QVector3D normal, QColor color) :
	mPos(pos),
	mNormal(normal),
	mColor(color)
{
}
