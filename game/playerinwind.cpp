#include "playerinwind.h"

PlayerInWind::PlayerInWind(int playerSpeed) {
	pixMap.load("://uncle.png");
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFocus(Qt::OtherFocusReason);
	moveBy(480, 500);
	speed = playerSpeed;
	height = 200;
	width = 100;
}

QRectF PlayerInWind::boundingRect() const {
	return QRectF(0, 0, width, height);
}

void PlayerInWind::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget) {
	Q_UNUSED(option);  //标明该参数没有使用
	Q_UNUSED(widget);
	painter->drawPixmap(0, 0, pixMap);
}

void PlayerInWind::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
	case Qt::Key_A:
	case Qt::Key_Left:
		if (x() - speed > 0)
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

void PlayerInWind::keyReleaseEvent(QKeyEvent *event) {

}

PlayerInWind::~PlayerInWind() {

}
