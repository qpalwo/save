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

	countDownTimer = new QTimer(this);
	connect(countDownTimer, SIGNAL(timeout()), this, SLOT(countDown()));
	countDownTimer->start(1000);

	stausDX = 30;
	stausX = 700;
	stausY = 60;
	stausDY = 60;
	staus1 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/machine_1.png"));
	staus2 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/machine_2.png"));
	staus3 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/machine_3.png"));
	teaching = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/machine_illustrate.png"));

	staus1->moveBy(stausX, stausY);
	staus2->moveBy(stausX, stausY + stausDY);
	staus3->moveBy(stausX, stausY + 2 * stausDY);
	teaching->moveBy(stausX + 10, stausY + 4 * stausDY);

	scene->addItem(staus1);
	scene->addItem(staus2);
	scene->addItem(staus3);
	scene->addItem(teaching);

	text1 = new QGraphicsSimpleTextItem(QString::number(nowMark, 10), staus1);
	text2 = new QGraphicsSimpleTextItem(QString::number(nowNeed, 10), staus2);
	text3 = new QGraphicsSimpleTextItem(QString::number(leftTime, 10), staus3);

	int x = 118;
	int y = 10;
	text1->moveBy(x, y);
	text2->moveBy(x, y);
	text3->moveBy(x, y);

	QFont font;
	font.setBold(true);
	font.setPixelSize(20);

	text1->setFont(font);
	text2->setFont(font);
	text3->setFont(font);

	text1->setBrush(QBrush(QColor(255, 255, 255)));
	text2->setBrush(QBrush(QColor(255, 255, 255)));
	text3->setBrush(QBrush(QColor(255, 255, 255)));
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

void KeepMoving::countDown() {
	if (leftTime > 0) {
		leftTime--;
		text1->setText(QString::number(nowMark, 10));
		text2->setText(QString::number(nowNeed, 10));
		text3->setText(QString::number(leftTime, 10));
	}
	else {
		if (nowNeed <= 0) {
			GainAchieve *achieve = new GainAchieve(true, 15, this);
			connect(achieve, SIGNAL(achieveClosed()), this, SLOT(closeMe()));
			achieve->show();
		}
		else {
			GainAchieve *achieve = new GainAchieve(false, 3, this);
			connect(achieve, SIGNAL(achieveClosed()), this, SLOT(closeMe()));
			achieve->show();
		}
		emit finishGame();
	}
}

void KeepMoving::determineHard() {
	switch (gameHard) {
	case 1:
		playerSpeed = 16;
		machineLunchSpeed = 800;
		lightLunchSpeed = 300;
		lightSpeed = 5;
		machineSpeed = 5;
		leftTime = 30;
		nowMark = 0;
		nowNeed = 100;
		break;
	case 2:
		playerSpeed = 13;
		machineLunchSpeed = 500;
		lightLunchSpeed = 500;
		lightSpeed = 4;
		machineSpeed = 6;
		leftTime = 45;
		nowMark = 0;
		nowNeed = 150;
		break;
	case 3:
	default:
		playerSpeed = 10;
		machineLunchSpeed = 300;
		lightLunchSpeed = 800;
		lightSpeed = 3;
		machineSpeed = 7;
		leftTime = 60;
		nowMark = 0;
		nowNeed = 250;
		break;
	}
}

void KeepMoving::reFreshBack() {
	setBackgroundBrush(backMovie->currentImage());
}

void KeepMoving::addMark() {
	nowMark += 10;
	nowNeed -= 10;
	if (nowNeed <= 0) {
		GainAchieve *achieve = new GainAchieve(true, 13, this);
		connect(achieve, SIGNAL(achieveClosed()), this, SLOT(closeMe()));
		achieve->show();
		emit finishGame();
	}
}

void KeepMoving::minusMark() {
	nowMark -= 10;
	nowNeed += 10;
}

void KeepMoving::closeMe() {
	GameWorld::getInstance()->closeKeepMoving();
}

KeepMoving::~KeepMoving() {
	delete ui;
	scene->deleteLater();
	playerInWind->deleteLater();
	backMovie->deleteLater();
	machineSendTimer->deleteLater();
	lighteSendTimer->deleteLater();
	reFreshBackTimer->deleteLater();
	countDownTimer->deleteLater();
}
