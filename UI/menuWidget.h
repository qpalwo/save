#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QImage>
#include <QPoint>
#include <QPushButton>
#include "openpagebutton.h"


namespace Ui {
class menuwidget;
}

class menuwidget : public QWidget
{
    Q_OBJECT

public:
    explicit menuwidget(QWidget *parent = 0);
    ~menuwidget();

private:
    Ui::menuwidget *ui;

    QImage backGround;

    OpenPageButton *acheive;
    OpenPageButton *bag;
    OpenPageButton *map;
    OpenPageButton *read;
    OpenPageButton *save;
    OpenPageButton *set;

    QPushButton *acheive1;

    int backX;

    void loadImage();
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void initbutton();
};

#endif // MENUWIDGET_H
