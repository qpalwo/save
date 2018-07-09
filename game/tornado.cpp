#include "tornado.h"
#define _ABS(x) ((x) > 0 ? (x) : -(x))

Tornado::Tornado(int x) {
	height = 30;
	width = 30;
	vy = 10;
	setY(5);
	setX(x);
	moveBy(x, y());
	pixMap.load(":/game/SunSmellCollect/smell.png");
}

QRectF Tornado::boundingRect() const {
	return QRectF(5, 5, 95, 85);
}

bool Tornado::collidesWithItem(const PlayerInWind *other, Qt::ItemSelectionMode mode) const {
	return (_ABS(other->x() - this->x()) < other->width &&_ABS(other->y() - this->y()) < height) ? true : false;
}

void Tornado::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	Q_UNUSED(option);
	Q_UNUSED(widget);
	painter->drawPixmap(0, 0, pixMap);
}

void Tornado::bindPlayer(PlayerInWind *targetPlayer) {
	playInWind = targetPlayer;
	reFreshTimer = new QTimer(this);
	connect(reFreshTimer, SIGNAL(timeout()), this, SLOT(reFresh()));
	reFreshTimer->start(80);
}

void Tornado::reFresh() {
	calculateVY();
	calculateY();
	moveBy(0, vy);
	if (y() > 960) {
		killMe();
		return;
	}
	if (playInWind != NULL) {
		if (collidesWithItem(playInWind)) {
			emit collided();
			reFreshTimer->stop();
			killMe();
		}
	}
}

void Tornado::calculateY() {
	setY(y() + vy);
}

void Tornado::calculateVY() {
	vy = vy + G;
}

void Tornado::killMe() {
	delete this;
}

void Tornado::finishGame() {
	reFreshTimer->stop();
	hide();
	delete this;
}

QPainterPath Tornado::shape() const {
	QPainterPath path;
	path.addEllipse(32, 25, 66, 60);
	return path;
}

Tornado::~Tornado() {

}


