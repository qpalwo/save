#include "achieve.h"
#include "ui_achieve.h"

Achieve::Achieve(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Achieve) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
}

Achieve::~Achieve() {
	delete ui;
}
