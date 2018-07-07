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

private:
    Ui::SceneDesert *ui;

	QImage backGround;
	QImage earth;
	QImage option_1;
	QImage option_2;
	QImage option_3;
	QImage conver;
	QImage name;
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
	QString mouse_out;
	struct plot q[100];

	bool stop;
	bool left;
	bool choose;
	bool zz;
	bool xx;
};

#endif // SCENEDESERT_H
