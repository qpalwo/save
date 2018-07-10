#ifndef SCENEFOREST_H
#define SCENEFOREST_H

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

struct plot2 {
	QString s;
	bool diff;
	bool hu;
	int l;
	int r;
};

#define BDL -2880
#define BDR 0

namespace Ui {
	class SceneForest;
}

class SceneForest : public QWidget
{
	Q_OBJECT

public:
	explicit SceneForest(QWidget *parent = 0);
	~SceneForest();
	void paintEvent(QPaintEvent * e);

private slots:
	void on_bag_clicked();

private:
	Ui::SceneForest *ui;

	QImage backGround;
	QImage earth;
	QImage conver;
	QImage uncle;
	QImage house_closed;
	QImage house_open;
	QPoint mouse;
	QString record_1;
	QString record_2;
	QString mouse_out;
	QString begin;

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

	struct plot2 q[100];
	
	bool stop;
	bool left;
	bool first;
	bool zxFuck;
	bool f[100];
};

#endif // SCENEDESERT_H