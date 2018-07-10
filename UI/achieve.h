#ifndef ACHIEVE_H
#define ACHIEVE_H

#include <QWidget>
#include <QPainter>
#include <QPIxmap>
#include "openpagebutton.h"

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
};

#endif // ACHIEVE_H
