#ifndef LOADING_H
#define LOADING_H
#pragma once
#include <QWidget>
#include <QMovie>
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

	void on_pushButton_4_clicked();

private:
    Ui::Loading *ui;
	QMovie * backGif;
};

#endif // LOADING_H
