#include "ending.h"
#include "ui_ending.h"
#include "UI/UiManager.h"

ending::ending(int flag, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ending) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	switch (flag) {
	case 1:
		backGround.load(":/ending/1.png");
		break;
	case 2:
		backGround.load(":/ending/2.png");
		break;
	case 3:
	default:
		backGround.load(":/ending/3.png");
		break;
	}
	back = new OpenPageButton(this, "/menuZ/menu/", "set_back_snow");
	back->setGeometry(830, 570, 70, 70);
	connect(back, SIGNAL(clicked()), this, SLOT(onBackClicked()));
}

void ending::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.drawImage(0, 0, backGround);
}

void ending::onBackClicked() {
	UiManager::getInstance()->openMainPage();
	UiManager::getInstance()->closeEnding();
}

ending::~ending() {
	delete ui;
	back->deleteLater();
}
