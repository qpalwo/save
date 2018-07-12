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
#include "openpagebutton.h"
#include <QHBoxLayout>
#include "attr/gameworld.h"
#include <QWidget>
#include <QtGlobal>
#include <QTime>
#include "set.h"
#include <QMediaPlayer>//add music
#include <QCursor>//add cursor
#include <QMouseEvent>

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

	void onBeginClicked();
	void onAchieveClicked();
	void onSetClicked();
	void onContinueClicked();
	void onEasyClicked();
	void onMidClicked();
    void onHardClicked();

    void changeVolume(int x);

private:
    Ui::MainWindow *ui;
	QTimer *verticalTimer;

	QImage back_mou;
	QImage for_mou;
	QImage earth;
	QImage sun;
	QImage moon;
	QImage cloud;
	QMovie *backGif = NULL;
	QMovie *rightPlayer = NULL;
	QMovie *rain = NULL;
	QMovie *icon = NULL;

    int v;//add volume

    QMediaPlayer *bgm;//add bgm

    QCursor *myCursor;//add cursor
	QTimer *mainTimer = NULL;

	OpenPageButton *open = NULL;
	OpenPageButton *b_continue = NULL;
	OpenPageButton *achieve = NULL;
    OpenPageButton *setting = NULL;
	OpenPageButton *easy = NULL;
	OpenPageButton *mid = NULL;
	OpenPageButton *hard = NULL;

    set *set_main = NULL;

	void loadImage();
	void loadWeatherImage();
	void initWeather();
	void initSun();
	void initTimer();
	void initVerticalTimer();
	void initMenu();
	void initHardChoose();
    void hideMenu();

	bool isDown = false;
	int weather;
	int sunY;
	int sunX;
	int forMouLocation;
	int p;
	int sceneHeight;
	int sceneType;
    int nowTime;
	bool showIcon = false;
};

#endif // MAINWINDOW_H
