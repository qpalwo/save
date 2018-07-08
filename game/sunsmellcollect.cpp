#include "sunsmellcollect.h"
#include "ui_sunsmellcollect.h"

SunSmellCollect::SunSmellCollect(QWidget *parent) :
	QGraphicsView(parent),
    ui(new Ui::SunSmellCollect)
{
    ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	setDragMode(QGraphicsView::NoDrag);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setBackgroundBrush(QPixmap(":/forest/scene/forest_1.png"));
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, 960, 720);
	setScene(scene);

	loadRes();
}

void SunSmellCollect::loadRes() {
	collecter = new CollecterOfGame();
	scene->addItem(collecter);
	sendTimer = new QTimer(this);
	connect(sendTimer, SIGNAL(timeout()), this, SLOT(sendSmell()));
	sendTimer->start(500);
}

void SunSmellCollect::sendSmell() {
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
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

void SunSmellCollect::focusInEvent(QFocusEvent *focusEvent) {
	if (collecter != NULL) {
		collecter->setFocus();
		bool temp = collecter->hasFocus();
	}
}

void SunSmellCollect::addMark() {
	collecter->moveBy(0, 10);
}


SunSmellCollect::~SunSmellCollect()
{
    delete ui;
	delete scene;
	delete collecter;
}
