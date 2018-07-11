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
	setBackgroundBrush(QPixmap(":/game/SunSmellCollect/back.png"));
	determineHard();
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
}

void AvoidStorm::sendTornado() {
	Tornado *tornado = new Tornado(qrand() % 860, tornadoVy, QString(":/game/SunSmellCollect/wind.png"));
	tornado->bindPlayer(playerInWind);
	scene->addItem(tornado);
	connect(this, SIGNAL(finishGame()), tornado, SLOT(finishGame()));
	connect(tornado, SIGNAL(collided()), this, SLOT(endGame()));
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
		break;
	case 2:
		playerSpeed = 13;
		lunchSpeed = 500;
		tornadoVy = 7;
		break;
	case 3:
	default:
		playerSpeed = 10;
		lunchSpeed = 300;
		tornadoVy = 9;
		break;
	}
}

AvoidStorm::~AvoidStorm() {
	delete ui;
}
