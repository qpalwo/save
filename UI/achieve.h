#ifndef ACHIEVE_H
#define ACHIEVE_H

#include <QWidget>
#include <QPainter>
#include <QPIxmap>

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

private:
    Ui::Achieve *ui;

	QPixmap back;
};

#endif // ACHIEVE_H
