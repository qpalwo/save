#include "mainwindow.h"
#include <QApplication>
#include "loading.h"
#include "UiManager.h"
#include "attr/gameworld.h"
#include "attr/player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	GameWorld *gamaWord = GameWorld::getInstance();
	Player *player = Player::getInstance();

	UiManager *uiManager = UiManager::getInstance();
	uiManager->init();
	//Loading loading;
	//loading.show();

    //MainWindow w;
    //w.show();

    return a.exec();
}
