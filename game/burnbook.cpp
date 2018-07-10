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
	scene->setFocus();
	grabKeyboard();
	leftBook = 3;
	loadRes();
}

void BurnBook::loadRes() {
	fireBurnBook = new FireBurnBook(700, 500);
	scene->addItem(fireBurnBook);
	addBook();
}

void BurnBook::addBook() {
	if (m_book == NULL && leftBook > 0) {
		m_book = new BookToBurn(30, 200);
		m_book->bindFire(fireBurnBook);
		scene->addItem(m_book);
		scene->setFocusItem(m_book);
		m_book->grabKeyboard();
		connect(m_book, SIGNAL(burned()), this, SLOT(onBurned()));
		connect(m_book, SIGNAL(unBurned()), this, SLOT(onUnBurned()));
		leftBook--;
	}
}


void BurnBook::onBurned() {
	m_book = NULL;
	addBook();
}

void BurnBook::onUnBurned() {
	m_book = NULL;
	addBook();
}


BurnBook::~BurnBook()
{
    delete ui;
}
