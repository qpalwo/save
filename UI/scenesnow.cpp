#include "scenesnow.h"
#include "ui_scenesnow.h"

SceneSnow::SceneSnow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneSnow)
{
    ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

	Player::getInstance()->setMapStaus(4);

    backX = 0;
    backY = 0;
    playerX = 0;
	talk = 0;
	ti = 0;

    stop = false;
    left = false;
	first = false;
	zxLock = false;
	rightThing = false;

    loadImage();
	loadPlot();

    menuwidget *menu = new menuwidget("snow",this);
    setFocus();
    menu->show();

}

void SceneSnow::loadImage()
{
    backGround.load(":/snow/scene/snow_2.png");
    earth.load(":/snow/scene/snow_1.png");
    player = new QMovie(":/snow/people/snow_right.gif");
    player_left = new QMovie(":/snow/people/snow_left.gif");
	girl.load(":/snow/people/yellow.png");
	conver.load(":/conver/convar/convar.png");
    player->start();
    player_left->start();
}

void SceneSnow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

	QPen pen; //画笔
	pen.setColor(QColor(255, 255, 0));
	QBrush brush(QColor(255, 255, 0, 125)); //画刷
	painter.setPen(pen); //添加画笔
	painter.setBrush(brush); //添加画刷

	painter.setPen(QColor(100, 100, 100));
	QFont font;
	font.setFamily("微软雅黑");
	font.setPointSize(14);	// 大小
	font.setBold(true);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);	// 设置字符间距
	painter.setFont(font);	// 使用字体

    painter.drawImage(backX, backY, backGround);

    if (playerX == 430)   stop = true;

    if (left)
    {
        if ((waitTime>0) && (waitTime <= 30))
			painter.drawPixmap(playerX, 235 - waitTime * 6, 100, 200, player_left->currentPixmap());
		else 
        painter.drawPixmap(playerX, 235, 100, 200, player_left->currentPixmap());
    }
    else
    {
		if ((waitTime>0) && (waitTime <= 30))
			painter.drawPixmap(playerX, 235-waitTime * 6, 100, 200, player->currentPixmap());
		else  painter.drawPixmap(playerX, 235, 100, 200, player->currentPixmap());
    }
    //探索

    painter.drawImage(backX, backY, earth);

	if (waitTime > 30) {
		if (waitTime == 31) {
			ti = qrand() % 7;
			Player::getInstance()->addBagThing(ti + 6);
		}
		painter.drawText(380, 280, get[ti]);
	}

	if (first) painter.drawText(180, 550, begin);
	if ((backX>=-2100)&&(backX<-1500))  painter.drawText(140, 550, begin2);

	painter.setPen(QColor(250, 250, 250));
	if (playerX >= 440) {		
		painter.drawImage(800, 250, girl);
		painter.drawImage(0, 0, conver);
		if (zxLock) {
			painter.drawText(280, 612, record_1);
			painter.drawText(280, 666, record_2);
		}
		else {
			painter.drawText(280, 612, q[talk].s);   f[talk] = true;
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

	painter.setPen(QColor(250, 10, 10));
	if (talk == 35) {
		painter.drawText(350, 280, get[9]);
		if (!ifget) {
			Player::getInstance()->addBagThing(3);
			ifget = true;
		}
	}

	if (talk == 33) {
		if (rightThing) talk = 35;
		else  talk = 39;
	}
	first = false;
}

void SceneSnow::keyPressEvent(QKeyEvent* e)
{
    if (stop)
    {
        switch (e->key())
        {
        case Qt::Key_A:
            backX += 10;
            left = true;
            break;
        case Qt::Key_Left:
            backX += 10;
            left = true;
            break;
        case Qt::Key_D:
            backX -= 10;
            left = false;
            break;
        case Qt::Key_Right:
            backX -= 10;
            left = false;
            break;
        default:
            break;
        }
        if (backX < BDL)
        {
            backX += 10;
            stop = false;
            playerX += 10;
        }
        if (backX > BDR)
        {
            backX -= 10;
            stop = false;
            playerX -= 10;
        }
		if ((e->key() == Qt::Key_W) || (e->key() == Qt::Key_Up)) {
			if (underTheSunshine(2))	waitTime++;
		}
		else waitTime = 0;
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
        if (playerX < 0)  playerX += 10;
        if (playerX > 860)  playerX -= 10;
		if (playerX < 430) first = true;

		if ((e->key() == Qt::Key_W) || (e->key() == Qt::Key_Up)) {
			if (underTheSunshine(1))  waitTime++;
		} else waitTime = 0;


		if ((e->key() == Qt::Key_Space) && (!q[talk].diff))  talk = q[talk].l;
		if (q[talk].diff) {
			if (e->key() == Qt::Key_Z) { talk = q[talk - 1].l;  zxLock = false; }
			if (e->key() == Qt::Key_X) { talk = q[talk].l;  zxLock = false; }
		}

		if (talk == 30) {
			GameWorld::getInstance()->beginBurnBook();
			if (f[4] && f[20]) {
				GainAchieve *Joker = new  GainAchieve(9, this);
				Joker->show();
			}
			else {
				GainAchieve *Joker = new  GainAchieve(10, this);
				Joker->show();
			}
		}
    }
    update();
}

bool SceneSnow::underTheSunshine(int n) {
	if (n == 2) {
		if ((backX >= -60) && (backX <= -10))  return true;
		if ((backX >= -1330) && (backX <= -1270))  return true;
		if ((backX >= -1660) && (backX <= -1620))  return true;
		if ((backX >= -2850) && (backX <= -2800))  return true;
	}
	return false;
}

void SceneSnow::gameOver() {
	gameover = true;
}

void SceneSnow::bagThingClick(int n) {
	if (n == 4) rightThing = true;
}

void SceneSnow::changeState(bool a, bool b, bool c, bool d) {
	statement[1] = a;
	statement[2] = b;
	statement[3] = c;
	statement[4] = d;
}

void SceneSnow::loadPlot() {
	begin = QString::fromLocal8Bit("白茫茫的大地...真干净...只是好冷啊,冷到连我都有触觉");
	begin2 = QString::fromLocal8Bit("唔，远处似乎有烟，应该有人吧...到那里去..到那里去就能活着");

	get[0] = QString::fromLocal8Bit("获得物品 [过期罐头]");
	get[1] = QString::fromLocal8Bit("获得物品  [啤酒]");
	get[2] = QString::fromLocal8Bit("获得物品 [巧克力]");
	get[3] = QString::fromLocal8Bit("获得物品 [病历单]");
	get[4] = QString::fromLocal8Bit("获得物品  [假发]");
	get[5] = QString::fromLocal8Bit("获得物品  [女装]");
	get[6] = QString::fromLocal8Bit("获得物品 [程序之书]");

	get[9]= QString::fromLocal8Bit("获得特殊物品 [红宝石]");


	q[0].s = QString::fromLocal8Bit("（到达房子口，看见一个正在烧书的少女）"); q[0].diff = false; q[0].hu = false;
	q[0].l = 1; q[1].s = QString::fromLocal8Bit("少女：看见了吗？这一定是冬天蚂蚁过冬的方式。"); q[1].diff = false; q[1].hu = false;

	q[1].l = 2; q[2].s = QString::fromLocal8Bit("z. 呼吸，感知，以及死亡。"); q[2].diff = true; q[2].hu = false;
	q[3].s = QString::fromLocal8Bit("x. 存储，囤积，和煎熬。"); q[3].diff = true; q[3].hu = false;

	q[2].l = 4; q[4].s = QString::fromLocal8Bit("少女(轻笑): 是一个很厉害的小妹妹了。"); q[4].diff = false; q[4].hu = false;
	q[3].l = 5; q[5].s = QString::fromLocal8Bit("少女：实际上下一句是呼吸感知以及死亡。"); q[5].diff = false; q[5].hu = false;

	q[4].l = 6; q[5].l = 6; q[6].s = QString::fromLocal8Bit("少女：很冷，一起来烤火吧"); q[6].diff = false; q[6].hu = false;

	q[6].l = 7; q[7].s = QString::fromLocal8Bit("（凑过去，看到一本装订精致的书，虽然看上去"); q[7].diff = false; q[7].hu = true;
	q[8].s = QString::fromLocal8Bit(" 上了年代，却被保护得很好）"); q[8].diff = false; q[8].hu = false;

	q[7].l = 9; q[9].s = QString::fromLocal8Bit("我：这书。。。你不喜欢了吗?"); q[9].diff = false; q[9].hu = false;

	q[9].l = 10; q[10].s = QString::fromLocal8Bit("少女：喜欢啊。。。甚至可以说得上是非常喜欢了。。。"); q[10].diff = false; q[10].hu = true;
	q[11].s = QString::fromLocal8Bit(" （指了指火堆）这里的书我都很喜欢。。"); q[11].diff = false; q[11].hu = false;

	q[10].l = 12; q[12].s = QString::fromLocal8Bit("少女：可是我真的很冷。。。很冷啊"); q[12].diff = false; q[12].hu =false;

	q[12].l = 13; q[13].s = QString::fromLocal8Bit("少女：抱歉，我可能就是这样一个冷漠的人吧。喜欢的东西"); q[13].diff = false; q[13].hu = true;
	q[14].s = QString::fromLocal8Bit("说舍弃就舍弃。辛苦收集的书是如此。。。"); q[14].diff = false; q[14].hu = false;

	q[13].l = 15; q[15].s = QString::fromLocal8Bit("少女：文化的传承也是如此。。。我。。。是不是错了"); q[15].diff = false; q[15].hu = false;

	q[15].l = 16; q[16].s = QString::fromLocal8Bit("z.。。。为了活着而已，根本就没有所谓的对错啊"); q[16].diff = true; q[16].hu = false;
	q[17].s = QString::fromLocal8Bit("x. 可是，你比书更重要。"); q[17].diff = true; q[17].hu = false;

	q[16].l = 18; q[18].s = QString::fromLocal8Bit("少女：是吗。。。。根本没有对错啊。。。反正也是为了活着"); q[18].diff = false; q[18].hu = true;
	q[19].s = QString::fromLocal8Bit("。。。只是活着而已。。。对了，你也来一起烧吧"); q[19].diff = false; q[19].hu = false;

	q[17].l = 20; q[20].s= QString::fromLocal8Bit("少女：我。。。比书更重要？？"); q[20].diff = false; q[20].hu = false;

	q[20].l = 21; q[21].s = QString::fromLocal8Bit("我：因为，书只是记录工具。。。人才是文化真正的传承者啊。"); q[21].diff = false; q[21].hu = true;
	q[22].s = QString::fromLocal8Bit("内化于心，外化于行，才是真正的传承之道！"); q[22].diff = false; q[22].hu = false;

	q[21].l = 23; q[23].s= QString::fromLocal8Bit("少女：。。。谢谢你，帮我解决了困惑很久的问题，火快要熄"); q[23].diff = false; q[23].hu = true;
	q[24].s = QString::fromLocal8Bit("灭了，一起来点燃它吧"); q[24].diff = false; q[24].hu = false;

	q[18].l = 30; q[23].l = 30; 


	q[30].s= QString::fromLocal8Bit("少女：很温暖的火焰啊，像阳光一样。。。虽然我也没见过"); q[30].diff = false; q[30].hu = true;
	q[31].s= QString::fromLocal8Bit("真正的阳光。"); q[31].diff = false; q[31].hu = false;

	q[30].l = 32; q[32].s= QString::fromLocal8Bit("我：没见过阳光？"); q[32].diff = false; q[32].hu = false;

	q[32].l = 33;  q[33].s = QString::fromLocal8Bit("少女：对，我们现在的阳光都已经驳杂了。听说之前的世界"); q[33].diff = false; q[33].hu = true;
	q[34].s = QString::fromLocal8Bit("有着纯净的阳光，温暖的，干净的阳光，可惜没能感受。"); q[34].diff = false; q[34].hu = false;
	q[33].l = 33;

	q[35].s= QString::fromLocal8Bit("少女：这是。。。阳光的味道吗。。很柔软的触感，"); q[35].diff = false; q[35].hu = true;
	q[36].s = QString::fromLocal8Bit("像书籍泛黄的内页。谢谢你，这个送给你吧"); q[36].diff = false; q[36].hu = false;

	q[35].l = 37; q[37].s = QString::fromLocal8Bit("明明没有温度，却像是跳动的火焰一般，灼烧这皮肤，骨骼，甚至心脏。"); q[37].diff = false; q[37].hu = true;
	q[38].s = QString::fromLocal8Bit("炽热的感觉解冻了尘封已久的触感，能感受到世界真好啊"); q[38].diff = false; q[38].hu = false;
	q[37].l = 37;

	q[39].s = QString::fromLocal8Bit("少女：谢谢你的好意。为了感谢你，请在这里多"); q[39].diff = false; q[39].hu = true;
	q[40].s = QString::fromLocal8Bit("停留几日恢复体力吧。"); q[40].diff = false; q[40].hu = false;
	q[39].l = 39;

}

SceneSnow::~SceneSnow()
{
    delete ui;
}
