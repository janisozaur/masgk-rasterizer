#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rasterizer.h"
#include "colorvertex.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	Rasterizer *raster = new Rasterizer(512, 512);
	ColorVertex c1(QVector3D(20, 20, 20), Qt::white);
	ColorVertex c2(QVector3D(30, 40, 20), Qt::white);
	ColorVertex c3(QVector3D(40, 20, 20), Qt::white);
	raster->triangle(c1, c2, c3);
	raster->getColorBuffer().save("out.png");
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}
