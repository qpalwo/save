#include "UiManager.h"

UiManager::UiManager() {
	
}


void UiManager::closeLoading() {
	if (loading != NULL) {
		loading->close();
		delete loading;
		loading = NULL;
	}
}

void UiManager::closeWordWIndow() {
	if (m_wordWindow != NULL) {
		m_wordWindow->close();
		delete m_wordWindow;
		m_wordWindow = NULL;
	}
}

void UiManager::closeMainPage() {
	if (mainWindow != NULL) {
		mainWindow->close();
		delete mainWindow;
		mainWindow = NULL;
	}
}

void UiManager::closeSceneDesert() {
	if (sceneDesert != NULL) {
		sceneDesert->close();
		delete sceneDesert;
		sceneDesert = NULL;
	}
}

void UiManager::closeSceneForest() {
	if (sceneForest != NULL) {
		sceneForest->close();
		delete sceneForest;
		sceneDesert = NULL;
	}
}

void UiManager::closeSunSmellCollect() {
	if (sunSmellCollect != NULL) {
		sunSmellCollect->close();
		delete sunSmellCollect;
		sunSmellCollect = NULL;
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
	if (!isWordWindowOpen) {
		m_wordWindow = new WordWindow();
		isWordWindowOpen = true;
	}
	else {
		m_wordWindow->showText();
	}
}

void UiManager::openSceneDesert() {
	sceneDesert = new SceneDesert();
	sceneDesert->show();
	openWordWIndow();
}

void UiManager::openSceneForest() {
	sceneForest = new SceneForest();
	sceneForest->show();
	openWordWIndow();
}

void UiManager::openSunSmellCollect() {
	sunSmellCollect = new SunSmellCollect();
	sunSmellCollect->show();
	openWordWIndow();
}

void UiManager::showMainWindow() {
	openMainPage();
	closeLoading();
	openWordWIndow();
}

void UiManager::showSceneDesert() {
	openSceneDesert();
	closeLoading();
	openWordWIndow();
}

void UiManager::showSceneForest() {
	openSceneForest();
	closeLoading();
	openWordWIndow();
}

void UiManager::showSunSmellCollect() {
	openSunSmellCollect();
	closeLoading();
	openWordWIndow();
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

