#include "saveandload.h"
#include "ui_saveandload.h"

SaveAndLoad::SaveAndLoad(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SaveAndLoad) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	back.load(":/back/background.png");
	backButton = new OpenPageButton(this, "/menuZ/menu/", "set_back_forest");
	backButton->setGeometry(830, 570, 70, 70);
	connect(backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));
	initGameWorldData();
	initSaveAndButton();
}

void SaveAndLoad::paintEvent(QPaintEvent * e) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, 960, 720, back);
	int x = 210, y = 108, dx = 328, dy = 153;
	painter.drawPixmap(x, y, 112, 84, pix1);
	painter.drawPixmap(x, y + dy, 112, 84, pix3);
	painter.drawPixmap(x, y + 2 * dy, 112, 84, pix5);
	painter.drawPixmap(x + dx, y, 112, 84, pix2);
	painter.drawPixmap(x + dx, y + dy, 112, 84, pix4);
	painter.drawPixmap(x + dx, y + 2 * dy, 112, 84, pix6);
}

void SaveAndLoad::onBackClicked() {
	close();
	deleteLater();
}

void SaveAndLoad::initGameWorldData() {
	shoot = GameWorld::getInstance()->getAllShoot();
	for (int i = 0; i < 6; i++) {
		if ((shoot + i)->length() > 1) {
			isSave[i] = true;
		}
	}
}

void SaveAndLoad::initSaveAndButton() {
	if (!isSave[0]) {
		button1 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button1 = new OpenPageButton(this, "/button/", "read");
		pix1.load(*shoot);
	}
	if (!isSave[1]) {
		button2 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button2 = new OpenPageButton(this, "/button/", "read");
		pix2.load(*(shoot + 1));
	}
	if (!isSave[2]) {
		button3 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button3 = new OpenPageButton(this, "/button/", "read");
		pix3.load(*(shoot + 2));
	}
	if (!isSave[3]) {
		button4 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button4 = new OpenPageButton(this, "/button/", "read");
		pix4.load(*(shoot + 3));
	}
	if (!isSave[4]) {
		button5 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button5 = new OpenPageButton(this, "/button/", "read");
		pix5.load(*(shoot + 4));
	}
	if (!isSave[5]) {
		button6 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button6 = new OpenPageButton(this, "/button/", "read");
		pix6.load(*(shoot + 5));
	}	
	int x = 363, y = 170, dx = 335, dy = 153;
	button1->setGeometry(x, y, 80, 26);
	button3->setGeometry(x, y + dy, 80, 26);
	button5->setGeometry(x, y + 2 * dy, 80, 26);
	button2->setGeometry(x + dx, y, 80, 26);
	button4->setGeometry(x + dx, y + dy, 80, 26);
	button6->setGeometry(x + dx, y + 2 * dy, 80, 26);
	connect(button1, SIGNAL(clicked()), this, SLOT(onButton1Clicked()));
	connect(button2, SIGNAL(clicked()), this, SLOT(onButton2Clicked()));
	connect(button3, SIGNAL(clicked()), this, SLOT(onButton3Clicked()));
	connect(button4, SIGNAL(clicked()), this, SLOT(onButton4Clicked()));
	connect(button5, SIGNAL(clicked()), this, SLOT(onButton5Clicked()));
	connect(button6, SIGNAL(clicked()), this, SLOT(onButton6Clicked()));
}

void SaveAndLoad::onButton1Clicked() {
	if (isSave[0]) {
		GameWorld::getInstance()->loadPlayer(0);
	}
}

void SaveAndLoad::onButton2Clicked() {
	if (isSave[1]) {
		GameWorld::getInstance()->loadPlayer(1);
	}
}

void SaveAndLoad::onButton3Clicked() {
	if (isSave[2]) {
		GameWorld::getInstance()->loadPlayer(2);
	}
}

void SaveAndLoad::onButton4Clicked() {
	if (isSave[3]) {
		GameWorld::getInstance()->loadPlayer(3);
	}
}

void SaveAndLoad::onButton5Clicked() {
	if (isSave[4]) {
		GameWorld::getInstance()->loadPlayer(4);
	}
}

void SaveAndLoad::onButton6Clicked() {
	if (isSave[5]) {
		GameWorld::getInstance()->loadPlayer(5);
	}
}

SaveAndLoad::~SaveAndLoad() {
	delete ui;
	delete backButton;
	delete button1;
	delete button2;
	delete button3;
	delete button4;
	delete button5;
	delete button6;
}
