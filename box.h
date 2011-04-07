#ifndef BOX_H
#define BOX_H

#include <QObject>

class RasterizerInterface;

class Box : public QObject
{
	Q_OBJECT
public:
	Box(RasterizerInterface *rasterizer);
	~Box();

public slots:
	void render();
	void scale(qreal s);

private:
	RasterizerInterface *mRasterizer;
	qreal mScale;
};

#endif // BOX_H
