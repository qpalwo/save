#ifndef ENDING_H
#define ENDING_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QString>
#include <QKeyEvent>
#include "openpagebutton.h"

namespace Ui {
class ending;
}

class ending : public QWidget
{
    Q_OBJECT

public:
    explicit ending(int flag,QWidget *parent = 0);
    ~ending();

public slots:
	void onBackClicked();


protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::ending *ui;
    QImage backGround;
	OpenPageButton *back;};

#endif // ENDING_H
