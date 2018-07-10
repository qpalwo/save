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
		mainWindow->hide();
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

void UiManager::closeBegining() {
	if (begining != NULL) {
		begining->close();
		//delete begining;
		begining = NULL;
	}
}

void UiManager::closeBurnBook() {
	if (burnBook != NULL) {
		burnBook->close();
		delete burnBook;
		burnBook = NULL;
	}
}

void UiManager::closeAchieve() {
	if (achieve != NULL) {
		achieve->close();
		delete achieve;
		achieve = NULL;
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

void UiManager::openSunSmellCollect(int hard) {
	sunSmellCollect = new SunSmellCollect(hard);
	sunSmellCollect->show();
	openWordWIndow();
}

void UiManager::openAvoidStorm(int hard) {
	avoidStorm = new AvoidStorm(hard);
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

void UiManager::openKeepMoving(int hard) {
	keepMoving = new KeepMoving(hard);
	keepMoving->show();
	openWordWIndow();
}

void UiManager::openBegining() {
	begining = new Begining();
	begining->show();
	openWordWIndow();
}

void UiManager::openBurnBook(int hard) {
	burnBook = new BurnBook(hard);
	burnBook->show();
	openWordWIndow();
}

void UiManager::openAchieve() {
	achieve = new Achieve();
	achieve->show();
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
	openSunSmellCollect(1);
	closeLoading();
}

void UiManager::showAvoidStorm() {
	openAvoidStorm(1);
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
	openKeepMoving(1);
	closeLoading();
}

void UiManager::showBurnBook() {
	openBurnBook(1);
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

