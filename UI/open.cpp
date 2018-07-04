#include "open.h"
#include "ui_open.h"

open::open(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::open)
{
    ui->setupUi(this);
}

void open::paintEvent(QPaintEvent *e) {

}

open::~open()
{
    delete ui;
}
