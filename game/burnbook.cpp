#include "burnbook.h"
#include "ui_burnbook.h"

BurnBook::BurnBook(QWidget *parent) :
	QGraphicsView(parent),
	ui(new Ui::BurnBook) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	setDragMode(QGraphicsView::NoDrag);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setBackgroundBrush(QPixmap(":/game/SunSmellCollect/back.png"));
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, 960, 720);
	setScene(scene);

	loadRes();
}

void BurnBook::loadRes() {
	fireBurnBook = new FireBurnBook(700, 500);
	scene->addItem(fireBurnBook);

	BookToBurn *book = new BookToBurn(30, 200);
	book->bindFire(fireBurnBook);
	scene->addItem(book);
	
}

BurnBook::~BurnBook()
{
    delete ui;
}
