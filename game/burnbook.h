#ifndef BURNBOOK_H
#define BURNBOOK_H

#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsScene>
#include <QTimer>
#include <QMovie>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include "fireburnbook.h"
#include "booktoburn.h"
#include "UI/gainachieve.h"

namespace Ui {
class BurnBook;
}

class BurnBook : public QGraphicsView
{
    Q_OBJECT

public:
    explicit BurnBook(int hard, QWidget *parent = 0);
    ~BurnBook();

public slots:
	void onBurned();
	void onUnBurned();
	void reFreshBack();

signals:
	void finishGame();

protected:

private:
    Ui::BurnBook *ui;
	QGraphicsScene *scene = NULL;
	FireBurnBook *fireBurnBook = NULL;
	BookToBurn *m_book = NULL;
	QMovie *back = NULL;
	QTimer *reFreshBackTimer = NULL;
	QGraphicsPixmapItem *staus1 = NULL;
	QGraphicsPixmapItem *staus2 = NULL;
	QGraphicsPixmapItem *staus3 = NULL;
	QGraphicsPixmapItem *staus4 = NULL;

	QGraphicsSimpleTextItem *text1 = NULL;
	QGraphicsSimpleTextItem *text2 = NULL;
	QGraphicsSimpleTextItem *text3 = NULL;
	QGraphicsSimpleTextItem *text4 = NULL;

	void addBook();
	void loadRes();
	void determineHard();
	void reFreshText();

	int gameHard;
	int allBook;
	int leftBook;
	int burnedBook;
	int nowNeed;
	int fireSize;
	int stausX;
	int stausY;
	int stausDX;
	int stausDY;
};

#endif // BURNBOOK_H
