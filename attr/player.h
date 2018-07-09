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

private:
	BagThing m_bagThing[12];

	void save();
	void load();

};

class Player : public QObject
{
    Q_OBJECT
public:
	static Player * getInstance();
	void checkStaus();

	void addPower(int);
	void minusPower(int);
	void addMood(int);
	void minusMood(int);
	void addSatiety(int);
	void minusSatiety(int);

signals:

public slots:

private:
	static Player* Instance;
	Player(QObject *parent = nullptr);

	const int HUNGGRY = 1;

	BackBag backBag;

	int m_power;
	int m_mood;
	int m_satiety;

	int m_staus;

	void save();
	void load();
};


#endif // PLAYER_H