#ifndef SET_H
#define SET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "openpagebutton.h"
#include <QLabel>

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

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void onBackClicked();
};

#endif // SET_H
