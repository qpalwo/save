#ifndef SUNSMELLCOLLECT_H
#define SUNSMELLCOLLECT_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <qgraphicsview.h>
#include "smellofgame.h"
#include "collecterofgame.h"
#include <QtGlobal>
#include <QTime>
#include <QTimer>

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

private:
    Ui::SunSmellCollect *ui = NULL;
	QGraphicsScene *scene = NULL;

	CollecterOfGame *collecter = NULL;
	QTimer *sendTimer = NULL;

	void loadRes();

	int gameHard;
};

#endif // SUNSMELLCOLLECT_H
