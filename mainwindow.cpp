#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rasterizer.h"
#include "colorvertex.h"

#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Rasterizer *raster = new Rasterizer(512, 512);
	ColorVertex c1(QVector3D(20, 120, 20), Qt::red);
	ColorVertex c2(QVector3D(130, 60, 20), Qt::green);
	ColorVertex c3(QVector3D(40, 20, 20), Qt::blue);
	raster->triangle(c1, c2, c3);
	QImage result = raster->getColorBuffer();
	ui->outputDisplayLabel->setPixmap(QPixmap::fromImage(result));
}

MainWindow::~MainWindow()
{
	delete ui;
}
