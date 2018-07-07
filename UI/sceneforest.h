#ifndef SCENEFOREST_H
#define SCENEFOREST_H

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

private:
    Ui::SceneForest *ui;

    QImage backGround;
    QImage earth;
    QMovie* player;
    QMovie* player_left;


    void loadImage();
    void keyPressEvent(QKeyEvent *e);

    int backX;
    int backY;
    int playerX;
    bool stop;
    bool left;

};

#endif // SCENEFOREST_H
