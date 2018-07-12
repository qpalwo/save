#include "scenedesert.h"
#include "ui_scenedesert.h"
#include "UI/UiManager.h"


SceneDesert::SceneDesert(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SceneDesert) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

	Player::getInstance()->setMapStaus(1);

	backX = 0;   backY = 0;
	playerX = 0;
	talk = 0;
	ti = 0;

	first = false;
	stop = false;
	left = false;
	zxFuck = false;
	zhu = false;
	gameover = false;

	loadImage();
	loadPlot();

	menuwidget *menu = new menuwidget("desert",this);
	setFocus();
	menu->show();

	setMouseTracking(true);     //ţ��    ���ð��������ܼ����λ��

	v = GameWorld::getInstance()->getVolume();//get volume
	bgm = new QMediaPlayer();//new
	bgm->setMedia(QUrl("qrc://res/music/beginning_bgm.mp3"));//music set
	bgm->setVolume(v);//set volume
	bgm->play();//play music


	myCursor = new QCursor(QPixmap(":/mouse/pointer_3.png"));//new cursor
	this->setCursor(*myCursor);//set cursor
}

void SceneDesert::loadImage() {
	backGround.load(":/desertB/scene/desert_1.png");
	earth.load(":/desertB/scene/desert_2.png");
	boat.load(":/desertB/scene/desert_boat.png");
	illustrate.load(":/ruins/scene/illustrate_desert.png");
	player = new QMovie(":/player/main.gif");
	player_left = new QMovie(":/player/main_left.gif");
	uncle.load(":/uncle.png");
	conver.load(":/conver/convar/convar.png");
	player->start();
	player_left->start();
}

void SceneDesert::paintEvent(QPaintEvent * e) {

	if ((talk == 44) || (talk == 34)) tomap = true;

	QPainter painter(this);
	QPen pen; //����
	pen.setColor(QColor(255, 255, 0));
	QBrush brush(QColor(255, 255, 0, 125)); //��ˢ
	painter.setPen(pen); //��ӻ���
	painter.setBrush(brush); //��ӻ�ˢ

	painter.drawImage(backX, backY, backGround);

	painter.setPen(QColor(250, 255, 250));
	QFont font;
	font.setFamily("΢���ź�");
	font.setPointSize(14);	// ��С
	font.setBold(true);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);	// �����ַ����
	painter.setFont(font);	// ʹ������

	if (playerX == 430)  stop = true;

	if (talk < 12) {
		if (left) painter.drawPixmap(playerX, 250, 100, 200, player_left->currentPixmap());
		else painter.drawPixmap(playerX, 250, 100, 200, player->currentPixmap());
	} else {
        painter.drawImage(210, 70, boat);
		painter.drawPixmap(720, 250, 100, 200, player_left->currentPixmap());
	}
    painter.drawImage(backX, backY, earth);

	if ((waitTime>0)&&(waitTime<=28))
		painter.drawRect(playerX, 260, 10+waitTime*3, 20); //���ƾ��� 

	if (waitTime > 28) {
		if (waitTime == 29) {
			ti = qrand() % 7;
			Player::getInstance()->addBagThing(ti + 6);
		}
		painter.drawText(380, 280, get[ti]);
	}

	if (first) { 
		painter.drawText(180, 140, begin);
		painter.drawText(320, 180, begin2);
		painter.drawImage(0, 430, illustrate);
	 }

		if (talk == 28) 
			if (zhu) talk = 40; else talk = 30;

	if (playerX >= 440) {
		painter.drawImage(850, 260, uncle);
		painter.drawImage(0, 0, conver);
		if (zxFuck) {
			painter.drawText(280, 612, record_1);
			painter.drawText(280, 666, record_2);
		}
		else {
			painter.drawText(280, 612, q[talk].s);  f[talk] = true;
			if (q[talk].hu) {
				painter.drawText(280, 666, q[talk + 1].s);
			}
			if (q[talk].diff) {
				record_1 = q[talk].s;
				record_2 = q[talk + 1].s;
				talk++;
				painter.drawText(280, 666, q[talk].s);
				zxFuck = true;
			}
		}
	}

	if (talk == 42) {
		painter.setPen(QColor(0, 255, 250));
		painter.drawText(360, 280, get[9]);
		if (!ifget) {
			Player::getInstance()->addBagThing(5);
			ifget = true;
		}
	}
	first = false;
}

void SceneDesert::keyPressEvent(QKeyEvent *e) {
	if (tomap) UiManager::getInstance()->fromDesertToMap();

	if (stop) {                         //main player stop
		switch (e->key()) {
		case Qt::Key_A: backX += 10;  left = true; break;
		case Qt::Key_Left: backX += 10; left = true; break;
		case Qt::Key_D: backX -= 10;  left = false;  break;
		case Qt::Key_Right: backX -= 10;  left = false;  break;
		}

		if ((e->key() == Qt::Key_S)|| (e->key() == Qt::Key_Down)) {
			if (underTheTree(2))	waitTime++;
		}	else waitTime = 0;

		if (backX < BDL) { backX += 10;  stop = false; playerX += 10; }
		if (backX > BDR) { backX -= 10;   stop = false; playerX -= 10; }
	}
	else {                                // back stop
		switch (e->key()) {
		case Qt::Key_A: playerX -= 10;  left = true;  break;
		case Qt::Key_Left: playerX -= 10;  left = true; break;
		case Qt::Key_D: playerX += 10; left = false; break;
		case Qt::Key_Right: playerX += 10; left = false; break;
		}
		if ((e->key() == Qt::Key_S) || (e->key() == Qt::Key_Down)) {
			if (underTheTree(1))  waitTime++;
		} else waitTime = 0;

		if (playerX < 430) first = true;

		if ((e->key() == Qt::Key_Space) && (!q[talk].diff))
			talk = q[talk].l;

		if (q[talk].diff) {
			if (e->key() == Qt::Key_Z) { talk = q[talk - 1].l;  zxFuck = false; }
			if (e->key() == Qt::Key_X) { talk = q[talk].l;  zxFuck = false; }
		}

		if (f[9] && (talk == 23)) {
			GainAchieve *Joker = new  GainAchieve(5, this);
			Joker->show();
		}
		if (talk==44) {
			GainAchieve *Joker = new  GainAchieve(6, this);
			Joker->show();
		}

		if ((talk == 41)||(talk==32))  GameWorld::getInstance()->beginAvoidStorm();
	

		if (playerX < 0) { playerX += 10; }
		if (playerX > 860) { playerX -= 10; }
	}
	
	update();
}

bool SceneDesert::underTheTree(int n) {
	if (n == 1) {
		if ((playerX >= 280) && (playerX <= 310))  return true;
		if ((playerX >= 490) && (playerX <= 520))  return true;
	}
	if (n == 2) {
		if ((backX >= -890) && (backX <= -860))  return true;
		if ((backX >= -1630) && (backX <= -1580))  return true;
	}
	return false;
}

void SceneDesert::gameOver() {
	gameover = true;
}

void SceneDesert::bagThingClick(int n) {
	if (n == 2) zhu = true;
}

void SceneDesert::changeState(bool a,bool b,bool c,bool d) {
	statement[1] = a;
	statement[2] = b;
	statement[3] = c;
	statement[4] = d;
}


void SceneDesert::loadPlot() {
	begin = QString::fromLocal8Bit("���ȵĸо�������͸���������������������ں������");
	begin2 = QString::fromLocal8Bit("�øϿ��Ҹ��ط���Ϣһ��");

	get[0] = QString::fromLocal8Bit("�����Ʒ [���ڹ�ͷ]");	
	get[1] = QString::fromLocal8Bit("�����Ʒ  [ơ��]");
	get[2] = QString::fromLocal8Bit("�����Ʒ [�ɿ���]");
	get[3] = QString::fromLocal8Bit("�����Ʒ [������]");
	get[4] = QString::fromLocal8Bit("�����Ʒ  [�ٷ�]");
	get[5] = QString::fromLocal8Bit("�����Ʒ  [Ůװ]");
	get[6] = QString::fromLocal8Bit("�����Ʒ [����֮��]");
	get[9] = QString::fromLocal8Bit("���������Ʒ [����]");


	q[0].s = QString::fromLocal8Bit("���壺С�����������ط���ʲô"); 	q[0].diff = false; q[0].hu = false;

	 q[0].l = 1;   q[1].s = QString::fromLocal8Bit("z. �����������");   q[1].diff = true;  q[1].hu = false;
	 q[0].r = 2;   q[2].s = QString::fromLocal8Bit("x. (��˵��)");          q[2].diff = true; q[2].hu = false;

	 q[1].l = 3;   q[3].s = QString::fromLocal8Bit("���壺��Ů�黳����ʫ�����ʹ���һ����");   q[3].diff = false; q[3].hu = false;

	 q[2].l = 4;  q[4].s = QString::fromLocal8Bit("���壺С���ﻹͦ���ߵġ�");      q[4].diff = false;  q[4].hu = false;

	q[3].l = 5;  q[4].l = 5;  q[5].s = QString::fromLocal8Bit("���壺�ߣ��������ȥ��䣨�ͳ�һϵ��֤������, �Ҳ��ǻ�");  q[5].diff = false;  q[5].hu = true;
	q[5].l = 6;  q[6].s = QString::fromLocal8Bit("��(�չ�ȥһ������ʻ֤,ѧ��֤,һ����ֵĶ�������Ƭ...");   q[6].diff = false;  q[6].hu = false;
	
	q[6].l = 7;  q[7].s = QString::fromLocal8Bit("z. ѯ����ֵĶ�����ʲô");      q[7].diff = true; q[7].hu = false;
	q[6].r = 8;  q[8].s = QString::fromLocal8Bit("x. ��ѯ��");      q[8].diff = true; q[8].hu = false;

	q[7].l = 9;  q[9].s = QString::fromLocal8Bit("���壺��ֵĶ���������������ɲ���ʲô��ֵĶ���, ����");  q[9].diff = false;  q[9].hu = true;
	q[9].l = 10; q[10].s= QString::fromLocal8Bit("�󱦱���������ô���۹⣬����������ȥ�ι�һ�¡�"); q[10].diff = false;  q[10].hu = false;

	q[8].l = 11; q[11].s = QString::fromLocal8Bit("���壺�߰ɣ�������������ˡ�"); q[11].diff = false;  q[11].hu = false;

	q[10].l = 12; q[11].l = 12;  q[12].s = QString::fromLocal8Bit("����ʹ���һ���ߵ�����ֵĶ�������ǰ�����ִ���");  q[12].diff = false;  q[12].hu = false; 

	q[12].l = 13; q[13].s = QString::fromLocal8Bit("���壺��ô�����ǲ����ر�ÿ�~");  q[13].diff = false;  q[13].hu = false;

	q[13].l = 14; q[14].s = QString::fromLocal8Bit("�ң��Ǻ���������������ʲô��");  q[14].diff = false;  q[14].hu = false;

	q[14].l = 15;  q[15].s = QString::fromLocal8Bit("����:��д�,�˷�����,����ֱǰ,����η�壡����ɫ�󺣵�ӵ��");  q[15].diff = false;  q[15].hu = true;
    q[16].s = QString::fromLocal8Bit("�Ǻ���Ľᾧ��������̫̫̫үү��ʱ��,���ǳ˴�����ն��...."); q[16].diff = false;  q[16].hu = false;

	q[15].l = 17; q[17].s = QString::fromLocal8Bit("�ң�(��ϣ��������ں�����ǰ�������Ѿ�û�к��ˡ�"); q[17].diff = false;  q[17].hu = false;

	q[17].l = 18; q[18].s = QString::fromLocal8Bit("���壺��˵��������һֱ�ڣ������ڣ��һ��ڣ���ô��˵��"); q[18].diff = false;  q[18].hu = true;
    q[19].s = QString::fromLocal8Bit("��û�����أ�����");  q[19].diff = false;  q[19].hu = false;

	q[18].l = 20; q[20].s= QString::fromLocal8Bit("z.�ɴ��Ѿ���ʻ����,�޷����˰�..���ܺ��еĴ�,����������");  q[20].diff = true;  q[20].hu = false;
    q[21].s = QString::fromLocal8Bit("x.�ǰ�����ʹ�Ѿ���ʧ����ʼ�����˼ǵ�.���˼ǵñ㲻����ʧ");  q[21].diff = true;  q[21].hu = false;

	q[20].l = 22; q[22].s = QString::fromLocal8Bit("���壺˭˵�����ܺ��У�Ҫ������л��ֳ��˵����⣬������");  q[22].diff = false;  q[22].hu = false;

	q[21].l = 23; q[23].s = QString::fromLocal8Bit("���壺ֻҪ�ǵã��㲻����ʧ��ֻҪ���ڹ������м�ֵ......");  q[23].diff = false;  q[23].hu = true;
    q[24].s = QString::fromLocal8Bit("���������Ϊ��ȱ��һ����л��ֵ����ӣ�����������һ���ʻ");  q[24].diff = false;  q[24].hu = false;

	q[22].l = 25; q[23].l = 25;  q[25].s = QString::fromLocal8Bit("���壺(̾��)��ô�����˰�...��һ��������ɳĮ����ô������");q[25].diff = false;  q[25].hu = true;
    q[26].s= QString::fromLocal8Bit("Ϊʲô���ǲ�һ��...�Ͳ���ôһ��...�ѵ������Ҫ������"); q[26].diff = false;  q[26].hu = false;

	q[25].l = 27; q[27].s = QString::fromLocal8Bit("�ң�(������л��ֵ�����...����������ʲô������"); q[27].diff = false;  q[27].hu = false;
	q[27].l = 28; q[28].l = 28;

    q[30].s = QString::fromLocal8Bit("���壺��Ȼû��ʲô�ã�������лл�㰡"); q[30].diff = false;  q[30].hu = false;
	q[30].l = 31;  q[31].s = QString::fromLocal8Bit("���壺�һ�������һ�Ρ���ʹ���ܲ���ɹ���������������һ��"); q[31].diff = false;  q[31].hu = false;

	q[31].l = 32; q[32].s = QString::fromLocal8Bit("���壺�����������ǽ����˰�������������Ҳ��ʻ����"); q[32].diff = false;  q[32].hu = true;
	q[33].s= QString::fromLocal8Bit("����֤���������п��ܵģ��ٴ��д������п��ܵģ�"); q[33].diff = false;  q[33].hu = false;

	q[32].l = 34;  q[34].s = QString::fromLocal8Bit("���壺ֻ�ǿ�ϧ����ôһ�㡣���������Ͳ���ôһ��"); q[34].diff = false;  q[34].hu = false;
	q[34].l = 34;

	q[40].s= QString::fromLocal8Bit("���壺�����������������������Ҿ�Ҫ�ɹ��ˣ�����������"); q[40].diff = false;  q[40].hu =true;
	q[40].l = 41;  q[41].s = QString::fromLocal8Bit("�󺣵��ٻ�!"); q[41].diff = false;  q[41].hu = false;

	q[41].l = 42;  q[42].s = QString::fromLocal8Bit("���壺лл�㣬С�������͸����"); q[42].diff = false;  q[42].hu = false;

	q[42].l = 43;  q[43].s = QString::fromLocal8Bit("���壺��������,���Ǻ��������������������������ò�Ϣ��"); q[43].diff = false;  q[43].hu = false;
	q[43].l = 44; q[44].l = 44;
}

void SceneDesert::mouseMoveEvent(QMouseEvent* event)
{
	//QPoint m = event->pos();
	//mouse = QString::number(m.x()) +'  ' + QString::number(m.y());

	mouse = event->pos();

    //	mouse_out = QString::number(event->x()) + '  ' + QString::number(event->y());
}

void SceneDesert::on_bag_clicked() {
	//QDialog *dlg = new QDialog(this);
	//dlg->show();
}

SceneDesert::~SceneDesert() {
	delete ui;
}
