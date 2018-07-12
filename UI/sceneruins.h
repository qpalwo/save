#ifndef SCENERUINS_H
#define SCENERUINS_H

#include <QWidget>
#include <QMainWindow>
#include <qpainter.h>
#include <qimage.h>
#include <qrect.h>
#include <qpixmap.h>
#include <qtimer.h>
#include <QTime>
#include <QMovie>
#include <QtGlobal>
#include <QMediaPlayer>//add music
#include <QCursor>//add cursor
#include<qlabel.h>
#include"attr/player.h"
#include"gainachieve.h"
#include "menuWidget.h"

#define BDL -2880
#define BDR 0

struct plot3 {
	QString s;
	bool diff;
	bool hu;
	int l;
	int r;
};

namespace Ui {
class SceneRuins;
}

class SceneRuins : public QWidget
{
    Q_OBJECT

public:
    explicit SceneRuins(QWidget *parent = 0);
    ~SceneRuins();
    void paintEvent(QPaintEvent *e);
	void gameOver();
	void bagThingClick(int n);
	void changeState(bool a, bool b, bool c, bool d);

public slots:
	void reFresh();
	void stopStratMovie();

private:
    Ui::SceneRuins *ui;

    QImage backGround;
    QImage earth;
	QImage sky;
	QImage conver;
	QImage child;
	QImage illustrate;
	QImage tower;
	QImage getI[10];

	QString record_1;
	QString record_2;
	QString begin;
	QString Ending1;
	QString Ending2;
	QString get[15];

    QMovie* player;
    QMovie* player_left;
	QMovie* color;
	QMovie *startMovie;
	QLabel *startLabel;
	QTimer *traffic = NULL;

	bool underDoor(int n);
    void loadImage();
    void keyPressEvent(QKeyEvent *e);
	void loadPlot();
	void initTimer();
	struct plot3 q[100];

	int v;//add volume

	QMediaPlayer *bgm;//add bgm

	QCursor *myCursor;//add cursor

    int backX;
    int backY;
    int playerX;
	int waitTime;
	int talk;
	int ti;
	bool isPlay = false;

    bool stop;
    bool left;
	bool zxLock;
	bool first;
	bool f[100] = {false};
	bool space1;
	bool space2;
	bool gameover;
	bool statement[5] = {false};
	bool rightThing;
	bool isSpace=false;
	bool ifget=false;
	bool tomap=false;
};

#endif // SCENERUINS_H
