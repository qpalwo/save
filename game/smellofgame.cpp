#include "smellofgame.h"
#define _ABS(x) ((x) > 0 ? (x) : -(x))

SmellOfGame::SmellOfGame(int x, int y, int vx, int vy) {
	setX(x);
	setY(y);
	height = 30;
	width = 30;
	this->vx = vx;
	this->vy = vy;
	moveBy(x, y);
	pixMap.load(":/game/SunSmellCollect/smell.png");
}

void SmellOfGame::bindCollecter(CollecterOfGame *targetCollecter) {
	collecter = targetCollecter;
	reFreshTimer = new QTimer(this);
	connect(reFreshTimer, SIGNAL(timeout()), this, SLOT(reFresh()));
	reFreshTimer->start(80);
}

void SmellOfGame::reFresh() {
	calculateVY();
	calculateX();
	calculateY();
	moveBy(vx, vy);
	if (y() > 960) {
		killMe();
		return;
	}
	if (collecter != NULL) {
		if (collidesWithItem(collecter)) {
			emit collected();
			reFreshTimer->stop();
			killMe();
		}
	}
}

QRectF SmellOfGame::boundingRect() const {
	return QRectF(5, 5, 90, 90);
}

void SmellOfGame::calculateX() {
	setX(x() + vx);
	if (x() > 960 - 55 || x() < -32) {
		vx = -vx;
	}
}

void SmellOfGame::calculateY() {
	setY(y() + vy);
}

void SmellOfGame::calculateVY() {
	vy = vy + G;
}

QPainterPath SmellOfGame::shape() const {
	QPainterPath path;
	path.addEllipse(32, 25, 66, 60);
	return path;
}

bool SmellOfGame::collidesWithItem(const CollecterOfGame *other, Qt::ItemSelectionMode mode) const {
	return (_ABS(other->x() - this->x()) < other->width &&_ABS(other->y() - this->y()) < height) ? true : false;
}

void SmellOfGame::paint(QPainter *painter,
	const QStyleOptionGraphicsItem *option,
	QWidget *widget) {
	Q_UNUSED(option);
	Q_UNUSED(widget);
	painter->drawPixmap(0, 0, pixMap);
}

void SmellOfGame::killMe() {
	deleteLater();
	//delete this;
}

void SmellOfGame::finishGame() {
	reFreshTimer->stop();
	hide();
	deleteLater();
	//delete this;
}

SmellOfGame::~SmellOfGame() {
	delete reFreshTimer;
}
