#ifndef AVOIDSTORM_H
#define AVOIDSTORM_H

#include <QGraphicsView>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include "playerinwind.h"
#include "tornado.h"
#include <QTimer>

namespace Ui {
class AvoidStorm;
}

class AvoidStorm : public QGraphicsView
{
    Q_OBJECT

public:
    explicit AvoidStorm(QWidget *parent = 0);
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

	void loadRes();
	
};

#endif // AVOIDSTORM_H
