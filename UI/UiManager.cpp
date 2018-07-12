#include "UiManager.h"

UiManager::UiManager() {
	
}

void UiManager::closeLoading() {
	if (loading != NULL) {
		loading->close();
		loading->deleteLater();
		loading = NULL;
	}
}

void UiManager::closeWordWIndow() {
	if (m_wordWindow != NULL) {
		m_wordWindow->close();
		m_wordWindow->deleteLater();
		m_wordWindow = NULL;
	}
}

void UiManager::closeMainPage() {
	if (mainWindow != NULL) {
		mainWindow->close();
		mainWindow->deleteLater();
		mainWindow = NULL;
	}
}

void UiManager::closeSceneDesert() {
	if (sceneDesert != NULL) {
		sceneDesert->close();
		sceneDesert->deleteLater();
		sceneDesert = NULL;
	}
}

void UiManager::closeSceneForest() {
	if (sceneForest != NULL) {
		sceneForest->close();
		sceneForest->deleteLater();
		sceneForest = NULL;
	}
}

void UiManager::closeSunSmellCollect() {
	if (sunSmellCollect != NULL) {
		sunSmellCollect->close();
		sunSmellCollect->deleteLater();
		sunSmellCollect = NULL;
	}
}

void UiManager::closeAvoidStorm() {
	if (avoidStorm != NULL) {
		avoidStorm->close();
		avoidStorm->deleteLater();
		avoidStorm = NULL;
	}
}

void UiManager::closeRuins() {
	if (sceneRuins != NULL) {
		sceneRuins->close();
		sceneRuins->deleteLater();
		sceneRuins = NULL;
	}
}

void UiManager::closeSnow() {
	if (sceneSnow != NULL) {
		sceneSnow->close();
		sceneSnow->deleteLater();
		sceneSnow = NULL;
	}
}

void UiManager::closeKeepMoving() {
	if (keepMoving != NULL) {
		keepMoving->close();
		keepMoving->deleteLater();
		keepMoving = NULL;
	}
}

void UiManager::closeBegining() {
	if (begining != NULL) {
		begining->close();
		begining->deleteLater();
		begining = NULL;
	}
}

void UiManager::closeBurnBook() {
	if (burnBook != NULL) {
		burnBook->close();
		burnBook->deleteLater();
		burnBook = NULL;
	}
}

void UiManager::closeAchieve() {
	if (achieve != NULL) {
		achieve->close();
		achieve->deleteLater();
		achieve = NULL;
	}
}

void UiManager::closeSaveAndLoad() {
	if (saveAndLoad != NULL) {
		saveAndLoad->close();
		saveAndLoad->deleteLater();
		saveAndLoad = NULL;
	}
}

void UiManager::closeGameMap() {
	if (gameMap != NULL) {
		gameMap->close();
		gameMap->deleteLater();
		gameMap = NULL;
	}
}

void UiManager::closeEnding() {
	if (end != NULL) {
		end->close();
		end->deleteLater();
		end = NULL;
	}
}

void UiManager::closeAll() {
	closeLoading();
	closeMainPage();
	closeSceneDesert();
	closeSceneForest();
	closeWordWIndow();
}

void UiManager::changeStaus(bool a, bool b, bool c, bool d) {
	if (sceneDesert != NULL) {
		sceneDesert->changeState(a, b, c, d);
	}
	else if (sceneForest != NULL) {
		sceneForest->changeState(a, b, c, d);
	}
	else if (sceneRuins != NULL) {
		sceneRuins->changeState(a, b, c, d);
	}
	else if (sceneSnow != NULL){
		sceneSnow->changeState(a, b, c, d);
	}
}

void UiManager::openLoading() {
	loading = new Loading();
	loading->show();
	QTimer::singleShot(3000, this, SLOT(showMainWindow()));
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

void UiManager::openSaveAndLoad() {
	saveAndLoad = new SaveAndLoad();
	saveAndLoad->show();
	openWordWIndow();
}

void UiManager::openGameMap(bool is) {
	gameMap = new GameMap(is);
	gameMap->show();
	openWordWIndow();
}

void UiManager::openEnding(int i) {
	end = new ending(i);
	end->show();
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

void UiManager::showRuins() {
	openRuins();
	closeLoading();
}

void UiManager::showSnow() {
	openSnow();
	closeLoading();
}

void UiManager::showKeepMoving() {
	openKeepMoving(3);
	closeLoading();
}

void UiManager::showBurnBook() {
	openBurnBook(3);
	closeLoading();
}

void UiManager::showSunSmellCollect() {
	openSunSmellCollect(3);
	closeLoading();
}

void UiManager::showAvoidStorm() {
	openAvoidStorm(3);
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

void UiManager::informeSnow() {
	if (sceneSnow != NULL) {
		//informe snow
		sceneSnow->gameOver();
	}
}

void UiManager::informeDesert() {
	if (sceneDesert != NULL) {
		sceneDesert->gameOver();
	}
}

void UiManager::informeForest() {
	if (sceneForest != NULL) {
		sceneForest->gameOver();
	}
}

void UiManager::informeRuins() {
	if (sceneRuins != NULL) {
		sceneRuins->gameOver();
	}
}

void UiManager::fromForestToMap() {
	openGameMap(true);
	closeSceneForest();
}

void UiManager::fromDesertToMap() {
	openGameMap(true);
	closeSceneDesert();
}

void UiManager::fromSnowToMap() {
	openGameMap(true);
	closeSnow();
}

void UiManager::fromRunisToMap() {
	openGameMap(true);
	closeRuins();
}

void UiManager::fromMapToForest() {
	openSceneForest();
	closeGameMap();
}

void UiManager::fromMapToDesert() {
	openSceneDesert();
	closeGameMap();
}

void UiManager::fromMapToRuins() {
	openRuins();
	closeGameMap();	
}

void UiManager::fromMapToSnow() {
	openSnow();
	closeGameMap();
}

void UiManager::fromBeginingToEnding() {
	openEnding(1);
	closeBegining();
}

void UiManager::fromForestToEnding(int i) {
	openEnding(i);
	closeSceneForest();
}

void UiManager::fromDesertToEnding(int i) {
	openEnding(i);
	closeSceneDesert();
}

void UiManager::fromSnowToEnding(int i) {
	openEnding(i);
	closeSnow();
}

void UiManager::fromRuinsToEnding(int i) {
	openEnding(i);
	closeRuins();
}

void UiManager::useThing(int id) {
	if (sceneDesert != NULL) {
		sceneDesert->bagThingClick(id);
	}
	else if (sceneForest != NULL) {
		sceneForest->bagThingClick(id);
	}
	else if (sceneRuins != NULL) {
		sceneRuins->bagThingClick(id);
	}
	else if (sceneSnow != NULL) {
		sceneSnow->bagThingClick(id);
	}
}

QString UiManager::screenShoot() {
	QPixmap shoot;
	if (sceneDesert != NULL) {
		shoot = sceneDesert->grab(QRect(0, 0, 960, 720));
	}
	else if (sceneForest != NULL) {
		shoot = sceneForest->grab(QRect(0, 0, 960, 720));
	}
	else if (sceneRuins != NULL) {
		shoot = sceneRuins->grab(QRect(0, 0, 960, 720));
	}
	else if (sceneSnow != NULL) {
		shoot = sceneSnow->grab(QRect(0, 0, 960, 720));
	}

	QString filePathName = "userInfo/shoot";

	filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");

	filePathName += ".png";

	if (!shoot.save(filePathName, "png")){
		qDebug() << "save widget screen failed";
	}
	return filePathName;
}

UiManager::~UiManager() {
	
}

