#include "UiManager.h"

UiManager::UiManager() {
	
}


void UiManager::closeLoading() {
	if (loading != NULL) {
		loading->close();
		delete loading;
	}
}

void UiManager::closeWordWIndow() {
	if (m_wordWindow != NULL) {
		m_wordWindow->close();
		delete m_wordWindow;
	}
}

void UiManager::closeMainPage() {
	if (mainWindow != NULL) {
		mainWindow->close();
		delete mainWindow;
	}
}

void UiManager::closeSceneDesert() {
	if (sceneDesert != NULL) {
		sceneDesert->close();
		delete sceneDesert;
	}
}

void UiManager::closeSceneForest() {
	if (sceneForest != NULL) {
		sceneForest->close();
		delete sceneForest;
	}
}

void UiManager::closeAll() {
	closeLoading();
	closeMainPage();
	closeSceneDesert();
	closeSceneForest();
	closeWordWIndow();
}

void UiManager::openLoading() {
	loading = new Loading();
	loading->show();
}

void UiManager::openMainPage() {
	mainWindow = new MainWindow();
	mainWindow->show();
}

void UiManager::openWordWIndow() {
	m_wordWindow = new WordWindow();
	m_wordWindow->showText();
}

void UiManager::openSceneDesert() {
	sceneDesert = new SceneDesert();
	sceneDesert->show();
}

void UiManager::openSceneForest() {
	sceneForest = new SceneForest();
	sceneForest->show();
}

void UiManager::showMainWindow() {
	openMainPage();
	closeLoading();
}

void UiManager::showSceneDesert() {
	openSceneDesert();
	closeLoading();
}

void UiManager::showSceneForest() {
	openSceneForest();
	closeLoading();
}

UiManager*UiManager::Instance = new UiManager();

UiManager* UiManager::getInstance() {
	return Instance;
}

void UiManager::init() {
	openWordWIndow();
	openLoading();
}


UiManager::~UiManager() {

}

