#ifndef LOADING_H
#define LOADING_H

#include <QWidget>
#include "UiManager.h"

namespace Ui {
class Loading;
}

class Loading : public QWidget
{
    Q_OBJECT

public:
    explicit Loading(QWidget *parent = 0);
    ~Loading();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Loading *ui;
};

#endif // LOADING_H
