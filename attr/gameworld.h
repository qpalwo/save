#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QObject>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <qbytearray.h>
#include <qstring.h>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QFile>
#include <QString>

class AchieveData {
public:
	AchieveData();
	~AchieveData();
	static const int ACHIEVE_ONE = 0;
	void addAchieve(int);
	bool *getAllAchieve();
	void save();
	

private:
	bool m_achieves[23] = { 0 };
	void load();

};



class GameWorld : public QObject
{
    Q_OBJECT
public:
	~GameWorld();
	static GameWorld * getInstance();
	void addAchieve(int);
	void quitGame();

	void setGameHard(int);
	int getGameHard();
	bool* getAllAchieve();
	QString* getAllSaves();
	void addSaves(QString, int);

	void fromMainToBegining();
	void fromBeginingToRuinsCity();
	void showAchieve();
	void showSaveAndLoad();
	void showGameMap();
	void hideAchieve();

	void beginSmellCollect();
	void beginAvoidStorm();
	void beginKeepMoving();
	void beginBurnBook();

    void setVolume(int v);
    int getVolume();

signals:

public slots:

private:
	GameWorld(QObject *parent = nullptr);
	static GameWorld *Instance;

	AchieveData m_achieve;
	QString savesPath[6];
	int gameHard;
    int volume = 20;

	void save();
	void load();
};


#endif // GAMEWORLD_H
