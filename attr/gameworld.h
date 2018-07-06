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
//#include "UI/UiManager.h"


class Achieve {
public:
	Achieve();
	~Achieve();
	static const int ACHIEVE_ONE = 0;
	void addAchieve(int);

private:
	bool m_achieves[25] = { 0 };
	void save();
	void load();

};

class GameWorld : public QObject
{
    Q_OBJECT
public:
	static GameWorld * getInstance();
	void addAchieve(int);
	void quitGame();
   

signals:

public slots:

private:
	GameWorld(QObject *parent = nullptr);
	static GameWorld *Instance;

	Achieve m_achieve;

	void save();
	void load();
};


#endif // GAMEWORLD_H