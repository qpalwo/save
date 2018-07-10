#include "sceneruins.h"
#include "ui_sceneruins.h"

SceneRuins::SceneRuins(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneRuins)
{
    ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);

    backX = 0;
    backY = 0;
    playerX = 0;
	talk = 0;

    stop = false;
    left = false;
	first = false;
	zxLock= false;

	loadImage();
	loadPlot();

    menuwidget *menu = new menuwidget("ruins",this);
    setFocus();
    menu->show();
}

void SceneRuins::loadImage()
{
    backGround.load(":/ruins/scene/ruins_2.png");
    earth.load(":/ruins/scene/ruins_1.png");
    player = new QMovie(":/player/main.gif");
    player_left = new QMovie(":/player/main_left.gif");
	child.load(":/ruins/people/pink_left.png");
	conver.load(":/conver/convar/convar.png");
    player->start();
    player_left->start();
}

void SceneRuins::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

	QPen pen; //画笔
	pen.setColor(QColor(255, 255, 0));
	QBrush brush(QColor(255, 255, 0, 125)); //画刷
	painter.setPen(pen); //添加画笔
	painter.setBrush(brush); //添加画刷

	painter.setPen(QColor(100, 200, 200));
	QFont font;
	font.setFamily("微软雅黑");
	font.setPointSize(14);	// 大小
	font.setBold(true);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);	// 设置字符间距
	painter.setFont(font);	// 使用字体


    painter.drawImage(backX, backY, backGround);

    if (playerX == 430)   stop = true;

    if (left)  {
        painter.drawPixmap(playerX, 235, 100, 200, player_left->currentPixmap());
    }  else  painter.drawPixmap(playerX, 235, 100, 200, player->currentPixmap());

	if ((waitTime>0) && (waitTime <= 28))
		painter.drawRect(playerX, 260, 10 + waitTime * 3, 20); //绘制矩形 

	if (first) 	painter.drawText(180, 150, begin);
    painter.drawImage(backX, backY, earth);

	painter.setPen(QColor(250, 250, 250));
	if (playerX >= 440) {
		painter.drawImage(750, 25, child);
		painter.drawImage(0, 0, conver);
		if (zxLock) {
			painter.drawText(280, 612, record_1);
			painter.drawText(280, 666, record_2);
		}
		else {
			painter.drawText(280, 612, q[talk].s);
			if (q[talk].hu) {
				painter.drawText(280, 666, q[talk + 1].s);
			}
			if (q[talk].diff) {
				record_1 = q[talk].s;
				record_2 = q[talk + 1].s;
				talk++;
				painter.drawText(280, 666, q[talk].s);
				zxLock = true;
			}
		}
	}
	first = false;
}

void SceneRuins::keyPressEvent(QKeyEvent* e)
{
    if (stop)
    {
        switch (e->key())
        {
        case Qt::Key_A: backX += 10;  left = true;    break;
        case Qt::Key_Left:  backX += 10; left = true;  break;
        case Qt::Key_D: backX -= 10; left = false    ; break;
        case Qt::Key_Right:    backX -= 10;  left = false;   break;
        default: break;
        }

        if (backX < BDL) {
            backX += 10;
            stop = false;
            playerX += 10;
        }
        if (backX > BDR)  {
            backX -= 10;
            stop = false;
            playerX -= 10;
        }

		if ((e->key() == Qt::Key_S) || (e->key() == Qt::Key_Down)) {
			if (underDoor(2))	waitTime++;
		}	else waitTime = 0;
    }
    else {
        switch (e->key())
        {
        case Qt::Key_A:
            playerX -= 10;
            left = true;
            break;
        case Qt::Key_Left:
            playerX -= 10;
            left = true;
            break;
        case Qt::Key_D:
            playerX += 10;
            left = false;
            break;
        case Qt::Key_Right:
            playerX += 10;
            left = false; break;
        default:
            break;
        }
        if (playerX < 0)
        {
            playerX += 10;
        }
        if (playerX > 860)
        {
            playerX -= 10;
        }

		if ((e->key() == Qt::Key_S) || (e->key() == Qt::Key_Down)) {
			if (underDoor(1))	waitTime++;
		}	else waitTime = 0;

		if (playerX < 430) first = true;

		if ((e->key() == Qt::Key_Space) && (!q[talk].diff))  talk = q[talk].l;

		if (q[talk].diff) {
			if (e->key() == Qt::Key_Z) { talk = q[talk - 1].l;  zxLock = false; }
			if (e->key() == Qt::Key_X) { talk = q[talk].l;  zxLock = false; }
		}
    }

    update();
}

bool SceneRuins::underDoor(int n) {
	if (n == 2) {
		if ((backX >= -70) && (backX <= -40))  return true;
		if ((backX >= -570) && (backX <= -530))  return true;
		if ((backX >= -1410) && (backX <= -1380))  return true;
		if ((backX >= -2110) && (backX <= -2070))  return true;
	}
	return false;
}

void SceneRuins::loadPlot() {
	begin = QString::fromLocal8Bit("千篇一律的灰色...果然,压抑的布局也会使人心情更不愉快啊");

	q[0].s= QString::fromLocal8Bit("恩？似乎有什么声音？(抬头)"); q[0].diff = false; q[0].hu = false;

	q[0].l = 1; q[1].s = QString::fromLocal8Bit("（看见一个小孩爬在塔上，快要掉下来）"); q[1].diff = false; q[1].hu = false;

	q[1].l = 2; q[2].s = QString::fromLocal8Bit("z.冲过去接住他（要求体力值大于**）"); q[2].diff = true; q[2].hu = false;
    q[3].s = QString::fromLocal8Bit("x.不冲过去"); q[3].diff = true; q[3].hu = false;

}

SceneRuins::~SceneRuins()
{
    delete ui;
}
