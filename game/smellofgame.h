#ifndef SMELLOFGAME_H
#define SMELLOFGAME_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QObject>
#include <QPainterPath>

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

	//bool collidesWithItem(const QGraphicsItem *other,
		//Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;

public slots:
	void reFresh();

private:
	QPixmap pixMap;

	QPainterPath shape() const;
	void calculateX();
	void calculateY();
	void calculateVY();

	const float G = 1.5;
	float vy;
	float vx;
	float x;
	float y;

};

#endif // SMELLOFGAME_H