#include "achieve.h"
#include "ui_achieve.h"

Achieve::Achieve(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Achieve) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	back.load(":/achieve/back.png");
}


void Achieve::paintEvent(QPaintEvent *e) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, 960, 720, back);
}

Achieve::~Achieve() {
	delete ui;
}
