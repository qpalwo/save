#include "gamemap.h"
#include "ui_gamemap.h"



/***************************
 ****   desert   ----->    1
 ****   forest   ----->    2
 ****   ruins    ----->    3
 ****   snow     ----->    4
****************************/



GameMap::GameMap(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::GameMap) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	m_map = Player::getInstance()->getMapStaus();
}

GameMap::~GameMap() {
	delete ui;
}
