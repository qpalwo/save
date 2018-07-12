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

	setMouseTracking(true);     //ţ��    ���ð��������ܼ����λ��
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
	QPen pen; //����
	pen.setColor(QColor(255, 255, 0));
	QBrush brush(QColor(255, 255, 0, 125)); //��ˢ
	painter.setPen(pen); //��ӻ���
	painter.setBrush(brush); //��ӻ�ˢ

	painter.setPen(QColor(100, 100, 20));
	QFont font;
	font.setFamily("΢���ź�");
	font.setPointSize(14);	// ��С
	font.setBold(true);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);	// �����ַ����
	painter.setFont(font);	// ʹ������

	painter.drawImage(backX, backY, backGround);

	if (playerX == 430)  stop = true;

	if (left) painter.drawPixmap(playerX, 235, 100, 200, player_left->currentPixmap());
	else painter.drawPixmap(playerX, 235, 100, 200, player->currentPixmap());
	painter.drawImage(backX, backY, earth);

	if ((waitTime>0) && (waitTime <= 28))
		painter.drawRect(playerX, 260, 10 + waitTime * 3, 20); //���ƾ��� 

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

	begin = QString::fromLocal8Bit("�����ɭ����....Ϊʲô���л�....��������������");

	get[0] = QString::fromLocal8Bit("�����Ʒ [���ڹ�ͷ]");
	get[1] = QString::fromLocal8Bit("�����Ʒ  [ơ��]");
	get[2] = QString::fromLocal8Bit("�����Ʒ [�ɿ���]");
	get[3] = QString::fromLocal8Bit("�����Ʒ [������]");
	get[4] = QString::fromLocal8Bit("�����Ʒ  [�ٷ�]");
	get[5] = QString::fromLocal8Bit("�����Ʒ  [Ůװ]");
	get[6] = QString::fromLocal8Bit("�����Ʒ [����֮��]");
	get[9] = QString::fromLocal8Bit("���������Ʒ [һ������]");


	q[0].s = QString::fromLocal8Bit("�������ǻ�԰�𡣡������ƺ��е�С��������"); q[0].diff = false; q[0].hu = true;
	q[1].s = QString::fromLocal8Bit("����Ϊʲô�����ڲ��������档������"); q[1].diff = false; q[1].hu = false;

	q[0].l = 2; q[2].s = QString::fromLocal8Bit("��С�ĵĴ�һ�����Ｗ�˽�ȥ��"); q[2].diff = false; q[2].hu = false;

	q[2].l = 3; q[3].s = QString::fromLocal8Bit("�ö໨����������Ϊʲô��һģһ��������"); q[3].diff = false; q[3].hu = true;
	q[4].s = QString::fromLocal8Bit("�ƺ�û����ŵĵط���"); q[4].diff = false; q[4].hu = false;

	q[3].l = 5;   q[5].s = QString::fromLocal8Bit("z. ֱ�Ӳ��ڻ�����");   q[5].diff = true;  q[5].hu = false;
	q[6].s = QString::fromLocal8Bit("x. ����ϸ����������·��");          q[6].diff = true; q[6].hu = false;

	q[5].l = 7;   q[7].s = QString::fromLocal8Bit("��û�취�ˣ�ֻ�ò���ȥ��");   q[7].diff = false; q[7].hu = false;

	q[6].l = 8;  q[8].s = QString::fromLocal8Bit("�ƺ�û������·�ˡ�������");      q[8].diff = false;  q[8].hu = false;

	q[7].l = 9; q[9].s = QString::fromLocal8Bit("�����������ܻ���������");   q[9].diff = false; q[9].hu = true;
	q[10].s = QString::fromLocal8Bit("��˭��������Ҿ��������ĵĻ��䣡����"); q[10].diff = false; q[10].hu = false;

	q[8].l = 11; q[11].s = QString::fromLocal8Bit("(��������) С���ѣ������ˣ������û��·��");   q[11].diff = false; q[11].hu = false;

	q[9].l = 12;  q[11].l = 12;  q[12].s = QString::fromLocal8Bit("�����ֲ������꣩"); q[12].diff = false; q[12].hu = true;
	q[13].s = QString::fromLocal8Bit("���꣺��������ҵ���Ѫ֮�أ���Ȼ���ܴ������߹���"); q[13].diff = false; q[13].hu = false;

	q[12].l = 14; q[14].s = QString::fromLocal8Bit("Ҫ���ȥ���������ɡ�"); q[14].diff = false; q[14].hu = true;
	q[15].s = QString::fromLocal8Bit("����������ĽŲ�����һ����·�����һ�������˽�ȥ��"); q[15].diff = false; q[15].hu = false;

	q[14].l = 16; q[16].s = QString::fromLocal8Bit("���꣨�����������ô��������ÿ������ǲ��������ظ�ԭ��"); q[16].diff = false; q[16].hu = true;
	q[17].s = QString::fromLocal8Bit("�����ģ����������ζ���Ҹ��������Ǹ��ָ�������ζ��"); q[17].diff = false; q[17].hu = false;

	q[16].l = 18; q[18].s = QString::fromLocal8Bit("z. �ǡ�����������һ�������"); q[18].diff = true;  q[18].hu = false;
	q[19].s = QString::fromLocal8Bit("x. ���������һ��ʵ�����"); q[19].diff = true;  q[19].hu = false;

	q[18].l = 20; q[20].s = QString::fromLocal8Bit("����(΢Ц):�ԣ��������һ������ݣ���֪������Ĳ�Ʒ��"); q[20].diff = false;  q[20].hu = true;
	q[21].s = QString::fromLocal8Bit("ʲô��"); q[21].diff = false;  q[21].hu = false;

	q[19].l = 22; q[22].s = QString::fromLocal8Bit("���꣺ʵ����أ���ô˵Ҳ�԰ɡ��������ÿ�ѧ�����˻�������"); q[22].diff = false;  q[22].hu = true;
	q[23].s = QString::fromLocal8Bit("�����Ҹ�ϲ������Ϊ����ݡ���֪������Ĳ�Ʒ��ʲô��"); q[23].diff = false;  q[23].hu = false;

	q[20].l = 24; q[22].l = 24; q[24].s = QString::fromLocal8Bit("z. ����ζ��"); q[24].diff = true;  q[24].hu = false;
	q[25].s = QString::fromLocal8Bit("x. ����?"); q[25].diff = true;  q[25].hu = false;

	q[24].l = 26; q[26].s = QString::fromLocal8Bit("��������һ�£����������ҿ��ǿ�ʼϲ�����ˣ�������С���ѡ�"); q[26].diff = false;  q[26].hu = true;
	q[27].s = QString::fromLocal8Bit("û����������ζ����ݣ���һ�޶�����ζ����ݡ�"); q[27].diff = false;  q[27].hu = false;

	q[25].l = 28; q[28].s = QString::fromLocal8Bit("���꣺ֲ����ܿ�ϧ����ֻ��¡����һ�ֻ��䡣������"); q[28].diff = false;  q[28].hu = true;
	q[29].s = QString::fromLocal8Bit("��ζ����ݣ���Щֲ���ζ�����������Ĳ�Ʒ��"); q[29].diff = false;  q[29].hu = false;

	q[26].l = 30; q[28].l = 30; q[30].s = QString::fromLocal8Bit("�ң�Ϊʲô���ղ���ζ��~��"); q[30].diff = false;  q[30].hu = false;

	q[30].l = 31; q[31].s = QString::fromLocal8Bit("���꣺Odors have a power of persuasion stronger than "); q[31].diff = false;  q[31].hu = true;
	q[32].s = QString::fromLocal8Bit("that of words, appearances, emotions, or will."); q[32].diff = false;  q[32].hu = false;

	q[31].l = 33; q[33].s = QString::fromLocal8Bit("�ң�����ŵҮ ?"); q[33].diff = false;  q[33].hu = false;

	q[33].l = 34; q[34].s = QString::fromLocal8Bit("���꣺������Ȼ���ǡ��ҽ���������ס��Щ���õĶ������ˡ�"); q[34].diff = false;  q[34].hu = true;
	q[35].s = QString::fromLocal8Bit("�������ţ���ζ���档�����õĻ��������õ���ζ����ô������"); q[35].diff = false;  q[35].hu = false;

	q[34].l = 36; q[36].s = QString::fromLocal8Bit("���꣺�����㻹û�м�����Щ������ĸ���ɡ�һ����ǧ�����"); q[36].diff = false;  q[36].hu = true;
	q[37].s = QString::fromLocal8Bit("�����ɹ��ģ������ģ������Ļ���������Ҳ��...."); q[37].diff = false;  q[37].hu = false;

	q[36].l = 38;  q[38].s = QString::fromLocal8Bit("���꣺�����������һ���ˡ�"); q[38].diff = false;  q[38].hu = true;
	q[39].s = QString::fromLocal8Bit("�����ֿ�ή��һ��Ļ���"); q[39].diff = false;  q[39].hu = false;

	q[38].l = 40; q[40].s = QString::fromLocal8Bit("z. �Ѿ���������ή��һ���˰�"); q[40].diff = true;  q[40].hu = false;
	q[41].s = QString::fromLocal8Bit("x. ����һ�뿪�Ĳ�����ð�"); q[41].diff = true;  q[41].hu = false;

	q[40].l = 42; q[42].s = QString::fromLocal8Bit("���꣺��ѽ...�����ӣ��ٹ���ʱ�䣬����׼���ռ�����������"); q[42].diff = false;  q[42].hu = true;
	q[43].s = QString::fromLocal8Bit("����ζ�ˡ���������һ���ռ���������ζ����ֲ������"); q[43].diff = false;  q[43].hu = false;

	q[41].l = 44; q[44].s= QString::fromLocal8Bit("���꣺������Ȥ��С���ѣ��Ҹ�ϲ�����ˡ�����ʱ�䣬���ռ���"); q[44].diff = false;  q[44].hu = true;
	q[45].s= QString::fromLocal8Bit("����������ζ��������һ�ްɡ�����һ���ռ���������ζ��"); q[45].diff = false;  q[45].hu = false;

	q[42].l = 46; q[44].l = 46; q[46].s= QString::fromLocal8Bit("����:����æ���ˡ��ռ���ζ���������۵����۰�...��ϧ��"); q[46].diff = false;  q[46].hu = true;
	q[47].s= QString::fromLocal8Bit("���ռ����Ķ�����½����ζ�������ռ��������ζ����"); q[47].diff = false;  q[47].hu = false;

	q[46].l = 48; q[48].s= QString::fromLocal8Bit("�ң��ӱ�������һ�°�"); q[48].diff = false;  q[48].hu = false;
	q[48].l = 48;
	//*********************
	q[49].s= QString::fromLocal8Bit("���꣺���Ǻ���Ķ����𣿽����ռ���ζ�ɣ�"); q[49].diff = false;  q[49].hu = false;

	q[49].l = 50; q[50].s = QString::fromLocal8Bit("z. ͬ��"); q[50].diff = true;  q[50].hu = false;

	q[51].s= QString::fromLocal8Bit("x. �ܾ�"); q[51].diff = false;  q[51].hu = false;

	q[50].l = 52;  q[52].s= QString::fromLocal8Bit("���꣺��Ϊ��л������͸���ɡ��Ҿ����ռ�����һ�����⣡"); q[52].diff = false;  q[52].hu = false;
	q[52].l = 53; q[53].s = QString::fromLocal8Bit("�����ζ�����������ɫ�ġ�����ɳɳ����ġ�����"); q[53].diff = false;  q[53].hu = true;
	q[54].s= QString::fromLocal8Bit("�ܺ��ŵ�ζ��������������������ζ����"); q[54].diff = false;  q[54].hu = false;
	q[53].l = 53;


	q[55].s = QString::fromLocal8Bit("���꣺лл�㣬��Ȼ�ⲻ������Ҫ�ģ�������лл�㣬"); q[55].diff = false;  q[55].hu = true;
	q[56].s= QString::fromLocal8Bit("��Щʳ����Ϊ�ҵĸ�л��"); q[56].diff = false;  q[56].hu = false;
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
