#include "mainwindow.h"
#include <QApplication>
#include "open.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
	//open open;
	//open.show();

    return a.exec();
}
