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
    int r1,r2,r3,r4,r5,r6;
    int c1,c2,c3,c4;
    r1 = 100;
    r2 = 165;
    r3 = 230;
    r4 = 295;
    r5 = 360;
    r6 = 425;
    c1 = 130;
    c2 = 330;
    c3 = 530;
    c4 = 730;
    painter.drawPixmap(0, 0, back);
    painter.drawPixmap(c1,r1,achieve1);
    painter.drawPixmap(c1,r2,achieve2);
    painter.drawPixmap(c1,r3,achieve3);
    painter.drawPixmap(c1,r4,achieve4);
    painter.drawPixmap(c1,r5,achieve5);
    painter.drawPixmap(c2,r1,achieve6);
    painter.drawPixmap(c2,r2,achieve7);
    painter.drawPixmap(c2,r3,achieve8);
    painter.drawPixmap(c2,r4,achieve9);
    painter.drawPixmap(c2,r5,achieve10);
    painter.drawPixmap(c2,r6,achieve11);
    painter.drawPixmap(c3,r1,achieve12);
    painter.drawPixmap(c3,r2,achieve13);
    painter.drawPixmap(c3,r3,achieve14);
    painter.drawPixmap(c3,r4,achieve15);
    painter.drawPixmap(c3,r5,achieve16);
    painter.drawPixmap(c3,r6,achieve17);
    painter.drawPixmap(c4,r1,achieve18);
    painter.drawPixmap(c4,r2,achieve19);
    painter.drawPixmap(c4,r3,achieve20);
    painter.drawPixmap(c4,r4,achieve21);
    painter.drawPixmap(c4,r5,achieve22);
    painter.drawPixmap(c4,r6,achieve23);
}

void Achieve::loadPixmap(){
    if(a)achieve1.load(":/achieve/achieve_1_2.png");
    else achieve1.load(":/achieve/achieve_1.png");
    if(a)achieve2.load(":/achieve/achieve_2_2.png");
    else achieve2.load(":/achieve/achieve_2.png");
    if(a)achieve3.load(":/achieve/achieve_3_2.png");
    else achieve3.load(":/achieve/achieve_3.png");
    if(a)achieve4.load(":/achieve/achieve_4_2.png");
    else achieve4.load(":/achieve/achieve_4.png");
    if(a)achieve5.load(":/achieve/achieve_5_2.png");
    else achieve5.load(":/achieve/achieve_5.png");
    if(a)achieve6.load(":/achieve/achieve_6_2.png");
    else achieve6.load(":/achieve/achieve_6.png");
    if(a)achieve7.load(":/achieve/achieve_7_2.png");
    else achieve7.load(":/achieve/achieve_7.png");
    if(a)achieve8.load(":/achieve/achieve_8_2.png");
    else achieve8.load(":/achieve/achieve_8.png");
    if(a)achieve9.load(":/achieve/achieve_9_2.png");
    else achieve9.load(":/achieve/achieve_9.png");
    if(a)achieve10.load(":/achieve/achieve_10_2.png");
    else achieve10.load(":/achieve/achieve_10.png");
    if(a)achieve11.load(":/achieve/achieve_11_2.png");
    else achieve11.load(":/achieve/achieve_11.png");
    if(a)achieve12.load(":/achieve/achieve_12_2.png");
    else achieve12.load(":/achieve/achieve_12.png");
    if(a)achieve13.load(":/achieve/achieve_13_2.png");
    else achieve13.load(":/achieve/achieve_13.png");
    if(a)achieve14.load(":/achieve/achieve_14_2.png");
    else achieve14.load(":/achieve/achieve_14.png");
    if(a)achieve15.load(":/achieve/achieve_15_2.png");
    else achieve15.load(":/achieve/achieve_15.png");
    if(a)achieve16.load(":/achieve/achieve_16_2.png");
    else achieve16.load(":/achieve/achieve_16.png");
    if(a)achieve17.load(":/achieve/achieve_17_2.png");
    else achieve17.load(":/achieve/achieve_17.png");
    if(a)achieve18.load(":/achieve/achieve_18_2.png");
    else achieve18.load(":/achieve/achieve_18.png");
    if(a)achieve19.load(":/achieve/achieve_19_2.png");
    else achieve19.load(":/achieve/achieve_19.png");
    if(a)achieve20.load(":/achieve/achieve_20_2.png");
    else achieve20.load(":/achieve/achieve_20.png");
    if(a)achieve21.load(":/achieve/achieve_21_2.png");
    else achieve21.load(":/achieve/achieve_21.png");
    if(a)achieve22.load(":/achieve/achieve_22_2.png");
    else achieve22.load(":/achieve/achieve_22.png");
    if(a)achieve23.load(":/achieve/achieve_23_2.png");
    else achieve23.load(":/achieve/achieve_23.png");

}

void Achieve::onBackClicked() {
	close();
}

Achieve::~Achieve() {
	delete ui;
}
