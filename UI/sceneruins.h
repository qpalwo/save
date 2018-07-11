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

private:
    Ui::SceneRuins *ui;

    QImage backGround;
	QImage backGround2;
    QImage earth;
	QImage earth2;
	QImage sky;
	QImage sky2;
	QImage conver;
	QImage child;

	QString record_1;
	QString record_2;
	QString begin;
	QString Ending1;
	QString Ending2;
	QString Achieve1;
	QString Achieve2;
	QString get[15];


    QMovie* player;
    QMovie* player_left;

	bool underDoor(int n);
    void loadImage();
    void keyPressEvent(QKeyEvent *e);
	void loadPlot();
	struct plot3 q[100];

    int backX;
    int backY;
    int playerX;
	int waitTime;
	int talk;
	int ti;

    bool stop;
    bool left;
	bool zxLock;
	bool first;
	bool f[100] = {false};
	bool space1;
	bool space2;
};

#endif // SCENERUINS_H
