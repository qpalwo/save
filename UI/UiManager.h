#pragma once

#include "mainwindow.h"
#include "scenedesert.h"
#include "sceneforest.h"
#include "wordwindow.h"
#include "loading.h"

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
	void closeAll();

	void openMainPage();
	void openWordWIndow();
	void openSceneDesert();
	void openSceneForest();
	void openLoading();

	void init();

public slots:
	void showMainWindow();
	void showSceneDesert();
	void showSceneForest();

private:
	static UiManager *Instance;
	WordWindow *m_wordWindow = NULL;
	MainWindow *mainWindow = NULL;
	SceneDesert *sceneDesert = NULL;
	SceneForest *sceneForest = NULL;
	QWidget *loading = NULL;

	bool isWordWindowOpen = false;

	UiManager();

};

