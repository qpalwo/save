#include "mainwindow.h"
#include <QApplication>
#include "loading.h"
#include "UiManager.h"
#include "attr/gameworld.h"
#include "attr/player.h"
#include "UI/ending.h"
#include "UI/gamemap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	GameWorld *gamaWord = GameWorld::getInstance();
	//Player *player = Player::getInstance();

	UiManager *uiManager = UiManager::getInstance();
	uiManager->init();
	//ending *e = new ending(1);
	//e->show();
	//GameMap *gm = new GameMap();
	//gm->show();
    return a.exec();
}
