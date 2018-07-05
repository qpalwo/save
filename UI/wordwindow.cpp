#include "wordwindow.h"
#include "ui_wordwindow.h"

WordWindow::WordWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::WordWindow) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	//setGeometry(960, 20, 10, 20);

}

void WordWindow::paintEvent(QPaintEvent *e) {
	QPainter painter(this);
	painter.setPen(QColor(0, 160, 230));
	QFont font;
	font.setFamily("HYQingTing");
	// ��С
	font.setPointSize(16);
	// б��
	font.setItalic(true);
	// �����ַ����
	font.setLetterSpacing(QFont::AbsoluteSpacing, 20);
	// ʹ������
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
