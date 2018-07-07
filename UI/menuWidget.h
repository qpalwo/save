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
#include <QGridLayout>


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

    OpenPageButton *achieve;
    OpenPageButton *bag;
    OpenPageButton *map;
    OpenPageButton *read;
    OpenPageButton *save;
    OpenPageButton *set;

    QGridLayout *myLayout;

    int backX;

    void loadImage();
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void initbutton();
};

#endif // MENUWIDGET_H
