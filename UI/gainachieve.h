#ifndef GAINACHIEVE_H
#define GAINACHIEVE_H

#include <QWidget>
#include "attr/gameworld.h"
#include "openpagebutton.h"
#include <QPixmap>
#include <QPainter>

namespace Ui {
class GainAchieve;
}

class GainAchieve : public QWidget
{
    Q_OBJECT

public:
    explicit GainAchieve(int, QWidget *parent = 0);
    ~GainAchieve();

private slots:
	void onConfirmClicked();

protected:
	void paintEvent(QPaintEvent * e);

private:
    Ui::GainAchieve *ui;
	QPixmap back;
	QPixmap achieve;
	OpenPageButton *confirm = NULL;

	int m_achieve;

	void loadRes();
};

#endif // GAINACHIEVE_H
