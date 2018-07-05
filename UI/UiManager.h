#pragma once

#include "mainwindow.h"
#include "loading.h"
#include "scenedesert.h"

class UiManager : QObject{
	Q_OBJECT
public:
	static UiManager* getInstance();
	~UiManager();

	void init();

public slots:
	void showMainWindow();
	void showSceneDesert();

private:
	static UiManager *Instance;
	UiManager();
	QWidget *window[10]{ 0 };
};

