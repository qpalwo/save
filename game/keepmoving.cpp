#include "keepmoving.h"
#include "ui_keepmoving.h"

KeepMoving::KeepMoving(QWidget *parent) :
	QGraphicsView(parent),
	ui(new Ui::KeepMoving) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	setDragMode(QGraphicsView::NoDrag);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setBackgroundBrush(QPixmap(":/forest/scene/forest_1.png"));
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, 960, 720);
	setScene(scene);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

	loadRes();
}

void KeepMoving::loadRes() {
	playerInWind = new PlayerInWind();
	scene->addItem(playerInWind);
	machineSendTimer = new QTimer(this);
	lighteSendTimer = new QTimer(this);
	connect(machineSendTimer, SIGNAL(timeout()), this, SLOT(sendMachine()));
	connect(lighteSendTimer, SIGNAL(timeout()), this, SLOT(sendLight()));
	machineSendTimer->start(500);
	lighteSendTimer->start(500);
}

void KeepMoving::sendMachine() {
	QString path;
	int m = qrand() % 3;
	if (m == 0) {
		path = ":/game/SunSmellCollect/machine.png";
	}
	else if(m == 1){
		path = ":/game/SunSmellCollect/machine2.png";
	}
	else if (m == 2) {
		path = ":/game/SunSmellCollect/machine3.png";
	}
	else {
		path = ":/game/SunSmellCollect/machine.png";
	}
	Tornado *tornado = new Tornado(qrand() % 860, path);
	tornado->bindPlayer(playerInWind);
	scene->addItem(tornado);
	connect(this, SIGNAL(finishGame()), tornado, SLOT(finishGame()));
	connect(tornado, SIGNAL(collided()), this, SLOT(minusMark()));
}

void KeepMoving::sendLight() {
	Tornado *tornado = new Tornado(qrand() % 860, QString(":/game/SunSmellCollect/light.png"));
	tornado->bindPlayer(playerInWind);
	scene->addItem(tornado);
	connect(this, SIGNAL(finishGame()), tornado, SLOT(finishGame()));
	connect(tornado, SIGNAL(collided()), this, SLOT(addMark()));
}

void KeepMoving::addMark() {
	playerInWind->moveBy(0, 10);
}

void KeepMoving::minusMark() {
	playerInWind->moveBy(0, -10);
}

KeepMoving::~KeepMoving() {
	delete ui;
}
