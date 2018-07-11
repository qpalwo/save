#include "collecterofgame.h"
#define _ABS(x) ((x) > 0 ? (x) : -(x))

CollecterOfGame::CollecterOfGame(int collecterSpeed) {
	pixMap.load(":/game/SunSmellCollect/bottle.png");
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFocus(Qt::OtherFocusReason);
	moveBy(480, 500);
	speed = collecterSpeed;
	height = 120;
	width = 100;
}

QRectF CollecterOfGame::boundingRect() const {
	return QRectF(0, 0, width, height);
}

void CollecterOfGame::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,
	QWidget *widget) {
	Q_UNUSED(option);  //标明该参数没有使用
	Q_UNUSED(widget);
	painter->drawPixmap(0, 0, width, height, pixMap);
}

void CollecterOfGame::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
	case Qt::Key_A:
	case Qt::Key_Left:
		if(x() - speed > 0)
			moveBy(-speed, 0);
		break;
	case Qt::Key_D:
	case Qt::Key_Right:
		if (x() + 135 + speed < 960)
		moveBy(speed, 0);
		break;
	default:
		break;
	}
}

void CollecterOfGame::keyReleaseEvent(QKeyEvent *event) {
	//moveBy(-10, 0);
}


CollecterOfGame::~CollecterOfGame() {
}
