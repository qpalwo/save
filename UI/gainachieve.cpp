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
	}
	else {

	}
}

GainAchieve::GainAchieve(int id, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::GainAchieve) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	this->m_achieve = id;
	m_isWin = true;
	loadRes();
	move(280, 300);
}

void GainAchieve::loadRes() {
	if (m_isWin) {
		back.load(":/achieve/acquire.png");
		QString s = ":/achieve/achieve_" + QString::number(this->m_achieve, 10) + "_2.png";
		achieve.load(s);
		confirm = new OpenPageButton(this, "/achieve/", "confirm");
		connect(confirm, SIGNAL(clicked()), this, SLOT(onConfirmClicked()));
		confirm->setGeometry(130, 90, 100, 26);
		confirm->show();
	}
	else {

	}
}

void GainAchieve::paintEvent(QPaintEvent * e) {
	QPainter painter(this);
	if (m_isWin) {
		painter.drawPixmap(0, 0, back);
		painter.drawPixmap(195, 32, achieve);
	}
}

void GainAchieve::onConfirmClicked() {
	close();
	deleteLater();
}

GainAchieve::~GainAchieve() {
	delete ui;
	delete confirm;
}
