#include "sceneforest.h"
#include "ui_sceneforest.h"

SceneForest::SceneForest(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SceneForest) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

	backX = 0;   backY = 0;
	playerX = 0;
	talk = 0;
	first = false;
	stop = false;
	left = false;
	zxFuck = false;
	rightThing = false;

	loadImage();
	loadPlot();

	menuwidget *menu = new menuwidget("forest",this);
	setFocus();
	menu->show();

	setMouseTracking(true);     //牛逼    不用按下鼠标就能监控其位置
}

void SceneForest::loadImage() {
	backGround.load(":/scene/forest_1.png");
	earth.load(":/scene/forest_2.png");
	player = new QMovie(":/people/forest_right.gif");
	player_left = new QMovie(":/people/forest_left.gif");
	uncle.load(":/people/young_right.png");
	house_closed.load(":/scene/forest_house_close.png");
	house_open.load(":/scene/forest_house_open.png");

	conver.load(":/conver/convar/convar.png");
	player->start();
	player_left->start();
}

void SceneForest::paintEvent(QPaintEvent * e) {
	QPainter painter(this);
	QPen pen; //画笔
	pen.setColor(QColor(255, 255, 0));
	QBrush brush(QColor(255, 255, 0, 125)); //画刷
	painter.setPen(pen); //添加画笔
	painter.setBrush(brush); //添加画刷

	painter.setPen(QColor(100, 100, 20));
	QFont font;
	font.setFamily("微软雅黑");
	font.setPointSize(14);	// 大小
	font.setBold(true);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);	// 设置字符间距
	painter.setFont(font);	// 使用字体

	painter.drawImage(backX, backY, backGround);

	if (playerX == 430)  stop = true;

	if (left) painter.drawPixmap(playerX, 235, 100, 200, player_left->currentPixmap());
	else painter.drawPixmap(playerX, 235, 100, 200, player->currentPixmap());
	painter.drawImage(backX, backY, earth);

	if ((waitTime>0) && (waitTime <= 28))
		painter.drawRect(playerX, 260, 10 + waitTime * 3, 20); //绘制矩形 

	if (waitTime > 28) {
		if (waitTime == 29) {
			ti = qrand() % 7;
			Player::getInstance()->addBagThing(ti + 6);
		}
		painter.drawText(380, 280, get[ti]);
	}

	if (first) 	painter.drawText(180, 150, begin);

	painter.setPen(QColor(250, 250, 250));

	if (talk == 2) 	playerX =560;
	else if (talk == 14) playerX = 630;

	if (talk >= 16) { 
		painter.drawImage(580, 240, uncle); 
	}	else	if (talk>=12) painter.drawImage(400, 240, uncle);

	if (playerX >= 440) {

		painter.drawImage(BDL, -10, house_closed);

		painter.drawImage(0, 0, conver);
		if (zxFuck) {
			painter.drawText(280, 612, record_1); 
	    	painter.drawText(280, 666, record_2);
		}
		else {
			painter.drawText(280, 612, q[talk].s);        f[talk] = true;
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

	if (talk == 48) {
		if (rightThing) talk = 49;
		else talk = 55;
	}
	if (talk == 53) {
		painter.setPen(QColor(0, 0, 250));
		painter.drawText(300, 280, get[9]);
		if (!ifget) {
			Player::getInstance()->addBagThing(4);
			ifget = true;
		}
	}
	first = false; 
}

void SceneForest::keyPressEvent(QKeyEvent *e) {
	if (stop) {                         //main player stop
		switch (e->key()) {
		case Qt::Key_A: backX += 10;  left = true; break;
		case Qt::Key_Left: backX += 10; left = true; break;
		case Qt::Key_D: backX -= 10;  left = false;  break;
		case Qt::Key_Right: backX -= 10;  left = false;  break;
		}

		if ((e->key() == Qt::Key_S) || (e->key() == Qt::Key_Down)) {
			if (underTheTree(2))	waitTime++;
		}
		else waitTime = 0;

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
			if (underTheTree(1))	waitTime++;
		}	else waitTime = 0;

		if (playerX < 430) first = true;

		if (talk == 53) {
			if (f[8] && f[20] && f[26] && f[44] && f[52]) {
				GainAchieve *Joker = new  GainAchieve(7, this);
				Joker->show();
			}
			else {
				GainAchieve *Joker = new  GainAchieve(8, this);
				Joker->show();
			}
		}
		if (talk == 55) {
			GainAchieve *Joker = new  GainAchieve(8, this);
			Joker->show();
		}

		if (playerX >= 440) {
			if ((e->key() == Qt::Key_Space) && (!q[talk].diff))	talk = q[talk].l;
			if (q[talk].diff) {
				if (e->key() == Qt::Key_Z) { talk = q[talk - 1].l;  zxFuck = false; }
				if (e->key() == Qt::Key_X) { talk = q[talk].l;  zxFuck = false; }
			}
		}

		if (talk==46) GameWorld::getInstance()->beginSmellCollect();

		if (playerX < 0) { playerX += 10; }
		if (playerX > 860) { playerX -= 10; }
	}
	
	update();
}

bool SceneForest::underTheTree(int n) {
	if (n == 1) {
		if ((playerX >= 90) && (playerX <= 120))  return true;
	}
	if (n == 2) {
		if ((backX >= -360) && (backX <= -330))  return true;
		if ((backX >= -1420) && (backX <= -1390))  return true;
		if ((backX >= -2050) && (backX <= -2020))  return true;
		if ((backX >= -2580) && (backX <= -2550))  return true;
	}
	return false;
}

void SceneForest::gameOver() {
	gameover = true;
}

void SceneForest::bagThingClick(int n) {
	if (n == 5) rightThing = true;
}

void SceneForest::changeState(bool a, bool b, bool c, bool d) {
	statement[1] = a;
	statement[2] = b;
	statement[3] = c;
	statement[4] = d;
}

void SceneForest::loadPlot() {

	begin = QString::fromLocal8Bit("这就是森林吗....为什么会有花....不是早就灭绝了吗");

	get[0] = QString::fromLocal8Bit("获得物品 [过期罐头]");
	get[1] = QString::fromLocal8Bit("获得物品  [啤酒]");
	get[2] = QString::fromLocal8Bit("获得物品 [巧克力]");
	get[3] = QString::fromLocal8Bit("获得物品 [病历单]");
	get[4] = QString::fromLocal8Bit("获得物品  [假发]");
	get[5] = QString::fromLocal8Bit("获得物品  [女装]");
	get[6] = QString::fromLocal8Bit("获得物品 [程序之书]");
	get[9] = QString::fromLocal8Bit("获得特殊物品 [一罐阳光]");


	q[0].s = QString::fromLocal8Bit("这里面是花园吗。。。。似乎有点小啊。。。"); q[0].diff = false; q[0].hu = true;
	q[1].s = QString::fromLocal8Bit("而且为什么是罩在玻璃罩里面。。。。"); q[1].diff = false; q[1].hu = false;

	q[0].l = 2; q[2].s = QString::fromLocal8Bit("（小心的从一扇门里挤了进去）"); q[2].diff = false; q[2].hu = false;

	q[2].l = 3; q[3].s = QString::fromLocal8Bit("好多花。。。可是为什么都一模一样。。。"); q[3].diff = false; q[3].hu = true;
	q[4].s = QString::fromLocal8Bit("似乎没有落脚的地方啊"); q[4].diff = false; q[4].hu = false;

	q[3].l = 5;   q[5].s = QString::fromLocal8Bit("z. 直接踩在花丛上");   q[5].diff = true;  q[5].hu = false;
	q[6].s = QString::fromLocal8Bit("x. 再仔细找找其他的路径");          q[6].diff = true; q[6].hu = false;

	q[5].l = 7;   q[7].s = QString::fromLocal8Bit("唔，没办法了，只好踩上去啊");   q[7].diff = false; q[7].hu = false;

	q[6].l = 8;  q[8].s = QString::fromLocal8Bit("似乎没有其它路了。。。。");      q[8].diff = false;  q[8].hu = false;

	q[7].l = 9; q[9].s = QString::fromLocal8Bit("（出现气急败坏的声音）");   q[9].diff = false; q[9].hu = true;
	q[10].s = QString::fromLocal8Bit("是谁允许你踩我精心培育的的花朵！！！"); q[10].diff = false; q[10].hu = false;

	q[8].l = 11; q[11].s = QString::fromLocal8Bit("(出现声音) 小朋友，别找了，这里可没有路。");   q[11].diff = false; q[11].hu = false;

	q[9].l = 12;  q[11].l = 12;  q[12].s = QString::fromLocal8Bit("（出现病弱青年）"); q[12].diff = false; q[12].hu = true;
	q[13].s = QString::fromLocal8Bit("青年：这里可是我的心血之地，当然不能从这里走过。"); q[13].diff = false; q[13].hu = false;

	q[12].l = 14; q[14].s = QString::fromLocal8Bit("要想进去，跟我来吧。"); q[14].diff = false; q[14].hu = true;
	q[15].s = QString::fromLocal8Bit("（跟上青年的脚步，在一串绕路后从另一个门走了进去）"); q[15].diff = false; q[15].hu = false;

	q[14].l = 16; q[16].s = QString::fromLocal8Bit("青年（深呼吸）：怎么样？这里好看吗？我是不是完美地复原了"); q[16].diff = false; q[16].hu = true;
	q[17].s = QString::fromLocal8Bit("花朵的模样？还有气味，我赋予了他们各种各样的气味！"); q[17].diff = false; q[17].hu = false;

	q[16].l = 18; q[18].s = QString::fromLocal8Bit("z. 是。。。这里像一座博物馆"); q[18].diff = true;  q[18].hu = false;
	q[19].s = QString::fromLocal8Bit("x. 这里。。。像一座实验基地"); q[19].diff = true;  q[19].hu = false;

	q[18].l = 20; q[20].s = QString::fromLocal8Bit("青年(微笑):对，这里就是一座博物馆，你知道这里的藏品是"); q[20].diff = false;  q[20].hu = true;
	q[21].s = QString::fromLocal8Bit("什么吗？"); q[21].diff = false;  q[21].hu = false;

	q[19].l = 22; q[22].s = QString::fromLocal8Bit("青年：实验基地？这么说也对吧。。我是用科学赋予了花朵新生"); q[22].diff = false;  q[22].hu = true;
	q[23].s = QString::fromLocal8Bit("可是我更喜欢称它为博物馆。你知道里面的藏品是什么吗"); q[23].diff = false;  q[23].hu = false;

	q[20].l = 24; q[22].l = 24; q[24].s = QString::fromLocal8Bit("z. 是气味吧"); q[24].diff = true;  q[24].hu = false;
	q[25].s = QString::fromLocal8Bit("x. 花朵?"); q[25].diff = true;  q[25].hu = false;

	q[24].l = 26; q[26].s = QString::fromLocal8Bit("青年楞了一下：哈哈哈，我可是开始喜欢你了，聪明的小朋友。"); q[26].diff = false;  q[26].hu = true;
	q[27].s = QString::fromLocal8Bit("没错这里是气味博物馆，独一无二的气味博物馆。"); q[27].diff = false;  q[27].hu = false;

	q[25].l = 28; q[28].s = QString::fromLocal8Bit("青年：植物？唔，很可惜，我只克隆出了一种花朵。这里是"); q[28].diff = false;  q[28].hu = true;
	q[29].s = QString::fromLocal8Bit("气味博物馆，那些植物的味道才是我珍贵的藏品。"); q[29].diff = false;  q[29].hu = false;

	q[26].l = 30; q[28].l = 30; q[30].s = QString::fromLocal8Bit("我：为什么是收藏气味呢~？"); q[30].diff = false;  q[30].hu = false;

	q[30].l = 31; q[31].s = QString::fromLocal8Bit("青年：Odors have a power of persuasion stronger than "); q[31].diff = false;  q[31].hu = true;
	q[32].s = QString::fromLocal8Bit("that of words, appearances, emotions, or will."); q[32].diff = false;  q[32].hu = false;

	q[31].l = 33; q[33].s = QString::fromLocal8Bit("我：格雷诺耶 ?"); q[33].diff = false;  q[33].hu = false;

	q[33].l = 34; q[34].s = QString::fromLocal8Bit("青年：不，当然不是。我仅仅是想留住这些美好的东西罢了。"); q[34].diff = false;  q[34].hu = true;
	q[35].s = QString::fromLocal8Bit("事物易逝，气味永存。让美好的花承载美好的气味，多么棒啊！"); q[35].diff = false;  q[35].hu = false;

	q[34].l = 36; q[36].s = QString::fromLocal8Bit("青年：对了你还没有见到那些花儿的母本吧。一朵我千辛万苦"); q[36].diff = false;  q[36].hu = true;
	q[37].s = QString::fromLocal8Bit("培育成功的，真正的，娇弱的花儿！可能也是...."); q[37].diff = false;  q[37].hu = false;

	q[36].l = 38;  q[38].s = QString::fromLocal8Bit("青年：这世界上最后一朵了。"); q[38].diff = false;  q[38].hu = true;
	q[39].s = QString::fromLocal8Bit("（出现枯萎了一半的花）"); q[39].diff = false;  q[39].hu = false;

	q[38].l = 40; q[40].s = QString::fromLocal8Bit("z. 已经。。。枯萎了一半了啊"); q[40].diff = true;  q[40].hu = false;
	q[41].s = QString::fromLocal8Bit("x. 还有一半开的不错，真好啊"); q[41].diff = true;  q[41].hu = false;

	q[40].l = 42; q[42].s = QString::fromLocal8Bit("青年：是呀...看样子，再过段时间，可以准备收集花，，死亡"); q[42].diff = false;  q[42].hu = true;
	q[43].s = QString::fromLocal8Bit("的气味了。现在你想一起收集其他的气味来移植给花吗？"); q[43].diff = false;  q[43].hu = false;

	q[41].l = 44; q[44].s= QString::fromLocal8Bit("青年：真是有趣的小朋友，我更喜欢你了。过段时间，我收集完"); q[44].diff = false;  q[44].hu = true;
	q[45].s= QString::fromLocal8Bit("花死亡的气味，给你送一罐吧。现在一起收集其他的气味吗？"); q[45].diff = false;  q[45].hu = false;

	q[42].l = 46; q[44].l = 46; q[46].s= QString::fromLocal8Bit("青年:终于忙完了。收集气味可真是甜蜜的劳累啊...可惜，"); q[46].diff = false;  q[46].hu = true;
	q[47].s= QString::fromLocal8Bit("能收集到的都是内陆的气味，真想收集到海洋的味道啊"); q[47].diff = false;  q[47].hu = false;

	q[46].l = 48; q[48].s= QString::fromLocal8Bit("我：从背包里找一下吧"); q[48].diff = false;  q[48].hu = false;
	q[48].l = 48;
	//*********************
	q[49].s= QString::fromLocal8Bit("青年：这是海里的东西吗？借我收集气味吧！"); q[49].diff = false;  q[49].hu = false;

	q[49].l = 50; q[50].s = QString::fromLocal8Bit("z. 同意"); q[50].diff = true;  q[50].hu = false;

	q[51].s= QString::fromLocal8Bit("x. 拒绝"); q[51].diff = false;  q[51].hu = false;

	q[50].l = 52;  q[52].s= QString::fromLocal8Bit("青年：作为感谢，这个送给你吧。我精心收集来的一罐阳光！"); q[52].diff = false;  q[52].hu = false;
	q[52].l = 53; q[53].s = QString::fromLocal8Bit("阳光的味道。。。金黄色的。。。沙沙作响的。。。"); q[53].diff = false;  q[53].hu = true;
	q[54].s= QString::fromLocal8Bit("很好闻的味道啊。。。是这个世界的味道吗"); q[54].diff = false;  q[54].hu = false;
	q[53].l = 53;


	q[55].s = QString::fromLocal8Bit("青年：谢谢你，虽然这不是我想要的，但还是谢谢你，"); q[55].diff = false;  q[55].hu = true;
	q[56].s= QString::fromLocal8Bit("这些食物作为我的感谢吧"); q[56].diff = false;  q[56].hu = false;
	q[55].l = 55;

}



void SceneForest::mouseMoveEvent(QMouseEvent* event)
{
	mouse = event->pos();
}

void SceneForest::on_bag_clicked() {
	//QDialog *dlg = new QDialog(this);
	//dlg->show();
}

SceneForest::~SceneForest() {
	delete ui;
}
