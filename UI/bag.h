#ifndef BAG_H
#define BAG_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QGridLayout>
#include <QTimeLine>

namespace Ui {
class Bag;
}

class Bag : public QWidget
{
    Q_OBJECT

public:
    explicit Bag(QWidget *parent = nullptr);
    ~Bag();

private:
    Ui::Bag *ui;

    QImage backGround;

    QImage bottle;
    QImage conch;
    QImage gem;
    QImage stellball;
    QImage stick;

    QTimeLine *timerShow;
    QTimeLine *timerHide;

    int backX;

    void paintEvent(QPaintEvent *e);
    void loadImage();
    void leaveEvent(QEvent *e);
    void enterEvent(QEvent *e);
    void initTimer();

private slots:
    void bagShow();
    void bagHide();

};

#endif // BAG_H
