#include "wordwindow.h"
#include "ui_wordwindow.h"

WordWindow::WordWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::WordWindow) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	QDesktopWidget *deskWgt = QApplication::desktop();
	move(deskWgt->width() / 2 - 480, deskWgt->height() / 2 + 340);
}

void WordWindow::paintEvent(QPaintEvent *e) {
	QPainter painter(this);
	painter.setPen(QColor(0, 0, 0));
	QFont font;
	font.setFamily("HYQingTing");
	// 大小
	font.setPointSize(16);
	font.setBold(true);
	// 设置字符间距
	font.setLetterSpacing(QFont::AbsoluteSpacing, 10);
	// 使用字体
	painter.setFont(font);
	painter.drawText(rect(), Qt::AlignCenter, showedText);
}

void WordWindow::showText() {
	QString url("https://api.lwl12.com/hitokoto/v1?encode=realjson");
	QNetworkRequest netRequest;
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	netRequest.setUrl(QUrl(url));
	connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handelWord(QNetworkReply *)));
	manager->get(netRequest);
}

void WordWindow::handelWord(QNetworkReply * reply) {
	QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
	QJsonObject obj = doc.object();
	showedText = obj.take("text").toString();
	int a = showedText.length();
	if (a >= 30) {
		showText();
		return;
	}
	update();
	this->show();
	QTimer::singleShot(20000, this, SLOT(hidWindow()));
}


void WordWindow::hidWindow() {
	this->hide();
}

WordWindow::~WordWindow() {
	delete ui;
}
