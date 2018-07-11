#include "sunsmellcollect.h"
#include "ui_sunsmellcollect.h"

SunSmellCollect::SunSmellCollect(int hard, QWidget *parent) :
	QGraphicsView(parent),
	ui(new Ui::SunSmellCollect) {
	ui->setupUi(this);
	gameHard = hard;
	setWindowFlag(Qt::FramelessWindowHint);
	setDragMode(QGraphicsView::NoDrag);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	back = new QMovie(":/game/SunSmellCollect/sunshine.gif");
	reFreshBackTimer = new QTimer(this);
	connect(reFreshBackTimer, SIGNAL(timeout()), this, SLOT(reFreshBack()));
	back->start();
	reFreshBackTimer->start(150);

	countDownTimer = new QTimer(this);
	connect(countDownTimer, SIGNAL(timeout()), this, SLOT(countDown()));
	countDownTimer->start(1000);

	determineHard();
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, 960, 720);
	setScene(scene);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	scene->setFocus();
	grabKeyboard();

	loadRes();
}

void SunSmellCollect::loadRes() {
	collecter = new CollecterOfGame(collecterSpeed);
	scene->addItem(collecter);
	scene->setFocusItem(collecter);
	collecter->grabKeyboard();
	sendTimer = new QTimer(this);
	connect(sendTimer, SIGNAL(timeout()), this, SLOT(sendSmell()));
	sendTimer->start(lunchSpeed);

	stausDX = 30;
	stausX = 700;
	stausY = 60;
	stausDY = 50;
	staus1 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/sunshine_1.png"));
	staus2 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/sunshine_2.png"));
	staus3 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/sunshine_3.png"));
	teaching = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/sunshine_illustrate.png"));

	staus1->moveBy(stausX, stausY);
	staus2->moveBy(stausX, stausY + stausDY);
	staus3->moveBy(stausX, stausY + 2 * stausDY);
	teaching->moveBy(stausX + 25, stausY + 5 * stausDY);

	scene->addItem(staus1);
	scene->addItem(staus2);
	scene->addItem(staus3);
	scene->addItem(teaching);

	text1 = new QGraphicsSimpleTextItem(QString::number(leftTime, 10), staus1);
	text2 = new QGraphicsSimpleTextItem(QString::number(nowMark, 10), staus2);
	text3 = new QGraphicsSimpleTextItem(QString::number(nowNeed, 10), staus3);

	int x = 138;
	int y = 25;
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

void SunSmellCollect::sendSmell() {
	bool type1 = qrand() % 2;
	bool type2 = qrand() % 2;
	int vx, vy;
	if (type1) {
		vx = qrand() % 20;
	}
	else {
		vx = -(qrand() % 20);
	}

	if (type2) {
		vy = qrand() % 10;
	}
	else {
		vy = -(qrand() % 10);
	}

	SmellOfGame *smell = new SmellOfGame((qrand() % (960 - 400)) + 200, qrand() % 150, vx, vy);
	smell->bindCollecter(collecter);
	scene->addItem(smell);
	connect(this, SIGNAL(finishGame()), smell, SLOT(finishGame()));
	connect(smell, SIGNAL(collected()), this, SLOT(addMark()));

}

void SunSmellCollect::determineHard() {
	switch (gameHard) {
	case 1:
		lunchSpeed = 300;
		collecterSpeed = 10;
		leftTime = 30;
		nowMark = 0;
		nowNeed = 15;
		break;
	case 2:
		lunchSpeed = 500;
		collecterSpeed = 13;
		leftTime = 45;
		nowMark = 0;
		nowNeed = 30;
		break;
	case 3:
	default:
		lunchSpeed = 700;
		collecterSpeed = 16;
		leftTime = 60;
		nowMark = 0;
		nowNeed = 60;
		break;
	}
}

void SunSmellCollect::countDown() {
	if (leftTime > 0) {
		leftTime--;
		text1->setText(QString::number(leftTime, 10));
		text2->setText(QString::number(nowMark, 10));
		text3->setText(QString::number(nowNeed, 10));
	}
	else {
		if (nowNeed <= 0) {
			GainAchieve *achieve = new GainAchieve(true, 15, this);
			connect(achieve, SIGNAL(achieveClosed()), this, SLOT(closeMe()));
			achieve->show();
		}
		else {
			GainAchieve *achieve = new GainAchieve(false, 2, this);
			connect(achieve, SIGNAL(achieveClosed()), this, SLOT(closeMe()));
			achieve->show();
		}
		emit finishGame();
	}
}

void SunSmellCollect::reFreshBack() {
	setBackgroundBrush(back->currentPixmap());
}

void SunSmellCollect::focusInEvent(QFocusEvent *focusEvent) {
	if (collecter != NULL) {
		collecter->setFocus();
		bool temp = collecter->hasFocus();
	}
}

void SunSmellCollect::addMark() {
	nowMark += 10;
	if(nowNeed > 0)
		nowNeed -= 10;
	text2->setText(QString::number(nowMark, 10));
	text3->setText(QString::number(nowNeed, 10));
	if (nowNeed <= 0) {
		GainAchieve *achieve = new GainAchieve(true, 15, this);
		connect(achieve, SIGNAL(achieveClosed()), this, SLOT(closeMe()));
		achieve->show();
		emit finishGame();
	}
}

void SunSmellCollect::closeMe() {
	GameWorld::getInstance()->closeCollectSmell();
}


SunSmellCollect::~SunSmellCollect() {
	delete ui;
	scene->deleteLater();
	collecter->deleteLater();
	back->deleteLater();
	sendTimer->deleteLater();
	reFreshBackTimer->deleteLater();
	countDownTimer->deleteLater();
}
