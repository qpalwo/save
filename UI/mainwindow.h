#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define _ABS(x) ((x) > 0 ? (x) : -(x))

#include <QMainWindow>
#include <qpainter.h>
#include <qimage.h>
#include <qrect.h>
#include <qpixmap.h>
#include <qtimer.h>
#include <QTime>
#include <QMovie>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <QFile>
#include <QtConcurrent/qtconcurrentrun.h>

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
	void keyPressEvent(QKeyEvent *e);

public slots:
	void handelWeather(QNetworkReply *);

private slots:
	void moveMou();
	void moveScene();

private:
    Ui::MainWindow *ui;
	QTimer *verticalTimer;

	QImage back_mou;
	QImage for_mou;
	QImage earth;
	QImage sun;
	QImage moon;
	QImage cloud;
	QMovie *backGif;
	QMovie *rightPlayer = NULL;
	QMovie *rain = NULL;

	void loadImage();
	void loadWeatherImage();
	void initWeather();
	void initSun();
	void initTimer();
	void initVerticalTimer();

	int weather;
	int sunY;
	int sunX;
	int forMouLocation;
	int p;
	int sceneHeight;
};

#endif // MAINWINDOW_H
