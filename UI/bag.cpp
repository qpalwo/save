#include "bag.h"
#include "ui_bag.h"

Bag::Bag(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bag)
{
    ui->setupUi(this);
}

Bag::~Bag()
{
    delete ui;
}
