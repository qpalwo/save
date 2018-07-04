#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowStaysOnTopHint);
	initTimer();
	initSun();
}

void MainWindow::paintEvent(QPaintEvent *e){
	QImage back_mou(":/openPic/res/op/for_moun.png");
	QImage for_mou(":/openPic/res/op/back_moun.png");
	QImage earth("::/openPic/res/op/earth.png");

	QPainter painter(this);
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
	//repaint();
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
	timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
