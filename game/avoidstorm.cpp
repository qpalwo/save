#include "avoidstorm.h"
#include "ui_avoidstorm.h"

AvoidStorm::AvoidStorm(int hard, QWidget *parent) :
	QGraphicsView(parent),
	ui(new Ui::AvoidStorm) {
	ui->setupUi(this);
	gameHard = hard;
	setWindowFlag(Qt::FramelessWindowHint);
	setDragMode(QGraphicsView::NoDrag);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	determineHard();
	back = new QMovie(":/game/SunSmellCollect/tornado.gif");
	reFreshBackTimer = new QTimer(this);
	back->start();
	connect(reFreshBackTimer, SIGNAL(timeout()), this, SLOT(reFreshBack()));
	reFreshBackTimer->start(150);
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, 960, 720);
	setScene(scene);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	scene->setFocus();
	grabKeyboard();

	loadRes();
}

void AvoidStorm::loadRes() {
	playerInWind = new PlayerInWind(playerSpeed);
	scene->addItem(playerInWind);
	scene->setFocusItem(playerInWind);
	playerInWind->grabKeyboard();
	sendTimer = new QTimer(this);
	connect(sendTimer, SIGNAL(timeout()), this, SLOT(sendTornado()));
	sendTimer->start(lunchSpeed);

	countDownTimer = new QTimer(this);
	connect(countDownTimer, SIGNAL(timeout()), this, SLOT(countDown()));
	countDownTimer->start(1000);

	stausDX = 30;
	stausX = 700;
	stausY = 60;
	stausDY = 50;
	staus1 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/tornado.png"));
	staus2 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/tornado_2.png"));
	staus3 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/tornado_3.png"));
	teaching = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/tornado_illustrate.png"));
	staus1->moveBy(stausX, stausY);
	staus2->moveBy(stausX, stausY + stausDY);
	staus3->moveBy(stausX, stausY + stausDY * 2);
	teaching->moveBy(stausX + 10, stausY + 6 * stausDY);
	
	scene->addItem(staus1);
	scene->addItem(staus2);
	scene->addItem(staus3);
	scene->addItem(teaching);

	text1 = new QGraphicsSimpleTextItem(QString::number(leftTime, 10), staus1);
	text2 = new QGraphicsSimpleTextItem(QString::number(nowShoot, 10), staus2);
	text3 = new QGraphicsSimpleTextItem(QString::number(leftShoot, 10), staus3);
	int x = 108;
	int y = 33;
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

void AvoidStorm::sendTornado() {
	Tornado *tornado = new Tornado(qrand() % 860, tornadoVy, QString(":/game/SunSmellCollect/wind.png"));
	tornado->bindPlayer(playerInWind);
	scene->addItem(tornado);
	connect(this, SIGNAL(finishGame()), tornado, SLOT(finishGame()));
	connect(tornado, SIGNAL(collided()), this, SLOT(endGame()));
}

void AvoidStorm::countDown() {
	if (leftTime > 0) {
		leftTime--;
		text1->setText(QString::number(leftTime, 10));
	}
	else {
		sendTimer->stop();
		if (leftShoot > 0) {
			GainAchieve *achieve = new GainAchieve(true, 3, this);
			connect(achieve, SIGNAL(achieveClosed()), this, SLOT(closeMe()));
			achieve->show();
		}
		else {
			GainAchieve *achieve = new GainAchieve(false, 1, this);
			connect(achieve, SIGNAL(achieveClosed()), this, SLOT(closeMe()));
			achieve->show();
		}
		emit finishGame();
	}
}

void AvoidStorm::reFreshBack() {
	setBackgroundBrush(back->currentImage());
}

void AvoidStorm::endGame() {
	nowShoot++;
	leftShoot--;
	if (leftShoot > 0) {
		text2->setText(QString::number(nowShoot, 10));
		text3->setText(QString::number(leftShoot, 10));
	}
	else {
		GainAchieve *achieve = new GainAchieve(false, 1, this);
		connect(achieve, SIGNAL(achieveClosed()), this, SLOT(closeMe()));
		achieve->show();
		emit finishGame();
	}
}

void AvoidStorm::closeMe() {
	GameWorld::getInstance()->closeAvoidStorm();
}

void AvoidStorm::determineHard() {
	nowShoot = 0;
	leftShoot = 10;
	switch (gameHard) {
	case 1:
		playerSpeed = 16;
		lunchSpeed = 800;
		tornadoVy = 5;
		leftTime = 30;
		break;
	case 2:
		playerSpeed = 13;
		lunchSpeed = 500;
		tornadoVy = 7;
		leftTime = 45;
		break;
	case 3:
	default:
		playerSpeed = 10;
		lunchSpeed = 300;
		tornadoVy = 9;
		leftTime = 60;
		break;
	}
}

AvoidStorm::~AvoidStorm() {
	delete ui;
	scene->deleteLater();
	playerInWind->deleteLater();
	back->deleteLater();
	sendTimer->deleteLater();
	reFreshBackTimer->deleteLater();
	countDownTimer->deleteLater();
}
