#ifndef BOOKTOBURN_H
#define BOOKTOBURN_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QPainterPath>
#include "fireburnbook.h"

class BookToBurn : public QObject, public QGraphicsItem 
{
	Q_OBJECT

public:
    BookToBurn();
	~BookToBurn();

	QRectF boundingRect() const;
	void paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option,
		QWidget *widget);

	bool collidesWithItem(const FireBurnBook *other,
		Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;

	void bindFire(FireBurnBook*);

	int height;
	int width;

signals:
	void burned();
	void unBurned();

public slots:
	void finishGame();
	void reFresh();

private:
	QPixmap pixMap;
	FireBurnBook * fireBurnBook = NULL;
	QTimer *reFreshTimer;

	QPainterPath shape() const;
	void calculateX();
	void calculateY();
	void calculateVY();
	void killMe();

	const float G = 1.5;
	float vy;
	float vx;
};

#endif // BOOKTOBURN_H