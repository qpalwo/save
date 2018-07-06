#include "sceneforest.h"
#include "ui_sceneforest.h"
#include <QKeyEvent>

SceneForest::SceneForest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneForest)
{
    ui->setupUi(this);
    backX = 0;
    backY = 0;
    p = 0;
    playerX = 0;
    loadImage();
}

void SceneForest::loadImage()
{
    backGround.load(":/forest/scene/forest_1.png");
    earth.load(":/forest/scene/forest_2.png");
    player = new QMovie(":/player/main.gif");
    player_left = new QMovie(":/player/main_left.gif");
    player->start();
    player_left->start();
}
void SceneForest::paintEvent(QPaintEvent * e) {
    QPainter painter(this);

    painter.drawImage(backX, backY, backGround);
    if (backX < -2880)
    {
        p = (-backX+960)/3840;
        painter.drawImage(backX + 3840*p, backY, backGround);
        painter.drawImage(backX + 3840*(p-1), backY, backGround);
    }

    if (playerX == 430)
    {
        stop = true;
    }

    if (left)
    {
        painter.drawPixmap(playerX, 235, 100, 200, player_left->currentPixmap());
    }
    else
    {
        painter.drawPixmap(playerX, 235, 100, 200, player->currentPixmap());
    }
    painter.drawImage(backX, backY, earth);
    if (backX < -2880)
    {
        p = (-backX+960)/3840;
        painter.drawImage(backX + 3840*p, backY, earth);
        painter.drawImage(backX + 3840*(p-1), backY, earth);
    }
}

void SceneForest::keyPressEvent(QKeyEvent* e)
{
    if (stop)
    {
        switch (e->key())
        {
        case Qt::Key_A:
            backX += 10;
            left = true;
            break;
        case Qt::Key_Left:
            backX += 10;
            left = true;
            break;
        case Qt::Key_D:
            backX -= 10;
            left = false;
            break;
        case Qt::Key_Right:
            backX -= 10;
            left = false;
            break;
        default:
            break;
        }
        if (backX > 0)
        {
            backX -= 10;
            stop = false;
            playerX -= 10;
        }
    }
    else {
        switch (e->key())
        {
        case Qt::Key_A:
            playerX -= 10;
            left = true;
            break;
        case Qt::Key_Left:
            playerX -= 10;
            left = true;
            break;
        case Qt::Key_D:
            playerX += 10;
            left = false;
            break;
        case Qt::Key_Right:
            playerX += 10;
            left = false; break;
        default:
            break;
        }
        if (playerX < 0)
        {
            playerX += 10;
        }
    }

    update();
}
SceneForest::~SceneForest()
{
    delete ui;
}
