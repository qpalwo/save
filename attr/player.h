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
	void useBagThing(int);
	void save(QString);
	void load(QString);
	void newBag();

private:
	BagThing m_bagThing[12];
	QString savePath;

	

};

class Player : public QObject
{
    Q_OBJECT
public:
	~Player();
	static Player * getInstance();
	void checkStaus();

	void changePower(int);
	void changeMood(int);
	BagThing *getBagThing();
	bool* getMapStaus();
	int getMyId();
	void setMapStaus(int);
	void addBagThing(int);
	void useBagThing(int);
	bool* nowStaus();
	void load();
	void load(QString path);
	void newPlayer(QString path, int hard, int id);

signals:
	void stausChange(bool, bool, bool, bool);

public slots:

private:
	static Player* Instance;
	Player(QObject *parent = nullptr);

	BackBag backBag;
	QString m_path;
	bool m_map[4];
	int m_id;
	int m_hard;
	int m_outScene;
	int m_power;
	int m_mood;

	bool m_staus[4] = {false};

	void save();
};


#endif // PLAYER_H