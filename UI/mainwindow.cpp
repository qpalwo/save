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
	//initWeather();
	initSun();
	loadImage();
	sceneHeight = 0;
}

void MainWindow::loadImage() {
	back_mou.load(":/openRes/back_moun_s.png");
	for_mou.load(":/openRes/fro_moun_s.png");
	earth.load(":/openRes/earth_s.png");
	rightPlayer = new QMovie(":/player/main.gif");
	if (sunX != -1) {
		sun.load(":/openRes/sun_s.png");
	backGif = new QMovie(":/openGif/background_sn.gif");
	}
	else {
		moon.load(":/openRes/moon_s.png");
		backGif = new QMovie(":/openGif/background_se.gif");
	}
	backGif->start();
	rightPlayer->start();
}

void MainWindow::paintEvent(QPaintEvent *e){
	QPainter painter(this);
	painter.drawPixmap(0, 0, 960, 720, backGif->currentPixmap());
	if (sunX != -1) {
		painter.drawImage(sunX, sunY, sun);
	}
	else {
		painter.drawImage(60, 100, moon);
	}
    painter.drawImage(0, sceneHeight, back_mou, forMouLocation, 0);
	if (forMouLocation + 960 > 3840) {
		painter.drawImage(3840 - forMouLocation, sceneHeight, back_mou);
	}
	painter.drawImage(0, sceneHeight, for_mou, forMouLocation, 0);
	if (forMouLocation + 960 > 3840) {
		painter.drawImage(3840 - forMouLocation, sceneHeight, for_mou);
	}
	painter.drawPixmap(380, 275 + sceneHeight, 200, 400, rightPlayer->currentPixmap());
	if (forMouLocation + 960 > 3840) {
		painter.drawImage(3840 - forMouLocation, sceneHeight, earth);
	}
	painter.drawImage(0, sceneHeight, earth, forMouLocation, 0);
}

void MainWindow::moveMou() {
	if (p >= 200 || p <= 0)
		p = 0;
	p++;
	forMouLocation = p * 19;
	update();
}

void MainWindow::moveScene() {
	if (sceneHeight >= 0 && sceneHeight <= 120) {
		sceneHeight++;
	}
	if (sceneHeight == 120) {
		verticalTimer->stop();
	}
}

void MainWindow::initVerticalTimer() {
	verticalTimer = new QTimer(this);
	connect(verticalTimer, SIGNAL(timeout()), this, SLOT(moveScene()));
	verticalTimer->start(8);
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
	initVerticalTimer();
}

void MainWindow::initWeather() {
	QString url("https://free-api.heweather.com/v5/weather?city=%E6%AD%A6%E6%B1%89&key=4e3b3b56219b44ed8e6c46afae3bf6a8");
	QNetworkRequest netRequest;
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	netRequest.setUrl(QUrl(url));
	connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handelWeather(QNetworkReply *)));
	manager->get(netRequest);
}

void MainWindow::handelWeather(QNetworkReply *reply) {
	QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
	QJsonObject obj = doc.object();
	QString whe(obj.value("HeWeather5").toArray().at(0).toObject()
			.take("now").toObject().take("cond").toObject().take("txt").toString());
	if (whe.compare("��")) {
		weather = 1;
	}
	else if (whe.compare("��")) {
		weather = 2;
	}
	else {
		weather = 3;
	}
	qDebug() << whe << weather;
	//UiManager::getInstance()->showMainWindow();
}


void MainWindow::initSun() {
	QTime time = QTime::currentTime();
	int hour = time.hour();
	hour = 20;
	if (hour >= 6 && hour < 12) {
		sunY = 300 - 56 * (hour - 6);
		sunX = 66 * (hour - 6) - 20;
	}
	else if (hour >= 12 && hour < 19) {
		sunY = 56 * (hour - 12) - 20;
		sunX = 66 * (hour - 6) - 20;
	}
	else {
		sunY = -1;
		sunX = -1;
	}
	forMouLocation = 0;

}

void MainWindow::initTimer() {
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(moveMou()));
	timer->start(90);
}

MainWindow::~MainWindow()
{
    delete ui;
}
