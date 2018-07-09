#ifndef TORNADO_H
#define TORNADO_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QPainterPath>
#include "playerinwind.h"



class Tornado : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
    Tornado(int);
	~Tornado();

	QRectF boundingRect() const;
	void paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option,
		QWidget *widget);

	bool collidesWithItem(const PlayerInWind *other,
		Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;
	void bindPlayer(PlayerInWind*);


	int height;
	int width;

signals:
	void collided();

public slots:
	void finishGame();
	void reFresh();

private:
	QPixmap pixMap;
	QTimer *reFreshTimer = NULL;
	PlayerInWind *playInWind = NULL;

	QPainterPath shape() const;
	void calculateY();
	void calculateVY();
	void killMe();

	float G = 1.5;
	float vy;
};

#endif // TORNADO_H