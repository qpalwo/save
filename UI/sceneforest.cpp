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

	setMouseTracking(true);     //ţ��    ���ð��������ܼ����λ��
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

	painter.drawText(220, 220, mouse_out);

	if (playerX == 430)  stop = true;

	if (left) painter.drawPixmap(playerX, 235, 100, 200, player_left->currentPixmap());
	else painter.drawPixmap(playerX, 235, 100, 200, player->currentPixmap());
	painter.drawImage(backX, backY, earth);

	if ((waitTime>0) && (waitTime <= 28))
		painter.drawRect(playerX, 260, 10 + waitTime * 3, 20); //���ƾ��� 


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

	begin= QString::fromLocal8Bit("�����ɭ����....Ϊʲô���л�....��������������");

	q[0].s = QString::fromLocal8Bit("�������ǻ�԰�𡣡������ƺ��е�С��������");q[0].diff = false; q[0].hu = true;
	q[1].s = QString::fromLocal8Bit("����Ϊʲô�����ڲ��������档������"); q[1].diff = false; q[1].hu = false;

	q[0].l = 2; q[2].s= QString::fromLocal8Bit("��С�ĵĴ�һ�����Ｗ�˽�ȥ��"); q[2].diff = false; q[2].hu = false;

	q[2].l = 3; q[3].s = QString::fromLocal8Bit("�ö໨����������Ϊʲô��һģһ��������"); q[3].diff = false; q[3].hu = true;
    q[4].s = QString::fromLocal8Bit("�ƺ�û����ŵĵط���"); q[4].diff = false; q[4].hu = false;

	q[3].l = 5;   q[5].s = QString::fromLocal8Bit("z. ֱ�Ӳ��ڻ�����");   q[5].diff = true;  q[5].hu = false;
    q[6].s = QString::fromLocal8Bit("x. ����ϸ����������·��");          q[6].diff = true; q[6].hu = false;

	q[5].l = 7;   q[7].s = QString::fromLocal8Bit("��û�취�ˣ�ֻ�ò���ȥ��");   q[7].diff = false; q[7].hu = false;

	q[6].l = 8;  q[8].s = QString::fromLocal8Bit("�ƺ�û������·�ˡ�������");      q[8].diff = false;  q[8].hu = false;

	q[7].l = 9; q[9].s= QString::fromLocal8Bit("�����������ܻ���������");   q[9].diff = false; q[9].hu = true;
	q[10].s = QString::fromLocal8Bit("��˭��������Ҿ��������ĵĻ��䣡����"); q[10].diff = false; q[10].hu = false;

	q[8].l = 11; q[11].s = QString::fromLocal8Bit("(��������) С���ѣ������ˣ������û��·��");   q[11].diff = false; q[11].hu = false;

	q[9].l = 12;  q[11].l = 12;  q[12].s = QString::fromLocal8Bit("�����ֲ������꣩"); q[12].diff = false; q[12].hu = true;
	q[13].s = QString::fromLocal8Bit("���꣺��������ҵ���Ѫ֮�أ���Ȼ���ܴ������߹���"); q[13].diff = false; q[13].hu = false;

	q[12].l = 14; q[14].s= QString::fromLocal8Bit("Ҫ���ȥ���������ɡ�"); q[14].diff = false; q[14].hu = true;
	q[15].s= QString::fromLocal8Bit("����������ĽŲ�����һ����·�����һ�������˽�ȥ��"); q[15].diff = false; q[15].hu = false;

	q[14].l = 16; q[16].s = QString::fromLocal8Bit("���꣨�����������ô��������ÿ������ǲ��������ظ�ԭ��"); q[16].diff = false; q[16].hu = true;
	q[17].s= QString::fromLocal8Bit("�����ģ����������ζ���Ҹ��������Ǹ��ָ�������ζ��"); q[17].diff = false; q[17].hu = false;

	q[16].l = 18; q[18].s = QString::fromLocal8Bit("z. �ǡ�����������һ�������"); q[18].diff = true;  q[18].hu = false;
	q[19].s= QString::fromLocal8Bit("x. ���������һ��ʵ�����"); q[19].diff = true;  q[19].hu = false;

	q[18].l = 20; q[20].s = QString::fromLocal8Bit("����(΢Ц):�ԣ��������һ������ݣ���֪������Ĳ�Ʒ��"); q[20].diff = false;  q[20].hu = true;
	q[21].s= QString::fromLocal8Bit("ʲô��"); q[21].diff = false;  q[21].hu = false;

	q[19].l = 22; q[22].s = QString::fromLocal8Bit("���꣺ʵ����أ���ô˵Ҳ�԰ɡ��������ÿ�ѧ�����˻�������"); q[22].diff = false;  q[22].hu = true;
	q[23].s= QString::fromLocal8Bit("�����Ҹ�ϲ������Ϊ����ݡ���֪������Ĳ�Ʒ��ʲô��"); q[23].diff = false;  q[23].hu = false;

	q[20].l = 24; q[22].l = 24; q[24].s= QString::fromLocal8Bit("z. ����ζ��"); q[24].diff = true;  q[24].hu = false;
	q[25].s = QString::fromLocal8Bit("x. ����?"); q[25].diff = true;  q[25].hu = false;

	q[24].l = 26; q[26].s= QString::fromLocal8Bit("��������һ�£����������ҿ��ǿ�ʼϲ�����ˣ�������С���ѡ�"); q[26].diff = false;  q[26].hu = true;
	q[27].s = QString::fromLocal8Bit("û����������ζ����ݣ���һ�޶�����ζ����ݡ�"); q[27].diff = false;  q[27].hu = false;

	q[25].l = 28; q[28].s= QString::fromLocal8Bit("���꣺ֲ����ܿ�ϧ����ֻ��¡����һ�ֻ��䡣������"); q[28].diff = false;  q[28].hu = true;
	q[29].s = QString::fromLocal8Bit("��ζ����ݣ���Щֲ���ζ�����������Ĳ�Ʒ��"); q[29].diff = false;  q[29].hu = false;

	q[26].l = 30; q[28].l = 30; q[30].s = QString::fromLocal8Bit("�ң�Ϊʲô���ղ���ζ��~��"); q[30].diff = false;  q[30].hu = false;

	q[30].l = 31; q[31].s = QString::fromLocal8Bit("���꣺Odors have a power of persuasion stronger than "); q[31].diff = false;  q[31].hu = true;
	q[32].s= QString::fromLocal8Bit("that of words, appearances, emotions, or will."); q[32].diff = false;  q[32].hu = false;

	q[31].l = 33; q[33].s = QString::fromLocal8Bit("�ң�����ŵҮ ?"); q[33].diff = false;  q[33].hu = false;

	q[33].l = 34; q[34].s= QString::fromLocal8Bit("���꣺������Ȼ���ǡ��ҽ���������ס��Щ���õĶ������ˡ�"); q[34].diff = false;  q[34].hu = true;
	q[35].s= QString::fromLocal8Bit("�������ţ���ζ���档�����õĻ��������õ���ζ����ô������"); q[35].diff = false;  q[35].hu = false;

	q[34].l = 36; q[36].s= QString::fromLocal8Bit("���꣺�����㻹û�м�����Щ������ĸ���ɡ�һ����ǧ�����"); q[36].diff = false;  q[36].hu = true;
	q[37].s= QString::fromLocal8Bit("�����ɹ��ģ������ģ������Ļ���������Ҳ��...."); q[37].diff = false;  q[37].hu = false;

	q[36].l = 38;  q[38].s= QString::fromLocal8Bit("���꣺�����������һ���ˡ�"); q[38].diff = false;  q[38].hu = true;
	q[39].s = QString::fromLocal8Bit("�����ֿ�ή��һ��Ļ���"); q[39].diff = false;  q[39].hu = false;

	q[38].l = 40; q[40].s= QString::fromLocal8Bit("z. �Ѿ���������ή��һ���˰�"); q[40].diff = true;  q[40].hu = false;
	q[41].s = QString::fromLocal8Bit("x. ����һ�뿪�Ĳ�����ð�"); q[41].diff = true;  q[41].hu = false;



	/*q[3].l = 5;  q[4].l = 5;  q[5].s = QString::fromLocal8Bit("���壺�ߣ��������ȥ��䣨�ͳ�һϵ��֤������, �Ҳ��ǻ�");  q[5].diff = false;  q[5].hu = true;

	q[5].l = 6;  q[6].s = QString::fromLocal8Bit("��(�չ�ȥһ������ʻ֤,ѧ��֤,һ����ֵĶ�������Ƭ...");   q[6].diff = false;  q[6].hu = true;

	q[6].l = 7;  q[7].s = QString::fromLocal8Bit("z. ѯ����ֵĶ�����ʲô");      q[7].diff = true; q[7].hu = false;
	q[6].r = 8;  q[8].s = QString::fromLocal8Bit("x. ��ѯ��");      q[8].diff = true; q[8].hu = false;

	q[7].l = 9;  q[9].s = QString::fromLocal8Bit("���壺��ֵĶ���������������ɲ���ʲô��ֵĶ���, ����");  q[9].diff = false;  q[9].hu = true;
	q[9].l = 10; q[10].s = QString::fromLocal8Bit("�󱦱���������ô���۹⣬����������ȥ�ι�һ�¡�"); q[10].diff = false;  q[10].hu = false;

	q[8].l = 11; q[11].s = QString::fromLocal8Bit("���壺�߰ɣ�������������ˡ�"); q[11].diff = false;  q[11].hu = false;

	q[10].l = 12; q[11].l = 12;  q[12].s = QString::fromLocal8Bit("����ʹ���һ���ߵ�����ֵĶ�������ǰ�����ִ���");  q[12].diff = false;  q[12].hu = false;

	q[12].l = 13; q[13].s = QString::fromLocal8Bit("���壺��ô�����ǲ����ر�ÿ�~");  q[13].diff = false;  q[13].hu = false;

	q[13].l = 14; q[14].s = QString::fromLocal8Bit("�ң��Ǻ���������������ʲô��");  q[14].diff = false;  q[14].hu = false;

	q[14].l = 15;  q[15].s = QString::fromLocal8Bit("����:��д�,�˷�����,����ֱǰ,����η�壡����ɫ�󺣵�ӵ��");  q[15].diff = false;  q[15].hu = true;
	q[15].l = 16; q[16].s = QString::fromLocal8Bit("�Ǻ���Ľᾧ��������̫̫̫үү��ʱ��,���ǳ˴�����ն��...."); q[16].diff = false;  q[16].hu = false;

	q[16].l = 17; q[17].s = QString::fromLocal8Bit("�ң�(��ϣ��������ں�����ǰ�������Ѿ�û�к��ˡ�"); q[17].diff = false;  q[17].hu = false;

	q[17].l = 18; q[18].s = QString::fromLocal8Bit("���壺��˵��������һֱ�ڣ������ڣ��һ��ڣ���ô��˵��"); q[18].diff = false;  q[18].hu = true;
	q[18].l = 19; q[19].s = QString::fromLocal8Bit("��û�����أ�����");  q[19].diff = false;  q[19].hu = false;

	q[19].l = 20; q[20].s = QString::fromLocal8Bit("z.�ɴ��Ѿ���ʻ����,�޷����˰�..���ܺ��еĴ�,����������");  q[20].diff = true;  q[20].hu = false;
	q[19].r = 21; q[21].s = QString::fromLocal8Bit("x.�ǰ�����ʹ�Ѿ���ʧ����ʼ�����˼ǵ�.���˼ǵñ㲻����ʧ");  q[21].diff = true;  q[21].hu = false;

	q[20].l = 22; q[22].s = QString::fromLocal8Bit("���壺˭˵�����ܺ��У�Ҫ������л��ֳ��˵����⣬������");  q[22].diff = false;  q[22].hu = false;

	q[21].l = 23; q[23].s = QString::fromLocal8Bit("���壺ֻҪ�ǵã��㲻����ʧ��ֻҪ���ڹ������м�ֵ......");  q[23].diff = false;  q[23].hu = true;
	q[23].l = 24; q[24].s = QString::fromLocal8Bit("���������Ϊ��ȱ��һ����л��ֵ����ӣ�����������һ���ʻ��");  q[24].diff = false;  q[24].hu = false;

	q[22].l = 25; q[24].l = 25;  q[25].s = QString::fromLocal8Bit("���壺(̾��)��ô�����˰�...��һ��������ɳĮ����ô������"); q[25].diff = false;  q[25].hu = true;
	q[25].l = 26; q[26].s = QString::fromLocal8Bit("Ϊʲô���ǲ�һ��...�Ͳ���ôһ��...�ѵ������Ҫ������"); q[26].diff = false;  q[26].hu = false;

	q[26].l = 27; q[27].s = QString::fromLocal8Bit("�ң�(������л��ֵ�����...����������ʲô������"); q[27].diff = false;  q[27].hu = false;

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
