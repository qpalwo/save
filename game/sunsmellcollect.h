#ifndef SUNSMELLCOLLECT_H
#define SUNSMELLCOLLECT_H

#include <QWidget>
#include <QImage>
#include <QMovie>
#include <QPainter>
#include <qgraphicsview.h>
#include "smellofgame.h"
#include "collecterofgame.h"
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>

namespace Ui {
class SunSmellCollect;
}

class SunSmellCollect : public QGraphicsView
{
    Q_OBJECT

public:
    explicit SunSmellCollect(int hard, QWidget *parent = 0);
    ~SunSmellCollect();

protected:
	void focusInEvent(QFocusEvent *focusEvent);

signals:
	void finishGame();

public slots:
	void addMark();
	void sendSmell();
	void reFreshBack();
	void countDown();
	void closeMe();

private:
    Ui::SunSmellCollect *ui = NULL;
	QGraphicsScene *scene = NULL;
	QMovie *back = NULL;

	CollecterOfGame *collecter = NULL;
	QTimer *sendTimer = NULL;
	QTimer *reFreshBackTimer = NULL;
	QTimer *countDownTimer = NULL;
	QGraphicsPixmapItem *staus1 = NULL;
	QGraphicsPixmapItem *staus2 = NULL;
	QGraphicsPixmapItem *staus3 = NULL;

	QGraphicsSimpleTextItem *text1 = NULL;
	QGraphicsSimpleTextItem *text2 = NULL;
	QGraphicsSimpleTextItem *text3 = NULL;

	void loadRes();
	void determineHard();

	int gameHard;
	int collecterSpeed;
	int lunchSpeed;
	int nowMark;
	int nowNeed;
	int leftTime;
	int stausDX;
	int stausX;
	int stausY;
	int stausDY;
};

#endif // SUNSMELLCOLLECT_H
