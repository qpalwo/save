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
#include "menuWidget.h"

#define BDL -2880
#define BDR 0

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

#endif // SCENERUINS_H
