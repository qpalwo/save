#pragma once

#include "mainwindow.h"
#include "loading.h"

class UiManager : QObject{
	Q_OBJECT
public:
	static UiManager* getInstance();
	~UiManager();

	void init();

public slots:
	void showMainWindow();

private:
	static UiManager *Instance;
	UiManager();
	MainWindow *mainWindow;
	Loading *loading;

};

