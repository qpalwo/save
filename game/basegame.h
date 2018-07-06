#ifndef BASEGAME_H
#define BASEGAME_H

#include <QWidget>

class BaseGame : public QWidget
{
    Q_OBJECT
public:
    explicit BaseGame(QWidget *parent = nullptr);

    virtual ~BaseGame();

        /*游戏初始化时候调用，如装载资源存档等*/
        virtual void initGame() = 0;

        /*保存游戏，调用即可保存全部游戏内容*/
        virtual void saveGame() = 0;
signals:

public slots:

private:

    int gameDiffLevel;

        /*游戏主题*/
        int gameType;

        /*游戏结束时候调用， 如分数结算等，释放资源*/
        virtual void endGame() = 0;

        /*获取游戏难度*/
        virtual void setGameDiffLevel() = 0;

};

#endif // BASEGAME_H
