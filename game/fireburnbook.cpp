#include "fireburnbook.h"

FireBurnBook::FireBurnBook(int x, int y, int size) {
	pixMap.load(":/game/SunSmellCollect/fire.png");
	moveBy(x, y);
	height = size;
	width = size;
}

QRectF FireBurnBook::boundingRect() const {
	return QRectF(0, 0, width, height);
}

void FireBurnBook::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget) {
	Q_UNUSED(option);  //标明该参数没有使用
	Q_UNUSED(widget);
	painter->drawPixmap(0, 0, width, height, pixMap);
}

FireBurnBook::~FireBurnBook() {

}
