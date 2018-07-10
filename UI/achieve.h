#ifndef ACHIEVE_H
#define ACHIEVE_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "openpagebutton.h"
#include <QLabel>
#include <QGridLayout>
#include "attr/gameworld.h"

namespace Ui {
class Achieve;
}

class Achieve : public QWidget
{
    Q_OBJECT

public:
    explicit Achieve(QWidget *parent = 0);
    ~Achieve();

protected:
	void paintEvent(QPaintEvent *e);

private slots:
	void onBackClicked();

private:
    Ui::Achieve *ui;

	QPixmap back;
	OpenPageButton *backButton = NULL;
    QPixmap achieve1;
    QPixmap achieve2;
    QPixmap achieve3;
    QPixmap achieve4;
    QPixmap achieve5;
    QPixmap achieve6;
    QPixmap achieve7;
    QPixmap achieve8;
    QPixmap achieve9;
    QPixmap achieve10;
    QPixmap achieve11;
    QPixmap achieve12;
    QPixmap achieve13;
    QPixmap achieve14;
    QPixmap achieve15;
    QPixmap achieve16;
    QPixmap achieve17;
    QPixmap achieve18;
    QPixmap achieve19;
    QPixmap achieve20;
    QPixmap achieve21;
    QPixmap achieve22;
    QPixmap achieve23;

    void loadPixmap();
    bool *a = NULL;
};

#endif // ACHIEVE_H
