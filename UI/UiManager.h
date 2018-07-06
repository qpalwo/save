#pragma once

#include "mainwindow.h"
#include "loading.h"
#include "scenedesert.h"
#include "sceneforest.h"
#include "wordwindow.h"

class UiManager : QObject{
	Q_OBJECT
public:
	static UiManager* getInstance();
	~UiManager();

	void init();

public slots:
	void showMainWindow();
	void showSceneDesert();
	void showSceneForest();

private:
	bool isLoading = true;

	static UiManager *Instance;

	UiManager();
	void initWordwindow();

	QWidget *window[10]{ 0 };
	WordWindow *m_wordWindow;
};

