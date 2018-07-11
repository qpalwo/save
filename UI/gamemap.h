#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include "attr/player.h"

namespace Ui {
class GameMap;
}

class GameMap : public QWidget
{
    Q_OBJECT

public:
    explicit GameMap(QWidget *parent = 0);
    ~GameMap();

private:
    Ui::GameMap *ui;
	bool *m_map;
};

#endif // GAMEMAP_H
