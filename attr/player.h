#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <qbytearray.h>
#include <QFile>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <QtConcurrent/qtconcurrentrun.h>

struct BagThing {
	int id;
	int num;
	QString name;
};

class BackBag {
public:
	BackBag();
	~BackBag();

	BagThing getBagThing(int);
	BagThing *getBagThing();
	void addBagThing(int);
	void save();
	void load();

private:
	BagThing m_bagThing[12];

	

};

class Player : public QObject
{
    Q_OBJECT
public:
	~Player();
	static Player * getInstance();
	void checkStaus();

	void addPower(int);
	void minusPower(int);
	void addMood(int);
	void minusMood(int);
	BagThing *getBagThing();
	void addBagThing(int);
	int nowStaus();
	void load();

signals:
	void stausChange();

public slots:

private:
	static Player* Instance;
	Player(QObject *parent = nullptr);

	const int HUNGGRY = 1;

	BackBag backBag;

	int m_power;
	int m_mood;

	int m_staus;

	void save();
};


#endif // PLAYER_H