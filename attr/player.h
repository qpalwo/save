#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
	static Player * getInstance();

signals:

public slots:

private:
	static Player* Instance;
	Player(QObject *parent = nullptr);
};

#endif // PLAYER_H