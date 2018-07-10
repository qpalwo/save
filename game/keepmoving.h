#ifndef KEEPMOVING_H
#define KEEPMOVING_H

#include <QGraphicsView>
#include <QPainter>
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
    explicit KeepMoving(QWidget *parent = 0);
    ~KeepMoving();

public slots:
	void sendMachine();
	void sendLight();

	void addMark();
	void minusMark();

private:
    Ui::KeepMoving *ui;
	QGraphicsScene *scene = NULL;
	PlayerInWind *playerInWind = NULL;
	QTimer *machineSendTimer = NULL;
	QTimer *lighteSendTimer = NULL;

	void loadRes();

};

#endif // KEEPMOVING_H
