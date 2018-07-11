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
    explicit GainAchieve(bool, int, QWidget *parent = 0);
    ~GainAchieve();

public slots:
	void onConfirmClicked();

signals:
	void achieveClosed();

protected:
	void paintEvent(QPaintEvent * e);

private:
    Ui::GainAchieve *ui;
	QPixmap back;
	QPixmap achieve;
	OpenPageButton *confirm = NULL;

	int m_achieve;
	bool m_isWin;

	void loadRes();
};

#endif // GAINACHIEVE_H
