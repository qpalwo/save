#ifndef ENDING_H
#define ENDING_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QString>
#include <QKeyEvent>

namespace Ui {
class ending;
}

class ending : public QWidget
{
    Q_OBJECT

public:
    explicit ending(int flag,QWidget *parent = 0);
    ~ending();

protected:
    void paintEvent(QPaintEvent *event);
    void initWord(int flag);
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::ending *ui;

    QImage backGround;

    QString p[11];
    int space;

};

#endif // ENDING_H
