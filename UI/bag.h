#ifndef BAG_H
#define BAG_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QGridLayout>
#include <QTimeLine>
#include <QCloseEvent>
#include <QString>

namespace Ui {
class Bag;
}

class Bag : public QWidget
{
    Q_OBJECT

public:
    Bag(QString res,QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *e);
    ~Bag();

private:
    Ui::Bag *ui;

    QImage backGround;
    QString scene;

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

signals:
    void exitBag();

};

#endif // BAG_H
