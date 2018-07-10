#include "scenedesert.h"
#include "ui_scenedesert.h"


SceneDesert::SceneDesert(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SceneDesert) {
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);

	backX = 0;   backY = 0;
	playerX = 0;
	talk = 0;
	first = false;
	stop = false;
	left = false;
	zxFuck = false;

	loadImage();
	loadPlot();

	menuwidget *menu = new menuwidget("desert",this);
	setFocus();
	menu->show();

	setMouseTracking(true);     //牛逼    不用按下鼠标就能监控其位置
}

void SceneDesert::loadImage() {
	backGround.load(":/desertB/scene/desert_1.png");
	earth.load(":/desertB/scene/desert_2.png");
	player = new QMovie(":/player/main.gif");
	player_left = new QMovie(":/player/main_left.gif");
	uncle.load(":/uncle.png");
	conver.load(":/conver/convar/convar.png");
	player->start();
	player_left->start();
}

void SceneDesert::paintEvent(QPaintEvent * e) {
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

	//painter.drawText(220, 220, mouse_out);

	if (playerX == 430)  stop = true;

	if (left) painter.drawPixmap(playerX, 250, 100, 200, player_left->currentPixmap());
	else painter.drawPixmap(playerX, 250, 100, 200, player->currentPixmap());
	painter.drawImage(backX, backY, earth);

	if ((waitTime>0)&&(waitTime<=28))
		painter.drawRect(playerX, 260, 10+waitTime*3, 20); //绘制矩形 

	if (first) { 
		painter.drawText(180, 140, begin);
		painter.drawText(320, 180, begin2);
	 }


	if (playerX >= 440) {
		painter.drawImage(850, 260, uncle);
		painter.drawImage(0, 0, conver);
		if (zxFuck) {
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
				zxFuck = true;
			}
		}
	}
	first = false;
}

void SceneDesert::keyPressEvent(QKeyEvent *e) {
	if (stop) {                         //main player stop
		switch (e->key()) {
		case Qt::Key_A: backX += 10;  left = true; break;
		case Qt::Key_Left: backX += 10; left = true; break;
		case Qt::Key_D: backX -= 10;  left = false;  break;
		case Qt::Key_Right: backX -= 10;  left = false;  break;
		}

		if ((e->key() == Qt::Key_S)|| (e->key() == Qt::Key_Down)) {
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
			if (underTheTree(1))  waitTime++;
		} else waitTime = 0;

		if (playerX < 430) first = true;

		if ((e->key() == Qt::Key_Space) && (!q[talk].diff))
			talk = q[talk].l;

		if (q[talk].diff) {
			if (e->key() == Qt::Key_Z) { talk = q[talk - 1].l;  zxFuck = false; }
			if (e->key() == Qt::Key_X) { talk = q[talk].l;  zxFuck = false; }
		}

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

void SceneDesert::loadPlot() {
	begin = QString::fromLocal8Bit("炎热的感觉。。。透不过气。。。就像是溺在海里。。。");
	begin2 = QString::fromLocal8Bit("得赶快找个地方休息一下");

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
	q[15].l = 16; q[16].s = QString::fromLocal8Bit("是海洋的结晶！早在我太太太爷爷的时候,他们乘船披荆斩棘...."); q[16].diff = false;  q[16].hu = false;

	q[16].l = 17; q[17].s = QString::fromLocal8Bit("我：(打断）可是早在很早以前世界上已经没有海了。"); q[17].diff = false;  q[17].hu = false;

	q[17].l = 18; q[18].s = QString::fromLocal8Bit("大叔：胡说！海明明一直在，船还在，我还在，怎么能说，"); q[18].diff = false;  q[18].hu = true;
	q[18].l = 19; q[19].s = QString::fromLocal8Bit("海没有了呢？？！");  q[19].diff = false;  q[19].hu = false;

	q[19].l = 20; q[20].s= QString::fromLocal8Bit("z.可船已经行驶不了,无法起航了啊..不能航行的船,还有意义吗");  q[20].diff = true;  q[20].hu = false;
	q[19].r = 21; q[21].s = QString::fromLocal8Bit("x.是啊，即使已经消失，但始终有人记得.有人记得便不会消失");  q[21].diff = true;  q[21].hu = false;

	q[20].l = 22; q[22].s = QString::fromLocal8Bit("大叔：谁说船不能航行！要不是轴承滑轮出了点问题，，，唉");  q[22].diff = false;  q[22].hu = false;

	q[21].l = 23; q[23].s = QString::fromLocal8Bit("大叔：只要记得，便不会消失，只要存在过，就有价值......");  q[23].diff = false;  q[23].hu = true;
	q[23].l = 24; q[24].s = QString::fromLocal8Bit("如果不是因为船缺少一个轴承滑轮的珠子，真想邀请你一起驾驶啊");  q[24].diff = false;  q[24].hu = false;

	q[22].l = 25; q[24].l = 25;  q[25].s = QString::fromLocal8Bit("大叔：(叹气)这么多年了啊...我一个人在这沙漠里这么多年了");q[25].diff = false;  q[25].hu = true;
	q[25].l = 26; q[26].s= QString::fromLocal8Bit("为什么还是差一点...就差那么一点...难道我真的要放弃吗"); q[26].diff = false;  q[26].hu = false;

	q[26].l = 27; q[27].s = QString::fromLocal8Bit("我：(唔，，轴承滑轮的问题...看看包里有什么东西吧"); q[27].diff = false;  q[27].hu = false;


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
