#include "openpagebutton.h"


OpenPageButton::OpenPageButton(QString res, QWidget *parent) :
	QPushButton(parent) {
	buttonState = __Normal;

	QString normal = ":/button/" + res + "_1.png";
	QString hover = ":/button/" + res + "_2.png";
	QString pressed = ":/button/" + res + "_3.png";

	normalPixmap.load(normal);
	hoverPixmap.load(hover);
	pressPixmap.load(pressed);

	this->setFixedSize(normalPixmap.size());

	this->setContentsMargins(0, 0, 0, 0);
}

OpenPageButton::OpenPageButton(QString path, QString res, QWidget *parent) :
	QPushButton(parent) {
	buttonState = __Normal;

	QString normal = ":/menuZ/menu/" + res + "_1.png";
	QString hover = ":/menuZ/menu/" + res + "_2.png";
	QString pressed = ":/menuZ/menu/" + res + "_3.png";

	normalPixmap.load(normal);
	hoverPixmap.load(hover);
	pressPixmap.load(pressed);

	this->setFixedSize(normalPixmap.size());

	this->setContentsMargins(0, 0, 0, 0);
}

OpenPageButton::OpenPageButton(QWidget *parent, QString path, QString res) : 
	QPushButton(parent) {
	buttonState = __Normal;

	QString normal = ":" + path + res + "_1.png";
	QString hover = ":" + path + res + "_2.png";
	QString pressed = ":" + path + res + "_3.png";

	normalPixmap.load(normal);
	hoverPixmap.load(hover);
	pressPixmap.load(pressed);

	this->setFixedSize(normalPixmap.size());

	this->setContentsMargins(0, 0, 0, 0);
}


void OpenPageButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);

	switch (buttonState) {
	case __Normal:
		painter.drawPixmap(this->rect(), normalPixmap);
		break;
	case __Hover:
		painter.drawPixmap(this->rect(), hoverPixmap);
		break;
	case __Pressed:
		painter.drawPixmap(this->rect(), pressPixmap);
	}

	//painter.drawText(this->rect(), Qt::AlignCenter, this->text());
}

void OpenPageButton::enterEvent(QEvent *) {
	buttonState = __Hover;
	if (this) {
		update();
	}
}

void OpenPageButton::leaveEvent(QEvent *) {
	buttonState = __Normal;
	if (this) {
		update();
	}
}

void OpenPageButton::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		buttonState = __Pressed;
		if (this) {
			update();
		}
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

		buttonState = __Hover;
		/*if (this) {
			update();
		}*/
	}
}

OpenPageButton::~OpenPageButton() {

}
