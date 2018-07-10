#ifndef FIREBURNBOOK_H
#define FIREBURNBOOK_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QPainterPath>

class FireBurnBook : public QObject, public QGraphicsItem 
{
	Q_OBJECT
public:
    FireBurnBook();
	~FireBurnBook();

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, 
		QWidget *widget);

	int height;
	int width;

private:
	QPixmap pixMap;
};

#endif // FIREBURNBOOK_H