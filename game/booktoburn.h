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
    BookToBurn(int, int);
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

	void onPressing();

protected:
	void keyReleaseEvent(QKeyEvent *event);
	void keyPressEvent(QKeyEvent *event);

private:
	QPixmap pixMap;
	FireBurnBook * fireBurnBook = NULL;
	QTimer *reFreshTimer = NULL;
	QTimer *pressTimer = NULL;

	QPainterPath shape() const;
	void calculateX();
	void calculateY();
	void calculateVY();
	void killMe();
	void throughBook();

	const float G = 2;
	float vy;
	float vx;

	int nowTime = 0;
	bool isRight = true;
	bool isThrough = false;
	bool isPressing = false;
};

#endif // BOOKTOBURN_H