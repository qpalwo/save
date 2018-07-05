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
}

void SceneDesert::loadImage() {
	backGround.load(":/desertB/scene/desert_1.png");
	earth.load(":/desertB/scene/desert_2.png");
	player = new QMovie(":/player/main.gif");
}

void SceneDesert::paintEvent(QPaintEvent * e) {
	QPainter painter(this);

	painter.drawImage(backX, backY, backGround);
	painter.drawImage(backX, backY, backGround);

}

void SceneDesert::keyPressEvent(QKeyEvent *e) {
	QPainter painter(this);
	switch (e->key())
	{
	case Qt::Key_A: playerX = - 30;
	case Qt::Key_D: playerX = +30;
	}
	painter.drawPixmap(playerX, 350, 200, 400, player->currentPixmap()); 
}


SceneDesert::~SceneDesert()
{
    delete ui;
}
