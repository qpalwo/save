#ifndef BASEGAME_H
#define BASEGAME_H

#include <QWidget>

namespace Ui {
	class BaseGame;
}

class BaseGame : public QWidget
{
    Q_OBJECT
public:
    explicit BaseGame(QWidget *parent = nullptr);
	virtual ~BaseGame();

	/*��Ϸ��ʼ��ʱ����ã���װ����Դ�浵��*/
	virtual void initGame() = 0;

	/*������Ϸ�����ü��ɱ���ȫ����Ϸ����*/
	virtual void saveGame() = 0;

signals:

public slots:

private:
	Ui::BaseGame *ui;

	int gameDiffLevel;

	/*��Ϸ����*/
	int gameType;

	/*��Ϸ����ʱ����ã� ���������ȣ��ͷ���Դ*/
	virtual void endGame() = 0;

	/*��ȡ��Ϸ�Ѷ�*/
	virtual void setGameDiffLevel() = 0;

};

#endif // BASEGAME_H