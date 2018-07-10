#include "keepmoving.h"
#include "ui_keepmoving.h"

KeepMoving::KeepMoving(int hard, QWidget *parent) :
	QGraphicsView(parent),
	ui(new Ui::KeepMoving) {
	ui->setupUi(this);
	gameHard = hard;
	setWindowFlag(Qt::FramelessWindowHint);
	setDragMode(QGraphicsView::NoDrag);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	backMovie = new QMovie(":/game/SunSmellCollect/machine.gif");
	reFreshBackTimer = new QTimer(this);
	connect(reFreshBackTimer, SIGNAL(timeout()), this, SLOT(reFreshBack()));
	backMovie->start();
	reFreshBackTimer->start(150);

	determineHard();
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, 960, 720);
	setScene(scene);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	scene->setFocus();
	grabKeyboard();

	loadRes();
}

void KeepMoving::loadRes() {
	playerInWind = new PlayerInWind(playerSpeed);
	scene->addItem(playerInWind);
	scene->setFocusItem(playerInWind);
	playerInWind->grabKeyboard();
	machineSendTimer = new QTimer(this);
	lighteSendTimer = new QTimer(this);
	connect(machineSendTimer, SIGNAL(timeout()), this, SLOT(sendMachine()));
	connect(lighteSendTimer, SIGNAL(timeout()), this, SLOT(sendLight()));
	machineSendTimer->start(machineLunchSpeed);
	lighteSendTimer->start(lightLunchSpeed);
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
	Tornado *tornado = new Tornado(qrand() % 860, machineSpeed, path);
	tornado->bindPlayer(playerInWind);
	scene->addItem(tornado);
	connect(this, SIGNAL(finishGame()), tornado, SLOT(finishGame()));
	connect(tornado, SIGNAL(collided()), this, SLOT(minusMark()));
}

void KeepMoving::sendLight() {
	Tornado *tornado = new Tornado(qrand() % 860, lightSpeed, QString(":/game/SunSmellCollect/light.png"));
	tornado->bindPlayer(playerInWind);
	scene->addItem(tornado);
	connect(this, SIGNAL(finishGame()), tornado, SLOT(finishGame()));
	connect(tornado, SIGNAL(collided()), this, SLOT(addMark()));
}

void KeepMoving::determineHard() {
	switch (gameHard) {
	case 1:
		playerSpeed = 16;
		machineLunchSpeed = 800;
		lightLunchSpeed = 300;
		lightSpeed = 5;
		machineSpeed = 5;

		break;
	case 2:
		playerSpeed = 13;
		machineLunchSpeed = 500;
		lightLunchSpeed = 500;
		lightSpeed = 4;
		machineSpeed = 6;
		break;
	case 3:
	default:
		playerSpeed = 10;
		machineLunchSpeed = 300;
		lightLunchSpeed = 800;
		lightSpeed = 3;
		machineSpeed = 7;
		break;
	}
}

void KeepMoving::reFreshBack() {
	setBackgroundBrush(backMovie->currentImage());
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
