#ifndef KEEPMOVING_H
#define KEEPMOVING_H

#include <QGraphicsView>
#include <QPainter>
#include <QMovie>
#include <QGraphicsScene>
#include <QTimer>
#include <QtGlobal>
#include <QTime>
#include "playerinwind.h"
#include "tornado.h"

namespace Ui {
class KeepMoving;
}

class KeepMoving : public QGraphicsView
{
    Q_OBJECT

public:
    explicit KeepMoving(int, QWidget *parent = 0);
    ~KeepMoving();

public slots:
	void sendMachine();
	void sendLight();

	void addMark();
	void minusMark();

	void reFreshBack();

private:
    Ui::KeepMoving *ui;
	QGraphicsScene *scene = NULL;
	PlayerInWind *playerInWind = NULL;
	QMovie *backMovie = NULL;
	QTimer *machineSendTimer = NULL;
	QTimer *lighteSendTimer = NULL;
	QTimer *reFreshBackTimer = NULL;

	void loadRes();
	void determineHard();

	int gameHard;
	int playerSpeed;
	float lightSpeed;
	float machineSpeed;
	int machineLunchSpeed;
	int lightLunchSpeed;

};

#endif // KEEPMOVING_H
