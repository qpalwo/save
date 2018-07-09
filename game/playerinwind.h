#ifndef PLAYERINWIND_H
#define PLAYERINWIND_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include <QPainterPath>

class PlayerInWind : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
    PlayerInWind();
	~PlayerInWind();
	QRectF boundingRect() const;
	void paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option,
		QWidget *widget);

	int height;
	int width;


public slots:


protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

private:
	QPixmap pixMap;

	int speed;
};

#endif // PLAYERINWIND_H