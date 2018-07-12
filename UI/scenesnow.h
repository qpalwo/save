#ifndef SCENESNOW_H
#define SCENESNOW_H

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
#include "gainachieve.h"
#include"attr/player.h"
#include "menuWidget.h"

#define BDL -2880
#define BDR 0

struct plot4 {
	QString s;
	bool diff;
	bool hu;
	int l;
	int r;
};

namespace Ui {
class SceneSnow;
}

class SceneSnow : public QWidget
{
    Q_OBJECT

public:
    explicit SceneSnow(QWidget *parent = 0);
    ~SceneSnow();
    void paintEvent(QPaintEvent *e);
	void gameOver();
	void bagThingClick(int n);
	void changeState(bool a, bool b, bool c, bool d);


private:
    Ui::SceneSnow *ui;

    QImage backGround;
    QImage earth;
	QImage conver;
	QImage girl;


	QString record_1;
	QString record_2;
	QString begin;
	QString begin2;
	QString get[15];

    QMovie* player;
    QMovie* player_left;

	bool underTheSunshine(int n);
    void loadImage();
    void keyPressEvent(QKeyEvent *e);
	void loadPlot();
	struct plot4 q[100];

	int v;//add volume

	QMediaPlayer *bgm;//add bgm

	QCursor *myCursor;//add cursor

    int backX;
    int backY;
    int playerX;
	int talk;
	int waitTime;
	int ti;

    bool stop;
    bool left;
	bool zxLock;
	bool first;
	bool f[100];
	bool statement[5];
	bool isShow = false;
	bool gameover;
	bool rightThing;
};

#endif // SCENESNOW_H
