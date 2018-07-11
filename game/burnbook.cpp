#include "burnbook.h"
#include "ui_burnbook.h"

BurnBook::BurnBook(int hard, QWidget *parent) :
	QGraphicsView(parent),
	ui(new Ui::BurnBook) {
	ui->setupUi(this);
	gameHard = hard;
	setWindowFlag(Qt::FramelessWindowHint);
	setDragMode(QGraphicsView::NoDrag);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	back = new QMovie(":/game/SunSmellCollect/book.gif");
	//back = new QMovie(":/game/SunSmellCollect/tornado.gif");
	reFreshBackTimer = new QTimer(this);
	connect(reFreshBackTimer, SIGNAL(timeout()), this, SLOT(reFreshBack()));
	back->start();
	reFreshBackTimer->start(150);
	determineHard(); // 决定游戏难度
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, 960, 720);
	setScene(scene);
	scene->setFocus();
	grabKeyboard();
	loadRes();
}

void BurnBook::loadRes() {
	fireBurnBook = new FireBurnBook(700, 500, fireSize);
	scene->addItem(fireBurnBook);
	stausDX = 30;
	stausX = 700;
	stausY = 60;
	stausDY = 40;
	staus1 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/book_1.png"));
	staus2 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/book_2.png"));
	staus3 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/book_3.png"));
	staus4 = new QGraphicsPixmapItem(QPixmap(":/game/SunSmellCollect/book_4.png"));
	staus1->moveBy(stausX, stausY);
	staus2->moveBy(stausX, stausY + stausDY);
	staus3->moveBy(stausX, stausY + 2 * stausDY);
	staus4->moveBy(stausX, stausY + 3 * stausDY);
	scene->addItem(staus1);
	scene->addItem(staus2);
	scene->addItem(staus3);
	scene->addItem(staus4);

	text1 = new QGraphicsSimpleTextItem(QString::number(nowNeed, 10), staus1);
	text2 = new QGraphicsSimpleTextItem(QString::number(allBook - leftBook, 10), staus2);
	text3 = new QGraphicsSimpleTextItem(QString::number(burnedBook, 10), staus3);
	text4 = new QGraphicsSimpleTextItem(QString::number(leftBook, 10), staus4);

	int x = 118;
	int y = 10;
	text1->moveBy(x, y);
	text2->moveBy(x, y);
	text3->moveBy(x, y);
	text4->moveBy(x, y);

	QFont font;
	font.setBold(true);
	font.setPixelSize(20);

	text1->setFont(font);
	text2->setFont(font);
	text3->setFont(font);
	text4->setFont(font);

	text1->setBrush(QBrush(QColor(255, 255, 255)));
	text2->setBrush(QBrush(QColor(255, 255, 255)));
	text3->setBrush(QBrush(QColor(255, 255, 255)));
	text4->setBrush(QBrush(QColor(255, 255, 255)));

	addBook();
}

void BurnBook::reFreshText() {
	if(nowNeed >= 0)
		text1->setText(QString::number(nowNeed, 10));
	text2->setText(QString::number(allBook - leftBook, 10));
	text3->setText(QString::number(burnedBook, 10));
	text4->setText(QString::number(leftBook, 10));

}

void BurnBook::addBook() {
	reFreshText();
	if (leftBook > 0 && m_book == NULL) {
		//leftBook = 0;
		m_book = new BookToBurn(30, 200);
		m_book->bindFire(fireBurnBook);
		scene->addItem(m_book);
		scene->setFocusItem(m_book);
		m_book->grabKeyboard();
		connect(m_book, SIGNAL(burned()), this, SLOT(onBurned()));
		connect(m_book, SIGNAL(unBurned()), this, SLOT(onUnBurned()));
	}
	else if (leftBook <= 0) {
		if (nowNeed <= 0) {
			GainAchieve *achieve = new GainAchieve(true, 5, this);
			achieve->show();
		}
		else {
			GainAchieve *achieve = new GainAchieve(false, 3, this);
			achieve->show();
		}
		emit finishGame();
	}
}

void BurnBook::determineHard() {
	leftBook = allBook = 1;
	burnedBook = 0;
	switch (gameHard) {
	case 1:
		fireSize = 150;
		nowNeed = 5;
		break;
	case 2:
		fireSize = 130;
		nowNeed = 6;
		break;
	case 3:
	default:
		fireSize = 110;
		nowNeed = 7;
		break;
	}
}

void BurnBook::onBurned() {
	m_book = NULL;
	leftBook--;
	burnedBook++;
	nowNeed--;
	addBook();
}

void BurnBook::onUnBurned() {
	m_book = NULL;
	leftBook--;
	addBook();
}

void BurnBook::reFreshBack() {
	setBackgroundBrush(back->currentImage());
}


BurnBook::~BurnBook()
{
    delete ui;
	delete scene;
	delete fireBurnBook;
	delete m_book;
	delete back;
	delete reFreshBackTimer;
	delete staus1;
	delete staus2;
	delete staus3;
	delete staus4;

	delete text1;
	delete text2;
	delete text3;
	delete text4;
}
