#pragma once

#include "mainwindow.h"
#include "loading.h"
class UiManager : QObject{
	Q_OBJECT
public:
	UiManager();
	~UiManager();

public slots:
	void showMainWindow();

private:
	MainWindow mainWindow;
	Loading loading;

};

