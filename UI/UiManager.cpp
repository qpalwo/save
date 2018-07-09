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

void UiManager::closeAvoidStorm() {
	if (avoidStorm != NULL) {
		avoidStorm->close();
		delete avoidStorm;
		avoidStorm = NULL;
	}
}

void UiManager::closeRuins() {
	if (sceneRuins != NULL) {
		sceneRuins->close();
		delete sceneRuins;
		sceneRuins = NULL;
	}
}

void UiManager::closeSnow() {
	if (sceneSnow != NULL) {
		sceneSnow->close();
		delete sceneSnow;
		sceneSnow = NULL;
	}
}

void UiManager::closeKeepMoving() {
	if (keepMoving != NULL) {
		keepMoving->close();
		delete keepMoving;
		keepMoving = NULL;
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

void UiManager::openAvoidStorm() {
	avoidStorm = new AvoidStorm();
	avoidStorm->show();
	openWordWIndow();
}

void UiManager::openRuins() {
	sceneRuins = new SceneRuins();
	sceneRuins->show();
	openWordWIndow();
}

void UiManager::openSnow() {
	sceneSnow = new SceneSnow();
	sceneSnow->show();
	openWordWIndow();
}

void UiManager::openKeepMoving() {
	keepMoving = new KeepMoving();
	keepMoving->show();
	openWordWIndow();
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

void UiManager::showSunSmellCollect() {
	openSunSmellCollect();
	closeLoading();
}

void UiManager::showAvoidStorm() {
	openAvoidStorm();
	closeLoading();
}

void UiManager::showRuins() {
	openRuins();
	closeLoading();
}

void UiManager::showSnow() {
	openSnow();
	closeLoading();
}

void UiManager::showKeepMoving() {
	openKeepMoving();
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

