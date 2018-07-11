#include "gainachieve.h"
#include "ui_gainachieve.h"

GainAchieve::GainAchieve(bool isWin, int id, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::GainAchieve) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	m_isWin = isWin;
	if (isWin) {
		this->m_achieve = id;
		loadRes();
		move(280, 300);
		GameWorld::getInstance()->addAchieve(m_achieve);
	}
	else {
		resize(QSize(340, 141));
		m_achieve = id;
		loadRes();
		move(280, 300);
	}
}

GainAchieve::GainAchieve(int id, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::GainAchieve) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	this->m_achieve = id;
	GameWorld::getInstance()->addAchieve(m_achieve);
	m_isWin = true;
	loadRes();
	move(280, 300);
}

void GainAchieve::loadRes() {
	confirm = new OpenPageButton(this, "/achieve/", "confirm");
	connect(confirm, SIGNAL(clicked()), this, SLOT(onConfirmClicked()));
	if (m_isWin) {
		back.load(":/achieve/acquire.png");
		QString s = ":/achieve/achieve_" + QString::number(this->m_achieve, 10) + "_2.png";
		achieve.load(s);
		confirm->setGeometry(130, 90, 100, 26);
	}
	else {
		switch (m_achieve) {
		case 1:
			back.load(":/game/SunSmellCollect/tornado_fail.png");
			break;
		case 2:
			back.load(":/game/SunSmellCollect/sunshine_fail.png");
			break;
		case 3:
			back.load(":/game/SunSmellCollect/machine_fail.png");
			break;
		case 4:
		default:
			back.load(":/game/SunSmellCollect/book_fail.png");
			break;
		}
		confirm->setGeometry(130, 100, 100, 26);
	}
	confirm->show();
}

void GainAchieve::paintEvent(QPaintEvent * e) {
	QPainter painter(this);
	if (m_isWin) {
		painter.drawPixmap(0, 0, back);
		painter.drawPixmap(195, 32, achieve);
	}
	else {
		painter.drawPixmap(0, 0, back);
	}
}

void GainAchieve::onConfirmClicked() {
	emit achieveClosed();
	close();
	deleteLater();
}

GainAchieve::~GainAchieve() {
	delete ui;
	delete confirm;
}
