#include "fireburnbook.h"

FireBurnBook::FireBurnBook(int x, int y) {
	pixMap.load(":/game/SunSmellCollect/fire.png");
	//setFlag(QGraphicsItem::ItemIsFocusable);
	//setFocus(Qt::OtherFocusReason);
	moveBy(x, y);
	height = 150;
	width = 150;
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
