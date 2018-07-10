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
    explicit BurnBook(QWidget *parent = 0);
    ~BurnBook();

private:
    Ui::BurnBook *ui;
	QGraphicsScene *scene = NULL;

	void loadRes();
};

#endif // BURNBOOK_H