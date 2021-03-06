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
	UiManager *uiManager = UiManager::getInstance();
	uiManager->init();
    return a.exec();
}
