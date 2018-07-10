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
	addBook();
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
	reFreshText();
}

void BurnBook::reFreshText() {
	if (text1 != NULL) {
		scene->removeItem(text1);
		scene->removeItem(text2);
		scene->removeItem(text3);
		scene->removeItem(text4);
		
		/*text1->deleteLater();
		text2->deleteLater();
		text3->deleteLater();
		text4->deleteLater();*/
		delete text1;
		delete text2;
		delete text3;
		delete text4;
	}

	QFont font;
	font.setPixelSize(20);  // 像素大小
	font.setItalic(true);  // 斜体
	font.setUnderline(true);  // 下划线

	text1 = new QGraphicsSimpleTextItem(QString("temptemp"));
	text2 = new QGraphicsSimpleTextItem(QString(allBook - leftBook));
	text3 = new QGraphicsSimpleTextItem(QString(burnedBook));
	text4 = new QGraphicsSimpleTextItem(QString(leftBook));

	text1->setFont(font);
	text2->setFont(font);
	text3->setFont(font);
	text4->setFont(font);

	stausDX = 30;
	stausX = 700;
	stausY = 60;
	stausDY = 40;
	text1->moveBy(stausX + stausDX, stausY);
	text1->moveBy(stausX + stausDX, stausY + stausDY);
	text1->moveBy(stausX + stausDX, stausY + 2 * stausDY);
	text1->moveBy(stausX + stausDX, stausY + 3 * stausDY);

	text1->setBrush(QBrush(QColor(0, 160, 230)));
	text2->setBrush(QBrush(QColor(0, 160, 230)));
	text3->setBrush(QBrush(QColor(0, 160, 230)));
	text4->setBrush(QBrush(QColor(0, 160, 230)));

	scene->addItem(text1);
	//scene->addItem(text2);
	//scene->addItem(text3);
	//scene->addItem(text4);
}

void BurnBook::addBook() {
	reFreshText();
	if (leftBook > 0 && m_book == NULL) {
		m_book = new BookToBurn(30, 200);
		m_book->bindFire(fireBurnBook);
		scene->addItem(m_book);
		scene->setFocusItem(m_book);
		m_book->grabKeyboard();
		connect(m_book, SIGNAL(burned()), this, SLOT(onBurned()));
		connect(m_book, SIGNAL(unBurned()), this, SLOT(onUnBurned()));
		leftBook--;
	}
	else if (leftBook <= 0) {
		finishGame();
	}
}

void BurnBook::determineHard() {
	leftBook = allBook = 8;
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

void BurnBook::finishGame() {

}


BurnBook::~BurnBook()
{
    delete ui;
}
