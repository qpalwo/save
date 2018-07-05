#include "mainwindow.h"
#include <QApplication>
#include "loading.h"
#include "UiManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	UiManager *uiManager = UiManager::getInstance();
	uiManager->init();
	//Loading loading;
	//loading.show();

    //MainWindow w;
    //w.show();

    return a.exec();
}
