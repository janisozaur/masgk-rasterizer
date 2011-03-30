#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rasterizer.h"
#include "qscriptctors.h"
#include "colorvertex.h"

#include <QPixmap>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->execPushButton, SIGNAL(clicked()), this, SLOT(executeScript()));

	mRaster = new Rasterizer(512, 512, this);
	mEngine.globalObject().setProperty("rasterizer", mEngine.newQObject(mRaster));
	mEngine.globalObject().setProperty("mainWindow", mEngine.newQObject(this));
	mEngine.globalObject().setProperty("QColor", mEngine.newFunction(QColor_ctor));

	//ColorVertex c1(QVector3D(20, 120, 20), Qt::red);
	//ColorVertex c2(QVector3D(130, 60, 20), Qt::green);
	//ColorVertex c3(QVector3D(40, 20, 20), Qt::blue);
	//mRaster->triangle(c1, c2, c3);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::render()
{
	QImage result = mRaster->getColorBuffer();
	ui->outputDisplayLabel->setPixmap(QPixmap::fromImage(result));
}

void MainWindow::executeScript()
{
	QScriptValue res = mEngine.evaluate(ui->scriptTextEdit->toPlainText());
	if (res.isValid() && !res.isUndefined()) {
		qDebug() << res.toString();
	}
	if (mEngine.hasUncaughtException()) {
		qDebug() << "uncaught exception " << mEngine.uncaughtException().toString()
				 << " backtrace:" << mEngine.uncaughtExceptionBacktrace()
				 << " in line" << mEngine.uncaughtExceptionLineNumber();
	}
}
