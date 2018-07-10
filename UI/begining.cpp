#include "begining.h"
#include "ui_begining.h"

Begining::Begining(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Begining)
{
    ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
}

Begining::~Begining()
{
    delete ui;
}
