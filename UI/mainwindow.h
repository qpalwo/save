#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpainter.h>
#include <qimage.h>
#include <qrect.h>
#include <qpixmap.h>
#include <qtimer.h>
#include <QTime>
#include <QMovie>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void paintEvent(QPaintEvent * e);

	
private slots:
	void moveMou();

private:
    Ui::MainWindow *ui;

	QImage back_mou;
	QImage for_mou;
	QImage earth;
	QImage sun;
	QImage moon;
	QMovie *backGif;


	void loadImage();
	void initWeather();
	void initSun();
	void initTimer();

	int weather;
	int sunY;
	int sunX;
	int forMouLocation;
	int p;
};

#endif // MAINWINDOW_H
