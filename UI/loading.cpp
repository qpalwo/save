#include "loading.h"
#include "ui_loading.h"

Loading::Loading(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
}

Loading::~Loading()
{
    delete ui;
}

void Loading::on_pushButton_clicked()
{
    UiManager::getInstance()->showMainWindow();
}

void Loading::on_pushButton_2_clicked()
{
	UiManager::getInstance()->showSceneDesert();
}