#include "achieve.h"
#include "ui_achieve.h"

Achieve::Achieve(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Achieve) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	back.load(":/achieve/back.png");
	backButton = new OpenPageButton(this, "/menuZ/menu/", "set_back_ruins");
	backButton->setGeometry(830, 570, 70, 70);
	connect(backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));
    a = GameWorld::getInstance()->getAllAchieve();

    loadPixmap();
}

void Achieve::paintEvent(QPaintEvent *e) {
	QPainter painter(this);
    painter.drawPixmap(0, 0, back);
    painter.drawPixmap(130,100,achieve1);
    painter.drawPixmap(130,165,achieve2);
    painter.drawPixmap(130,230,achieve3);
    painter.drawPixmap(130,295,achieve4);
    painter.drawPixmap(130,360,achieve5);
    painter.drawPixmap(320,100,achieve6);
    painter.drawPixmap(320,380,achieve7);
}

void Achieve::loadPixmap(){
	
    if(*(a + 13)) achieve1.load(":/achieve/achieve_1_2.png");
    else achieve1.load(":/achieve/achieve_1.png");
    achieve2.load(":/achieve/achieve_1.png");
    achieve3.load(":/achieve/achieve_1.png");
    achieve4.load(":/achieve/achieve_1.png");
    achieve5.load(":/achieve/achieve_1.png");
    achieve6.load(":/achieve/achieve_1.png");
    achieve7.load(":/achieve/achieve_1.png");
    achieve8.load(":/achieve/achieve_1.png");
    achieve9.load(":/achieve/achieve_1.png");
    achieve10.load(":/achieve/achieve_1.png");
    achieve11.load(":/achieve/achieve_1.png");
    achieve12.load(":/achieve/achieve_1.png");
    achieve13.load(":/achieve/achieve_1.png");
    achieve14.load(":/achieve/achieve_1.png");

}

void Achieve::onBackClicked() {
	close();
}

Achieve::~Achieve() {
	delete ui;
}
