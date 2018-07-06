#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QMouseEvent>
#include <QImage>
#include <QPoint>


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
    QPixmap acheive;
    QPixmap bag;
    QPixmap map;
    QPixmap read;
    QPixmap save;
    QPixmap set;

    int backX;

    int buttonState;

    void loadImage();
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // MENUWIDGET_H
