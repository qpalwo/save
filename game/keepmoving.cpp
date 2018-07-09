#include "keepmoving.h"
#include "ui_keepmoving.h"

KeepMoving::KeepMoving(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeepMoving)
{
    ui->setupUi(this);
}

KeepMoving::~KeepMoving()
{
    delete ui;
}
