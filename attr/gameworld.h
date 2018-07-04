#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QObject>

class GameWorld : public QObject
{
    Q_OBJECT
public:
	static GameWorld * getInstance();
   

signals:

public slots:

private:
	GameWorld(QObject *parent = nullptr);
	static GameWorld *Instance;
};

#endif // GAMEWORLD_H