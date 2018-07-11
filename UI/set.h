#ifndef SET_H
#define SET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "openpagebutton.h"
#include <QLabel>
#include <QPoint>
#include <QMouseEvent>
#include "attr/gameworld.h"

namespace Ui {
class set;
}

class set : public QWidget
{
    Q_OBJECT

public:
    explicit set(QWidget *parent = 0);
    ~set();

private:
    Ui::set *ui;

    QPixmap back;
    OpenPageButton *backButton = NULL;
    QImage volumeBack;
    QPixmap volumeCover;
    QPoint mouse;
    QString s;
    QLabel *volumeSetting;
    bool press;
    int volume;
    int volumeShow;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void onBackClicked();

};

#endif // SET_H
