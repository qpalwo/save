#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	setWindowFlag(Qt::CustomizeWindowHint);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	sceneType = qrand() % 4;
	initTimer();
	initWeather();
	initSun();
	loadImage();
	sceneHeight = 0;
	initMenu();
}


void MainWindow::initMenu() {
	if (!isDown) {
		open = new OpenPageButton("begin", this);
		b_continue = new OpenPageButton("continue", this);
		achieve = new OpenPageButton("achieve", this);
		set = new OpenPageButton("set", this);

		open->hide();
		b_continue->hide();
		achieve->hide();
		set->hide();
	}

	if (isDown && open != NULL) {
		open->setGeometry(rect().x() + 300, rect().y() - 40 + sceneHeight * 2, 130, 50);
		b_continue->setGeometry(rect().x() + 500, rect().y() -40 + sceneHeight * 2, 130, 50);
		achieve->setGeometry(rect().x() + 300, rect().y() + 30 + sceneHeight * 2, 130, 50);
		set->setGeometry(rect().x() + 500, rect().y() + 30 + sceneHeight * 2, 130, 50);

		open->show();
		b_continue->show();
		achieve->show();
		set->show();
	}
	if (!isDown) {
		connect(open, SIGNAL(clicked()), this, SLOT(onBeginClicked()));
		connect(b_continue, SIGNAL(clicked()), this, SLOT(onContinueClicked()));
		connect(achieve, SIGNAL(clicked()), this, SLOT(onAchieveClicked()));
		connect(set, SIGNAL(clicked()), this, SLOT(onSetClicked()));
	}
}

void MainWindow::hideMenu() {
	if (isDown && open != NULL) {
		open->hide();
		b_continue->hide();
		achieve->hide();
		set->hide();
		isDown = false;
	}
}

void MainWindow::initHardChoose() {
	hideMenu();
	easy = new OpenPageButton("easy", this);
	mid = new OpenPageButton("mid", this);
	hard = new OpenPageButton("hard", this);

	easy->setGeometry(rect().x() + 400, rect().y() - 40 + sceneHeight * 2, 130, 50);
	mid->setGeometry(rect().x() + 400, rect().y() + 30 + sceneHeight * 2, 130, 50);
	hard->setGeometry(rect().x() + 400, rect().y() + 100 + sceneHeight * 2, 130, 50);

	easy->show();
	mid->show();
	hard->show();

	connect(easy, SIGNAL(clicked()), this, SLOT(onEasyClicked()));
	connect(mid, SIGNAL(clicked()), this, SLOT(onMidClicked()));
	connect(hard, SIGNAL(clicked()), this, SLOT(onHardClicked()));
}



void MainWindow::loadImage() {
	//sceneType = 2;
	switch (sceneType) {
	case 0:  //mou
		rightPlayer = new QMovie(":/player/main_op.gif");
		back_mou.load(":/openRes/back_moun_s.png");
		for_mou.load(":/openRes/fro_moun_s.png");
		earth.load(":/openRes/earth_s.png");
		break;
	case 1:  //forest
		rightPlayer = new QMovie(":/player/forest_right.gif");
		if (nowTime >= 7 && nowTime <= 19) {
			for_mou.load(":/openRes/fro_forest_s.png");
			earth.load(":/openRes/forest_s.png");
		}
		else if (nowTime > 19 || nowTime < 7) {
			for_mou.load(":/openRes/fro_forest_n.png");
			earth.load(":/openRes/forest_n.png");
		}
		break;
	case 2: //snow
		rightPlayer = new QMovie(":/player/snow_right.gif");
		if (nowTime >= 7 && nowTime <= 17) {
			for_mou.load(":/openRes/fro_snow_s.png");
			earth.load(":/openRes/snow_s.png");
		}
		else if (nowTime > 17 && nowTime <= 20) {
			for_mou.load(":/openRes/fro_snow_d.png");
			earth.load(":/openRes/snow_d.png");
		} 
		else if(nowTime > 20 || nowTime < 7){
			for_mou.load(":/openRes/fro_snow_n.png");
			earth.load(":/openRes/snow_n.png");
		}
		break;
	case 3: //ruin
		rightPlayer = new QMovie(":/player/main_op.gif");
		if (nowTime >= 7 && nowTime <= 19) {
			for_mou.load(":/openRes/fro_ruins_s.png");
			earth.load(":/openRes/ruins_s.png");
		}
		else if (nowTime > 19 || nowTime < 7 ) {
			for_mou.load(":/openRes/fro_ruins_n.png");
			earth.load(":/openRes/ruins_n.png");
		}
		break;
	default:
		rightPlayer = new QMovie(":/player/main_op.gif");
		back_mou.load(":/openRes/back_moun_s.png");
		for_mou.load(":/openRes/fro_moun_s.png");
		earth.load(":/openRes/earth_s.png");
		break;
	}
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

void MainWindow::paintEvent(QPaintEvent *e) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, 960, 720, backGif->currentPixmap());
	if (weather == 0) {
		if (sunX != -1) {
			painter.drawImage(sunX, sunY, sun);
		}
		else {
			painter.drawImage(60, 100, moon);
		}
	}

	switch (sceneType) {
	case 1: //forest
	case 2: //snow
	case 3: //ruin
		painter.drawImage(0, sceneHeight + 155, for_mou, forMouLocation, 0);
		if (forMouLocation + 960 > 3840) {
			painter.drawImage(3840 - forMouLocation, sceneHeight + 155, for_mou);
		}
		painter.drawPixmap(380, 390 + sceneHeight, 100, 200, rightPlayer->currentPixmap());
		if (forMouLocation + 960 > 3840) {
			painter.drawImage(3840 - forMouLocation, sceneHeight + 155, earth);
		}
		painter.drawImage(0, sceneHeight + 155, earth, forMouLocation, 0);
		break;
	case 0: //mou
	default:
		painter.drawImage(0, sceneHeight, back_mou, forMouLocation, 0);
		if (forMouLocation + 960 > 3840) {
			painter.drawImage(3840 - forMouLocation, sceneHeight, back_mou);
		}
		painter.drawImage(0, sceneHeight, for_mou, forMouLocation, 0);
		if (forMouLocation + 960 > 3840) {
			painter.drawImage(3840 - forMouLocation, sceneHeight, for_mou);
		}
		painter.drawPixmap(380, 390 + sceneHeight, 100, 200, rightPlayer->currentPixmap());
		if (forMouLocation + 960 > 3840) {
			painter.drawImage(3840 - forMouLocation, sceneHeight, earth);
		}
		painter.drawImage(0, sceneHeight, earth, forMouLocation, 0);
		break;
	}

	if (weather == 1) {
		painter.drawImage(0, 0, cloud);
	}
	else if (weather == 2) {
		painter.drawImage(0, 0, cloud);
		painter.drawPixmap(0, 0, 960, 720, rain->currentPixmap());
	}
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
	initMenu();
}

void MainWindow::initVerticalTimer() {
	verticalTimer = new QTimer(this);
	connect(verticalTimer, SIGNAL(timeout()), this, SLOT(moveScene()));
	verticalTimer->start(8);
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
	if (!isDown) {
		isDown = true;
		initVerticalTimer();
	}
}

void MainWindow::onContinueClicked() {
	GameWorld::getInstance()->quitGame();

}

void MainWindow::onAchieveClicked() {

}

void MainWindow::onSetClicked() {

}

void MainWindow::onBeginClicked() {
	initHardChoose();
}

void MainWindow::onEasyClicked() {
	GameWorld::getInstance()->setGameHard(1);
	GameWorld::getInstance()->fromMainToBegining();
}

void MainWindow::onMidClicked() {
	GameWorld::getInstance()->setGameHard(2);
	GameWorld::getInstance()->fromMainToBegining();
}

void MainWindow::onHardClicked() {
	GameWorld::getInstance()->setGameHard(3);
	GameWorld::getInstance()->fromMainToBegining();
}

extern void saveToDisk(QByteArray content, QString path);

extern QByteArray loadFromDisk(QString path);

void MainWindow::initWeather() {
	QTime time = QTime::currentTime();
	int hour = time.hour();
	QJsonDocument document = QJsonDocument::fromJson(loadFromDisk(QString("userInfo/weather.info")));
	if (!document.isNull()) {
		QJsonObject obj = document.object();
		int time = obj.take("time").toString().toInt();
		if (_ABS(time - hour) <= 2) {
			weather = obj.take("weather").toString().toInt();
			loadWeatherImage();
			qDebug() << "read weather cache successful  " << obj.take("string").toString();
			return;
		}
	}
	QString url("https://free-api.heweather.com/v5/weather?city=%E6%AD%A6%E6%B1%89&key=4e3b3b56219b44ed8e6c46afae3bf6a8&lang=en");
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

	//int a = whe.toLower().compare("overcast");

	if (whe.toLower().mid(0, 5).compare("sunny") == 0) {
		weather = 0;
	}
	else if (whe.toLower().mid(0, 8).compare("overcast") == 0) {
		weather = 2;
	}
	else if (whe.toLower().mid(0, 6).compare("cloudy") == 0) {
		weather = 1;
	}
	else {
		weather = 2;
	}
	//weather = 0;
	loadWeatherImage();

	QJsonObject saves;
	saves.insert("weather", weather);
	saves.insert("string", whe);
	saves.insert("time", QTime::currentTime().hour());
	QJsonDocument document;
	document.setObject(saves);
	QByteArray bytearr = document.toJson(QJsonDocument::Compact);
	QtConcurrent::run(saveToDisk, bytearr, QString("userInfo/weather.info"));

	qDebug() << whe << weather;
}

void MainWindow::loadWeatherImage() {
	if (weather == 1) {
		cloud.load(":/openRes/cloud.png");
	}
	else if (weather == 2) {
		cloud.load(":/openRes/cloud.png");
		rain = new QMovie(":/openRes/rain.gif");
		rain->start();
	}
}


void MainWindow::initSun() {
	QTime time = QTime::currentTime();
	int hour = time.hour();
	nowTime = hour;
	//hour = 19;
	//nowTime = 19;
	if (hour >= 6 && hour < 12) {
		sunY = 300 - 56 * (hour - 6);
		sunX = 66 * (hour - 6) - 20;
	}
	else if (hour >= 12 && hour <= 19) {
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

MainWindow::~MainWindow() {
	delete ui;
	delete backGif;
	delete rightPlayer;
	delete rain;
	delete open;
	delete achieve;
	delete set;
	delete b_continue;
	delete easy;
	delete mid;
	delete hard;
}