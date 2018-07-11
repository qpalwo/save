#ifndef SCENEDESERT_H
#define SCENEDESERT_H

#include <QMainWindow>
#include <qpainter.h>
#include <qimage.h>
#include <qrect.h>
#include <qpixmap.h>
#include <qtimer.h>
#include <QTime>
#include <QMovie>
#include <QWidget>
#include <QKeyEvent>
#include <qstring.h>
#include<QMouseEvent>
#include <QtGlobal>
#include"attr/player.h"
#include"gainachieve.h"
#include "menuwidget.h"

#define BDL -2880
#define BDR 0

struct plot {
	QString s;
	bool diff;
	bool hu;
	int l;
	int r;
};

namespace Ui {
class SceneDesert;
}

class SceneDesert : public QWidget
{
    Q_OBJECT

public:
    explicit SceneDesert(QWidget *parent = 0);
    ~SceneDesert();
	void paintEvent(QPaintEvent * e);
	void gameOver();
	void bagThingClick(int n);
	void changeState(bool a,bool b, bool c, bool d);

private slots:
	void on_bag_clicked();

private:
    Ui::SceneDesert *ui;

	QImage backGround;
	QImage earth;
	QImage conver;
	QImage uncle;
	QImage boat;

	QString record_1;
	QString record_2;
	QString mouse_out;
	QString begin;
	QString begin2;
	QString get[10];
	QPoint mouse;

	QMovie *player; 
	QMovie *player_left;

	bool underTheTree(int n);
	void loadImage();
    void keyPressEvent(QKeyEvent *e);
	void mouseMoveEvent(QMouseEvent* event);
	void loadPlot();

	int backX;
	int backY;
	int playerX;
	int waitTime;
	int talk;
	int ti;
	struct plot q[100];

	bool stop;
	bool left;
	bool first;
	bool zxFuck;
	bool f[100];
	bool zhu;
	bool gameover;
	bool statement[5];
};

#endif // SCENEDESERT_H
