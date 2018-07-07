#ifndef SUNSMELLCOLLECT_H
#define SUNSMELLCOLLECT_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <qgraphicsview.h>
#include "smellofgame.h"

namespace Ui {
class SunSmellCollect;
}

class SunSmellCollect : public QGraphicsView
{
    Q_OBJECT

public:
    explicit SunSmellCollect(QWidget *parent = 0);
    ~SunSmellCollect();

private:
    Ui::SunSmellCollect *ui;
	QGraphicsScene *scene;

	void loadRes();
};

#endif // SUNSMELLCOLLECT_H
