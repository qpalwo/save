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
	QMovie *player; 

	void loadImage();
	void moveMent();
	void keyPressEvent(QKeyEvent *e);

	int backX;
	int backY;
	int backLocation;
	int playerX;
	int p;
};

#endif // SCENEDESERT_H
