#include "scenesnow.h"
#include "ui_scenesnow.h"

SceneSnow::SceneSnow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneSnow)
{
    ui->setupUi(this);
}

SceneSnow::~SceneSnow()
{
    delete ui;
}
