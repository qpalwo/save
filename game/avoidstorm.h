#ifndef AVOIDSTORM_H
#define AVOIDSTORM_H

#include <QGraphicsView>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include "playerinwind.h"
#include "tornado.h"
#include <QTimer>
#include <QtGlobal>
#include <QTime>

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

private:
    Ui::AvoidStorm *ui;

	QGraphicsScene *scene = NULL;
	PlayerInWind *playerInWind = NULL;
	QPixmap back;
	QTimer *sendTimer = NULL;

	int gameHard;
	int playerSpeed;
	float tornadoVy;
	int lunchSpeed;

	void loadRes();
	void determineHard();
	
};

#endif // AVOIDSTORM_H
