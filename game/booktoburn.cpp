#include "booktoburn.h"
#define _ABS(x) ((x) > 0 ? (x) : -(x))

BookToBurn::BookToBurn(int x, int y) {
	pixMap.load(":/game/SunSmellCollect/book.png");
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFocus(Qt::OtherFocusReason);
	vy = 0;
	moveBy(x, y);
	setX(x);
	setY(y);
}

void BookToBurn::bindFire(FireBurnBook *fire) {
	fireBurnBook = fire;
	reFreshTimer = new QTimer(this);
	connect(reFreshTimer, SIGNAL(timeout()), this, SLOT(reFresh()));
	reFreshTimer->start(100);
	reFreshTimer = new QTimer(this);
	pressTimer = new QTimer(this);

	connect(reFreshTimer, SIGNAL(timeout()), this, SLOT(reFresh()));
	connect(pressTimer, SIGNAL(timeout()), this, SLOT(onPressing()));
	reFreshTimer->start(100);
}

void BookToBurn::keyPressEvent(QKeyEvent *event) {
	if (!event->isAutoRepeat() && !isPressing) {
		isPressing = true;
		nowTime = 0;
		pressTimer->start(50);
	}
}

void BookToBurn::keyReleaseEvent(QKeyEvent *event) {
	if (!event->isAutoRepeat() && isPressing) {
		isPressing = false;
		pressTimer->stop();
		throughBook();
	}
}


QRectF BookToBurn::boundingRect() const {
	return QRectF(0, 0, 80, 80);
}

void BookToBurn::onPressing() {
	nowTime++;
}

void BookToBurn::throughBook() {
	vx = nowTime;
	isThrough = true;
	reFreshTimer->start(80);
}

void BookToBurn::reFresh() {
	if (!isPressing) {
		if (!isThrough) {
			if (x() > 600)
				isRight = false;
			if (x() < 30)
				isRight = true;
			if (isRight) {
				moveBy(10, 0);
				setX(x() + 10);
			}
			else {
				moveBy(-10, 0);
				setX(x() - 10);
			}
		}

		if (isThrough) {
			calculateVY();
			calculateX();
			calculateY();
			moveBy(vx, vy);
			if (y() >= 960) {
				emit unBurned();
				killMe();
				return;
			}
			if (fireBurnBook != NULL) {
				if (collidesWithItem(fireBurnBook)) {
					emit burned();
					reFreshTimer->stop();
					killMe();
				}
			}
		}
	}
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
	painter->drawPixmap(0, 0, 80, 80, pixMap);
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
	delete reFreshTimer;
	delete pressTimer;
}
