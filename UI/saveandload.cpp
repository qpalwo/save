#include "saveandload.h"
#include "ui_saveandload.h"

SaveAndLoad::SaveAndLoad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaveAndLoad)
{
    ui->setupUi(this);
}

SaveAndLoad::~SaveAndLoad()
{
    delete ui;
}
