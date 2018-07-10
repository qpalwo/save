#include "achieve.h"
#include "ui_achieve.h"

Achieve::Achieve(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Achieve) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	back.load(":/achieve/back.png");
	backButton = new OpenPageButton(this, "/menuZ/menu/", "set_back_ruins");
	backButton->setGeometry(830, 570, 70, 70);
	connect(backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));
}



void Achieve::paintEvent(QPaintEvent *e) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, back);
}

void Achieve::onBackClicked() {
	close();
}

Achieve::~Achieve() {
	delete ui;
}
