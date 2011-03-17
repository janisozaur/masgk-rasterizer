#include "colorvertex.h"

ColorVertex::ColorVertex()
{

}

ColorVertex::ColorVertex(QVector3D pos, QColor color) :
	mPos(pos),
	mColor(color)
{
}
