#ifndef SMELLOFGAME_H
#define SMELLOFGAME_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QPainterPath>
#include "collecterofgame.h"

class SmellOfGame : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
    SmellOfGame(int x, int y, int vx, int vy);
	~SmellOfGame();

	QRectF boundingRect() const;
	void paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option,
		QWidget *widget);

	bool collidesWithItem(const CollecterOfGame *other,
		Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;

	void bindCollecter(CollecterOfGame*);

	int height;
	int width;

signals:
	void collected();

public slots:
	void finishGame();
	void reFresh();

private:
	QPixmap pixMap;
	CollecterOfGame *collecter = NULL;
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

#endif // SMELLOFGAME_H