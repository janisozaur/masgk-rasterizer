#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScriptEngine>

namespace Ui {
	class MainWindow;
}

class RasterizerInterface;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void render();
	void renderDepth();
	void renderNormal();
	void executeScript();

private:
	Ui::MainWindow *ui;
	RasterizerInterface *mRaster;
	QScriptEngine mEngine;
};

#endif // MAINWINDOW_H
