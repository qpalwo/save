#include "scenedesert.h"
#include "ui_scenedesert.h"


SceneDesert::SceneDesert(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SceneDesert) {
	ui->setupUi(this);

	backX = 0;   backY = 0;
	playerX = 0;
	talk = 0;
	stop = false;
	left = false;
	choose = false;
	zz = false;
	xx = false;
	loadImage();
	loadPlot();

	setMouseTracking(true);     //牛逼    不用按下鼠标就能监控其位置
}

void SceneDesert::loadImage() {
	backGround.load(":/desertB/scene/desert_1.png");
	earth.load(":/desertB/scene/desert_2.png");
	player = new QMovie(":/player/main.gif");
	player_left = new QMovie(":/player/main_left.gif");
	option_1.load(":/conver/convar/choice_1.png");
	option_2.load(":/conver/convar/choice_2.png");
	option_3.load(":/conver/convar/choice_3.png");
	conver.load(":/conver/convar/convar.png");
	name.load(":/conver/convar/name.png");
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

	painter.drawText(220, 220, mouse_out);

	if (playerX == 430)  stop = true;

	if (left) painter.drawPixmap(playerX, 250, 100, 200, player_left->currentPixmap());
	else painter.drawPixmap(playerX, 250, 100, 200, player->currentPixmap());
	painter.drawImage(backX, backY, earth);

	if ((waitTime>0)&&(waitTime<=28))
		painter.drawRect(playerX, 260, 10+waitTime*3, 20); //绘制矩形 

	if (playerX >= 560) {
		painter.drawPixmap(850, 250, 100, 200, player_left->currentPixmap());
		painter.drawImage(0, 0, conver);

		painter.drawText(280, 620, q[talk].s);

	}

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
		//case Qt::Key_Z: zz = true;  break;
	//	case Qt::Key_X: xx = true;  break;
		//case Qt::Key_Space: if (q[talk].trigger) choose = true; break;
		}
		if ((e->key() == Qt::Key_S) || (e->key() == Qt::Key_Down)) {
			if (underTheTree(1))	waitTime++;
		}
		else waitTime = 0;


		if ((e->key() == Qt::Key_Space) && (!q[talk].diff))  talk = q[talk].l;

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
	int i = 0, j = 0;

	q[0].s = QString::fromLocal8Bit("大叔：小姑娘，来这荒凉地方干什么"); 	q[0].diff = false;

	j++; q[0].l = 1;   q[1].s = QString::fromLocal8Bit("z. 我是来体验的");   q[1].diff = true;
	j++; q[0].r = 2;   q[2].s = QString::fromLocal8Bit("x. (不说话)");           q[2].diff = true;

	j++; q[1].l = 3;   q[3].s = QString::fromLocal8Bit("大叔：少女情怀总是诗啊，和大叔一样！");  

	j++; q[2].l = 4;  q[4].s = QString::fromLocal8Bit("大叔：小姑娘还挺害羞的。");   

}



void SceneDesert::mouseMoveEvent(QMouseEvent* event)
{
	//QPoint m = event->pos();
	//mouse = QString::number(m.x()) +'  ' + QString::number(m.y());

	mouse = event->pos();

	mouse_out = QString::number(event->x()) + '  ' + QString::number(event->y());
	//setText(QString("(%1,%2)").arg(m.x()).arg(m.y()));

}

SceneDesert::~SceneDesert() {
	delete ui;
}
