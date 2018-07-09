#pragma once

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
	void closeAll();

	void openMainPage();
	void openWordWIndow();
	void openSceneDesert();
	void openSceneForest();
	void openLoading();
	void openSunSmellCollect();
	void openAvoidStorm();
	void openRuins();
	void openSnow();
	void openKeepMoving();

	void init();

public slots:
	void showMainWindow();
	void showSceneDesert();
	void showSceneForest();
	void showSunSmellCollect();
	void showAvoidStorm();
	void showRuins();
	void showSnow();
	void showKeepMoving();

private:
	static UiManager *Instance;
	WordWindow *m_wordWindow = NULL;
	MainWindow *mainWindow = NULL;
	SceneDesert *sceneDesert = NULL;
	SceneForest *sceneForest = NULL;
	SceneRuins *sceneRuins = NULL;
	SceneSnow *sceneSnow = NULL;
	QWidget *loading = NULL;

	SunSmellCollect *sunSmellCollect = NULL;
	AvoidStorm *avoidStorm = NULL;
	KeepMoving *keepMoving = NULL;

	bool isWordWindowOpen = false;

	UiManager();

};

