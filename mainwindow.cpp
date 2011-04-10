#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rasterizer.h"
#include "qscriptctors.h"
#include "colorvertex.h"
#include "vertexprocessor.h"

#include <QTime>
#include <QPixmap>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mTimerId(-1)
{
	ui->setupUi(this);
	connect(ui->execPushButton, SIGNAL(clicked()), this, SLOT(executeScript()));

	mRaster = new Rasterizer(512, 512, this);
	mEngine.globalObject().setProperty("rasterizer", mEngine.newQObject(mRaster));
	mEngine.globalObject().setProperty("mainWindow", mEngine.newQObject(this));
	mEngine.globalObject().setProperty("QColor", mEngine.newFunction(QColor_ctor));
	mEngine.globalObject().setProperty("QVector3D", mEngine.newFunction(QVector3D_ctor));
	mEngine.globalObject().setProperty("Box", mEngine.newFunction(Box_ctor));
	mEngine.globalObject().setProperty("Sphere", mEngine.newFunction(Sphere_ctor));
	mEngine.globalObject().setProperty("Cylinder", mEngine.newFunction(Cylinder_ctor));
	qScriptRegisterMetaType(&mEngine, vertexProcessorToScriptValue, vertexProcessorFromScriptValue);
	qScriptRegisterMetaType(&mEngine, boxToScriptValue, boxFromScriptValue);
	qScriptRegisterMetaType(&mEngine, sphereToScriptValue, sphereFromScriptValue);
	qScriptRegisterMetaType(&mEngine, cylinderToScriptValue, cylinderFromScriptValue);

	mRaster->setVertexProcessor(new VertexProcessor(this));

	QAction* action = new QAction(ui->scriptTextEdit);
	action->setShortcut(tr("Ctrl+Return"));
	connect(action, SIGNAL(triggered()), ui->execPushButton, SLOT(click()));
	ui->scriptTextEdit->addAction(action);

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

void MainWindow::renderDepth()
{
	QImage result = mRaster->getDepthBuffer();
	ui->outputDisplayLabel->setPixmap(QPixmap::fromImage(result));
}

void MainWindow::renderNormal()
{
	QImage result = mRaster->getNormalBuffer();
	ui->outputDisplayLabel->setPixmap(QPixmap::fromImage(result));
}

void MainWindow::executeScript()
{
	QString script(ui->scriptTextEdit->toPlainText());
	QTime time;
	time.start();
	QScriptValue res = mEngine.evaluate(script);
	int taken = time.elapsed();
	qDebug() << "time taken:" << taken;
	if (res.isValid() && !res.isUndefined()) {
		qDebug() << res.toString();
	}
	if (mEngine.hasUncaughtException()) {
		qDebug() << "uncaught exception " << mEngine.uncaughtException().toString()
				 << " backtrace:" << mEngine.uncaughtExceptionBacktrace()
				 << " in line" << mEngine.uncaughtExceptionLineNumber();
	}
}

void MainWindow::on_savePushButton_clicked()
{
	const QPixmap *p = ui->outputDisplayLabel->pixmap();
	if (p != NULL) {
		p->save("out.png");
	}
}

void MainWindow::on_startPushButton_clicked()
{
	mTimerId = startTimer(ui->intervalSlider->value());
	ui->startPushButton->setEnabled(false);
	ui->stopPushButton->setEnabled(true);
	ui->intervalSlider->setEnabled(false);
}

void MainWindow::on_stopPushButton_clicked()
{
	killTimer(mTimerId);
	mTimerId = -1;
	ui->startPushButton->setEnabled(true);
	ui->stopPushButton->setEnabled(false);
	ui->intervalSlider->setEnabled(true);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == mTimerId) {
		executeScript();
	}
}
