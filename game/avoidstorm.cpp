#include "avoidstorm.h"
#include "ui_avoidstorm.h"

AvoidStorm::AvoidStorm(QWidget *parent) :
	QGraphicsView(parent),
	ui(new Ui::AvoidStorm) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	setDragMode(QGraphicsView::NoDrag);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setBackgroundBrush(QPixmap(":/game/SunSmellCollect/back.png"));
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, 960, 720);
	setScene(scene);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

	loadRes();
}

void AvoidStorm::loadRes() {
	playerInWind = new PlayerInWind();
	scene->addItem(playerInWind);
	sendTimer = new QTimer(this);
	connect(sendTimer, SIGNAL(timeout()), this, SLOT(sendTornado()));
	sendTimer->start(500);
}

void AvoidStorm::sendTornado() {
	Tornado *tornado = new Tornado(qrand() % 860, QString(":/game/SunSmellCollect/smell.png"));
	tornado->bindPlayer(playerInWind);
	scene->addItem(tornado);
	connect(this, SIGNAL(finishGame()), tornado, SLOT(finishGame()));
	connect(tornado, SIGNAL(collided()), this, SLOT(endGame()));
}

void AvoidStorm::endGame() {
	playerInWind->moveBy(0, 10);
}

AvoidStorm::~AvoidStorm() {
	delete ui;
}
