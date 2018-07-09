#include "sceneforest.h"
#include "ui_sceneforest.h"

SceneForest::SceneForest(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SceneForest) {
	ui->setupUi(this);

	backX = 0;   backY = 0;
	playerX = 0;
	talk = 0;
	first = false;
	stop = false;
	not_yet = true;
	left = false;
	choose = false;
	zz = false;
	xx = false;
	loadImage();
	loadPlot();

	setMouseTracking(true);     //牛逼    不用按下鼠标就能监控其位置
}

void SceneForest::loadImage() {
	backGround.load(":/scene/forest_1.png");
	earth.load(":/scene/forest_2.png");
	player = new QMovie(":/people/forest_right.gif");
	player_left = new QMovie(":/people/forest_left.gif");
	uncle.load(":/people/young.png");
	house_closed.load(":/scene/forest_house_close.png");
	house_open.load(":/scene/forest_house_open.png");
	option_1.load(":/conver/convar/choice_1.png");
	option_2.load(":/conver/convar/choice_2.png");
	option_3.load(":/conver/convar/choice_3.png");
	conver.load(":/conver/convar/convar.png");
	name.load(":/conver/convar/name.png");
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

	painter.drawText(220, 220, mouse_out);

	if (playerX == 430)  stop = true;

	if (left) painter.drawPixmap(playerX, 235, 100, 200, player_left->currentPixmap());
	else painter.drawPixmap(playerX, 235, 100, 200, player->currentPixmap());
	painter.drawImage(backX, backY, earth);

	if ((waitTime>0) && (waitTime <= 28))
		painter.drawRect(playerX, 260, 10 + waitTime * 3, 20); //绘制矩形 


	if (first) 	painter.drawText(180, 150, begin);

	painter.setPen(QColor(250, 250, 250));
	if (playerX >= 440) {
		painter.drawImage(850, 260, uncle);
		if (not_yet)
			painter.drawImage(BDL, -10, house_closed);
		else	painter.drawImage(BDL, -10, house_open);
		painter.drawImage(0, 0, conver);

		painter.drawText(280, 612, q[talk].s);
		if (q[talk].hu) {
			painter.drawText(280, 666, q[talk+1].s);
		}
		if (q[talk].diff ) {
			talk++;
			painter.drawText(280, 666, q[talk].s);
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
		}
		else waitTime = 0;

		if (playerX < 430) first = true;

		if ((e->key() == Qt::Key_G) && (!q[talk].diff))
			talk = q[talk].l;

		if (q[talk].diff) {
			if (e->key() == Qt::Key_Z) talk = q[talk - 1].l;
			if (e->key() == Qt::Key_X) talk = q[talk].l;
		}

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


void SceneForest::loadPlot() {
	int i = 0, j = 0;

	begin= QString::fromLocal8Bit("这就是森林吗....为什么会有花....不是早就灭绝了吗");

	q[0].s = QString::fromLocal8Bit("这里面是花园吗。。。。似乎有点小啊。。。");q[0].diff = false; q[0].hu = true;
	q[1].s = QString::fromLocal8Bit("而且为什么是罩在玻璃罩里面。。。。"); q[1].diff = false; q[1].hu = false;

	q[0].l = 2; q[2].s= QString::fromLocal8Bit("（小心的从一扇门里挤了进去）"); q[2].diff = false; q[2].hu = false;

	q[2].l = 3; q[3].s = QString::fromLocal8Bit("好多花。。。可是为什么都一模一样。。。"); q[3].diff = false; q[3].hu = true;
    q[4].s = QString::fromLocal8Bit("似乎没有落脚的地方啊"); q[4].diff = false; q[4].hu = false;

	q[3].l = 5;   q[5].s = QString::fromLocal8Bit("z. 直接踩在花丛上");   q[5].diff = true;  q[5].hu = false;
    q[6].s = QString::fromLocal8Bit("x. 再仔细找找其他的路径");          q[6].diff = true; q[6].hu = false;

	q[5].l = 7;   q[7].s = QString::fromLocal8Bit("唔，没办法了，只好踩上去啊");   q[7].diff = false; q[7].hu = false;

	q[6].l = 8;  q[8].s = QString::fromLocal8Bit("似乎没有其它路了。。。。");      q[8].diff = false;  q[8].hu = false;

	q[7].l = 9; q[9].s= QString::fromLocal8Bit("（出现气急败坏的声音）");   q[9].diff = false; q[9].hu = true;
	q[10].s = QString::fromLocal8Bit("是谁允许你踩我精心培育的的花朵！！！"); q[10].diff = false; q[10].hu = false;

	q[8].l = 11; q[11].s = QString::fromLocal8Bit("(出现声音) 小朋友，别找了，这里可没有路。");   q[11].diff = false; q[11].hu = false;

	q[9].l = 12;  q[11].l = 12;  q[12].s = QString::fromLocal8Bit("（出现病弱青年）"); q[12].diff = false; q[12].hu = true;
	q[13].s = QString::fromLocal8Bit("青年：这里可是我的心血之地，当然不能从这里走过。"); q[13].diff = false; q[13].hu = false;

	q[12].l = 14; q[14].s= QString::fromLocal8Bit("要想进去，跟我来吧。"); q[14].diff = false; q[14].hu = true;
	q[15].s= QString::fromLocal8Bit("（跟上青年的脚步，在一串绕路后从另一个门走了进去）"); q[15].diff = false; q[15].hu = false;

	q[14].l = 16; q[16].s = QString::fromLocal8Bit("青年（深呼吸）：怎么样？这里好看吗？我是不是完美地复原了"); q[16].diff = false; q[16].hu = true;
	q[17].s= QString::fromLocal8Bit("花朵的模样？还有气味，我赋予了他们各种各样的气味！"); q[17].diff = false; q[17].hu = false;

	q[16].l = 18; q[18].s = QString::fromLocal8Bit("z. 是。。。这里像一座博物馆"); q[18].diff = true;  q[18].hu = false;
	q[19].s= QString::fromLocal8Bit("x. 这里。。。像一座实验基地"); q[19].diff = true;  q[19].hu = false;

	q[18].l = 20; q[20].s = QString::fromLocal8Bit("青年(微笑):对，这里就是一座博物馆，你知道这里的藏品是"); q[20].diff = false;  q[20].hu = true;
	q[21].s= QString::fromLocal8Bit("什么吗？"); q[21].diff = false;  q[21].hu = false;

	q[19].l = 22; q[22].s = QString::fromLocal8Bit("青年：实验基地？这么说也对吧。。我是用科学赋予了花朵新生"); q[22].diff = false;  q[22].hu = true;
	q[23].s= QString::fromLocal8Bit("可是我更喜欢称它为博物馆。你知道里面的藏品是什么吗"); q[23].diff = false;  q[23].hu = false;

	q[20].l = 24; q[22].l = 24; q[24].s= QString::fromLocal8Bit("z. 是气味吧"); q[24].diff = true;  q[24].hu = false;
	q[25].s = QString::fromLocal8Bit("x. 花朵?"); q[25].diff = true;  q[25].hu = false;

	q[24].l = 26; q[26].s= QString::fromLocal8Bit("青年楞了一下：哈哈哈，我可是开始喜欢你了，聪明的小朋友。"); q[26].diff = false;  q[26].hu = true;
	q[27].s = QString::fromLocal8Bit("没错这里是气味博物馆，独一无二的气味博物馆。"); q[27].diff = false;  q[27].hu = false;

	q[25].l = 28; q[28].s= QString::fromLocal8Bit("青年：植物？唔，很可惜，我只克隆出了一种花朵。这里是"); q[28].diff = false;  q[28].hu = true;
	q[29].s = QString::fromLocal8Bit("气味博物馆，那些植物的味道才是我珍贵的藏品。"); q[29].diff = false;  q[29].hu = false;

	q[26].l = 30; q[28].l = 30; q[30].s = QString::fromLocal8Bit("我：为什么是收藏气味呢~？"); q[30].diff = false;  q[30].hu = false;

	q[30].l = 31; q[31].s = QString::fromLocal8Bit("青年：Odors have a power of persuasion stronger than "); q[31].diff = false;  q[31].hu = true;
	q[32].s= QString::fromLocal8Bit("that of words, appearances, emotions, or will."); q[32].diff = false;  q[32].hu = false;

	q[31].l = 33; q[33].s = QString::fromLocal8Bit("我：格雷诺耶 ?"); q[33].diff = false;  q[33].hu = false;

	q[33].l = 34; q[34].s= QString::fromLocal8Bit("青年：不，当然不是。我仅仅是想留住这些美好的东西罢了。"); q[34].diff = false;  q[34].hu = true;
	q[35].s= QString::fromLocal8Bit("事物易逝，气味永存。让美好的花承载美好的气味，多么棒啊！"); q[35].diff = false;  q[35].hu = false;

	q[34].l = 36; q[36].s= QString::fromLocal8Bit("青年：对了你还没有见到那些花儿的母本吧。一朵我千辛万苦"); q[36].diff = false;  q[36].hu = true;
	q[37].s= QString::fromLocal8Bit("培育成功的，真正的，娇弱的花儿！可能也是...."); q[37].diff = false;  q[37].hu = false;

	q[36].l = 38;  q[38].s= QString::fromLocal8Bit("青年：这世界上最后一朵了。"); q[38].diff = false;  q[38].hu = true;
	q[39].s = QString::fromLocal8Bit("（出现枯萎了一半的花）"); q[39].diff = false;  q[39].hu = false;

	q[38].l = 40; q[40].s= QString::fromLocal8Bit("z. 已经。。。枯萎了一半了啊"); q[40].diff = true;  q[40].hu = false;
	q[41].s = QString::fromLocal8Bit("x. 还有一半开的不错，真好啊"); q[41].diff = true;  q[41].hu = false;



	/*q[3].l = 5;  q[4].l = 5;  q[5].s = QString::fromLocal8Bit("大叔：走！大叔带你去逛逛（掏出一系列证件）看, 我不是坏");  q[5].diff = false;  q[5].hu = true;

	q[5].l = 6;  q[6].s = QString::fromLocal8Bit("人(凑过去一看）驾驶证,学生证,一张奇怪的东西的照片...");   q[6].diff = false;  q[6].hu = true;

	q[6].l = 7;  q[7].s = QString::fromLocal8Bit("z. 询问奇怪的东西是什么");      q[7].diff = true; q[7].hu = false;
	q[6].r = 8;  q[8].s = QString::fromLocal8Bit("x. 不询问");      q[8].diff = true; q[8].hu = false;

	q[7].l = 9;  q[9].s = QString::fromLocal8Bit("大叔：奇怪的东西？哈哈哈，这可不是什么奇怪的东西, 这是");  q[9].diff = false;  q[9].hu = true;
	q[9].l = 10; q[10].s = QString::fromLocal8Bit("大宝贝。看你这么有眼光，我破例带你去参观一下。"); q[10].diff = false;  q[10].hu = false;

	q[8].l = 11; q[11].s = QString::fromLocal8Bit("大叔：走吧，这热浪真可溺人。"); q[11].diff = false;  q[11].hu = false;

	q[10].l = 12; q[11].l = 12;  q[12].s = QString::fromLocal8Bit("结果和大叔一起走到了奇怪的东西的面前（出现船）");  q[12].diff = false;  q[12].hu = false;

	q[12].l = 13; q[13].s = QString::fromLocal8Bit("大叔：怎么样？是不是特别好看~");  q[13].diff = false;  q[13].hu = false;

	q[13].l = 14; q[14].s = QString::fromLocal8Bit("我：是很厉害。。。这是什么呢");  q[14].diff = false;  q[14].hu = false;

	q[14].l = 15;  q[15].s = QString::fromLocal8Bit("大叔:这叫船,乘风破浪,勇往直前,无所畏惧！是蓝色大海的拥护");  q[15].diff = false;  q[15].hu = true;
	q[15].l = 16; q[16].s = QString::fromLocal8Bit("是海洋的结晶！早在我太太太爷爷的时候,他们乘船披荆斩棘...."); q[16].diff = false;  q[16].hu = false;

	q[16].l = 17; q[17].s = QString::fromLocal8Bit("我：(打断）可是早在很早以前世界上已经没有海了。"); q[17].diff = false;  q[17].hu = false;

	q[17].l = 18; q[18].s = QString::fromLocal8Bit("大叔：胡说！海明明一直在，船还在，我还在，怎么能说，"); q[18].diff = false;  q[18].hu = true;
	q[18].l = 19; q[19].s = QString::fromLocal8Bit("海没有了呢？？！");  q[19].diff = false;  q[19].hu = false;

	q[19].l = 20; q[20].s = QString::fromLocal8Bit("z.可船已经行驶不了,无法起航了啊..不能航行的船,还有意义吗");  q[20].diff = true;  q[20].hu = false;
	q[19].r = 21; q[21].s = QString::fromLocal8Bit("x.是啊，即使已经消失，但始终有人记得.有人记得便不会消失");  q[21].diff = true;  q[21].hu = false;

	q[20].l = 22; q[22].s = QString::fromLocal8Bit("大叔：谁说船不能航行！要不是轴承滑轮出了点问题，，，唉");  q[22].diff = false;  q[22].hu = false;

	q[21].l = 23; q[23].s = QString::fromLocal8Bit("大叔：只要记得，便不会消失，只要存在过，就有价值......");  q[23].diff = false;  q[23].hu = true;
	q[23].l = 24; q[24].s = QString::fromLocal8Bit("如果不是因为船缺少一个轴承滑轮的珠子，真想邀请你一起驾驶啊");  q[24].diff = false;  q[24].hu = false;

	q[22].l = 25; q[24].l = 25;  q[25].s = QString::fromLocal8Bit("大叔：(叹气)这么多年了啊...我一个人在这沙漠里这么多年了"); q[25].diff = false;  q[25].hu = true;
	q[25].l = 26; q[26].s = QString::fromLocal8Bit("为什么还是差一点...就差那么一点...难道我真的要放弃吗"); q[26].diff = false;  q[26].hu = false;

	q[26].l = 27; q[27].s = QString::fromLocal8Bit("我：(唔，，轴承滑轮的问题...看看包里有什么东西吧"); q[27].diff = false;  q[27].hu = false;

	*/
}



void SceneForest::mouseMoveEvent(QMouseEvent* event)
{
	//QPoint m = event->pos();
	//mouse = QString::number(m.x()) +'  ' + QString::number(m.y());

	mouse = event->pos();

	mouse_out = QString::number(event->x()) + '  ' + QString::number(event->y());
	//setText(QString("(%1,%2)").arg(m.x()).arg(m.y()));

}

void SceneForest::on_bag_clicked() {
	//QDialog *dlg = new QDialog(this);
	//dlg->show();
}

SceneForest::~SceneForest() {
	delete ui;
}
