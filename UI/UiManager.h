#pragma once

#include "QTimer"
#include "mainwindow.h"
#include "scenedesert.h"
#include "sceneforest.h"
#include "wordwindow.h"
#include "loading.h"
#include "game/sunsmellcollect.h"
#include "game/avoidstorm.h"
#include "sceneruins.h"
#include "scenesnow.h"
#include "game/keepmoving.h"
#include "begining.h"
#include "game/burnbook.h"
#include "achieve.h"
#include "saveandload.h"
#include "gamemap.h"

class UiManager : QObject{
	Q_OBJECT
public:
	static UiManager* getInstance();
	~UiManager();

	void closeLoading();
	void closeWordWIndow();
	void closeMainPage();
	void closeSceneDesert();
	void closeSceneForest();
	void closeSunSmellCollect();
	void closeAvoidStorm();
	void closeRuins();
	void closeSnow();
	void closeKeepMoving();
	void closeBegining();
	void closeBurnBook();
	void closeAchieve();
	void closeSaveAndLoad();
	void closeGameMap();
	void closeAll();

	void openSceneDesert();
	void openSceneForest();
	void openRuins();
	void openSnow();
	void openBegining();
	void openMainPage();
	void openWordWIndow();
	void openLoading();
	void openAchieve();
	void openSaveAndLoad();
	void openGameMap();
	void openSunSmellCollect(int);
	void openAvoidStorm(int);
	void openBurnBook(int);
	void openKeepMoving(int);

	void init();

	void informeSnow();
	void informeDesert();
	void informeForest();
	void informeRuins();

public slots:
	void showMainWindow();
	void showSceneDesert();
	void showSceneForest();
	void showSunSmellCollect();
	void showAvoidStorm();
	void showRuins();
	void showSnow();
	void showKeepMoving();
	void showBurnBook();

private:
	static UiManager *Instance;
	WordWindow *m_wordWindow = NULL;
	MainWindow *mainWindow = NULL;
	SceneDesert *sceneDesert = NULL;
	SceneForest *sceneForest = NULL;
	SceneRuins *sceneRuins = NULL;
	SceneSnow *sceneSnow = NULL;
	QWidget *loading = NULL;
	Begining *begining = NULL;
	Achieve *achieve = NULL;
	SaveAndLoad *saveAndLoad = NULL;

	SunSmellCollect *sunSmellCollect = NULL;
	AvoidStorm *avoidStorm = NULL;
	KeepMoving *keepMoving = NULL;
	BurnBook *burnBook = NULL;
	GameMap *gameMap = NULL;

	bool isWordWindowOpen = false;

	UiManager();

};

