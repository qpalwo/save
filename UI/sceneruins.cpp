#include "sceneruins.h"
#include "ui_sceneruins.h"

SceneRuins::SceneRuins(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneRuins)
{
    ui->setupUi(this);
}

SceneRuins::~SceneRuins()
{
    delete ui;
}
