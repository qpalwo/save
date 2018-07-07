#include "smellofgame.h"
#define _ABS(x) ((x) > 0 ? (x) : -(x))

SmellOfGame::SmellOfGame(int x, int y, int vx, int vy)
{
	setX(x);
	setY(y);
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	moveBy(x, y);
	pixMap.load(":/game/SunSmellCollect/smell.png");
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(reFresh()));
	timer->start(80);
}

void SmellOfGame::reFresh() {
	calculateVY();
	calculateX();
	calculateY();
	moveBy(vx, vy);
}

QRectF SmellOfGame::boundingRect() const {
	qreal penWidth = 1;
	//return QRectF(32, 25, 66, 60);
	return QRectF(10, 5, 90, 90);
}

void SmellOfGame::calculateX() {
	this->x = this->x + vx;
	if (this->x > 960 - 55 || this->x < -32) {
		vx = -vx;
	}
}

void SmellOfGame::calculateY() {
	this->y = this->y + vy;
}

void SmellOfGame::calculateVY() {
	vy = vy + G;
}

QPainterPath SmellOfGame::shape() const {
	QPainterPath path;
	path.addEllipse(32, 25, 66, 60);
	return path;
}
/*
bool SmellOfGame::collidesWithItem(const QGraphicsItem *other,
	Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const {
	if(typeid(other) == typeid(this)) {
		(_ABS(other->x - this->x) < 35 &&
			_ABS(other->y - this->y) < 35) ? true : false;
	}

}*/

void SmellOfGame::paint(QPainter *painter,
	const QStyleOptionGraphicsItem *option,
	QWidget *widget) {
	Q_UNUSED(option);  //标明该参数没有使用
	Q_UNUSED(widget);
	painter->drawPixmap(0, 0, pixMap);
}

SmellOfGame::~SmellOfGame() {

}
