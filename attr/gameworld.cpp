#include "gameworld.h"

GameWorld::GameWorld(QObject *parent) : QObject(parent)
{

}

GameWorld* GameWorld::Instance = new GameWorld();

GameWorld* GameWorld::getInstance() {
	return Instance;
}
