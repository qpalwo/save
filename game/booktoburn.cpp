#include "booktoburn.h"
#define _ABS(x) ((x) > 0 ? (x) : -(x))

BookToBurn::BookToBurn() {
	pixMap.load(":/game/SunSmellCollect/book.png");
}

void BookToBurn::bindFire(FireBurnBook *fire) {
	fireBurnBook = fire;
	reFreshTimer = new QTimer(this);
	connect(reFreshTimer, SIGNAL(timeout()), this, SLOT(reFresh()));
	reFreshTimer->start(100);
}

QRectF BookToBurn::boundingRect() const {
	return QRectF(5, 5, 90, 90);
}

void BookToBurn::reFresh() {

}

void BookToBurn::calculateX() {
	setX(x() + vx);
	if (x() > 960 - 55 || x() < -32) {
		vx = -vx;
	}
}

void BookToBurn::calculateY() {
	setY(y() + vy);
}

void BookToBurn::calculateVY() {
	vy = vy + G;
}

QPainterPath BookToBurn::shape() const {
	QPainterPath path;
	path.addRect(10, 10, 100, 100);
	//path.addEllipse(32, 25, 66, 60);
	return path;
}

bool BookToBurn::collidesWithItem(const FireBurnBook *other, Qt::ItemSelectionMode mode) const {
	int dx = this->x() - 680;
	int dy = this->y() - 550;
	if ((dx < 0 && dx > -this->width)
		|| (dx > 0 && dx < other->width)) {

		if ((dy < 0 && dy > -this->height)
			|| (dy > 0 && dy < other->height)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void BookToBurn::paint(QPainter *painter,
	const QStyleOptionGraphicsItem *option,
	QWidget *widget) {
	Q_UNUSED(option);
	Q_UNUSED(widget);
	painter->drawPixmap(0, 0, 100, 100, pixMap);
}

void BookToBurn::killMe() {
	delete this;
}

void BookToBurn::finishGame() {
	reFreshTimer->stop();
	hide();
	delete this;
}

BookToBurn::~BookToBurn() {

}
