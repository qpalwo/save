#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	setWindowFlag(Qt::CustomizeWindowHint);
    //setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowStaysOnTopHint);
	initTimer();
	initSun();
	loadImage();
}

void MainWindow::loadImage() {
	back_mou.load(":/openRes/back_moun_s.png");
	for_mou.load(":/openRes/fro_moun_s.png");
	earth.load(":/openRes/earth_s.png");
	if (sunX != -1) {
		sun.load(":/openRes/sun_s.png");
		
	}
	else {
		moon.load(":/openRes/moon_s.png");
		backGif = new QMovie(":/openGif/background_se.gif");
	}
	
}

void MainWindow::paintEvent(QPaintEvent *e){
	QPainter painter(this);
	if (sunX != -1) {
		painter.drawImage(sunX, sunY, sun);
	}
	else {
		painter.drawImage(60, 100, moon);
	}
    painter.drawImage(0, 0, back_mou, forMouLocation, 0);
	painter.drawImage(0, 0, for_mou, forMouLocation, 0);
	painter.drawImage(0, 0, earth, forMouLocation, 0);

	if (forMouLocation + 960 > 3840) {
		painter.drawImage(3840 - forMouLocation, 0, back_mou);
		painter.drawImage(3840 - forMouLocation, 0, for_mou);
		painter.drawImage(3840 - forMouLocation, 0, earth);
    }
}

void MainWindow::moveMou() {
	if (p >= 200)
		p = 0;
	p++;
	forMouLocation = p * 19;
	update();
}

void MainWindow::initWeather() {

}

void MainWindow::initSun() {
	QTime time = QTime::currentTime();
	int hour = time.hour();
	if (hour > 6 && hour < 12) {
		sunY = 56 * (hour - 6);
		sunX = 66 * hour + 40;
	}
	else if (hour >= 12 && hour < 19) {
		sunY = 340 - 56 * (hour - 12);
		sunX = 66 * (hour - 6) + 40;
	}
	else {
		sunY = -1;
		sunX = -1;
	}
}

void MainWindow::initTimer() {
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(moveMou()));
	timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
