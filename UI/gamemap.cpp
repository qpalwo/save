#include "gamemap.h"
#include "ui_gamemap.h"
#include "UiManager.h"



/***************************
 ****   desert   ----->    1
 ****   forest   ----->    2
 ****   ruins    ----->    3
 ****   snow     ----->    4
****************************/



GameMap::GameMap(bool is, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::GameMap) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	m_map = Player::getInstance()->getMapStaus();
	m_is = is;
    loadImage();
    backButton = new OpenPageButton(this, "/menuZ/menu/", "set_back_desert");
    backButton->setGeometry(830, 570, 70, 70);
    connect(backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));

    myLabel = new QLabel(this);
    setMouseTracking(true);
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

void GameMap::mouseMoveEvent(QMouseEvent *event){
    mouse = event->pos();
    posX=mouse.x();
    posY=mouse.y();
    if(posX>373&&posX<541&&posY>290&&posY<566) id = 3;
    else{
        if(posX>542&&posX<750&&posY>182&&posY<508) id = 4;
        else{
            if(posX>293&&posX<537&&posY>566&&posY<663) id = 1;
            else{
                if(posX>542&&posX<767&&posY>508&&posY<669) id = 2;
                else id =0;
            }
        }
    }

    if(id != 0){
        small.load(":/GameMap/small_2.png");
        myLabel->setPixmap(small);
        myLabel->show();
    switch (id) {
    case 1:
        myLabel->setGeometry(109,628,54,54);
        break;
    case 2:
        myLabel->setGeometry(859,495,54,54);
        break;
    case 3:
        myLabel->setGeometry(198,363,54,54);
        break;
    case 4:
        myLabel->setGeometry(788,313,54,54);
        break;
    default:
        break;
    }
    }
    else myLabel->hide();
}

void GameMap::mouseReleaseEvent(QMouseEvent *event){
	if (m_is) {
		if (posX > 373 && posX < 541 && posY>290 && posY < 566) id = 3;
		else {
			if (posX > 542 && posX < 750 && posY>182 && posY < 508) id = 4;
			else {
				if (posX > 293 && posX < 537 && posY>566 && posY < 663) id = 1;
				else {
					if (posX > 542 && posX < 767 && posY>508 && posY < 669) id = 2;
					else id = 0;
				}
			}
		}

		switch (id) {
		case 1:
			if(!*m_map)
				UiManager::getInstance()->fromMapToDesert();
			break;
		case 2:
			if(!*(m_map + 1))
				UiManager::getInstance()->fromMapToForest();
			break;
		case 3:
			if (!*(m_map + 2))
				UiManager::getInstance()->fromMapToRuins();
			break;
		case 4:
			if (!*(m_map + 3))
				UiManager::getInstance()->fromMapToSnow();
			break;
		default:
			break;
		}
	}


}

void GameMap::onBackClicked(){
    close();
    deleteLater();
}

GameMap::~GameMap() {
	delete ui;
}
