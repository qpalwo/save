#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowStaysOnTopHint);
}

void MainWindow::paintEvent(QPaintEvent *e){
	QImage back_mou(":/openpic/back_b");
	QImage for_mou(":/openpic/back_for");
	QImage earth(":/openpic/back_mid");

	QPainter painter(this);
	painter.drawImage(0, 0, back_mou, 200, 300);
	painter.drawImage(0, 0, for_mou, 200, 300);
	painter.drawImage(0, 0, earth, 200, 300);
}

MainWindow::~MainWindow()
{
    delete ui;
}
