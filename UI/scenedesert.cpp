#include "scenedesert.h"
#include "ui_scenedesert.h"
#include <QKeyEvent>

SceneDesert::SceneDesert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneDesert)
{
    ui->setupUi(this);
	
	backX = 0;   backY = 0; 
	playerX = 0;  
	stop = false; 
	stopB = false;
	left = false;
	loadImage();
}

void SceneDesert::loadImage() {
	backGround.load(":/desertB/scene/desert_1.png");
	earth.load(":/desertB/scene/desert_2.png");
	player = new QMovie(":/player/main.gif");
	player_left = new QMovie(":/player/main_left.gif");
	player->start(); 
	player_left->start();
}

void SceneDesert::paintEvent(QPaintEvent * e) {
	QPainter painter(this);

    painter.drawImage(backX, backY, backGround);
	
	if (playerX >= 430) {
		stop = true;  
	}
	if (left) painter.drawPixmap(playerX,250, 100, 200, player_left->currentPixmap());
	else painter.drawPixmap(playerX, 250, 100, 200, player->currentPixmap());
    painter.drawImage(backX, backY, earth);
}

void SceneDesert::keyPressEvent(QKeyEvent *e) {
	if (stop) {
		switch (e->key())
		{
		case Qt::Key_A: backX += 10;  left = true; break;
		case Qt::Key_Left: backX += 10; left = true; break;
		case Qt::Key_D: backX -= 10;  left = false;  break;
		case Qt::Key_Right: backX -= 10;  left = false;  break;
		}
		if (backX <= -2890) backX += 10;
		if (backX >= 0) backX -= 10;
	}
	else {
		switch (e->key())
		{
		case Qt::Key_A: playerX -= 10;  left = true;  break;
		case Qt::Key_Left: playerX -= 10;  left = true; break;
		case Qt::Key_D: playerX += 10; left = false; break;
		case Qt::Key_Right: playerX += 10; left = false; break;
		}
	}
	update();
}


SceneDesert::~SceneDesert()
{
    delete ui;
}
