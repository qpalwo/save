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
	QMovie *player; 
	QMovie *player_left;

	void loadImage();
    void keyPressEvent(QKeyEvent *e);
	void plot(QKeyEvent *e);

	int backX;
	int backY;
	//int backLocation;
	int playerX;
	bool stop;
	bool left;
};

#endif // SCENEDESERT_H
