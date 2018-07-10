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
	/*bool *ddd = GameWorld::getInstance()->getAllAchieve();
	BagThing* b = Player::getInstance()->getBagThing();
	int c = 0;*/
    return a.exec();
}
