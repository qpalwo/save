#include "UiManager.h"

UiManager::UiManager() {
	//loading.show();
	//showMainWindow();
	//initWordwindow();
}

void UiManager::showMainWindow() {
	isLoading = false;
	window[1]->show();
	window[0]->close();
}

void UiManager::showSceneDesert() {
	isLoading = false;
	window[2]->show();
	window[0]->close();
}

void UiManager::showSceneForest() {
	isLoading = false;
	window[3]->show();
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
	window[3] = new SceneForest();
	window[0]->show();
	m_wordWindow = new WordWindow();
	initWordwindow();
}

void UiManager::initWordwindow() {
	//if (!isLoading) {
		m_wordWindow->showText();
	//}
}

UiManager::~UiManager() {

}

