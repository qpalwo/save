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
	SmellOfGame *smell = new SmellOfGame(300, 200, -20, -10);
	SmellOfGame *smell1 = new SmellOfGame(130, 200, -20, -10);
	scene->addItem(smell);
	scene->addItem(smell1);
	bool is = smell->collidesWithItem(smell1);
}


SunSmellCollect::~SunSmellCollect()
{
    delete ui;
	delete scene;
}
