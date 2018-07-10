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

    QMovie* player;
    QMovie* player_left;

	bool underTheSunshine(int n);
    void loadImage();
    void keyPressEvent(QKeyEvent *e);
	void loadPlot();
	struct plot4 q[100];

    int backX;
    int backY;
    int playerX;
	int talk;
	int waitTime;

    bool stop;
    bool left;
	bool zxLock;
	bool first;
	bool f[100];
};

#endif // SCENESNOW_H
