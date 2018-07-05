#include "UiManager.h"

UiManager::UiManager() {
	//loading.show();
	//showMainWindow();
}

void UiManager::showMainWindow() {
	window[1]->show();
	window[0]->close();
}

void UiManager::showSceneDesert() {
	window[2]->show();
	window[0]->close();
}

UiManager*UiManager::Instance = new UiManager();

UiManager* UiManager::getInstance() {
	return Instance;
}

void UiManager::init() {
	window[0] = new Loading();
	window[1] = new MainWindow();
	window[2] = new SceneDesert();
	window[0]->show();
	//showMainWindow();
}

UiManager::~UiManager() {

}

