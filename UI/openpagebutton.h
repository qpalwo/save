#ifndef OPENPAGEBUTTON_H
#define OPENPAGEBUTTON_H

#include <QPainter> 
#include <QMouseEvent>  
#include <qpushbutton.h>  
#include <qpixmap.h>
#include <qstring.h>
#include <qpoint.h>
#include <qwidget.h>

#define __Normal 0
#define __Hover 1
#define __Pressed 2

class OpenPageButton:public QPushButton 
{
public:
	OpenPageButton(QString res, QWidget *parent);
	OpenPageButton(QString path,QString res, QWidget *parent);
	OpenPageButton(QWidget *parent, QString path, QString res);
	~OpenPageButton();

signals:

private:
	QPixmap normalPixmap;
	QPixmap hoverPixmap;
	QPixmap pressPixmap;
	int buttonState = 0;

	void paintEvent(QPaintEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
};

#endif // OPENPAGEBUTTON_H