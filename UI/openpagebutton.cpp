#include "openpagebutton.h"


OpenPageButton::OpenPageButton(QString res, QWidget *parent) :
	QPushButton(parent) {
	buttonState = Normal;

	QString normal = ":/button/" + res + "_1.png";
	QString hover = ":/button/" + res + "_2.png";
	QString pressed = ":/button/" + res + "_3.png";

	normalPixmap.load(normal);
	hoverPixmap.load(hover);
	pressPixmap.load(pressed);

	this->setFixedSize(normalPixmap.size());

	this->setContentsMargins(0, 0, 0, 0);
}

void OpenPageButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);

	switch (buttonState) {
	case Normal:
		painter.drawPixmap(this->rect(), normalPixmap);
		break;
	case Hover:
		painter.drawPixmap(this->rect(), hoverPixmap);
		break;
	case Pressed:
		painter.drawPixmap(this->rect(), pressPixmap);
	}

	//painter.drawText(this->rect(), Qt::AlignCenter, this->text());
}

void OpenPageButton::enterEvent(QEvent *) {
	buttonState = Hover;
	update();
}

void OpenPageButton::leaveEvent(QEvent *) {
	buttonState = Normal;
	update();
}

void OpenPageButton::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		buttonState = Pressed;
		update();
	}
}

bool isOnOpenPageButton(const QPoint &point, const OpenPageButton *pushButton) {
	if (point.x() < 0 || point.x() > pushButton->width() ||
		point.y() < 0 || point.y() > pushButton->height()) {
		return false;
	}
	return true;
}

void OpenPageButton::mouseReleaseEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		//判断鼠标抬起时是否在PushButton之上   
		if (isOnOpenPageButton(e->pos(), this)) {
			emit clicked();
		}

		buttonState = Hover;
		update();
	}
}
