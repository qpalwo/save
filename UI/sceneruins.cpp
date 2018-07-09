#include "sceneruins.h"
#include "ui_sceneruins.h"

SceneRuins::SceneRuins(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneRuins)
{
    ui->setupUi(this);
    backX = 0;
    backY = 0;
    playerX = 0;
    stop = false;
    left = false;
    loadImage();

    menuwidget *menu = new menuwidget(this);

    setFocus();

    menu->show();
}

void SceneRuins::loadImage()
{
    backGround.load(":/ruins/scene/ruins_2.png");
    earth.load(":/ruins/scene/ruins_1.png");
    player = new QMovie(":/player/main.gif");
    player_left = new QMovie(":/player/main_left.gif");
    player->start();
    player_left->start();
}

void SceneRuins::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawImage(backX, backY, backGround);

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
}

void SceneRuins::keyPressEvent(QKeyEvent* e)
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
        if (backX < BDL)
        {
            backX += 10;
            stop = false;
            playerX += 10;
        }
        if (backX > BDR)
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
        if (playerX > 860)
        {
            playerX -= 10;
        }
    }

    update();
}

SceneRuins::~SceneRuins()
{
    delete ui;
}
