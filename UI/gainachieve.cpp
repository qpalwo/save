#include "gainachieve.h"
#include "ui_gainachieve.h"

GainAchieve::GainAchieve(int id, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::GainAchieve) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	loadRes();
	m_achieve = id;
}

void GainAchieve::loadRes() {
	back.load(":/achieve/acquire.png");
	QString s = ":/achieve/achieve_" + QString::number(m_achieve, 10) + "_2.png";
	achieve.load(s);
	//:/achieve/confirm_1.png
	confirm = new OpenPageButton(this, "/achieve/", "confirm");
	connect(confirm, SIGNAL(clicked()), this, SLOT(onConfirmClicked));
	confirm->setGeometry(100, 100, 80, 26);
}

void GainAchieve::paintEvent(QPaintEvent * e) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, back);
	painter.drawPixmap(50, 30, achieve);
}

void GainAchieve::onConfirmClicked() {
	close();
}

GainAchieve::~GainAchieve() {
	delete ui;
	delete confirm;
}
