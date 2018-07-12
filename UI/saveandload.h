#ifndef SAVEANDLOAD_H
#define SAVEANDLOAD_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include "openpagebutton.h"
#include "attr/player.h"
#include "attr/gameworld.h"

namespace Ui {
class SaveAndLoad;
}

class SaveAndLoad : public QWidget
{
    Q_OBJECT

public:
    explicit SaveAndLoad(QWidget *parent = 0);
    ~SaveAndLoad();

protected:
	void paintEvent(QPaintEvent * e);

public slots:
	void onBackClicked();

	void onButton1Clicked();
	void onButton2Clicked();
	void onButton3Clicked();
	void onButton4Clicked();
	void onButton5Clicked();
	void onButton6Clicked();

private:
    Ui::SaveAndLoad *ui;

	QPixmap back;
	QPixmap pix1;
	QPixmap pix2;
	QPixmap pix3;
	QPixmap pix4;
	QPixmap pix5;
	QPixmap pix6;

	OpenPageButton *button1 = NULL;
	OpenPageButton *button2 = NULL;
	OpenPageButton *button3 = NULL;
	OpenPageButton *button4 = NULL;
	OpenPageButton *button5 = NULL;
	OpenPageButton *button6 = NULL;
	OpenPageButton *backButton = NULL;

	QString *shoot = NULL;

	bool isSave[6] = { false };

	void initSaveAndButton();
	void initGameWorldData();
};

#endif // SAVEANDLOAD_H
