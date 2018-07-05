#include "scenedesert.h"
#include "ui_scenedesert.h"

SceneDesert::SceneDesert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneDesert)
{
    ui->setupUi(this);
	
	backX = 0;   backY = 0; 
	playerX = 0;  
}

void SceneDesert::loadImage() {
	backGround.load(":/openRes/desert_1.png");
	earth.load(":/openRes/desert_2.png");
	player = new QMovie(":/openGif/background_sn.gif");
}

void SceneDesert::paintEvent(QPaintEvent * e) {
	QPainter painter(this);

	painter.drawImage(backX, backY, backGround);
	painter.drawImage(backX, backY, backGround);

}

SceneDesert::~SceneDesert()
{
    delete ui;
}
