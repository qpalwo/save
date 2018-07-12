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

	setMouseTracking(true);     //牛逼    不用按下鼠标就能监控其位置

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
	QPen pen; //画笔
	pen.setColor(QColor(255, 255, 0));
	QBrush brush(QColor(255, 255, 0, 125)); //画刷
	painter.setPen(pen); //添加画笔
	painter.setBrush(brush); //添加画刷

	painter.drawImage(backX, backY, backGround);

	painter.setPen(QColor(250, 255, 250));
	QFont font;
	font.setFamily("微软雅黑");
	font.setPointSize(14);	// 大小
	font.setBold(true);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);	// 设置字符间距
	painter.setFont(font);	// 使用字体

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
		painter.drawRect(playerX, 260, 10+waitTime*3, 20); //绘制矩形 

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
	begin = QString::fromLocal8Bit("炎热的感觉。。。透不过气。。。就像是溺在海里。。。");
	begin2 = QString::fromLocal8Bit("得赶快找个地方休息一下");

	get[0] = QString::fromLocal8Bit("获得物品 [过期罐头]");	
	get[1] = QString::fromLocal8Bit("获得物品  [啤酒]");
	get[2] = QString::fromLocal8Bit("获得物品 [巧克力]");
	get[3] = QString::fromLocal8Bit("获得物品 [病历单]");
	get[4] = QString::fromLocal8Bit("获得物品  [假发]");
	get[5] = QString::fromLocal8Bit("获得物品  [女装]");
	get[6] = QString::fromLocal8Bit("获得物品 [程序之书]");
	get[9] = QString::fromLocal8Bit("获得特殊物品 [海螺]");


	q[0].s = QString::fromLocal8Bit("大叔：小姑娘，来这荒凉地方干什么"); 	q[0].diff = false; q[0].hu = false;

	 q[0].l = 1;   q[1].s = QString::fromLocal8Bit("z. 我是来体验的");   q[1].diff = true;  q[1].hu = false;
	 q[0].r = 2;   q[2].s = QString::fromLocal8Bit("x. (不说话)");          q[2].diff = true; q[2].hu = false;

	 q[1].l = 3;   q[3].s = QString::fromLocal8Bit("大叔：少女情怀总是诗啊，和大叔一样！");   q[3].diff = false; q[3].hu = false;

	 q[2].l = 4;  q[4].s = QString::fromLocal8Bit("大叔：小姑娘还挺害羞的。");      q[4].diff = false;  q[4].hu = false;

	q[3].l = 5;  q[4].l = 5;  q[5].s = QString::fromLocal8Bit("大叔：走！大叔带你去逛逛（掏出一系列证件）看, 我不是坏");  q[5].diff = false;  q[5].hu = true;
	q[5].l = 6;  q[6].s = QString::fromLocal8Bit("人(凑过去一看）驾驶证,学生证,一张奇怪的东西的照片...");   q[6].diff = false;  q[6].hu = false;
	
	q[6].l = 7;  q[7].s = QString::fromLocal8Bit("z. 询问奇怪的东西是什么");      q[7].diff = true; q[7].hu = false;
	q[6].r = 8;  q[8].s = QString::fromLocal8Bit("x. 不询问");      q[8].diff = true; q[8].hu = false;

	q[7].l = 9;  q[9].s = QString::fromLocal8Bit("大叔：奇怪的东西？哈哈哈，这可不是什么奇怪的东西, 这是");  q[9].diff = false;  q[9].hu = true;
	q[9].l = 10; q[10].s= QString::fromLocal8Bit("大宝贝。看你这么有眼光，我破例带你去参观一下。"); q[10].diff = false;  q[10].hu = false;

	q[8].l = 11; q[11].s = QString::fromLocal8Bit("大叔：走吧，这热浪真可溺人。"); q[11].diff = false;  q[11].hu = false;

	q[10].l = 12; q[11].l = 12;  q[12].s = QString::fromLocal8Bit("结果和大叔一起走到了奇怪的东西的面前（出现船）");  q[12].diff = false;  q[12].hu = false; 

	q[12].l = 13; q[13].s = QString::fromLocal8Bit("大叔：怎么样？是不是特别好看~");  q[13].diff = false;  q[13].hu = false;

	q[13].l = 14; q[14].s = QString::fromLocal8Bit("我：是很厉害。。。这是什么呢");  q[14].diff = false;  q[14].hu = false;

	q[14].l = 15;  q[15].s = QString::fromLocal8Bit("大叔:这叫船,乘风破浪,勇往直前,无所畏惧！是蓝色大海的拥护");  q[15].diff = false;  q[15].hu = true;
    q[16].s = QString::fromLocal8Bit("是海洋的结晶！早在我太太太爷爷的时候,他们乘船披荆斩棘...."); q[16].diff = false;  q[16].hu = false;

	q[15].l = 17; q[17].s = QString::fromLocal8Bit("我：(打断）可是早在很早以前世界上已经没有海了。"); q[17].diff = false;  q[17].hu = false;

	q[17].l = 18; q[18].s = QString::fromLocal8Bit("大叔：胡说！海明明一直在，船还在，我还在，怎么能说，"); q[18].diff = false;  q[18].hu = true;
    q[19].s = QString::fromLocal8Bit("海没有了呢？？！");  q[19].diff = false;  q[19].hu = false;

	q[18].l = 20; q[20].s= QString::fromLocal8Bit("z.可船已经行驶不了,无法起航了啊..不能航行的船,还有意义吗");  q[20].diff = true;  q[20].hu = false;
    q[21].s = QString::fromLocal8Bit("x.是啊，即使已经消失，但始终有人记得.有人记得便不会消失");  q[21].diff = true;  q[21].hu = false;

	q[20].l = 22; q[22].s = QString::fromLocal8Bit("大叔：谁说船不能航行！要不是轴承滑轮出了点问题，，，唉");  q[22].diff = false;  q[22].hu = false;

	q[21].l = 23; q[23].s = QString::fromLocal8Bit("大叔：只要记得，便不会消失，只要存在过，就有价值......");  q[23].diff = false;  q[23].hu = true;
    q[24].s = QString::fromLocal8Bit("如果不是因为船缺少一个轴承滑轮的珠子，真想邀请你一起驾驶");  q[24].diff = false;  q[24].hu = false;

	q[22].l = 25; q[23].l = 25;  q[25].s = QString::fromLocal8Bit("大叔：(叹气)这么多年了啊...我一个人在这沙漠里这么多年了");q[25].diff = false;  q[25].hu = true;
    q[26].s= QString::fromLocal8Bit("为什么还是差一点...就差那么一点...难道我真的要放弃吗"); q[26].diff = false;  q[26].hu = false;

	q[25].l = 27; q[27].s = QString::fromLocal8Bit("我：(唔，，轴承滑轮的问题...看看包里有什么东西吧"); q[27].diff = false;  q[27].hu = false;
	q[27].l = 28; q[28].l = 28;

    q[30].s = QString::fromLocal8Bit("大叔：虽然没有什么用，但还是谢谢你啊"); q[30].diff = false;  q[30].hu = false;
	q[30].l = 31;  q[31].s = QString::fromLocal8Bit("大叔：我还是想试一次。即使可能不会成功，但还是想启航一次"); q[31].diff = false;  q[31].hu = false;

	q[31].l = 32; q[32].s = QString::fromLocal8Bit("大叔：船。。。还是解体了啊。。。但是我也驾驶过，"); q[32].diff = false;  q[32].hu = true;
	q[33].s= QString::fromLocal8Bit("至少证明，还是有可能的！再次行船还是有可能的！"); q[33].diff = false;  q[33].hu = false;

	q[32].l = 34;  q[34].s = QString::fromLocal8Bit("大叔：只是可惜差那么一点。。。。。就差那么一点"); q[34].diff = false;  q[34].hu = false;
	q[34].l = 34;

	q[40].s= QString::fromLocal8Bit("大叔：是它！就是它！哈哈哈，我就要成功了！！听见了吗，"); q[40].diff = false;  q[40].hu =true;
	q[40].l = 41;  q[41].s = QString::fromLocal8Bit("大海的召唤!"); q[41].diff = false;  q[41].hu = false;

	q[41].l = 42;  q[42].s = QString::fromLocal8Bit("大叔：谢谢你，小姑娘。这个送给你吧"); q[42].diff = false;  q[42].hu = false;

	q[42].l = 43;  q[43].s = QString::fromLocal8Bit("大叔：听见了吗,这是海的心脏跳动的声音。。。经久不息。"); q[43].diff = false;  q[43].hu = false;
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
