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

    loadImage();
    backButton = new OpenPageButton(this, "/menuZ/menu/", "set_back_desert");
    backButton->setGeometry(830, 570, 70, 70);
    connect(backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));
}

void GameMap::loadImage(){
    initial.load(":/GameMap/map_initial.png");
    desert.load(":/GameMap/map_desert.png");
    forest.load(":/GameMap/map_forest.png");
    ruins.load(":/GameMap/map_ruins.png");
    snow.load(":/GameMap/map_snow.png");
}

void GameMap::paintEvent(QPaintEvent *event){
    QPainter paint(this);
    paint.drawImage(0,0,initial);
    if(!*m_map) paint.drawImage(0,0,desert);
    if(!*(m_map+1)) paint.drawImage(0,0,forest);
    if(!*(m_map+2)) paint.drawImage(0,0,ruins);
    if(!*(m_map+3)) paint.drawImage(0,0,snow);
}

void GameMap::onBackClicked(){
    close();
    deleteLater();
}

GameMap::~GameMap() {
	delete ui;
}
