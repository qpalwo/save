#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include <QPainterPath>

class CollecterOfGame : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	CollecterOfGame();
	~CollecterOfGame();

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	int height;
	int width;

public slots:
	void keyReleaseEvent(QKeyEvent *event);
protected:
	void keyPressEvent(QKeyEvent *event);

private:
	QPixmap pixMap;

	int speed;
	
};
