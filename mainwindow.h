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

private slots:
	void on_savePushButton_clicked();

	void on_startPushButton_clicked();

	void on_stopPushButton_clicked();

private:
	Ui::MainWindow *ui;
	RasterizerInterface *mRaster;
	QScriptEngine mEngine;
	int mTimerId;

protected:
	virtual void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
