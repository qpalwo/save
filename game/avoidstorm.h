#ifndef AVOIDSTORM_H
#define AVOIDSTORM_H

#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsScene>
#include "playerinwind.h"
#include "tornado.h"
#include <QTimer>
#include <QtGlobal>
#include <QTime>
#include <QMovie>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>

namespace Ui {
class AvoidStorm;
}

class AvoidStorm : public QGraphicsView
{
    Q_OBJECT

public:
    explicit AvoidStorm(int hard, QWidget *parent = 0);
    ~AvoidStorm();

signals:
	void finishGame();

public slots:
	void endGame();
	void sendTornado();

	void reFreshBack();
	void countDown();

private:
    Ui::AvoidStorm *ui;

	QGraphicsScene *scene = NULL;
	PlayerInWind *playerInWind = NULL;
	QMovie *back = NULL;
	QTimer *sendTimer = NULL;
	QTimer *reFreshBackTimer = NULL;
	QTimer *countDownTimer = NULL;
	QGraphicsPixmapItem *staus = NULL;
	QGraphicsSimpleTextItem *text = NULL;

	int gameHard;
	int playerSpeed;
	float tornadoVy;
	int lunchSpeed;
	int leftTime;
	int stausDX;
	int stausX;
	int stausY;
	int stausDY;

	void loadRes();
	void determineHard();
	
};

#endif // AVOIDSTORM_H
