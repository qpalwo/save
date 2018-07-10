#include "fireburnbook.h"

FireBurnBook::FireBurnBook() {
	pixMap.load(":/game/SunSmellCollect/fire.png");
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFocus(Qt::OtherFocusReason);
	moveBy(680, 550);
	height = 150;
	width = 150;
}

QRectF FireBurnBook::boundingRect() const {
	return QRectF(0, 0, width, height);
}

void FireBurnBook::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget) {
	Q_UNUSED(option);  //�����ò���û��ʹ��
	Q_UNUSED(widget);
	painter->drawPixmap(0, 0, width, height, pixMap);
}

FireBurnBook::~FireBurnBook() {

}