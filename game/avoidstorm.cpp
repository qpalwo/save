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
	stausDY = 40;
	staus = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/tornado.png"));
	staus->moveBy(stausX, stausY);
	scene->addItem(staus);
	text = new QGraphicsSimpleTextItem(QString::number(leftTime, 10), staus);
	int x = 108;
	int y = 33;
	text->moveBy(x, y);
	QFont font;
	font.setBold(true);
	font.setPixelSize(20);
	text->setFont(font);
	text->setBrush(QBrush(QColor(255, 255, 255)));
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
		text->setText(QString::number(leftTime, 10));
	}
	else {
		emit finishGame();
	}
}

void AvoidStorm::reFreshBack() {
	setBackgroundBrush(back->currentImage());
}

void AvoidStorm::endGame() {
	playerInWind->moveBy(0, 10);
}

void AvoidStorm::determineHard() {
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
}
