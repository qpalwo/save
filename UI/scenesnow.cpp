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

	QPen pen; //����
	pen.setColor(QColor(255, 255, 0));
	QBrush brush(QColor(255, 255, 0, 125)); //��ˢ
	painter.setPen(pen); //��ӻ���
	painter.setBrush(brush); //��ӻ�ˢ

	painter.setPen(QColor(100, 100, 100));
	QFont font;
	font.setFamily("΢���ź�");
	font.setPointSize(14);	// ��С
	font.setBold(true);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);	// �����ַ����
	painter.setFont(font);	// ʹ������

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
    //̽��

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
	begin = QString::fromLocal8Bit("��ãã�Ĵ��...��ɾ�...ֻ�Ǻ��䰡,�䵽���Ҷ��д���");
	begin2 = QString::fromLocal8Bit("��Զ���ƺ����̣�Ӧ�����˰�...������ȥ..������ȥ���ܻ���");

	get[0] = QString::fromLocal8Bit("�����Ʒ [���ڹ�ͷ]");
	get[1] = QString::fromLocal8Bit("�����Ʒ  [ơ��]");
	get[2] = QString::fromLocal8Bit("�����Ʒ [�ɿ���]");
	get[3] = QString::fromLocal8Bit("�����Ʒ [������]");
	get[4] = QString::fromLocal8Bit("�����Ʒ  [�ٷ�]");
	get[5] = QString::fromLocal8Bit("�����Ʒ  [Ůװ]");
	get[6] = QString::fromLocal8Bit("�����Ʒ [����֮��]");

	get[9]= QString::fromLocal8Bit("���������Ʒ [�챦ʯ]");


	q[0].s = QString::fromLocal8Bit("�����﷿�ӿڣ�����һ�������������Ů��"); q[0].diff = false; q[0].hu = false;
	q[0].l = 1; q[1].s = QString::fromLocal8Bit("��Ů������������һ���Ƕ������Ϲ����ķ�ʽ��"); q[1].diff = false; q[1].hu = false;

	q[1].l = 2; q[2].s = QString::fromLocal8Bit("z. ��������֪���Լ�������"); q[2].diff = true; q[2].hu = false;
	q[3].s = QString::fromLocal8Bit("x. �洢���ڻ����ͼ尾��"); q[3].diff = true; q[3].hu = false;

	q[2].l = 4; q[4].s = QString::fromLocal8Bit("��Ů(��Ц): ��һ����������С�����ˡ�"); q[4].diff = false; q[4].hu = false;
	q[3].l = 5; q[5].s = QString::fromLocal8Bit("��Ů��ʵ������һ���Ǻ�����֪�Լ�������"); q[5].diff = false; q[5].hu = false;

	q[4].l = 6; q[5].l = 6; q[6].s = QString::fromLocal8Bit("��Ů�����䣬һ���������"); q[6].diff = false; q[6].hu = false;

	q[6].l = 7; q[7].s = QString::fromLocal8Bit("���չ�ȥ������һ��װ�����µ��飬��Ȼ����ȥ"); q[7].diff = false; q[7].hu = true;
	q[8].s = QString::fromLocal8Bit(" ���������ȴ�������úܺã�"); q[8].diff = false; q[8].hu = false;

	q[7].l = 9; q[9].s = QString::fromLocal8Bit("�ң����顣�����㲻ϲ������?"); q[9].diff = false; q[9].hu = false;

	q[9].l = 10; q[10].s = QString::fromLocal8Bit("��Ů��ϲ������������������˵�����Ƿǳ�ϲ���ˡ�����"); q[10].diff = false; q[10].hu = true;
	q[11].s = QString::fromLocal8Bit(" ��ָ��ָ��ѣ���������Ҷ���ϲ������"); q[11].diff = false; q[11].hu = false;

	q[10].l = 12; q[12].s = QString::fromLocal8Bit("��Ů����������ĺ��䡣�������䰡"); q[12].diff = false; q[12].hu =false;

	q[12].l = 13; q[13].s = QString::fromLocal8Bit("��Ů����Ǹ���ҿ��ܾ�������һ����Į���˰ɡ�ϲ���Ķ���"); q[13].diff = false; q[13].hu = true;
	q[14].s = QString::fromLocal8Bit("˵�����������������ռ���������ˡ�����"); q[14].diff = false; q[14].hu = false;

	q[13].l = 15; q[15].s = QString::fromLocal8Bit("��Ů���Ļ��Ĵ���Ҳ����ˡ������ҡ������ǲ��Ǵ���"); q[15].diff = false; q[15].hu = false;

	q[15].l = 16; q[16].s = QString::fromLocal8Bit("z.������Ϊ�˻��Ŷ��ѣ�������û����ν�ĶԴ�"); q[16].diff = true; q[16].hu = false;
	q[17].s = QString::fromLocal8Bit("x. ���ǣ���������Ҫ��"); q[17].diff = true; q[17].hu = false;

	q[16].l = 18; q[18].s = QString::fromLocal8Bit("��Ů�����𡣡���������û�жԴ�����������Ҳ��Ϊ�˻���"); q[18].diff = false; q[18].hu = true;
	q[19].s = QString::fromLocal8Bit("������ֻ�ǻ��Ŷ��ѡ��������ˣ���Ҳ��һ���հ�"); q[19].diff = false; q[19].hu = false;

	q[17].l = 20; q[20].s= QString::fromLocal8Bit("��Ů���ҡ������������Ҫ����"); q[20].diff = false; q[20].hu = false;

	q[20].l = 21; q[21].s = QString::fromLocal8Bit("�ң���Ϊ����ֻ�Ǽ�¼���ߡ������˲����Ļ������Ĵ����߰���"); q[21].diff = false; q[21].hu = true;
	q[22].s = QString::fromLocal8Bit("�ڻ����ģ��⻯���У����������Ĵ���֮����"); q[22].diff = false; q[22].hu = false;

	q[21].l = 23; q[23].s= QString::fromLocal8Bit("��Ů��������лл�㣬���ҽ��������ܾõ����⣬���ҪϨ"); q[23].diff = false; q[23].hu = true;
	q[24].s = QString::fromLocal8Bit("���ˣ�һ������ȼ����"); q[24].diff = false; q[24].hu = false;

	q[18].l = 30; q[23].l = 30; 


	q[30].s= QString::fromLocal8Bit("��Ů������ů�Ļ��氡��������һ����������Ȼ��Ҳû����"); q[30].diff = false; q[30].hu = true;
	q[31].s= QString::fromLocal8Bit("���������⡣"); q[31].diff = false; q[31].hu = false;

	q[30].l = 32; q[32].s= QString::fromLocal8Bit("�ң�û�������⣿"); q[32].diff = false; q[32].hu = false;

	q[32].l = 33;  q[33].s = QString::fromLocal8Bit("��Ů���ԣ��������ڵ����ⶼ�Ѿ������ˡ���˵֮ǰ������"); q[33].diff = false; q[33].hu = true;
	q[34].s = QString::fromLocal8Bit("���Ŵ��������⣬��ů�ģ��ɾ������⣬��ϧû�ܸ��ܡ�"); q[34].diff = false; q[34].hu = false;
	q[33].l = 33;

	q[35].s= QString::fromLocal8Bit("��Ů�����ǡ����������ζ���𡣡�������Ĵ��У�"); q[35].diff = false; q[35].hu = true;
	q[36].s = QString::fromLocal8Bit("���鼮���Ƶ���ҳ��лл�㣬����͸����"); q[36].diff = false; q[36].hu = false;

	q[35].l = 37; q[37].s = QString::fromLocal8Bit("����û���¶ȣ�ȴ���������Ļ���һ�㣬������Ƥ�����������������ࡣ"); q[37].diff = false; q[37].hu = true;
	q[38].s = QString::fromLocal8Bit("���ȵĸо��ⶳ�˳����ѾõĴ��У��ܸ��ܵ�������ð�"); q[38].diff = false; q[38].hu = false;
	q[37].l = 37;

	q[39].s = QString::fromLocal8Bit("��Ů��лл��ĺ��⡣Ϊ�˸�л�㣬���������"); q[39].diff = false; q[39].hu = true;
	q[40].s = QString::fromLocal8Bit("ͣ�����ջָ������ɡ�"); q[40].diff = false; q[40].hu = false;
	q[39].l = 39;

}

SceneSnow::~SceneSnow()
{
    delete ui;
}
