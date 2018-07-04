#include "UiManager.h"

UiManager::UiManager() {
	loading.show();
	showMainWindow();
}

void UiManager::showMainWindow() {
	mainWindow.show();
	loading.close();
}

UiManager::~UiManager() {

}
