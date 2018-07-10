#ifndef BURNBOOK_H
#define BURNBOOK_H

#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsScene>
#include <QTimer>
#include "fireburnbook.h"
#include "booktoburn.h"

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

protected:

private:
    Ui::BurnBook *ui;
	QGraphicsScene *scene = NULL;
	FireBurnBook *fireBurnBook = NULL;
	BookToBurn *m_book = NULL;

	void addBook();
	void loadRes();

	int gameHard;
	int leftBook;
};

#endif // BURNBOOK_H
