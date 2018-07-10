#ifndef BEGINING_H
#define BEGINING_H

#include <QWidget>
#include <qpainter.h>
#include <qimage.h>
#include <QKeyEvent>
#include <qstring.h>

namespace Ui {
class Begining;
}

class Begining : public QWidget
{
    Q_OBJECT

public:
    explicit Begining(QWidget *parent = 0);
    ~Begining();
	void paintEvent(QPaintEvent * e);

private:
    Ui::Begining *ui;
	void load();
	void keyPressEvent(QKeyEvent *e);

	int count;
	int c2;
	int jump;
	int jump2;
	bool zx;
	bool Lock;
	
	bool jump1;

	QImage back;
	QString p[50];
};

#endif // BEGINING_H
