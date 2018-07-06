#include "scenedesert.h"
#include "ui_scenedesert.h"
#include <QKeyEvent>
#define BDL -2880
#define BDR 0

SceneDesert::SceneDesert(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SceneDesert) {
	ui->setupUi(this);

	backX = 0;   backY = 0;
	playerX = 0;
	stop = false;
	left = false;
	loadImage();
}

void SceneDesert::loadImage() {
	backGround.load(":/desertB/scene/desert_1.png");
	earth.load(":/desertB/scene/desert_2.png");
	player = new QMovie(":/player/main.gif");
	player_left = new QMovie(":/player/main_left.gif");
	option_1.load(":/conver/convar/choice_1.png");
	option_2.load(":/conver/convar/choice_2.png");
	option_3.load(":/conver/convar/choice_3.png");
	conver.load(":/conver/convar/convar.png");
	name.load(":/conver/convar/name.png");
	player->start();
	player_left->start();
}

void SceneDesert::paintEvent(QPaintEvent * e) {
	QPainter painter(this);
	QPen pen; //»­±Ê
	pen.setColor(QColor(255, 255, 0));
	QBrush brush(QColor(255, 255, 0, 125)); //»­Ë¢
	painter.setPen(pen); //Ìí¼Ó»­±Ê
	painter.setBrush(brush); //Ìí¼Ó»­Ë¢
	

	painter.drawImage(backX, backY, backGround);

	if (playerX == 430) {
		stop = true;
	}
	if (left) painter.drawPixmap(playerX, 250, 100, 200, player_left->currentPixmap());
	else painter.drawPixmap(playerX, 250, 100, 200, player->currentPixmap());
	painter.drawImage(backX, backY, earth);

	if ((waitTime>0)&&(waitTime<=30))
		painter.drawRect(playerX, 260, 10+waitTime*3, 20); //»æÖÆ¾ØÐÎ

}

void SceneDesert::keyPressEvent(QKeyEvent *e) {
	if (stop) {                         //main player stop
		switch (e->key()) {
		case Qt::Key_A: backX += 10;  left = true; break;
		case Qt::Key_Left: backX += 10; left = true; break;
		case Qt::Key_D: backX -= 10;  left = false;  break;
		case Qt::Key_Right: backX -= 10;  left = false;  break;
		}
		if (backX < BDL) { backX += 10;  stop = false; playerX += 10; }
		if (backX > BDR) { backX -= 10;   stop = false; playerX -= 10; }
	}
	else {                                // back stop
		switch (e->key()) {
		case Qt::Key_A: playerX -= 10;  left = true;  break;
		case Qt::Key_Left: playerX -= 10;  left = true; break;
		case Qt::Key_D: playerX += 10; left = false; break;
		case Qt::Key_Right: playerX += 10; left = false; break;
		}
		if (e->key() == Qt::Key_Space) {
			if (underTheTree(1))	waitTime++;
		}
		else waitTime = 0;

		if (playerX < 0) { playerX += 10; }
		if (playerX > 860) { playerX -= 10; }
	}

	update();
}

bool SceneDesert::underTheTree(int n) {
	if (n == 1) {
		if ((playerX >= 280) && (playerX <= 310))  return true;
		if ((playerX >= 490) && (playerX <= 520))  return true;
	}
	return false;
}


SceneDesert::~SceneDesert() {
	delete ui;
}
