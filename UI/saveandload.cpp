#include "saveandload.h"
#include "ui_saveandload.h"

SaveAndLoad::SaveAndLoad(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SaveAndLoad) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	back.load(":/back/background.png");
	backButton = new OpenPageButton(this, "/menuZ/menu/", "set_back_forest");
	backButton->setGeometry(830, 570, 70, 70);
	connect(backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));
	initSaveAndButton();
}

void SaveAndLoad::paintEvent(QPaintEvent * e) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, 960, 720, back);
}

void SaveAndLoad::onBackClicked() {
	close();
	deleteLater();
}

void SaveAndLoad::initGameWorldData() {
	
}

void SaveAndLoad::initSaveAndButton() {
	if (!isSave[0]) {
		button1 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button1 = new OpenPageButton(this, "/button/", "read");
	}
	if (!isSave[1]) {
		button2 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button2 = new OpenPageButton(this, "/button/", "read");
	}
	if (!isSave[2]) {
		button3 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button3 = new OpenPageButton(this, "/button/", "read");
	}
	if (!isSave[3]) {
		button4 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button4 = new OpenPageButton(this, "/button/", "read");
	}
	if (!isSave[4]) {
		button5 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button5 = new OpenPageButton(this, "/button/", "read");
	}
	if (!isSave[5]) {
		button6 = new OpenPageButton(this, "/button/", "save");
	}
	else {
		button6 = new OpenPageButton(this, "/button/", "read");
	}	
	int x = 363, y = 170, dx = 335, dy = 153;
	button1->setGeometry(x, y, 80, 26);
	button3->setGeometry(x, y + dy, 80, 26);
	button5->setGeometry(x, y + 2 * dy, 80, 26);
	button2->setGeometry(x + dx, y, 80, 26);
	button4->setGeometry(x + dx, y + dy, 80, 26);
	button6->setGeometry(x + dx, y + 2 * dy, 80, 26);
}

SaveAndLoad::~SaveAndLoad() {
	delete ui;
	delete backButton;
	delete button1;
	delete button2;
	delete button3;
	delete button4;
	delete button5;
	delete button6;
}
