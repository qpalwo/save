#include "sceneruins.h"
#include "ui_sceneruins.h"
#include "UI/UiManager.h"
SceneRuins::SceneRuins(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneRuins)
{
    ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	startMovie = new QMovie(":/ruins/scene/tower.gif");
	startLabel = new QLabel(this);
	startLabel->setMovie(startMovie);
	QTimer::singleShot(4000, this, SLOT(stopStratMovie()));
	startMovie->start();
	startLabel->setGeometry(0, 0, 960, 720);

	Player::getInstance()->setMapStaus(3);

    backX = 0;
    backY = 0;
    playerX = 0;
	talk = 0;
	ti = 0;

    stop = false;
    left = false;
	first = false;
	zxLock= false;
	space1 = false;
	space2 = false;
	rightThing = false;

	loadImage();
	loadPlot(); 

    menuwidget *menu = new menuwidget("ruins",this);
    setFocus();
    menu->show();

	v = GameWorld::getInstance()->getVolume();//get volume
	bgm = new QMediaPlayer();//new
	//bgm->setMedia(QUrl("qrc://res/music/beginning_bgm.mp3"));//music set
	//bgm->setVolume(v);//set volume
	//bgm->play();//play music


	myCursor = new QCursor(QPixmap(":/mouse/pointer_3.png"));//new cursor
	this->setCursor(*myCursor);//set cursor
}

void SceneRuins::stopStratMovie() {
	startMovie->stop();
	startLabel->close();
}

void SceneRuins::loadImage()
{
    backGround.load(":/ruins/scene/ruins_2.png");
    earth.load(":/ruins/scene/ruins_1.png");
	illustrate.load(":/ruins/scene/illustrate_ruins.png");
	sky.load(":/ruins/scene/ruins_back.png");
	tower.load(":/ruins/scene/tower.png");

    player = new QMovie(":/player/main.gif");
    player_left = new QMovie(":/player/main_left.gif");
	color = new QMovie(":/ruins/scene/color.gif");
	child.load(":/ruins/people/pink_left.png");
	conver.load(":/conver/convar/convar.png");
    player->start();
    player_left->start();
	color->start();
}

void SceneRuins::reFresh() {
	update();
}

void SceneRuins::initTimer() {
	if (!isPlay) {
		QTimer *timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(reFresh()));
		timer->start(150);
		player->stop();
	}
}

void SceneRuins::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

	QPen pen; //����
	pen.setColor(QColor(255, 255, 0));
	QBrush brush(QColor(255, 255, 0, 125)); //��ˢ
	painter.setPen(pen); //��ӻ���
	painter.setBrush(brush); //��ӻ�ˢ

	painter.setPen(QColor(100, 200, 200));
	QFont font;
	font.setFamily("΢���ź�");
	font.setPointSize(14);	// ��С
	font.setBold(true);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);	// �����ַ����
	painter.setFont(font);	// ʹ������
	

	painter.drawImage(0, 0, sky);
	painter.drawImage(backX, backY , backGround);
	

    if (playerX == 430)   stop = true;

    if (left)  {
        painter.drawPixmap(playerX, 235, 100, 200, player_left->currentPixmap());
    }  else  painter.drawPixmap(playerX, 235, 100, 200, player->currentPixmap());

	if ((waitTime>0) && (waitTime <= 28))
		painter.drawRect(playerX, 260, 10 + waitTime * 3, 20); //���ƾ��� 

	if (waitTime > 28) {
		if (waitTime == 29) {
			ti = qrand() % 7; 
			Player::getInstance()->addBagThing(ti + 6);
		}
		painter.drawText(380, 280, get[ti]);
	}

    painter.drawImage(backX, backY, earth);
	if (first) {
		painter.drawText(180, 150, begin);
		painter.drawImage(0, 230, illustrate);
	}

	painter.setPen(QColor(250, 250, 250));
	if (playerX >= 440) {
		painter.drawImage(0, 0, tower);
		painter.drawImage(750, 25, child);
		painter.drawImage(0, 0, conver);
		
		if (zxLock) {
			painter.drawText(280, 612, record_1);
			painter.drawText(280, 666, record_2);
		}
		else {
			painter.drawText(280, 612, q[talk].s);    f[talk] = true;
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
	
	if (talk == 28) {  
		if (f[4] && f[14]) {
			if (!space1){
				painter.drawText(280, 612, q[40].s);
				painter.drawText(280, 666, q[41].s);
			}
			else {
			
				initTimer();
				painter.drawPixmap(0, 0, 960, 720, color->currentPixmap());
				painter.drawImage(0, 0, tower);
				if (left) 	painter.drawPixmap(playerX, 235, 100, 200, player_left->currentPixmap());
				else  painter.drawPixmap(playerX, 235, 100, 200, player->currentPixmap());
				painter.drawImage(750, 25, child);

				painter.drawText(160, 520, Ending1);
				painter.drawText(100, 565, Ending2);
				painter.setPen(QColor(0, 250, 250));
				painter.drawText(350, 610, get[9]);
				if (!ifget) {
					Player::getInstance()->addBagThing(2);
					ifget = true;
				}
				if (!isSpace) {
					GainAchieve *Joker = new  GainAchieve(3, this);
					Joker->show();
					isSpace = true;
					tomap = true;
				}
			}
		}
		else {
			if (!space1) 
				painter.drawText(280, 612, q[30].s);
			else {
				if (!space2) 
					painter.drawText(280, 612, q[31].s);
				else {
					painter.drawText(280, 612, q[32].s);
					painter.drawText(280, 666, q[33].s);
					tomap = true;
				}
			}
		}
	}

	first = false;
}

void SceneRuins::keyPressEvent(QKeyEvent* e)
{
	if (tomap) UiManager::getInstance()->fromRunisToMap();
    if (stop)
    {
        switch (e->key())
        {
        case Qt::Key_A: backX += 10;  left = true;    break;
        case Qt::Key_Left:  backX += 10; left = true;  break;
        case Qt::Key_D: backX -= 10; left = false    ; break;
        case Qt::Key_Right:    backX -= 10;  left = false;   break;
        default: break;
        }

        if (backX < BDL) {  backX += 10; playerX += 10;  stop = false;  }
        if (backX > BDR)  {
            backX -= 10;
            stop = false;
            playerX -= 10;
        }

		if ((e->key() == Qt::Key_S) || (e->key() == Qt::Key_Down)) {
			if (underDoor(2))	waitTime++;
		}	else waitTime = 0;
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
        if (playerX > 860)   playerX -= 10;

		if ((e->key() == Qt::Key_S) || (e->key() == Qt::Key_Down)) {
			if (underDoor(1))	waitTime++;
		}	else waitTime = 0;

		if ((space1) && (space2)) {
			GainAchieve *Joker = new  GainAchieve(4, this);
			Joker->show();
		}
	    if ((talk == 28) && space1) space2 = true;
		if ((talk == 28) && (e->key() == Qt::Key_Space)) space1 = true;
	
		if ((e->key() == Qt::Key_Space) && (!q[talk].diff))  talk = q[talk].l;
		if (q[talk].diff) {
			if (e->key() == Qt::Key_Z) { talk = q[talk - 1].l;  zxLock = false; }
			if (e->key() == Qt::Key_X) { talk = q[talk].l;  zxLock = false; }
		}

		if (talk == 11)  GameWorld::getInstance()->beginKeepMoving();
  
        if (playerX < 430) first = true;
    }

    update();
}

bool SceneRuins::underDoor(int n) {
	if (n == 1) {
		if ((playerX >= 390) && (playerX <= 420)) return true;
	}
	if (n == 2) {
		if ((backX >= -500) && (backX <= -460))  return true;
		if ((backX >= -1340) && (backX <= -1300))  return true;
		if ((backX >= -2040) && (backX <= -2000))  return true;
	}
	return false;
}

void SceneRuins::gameOver() {
	gameover = true;
}

void SceneRuins::bagThingClick(int n) {
	if (n == 2) rightThing = true;
}

void SceneRuins::changeState(bool a, bool b, bool c, bool d) {
	statement[1] = a;
	statement[2] = b;
	statement[3] = c;
	statement[4] = d;
}



void SceneRuins::loadPlot() {
	begin = QString::fromLocal8Bit("ǧƪһ�ɵĻ�ɫ...��Ȼ,ѹ�ֵĲ���Ҳ��ʹ�����������찡");

	get[0] = QString::fromLocal8Bit("�����Ʒ [���ڹ�ͷ]");
	get[1] = QString::fromLocal8Bit("�����Ʒ  [ơ��]");
	get[2] = QString::fromLocal8Bit("�����Ʒ [�ɿ���]");
	get[3] = QString::fromLocal8Bit("�����Ʒ [������]");
	get[4] = QString::fromLocal8Bit("�����Ʒ  [�ٷ�]");
	get[5] = QString::fromLocal8Bit("�����Ʒ  [Ůװ]");
	get[6] = QString::fromLocal8Bit("�����Ʒ [����֮��]");
	get[9] = QString::fromLocal8Bit("���������Ʒ [����]");


	q[0].s= QString::fromLocal8Bit("�����ƺ���ʲô������(̧ͷ)"); q[0].diff = false; q[0].hu = false;

	q[0].l = 1; q[1].s = QString::fromLocal8Bit("������һ��С���������ϣ���Ҫ��������"); q[1].diff = false; q[1].hu = false;

	q[1].l = 2; q[2].s = QString::fromLocal8Bit("z.���ȥ��ס����Ҫ������ֵ����**��"); q[2].diff = true; q[2].hu = false;
    q[3].s = QString::fromLocal8Bit("x.�����ȥ"); q[3].diff = true; q[3].hu = false;

	q[2].l = 4; q[4].s = QString::fromLocal8Bit("�����������۰�"); q[4].diff = false; q[4].hu = false;

	q[3].l = 5; q[5].s= QString::fromLocal8Bit("���ˣ��᲻������������"); q[5].diff = false; q[5].hu = false;

	q[4].l = 6; q[6].s= QString::fromLocal8Bit("�ң��ԣ�������ôΣ�յ���Ϸ��һ���������ܲ���ȫ"); q[6].diff = false; q[6].hu = false;

	q[6].l = 7; q[7].s= QString::fromLocal8Bit("С�����ҡ����Ҳ�û��������Ϸ������������Ҫ���£�"); q[7].diff = false; q[7].hu = false;

	q[7].l = 8; q[8].s = QString::fromLocal8Bit("�ң�ʲô��Ҫ�����鰡��"); q[8].diff = false; q[8].hu = false;

	q[8].l = 9; q[9].s = QString::fromLocal8Bit("С������Ҫ��һ������Ҫ���ˣ����������ϣ�"); q[9].diff = false; q[9].hu = false;

	q[5].l = 10; q[10].s= QString::fromLocal8Bit("С����ûʲô���������Լ����Եģ�"); q[10].diff = false; q[10].hu = false;

	q[9].l = 11; q[10].l = 11; q[11].s= QString::fromLocal8Bit("С����лл��.���ڵ��˰�...��Ȼ����ʲô��û��"); q[11].diff = false; q[11].hu = false;

	q[11].l = 12; q[12].s = QString::fromLocal8Bit("z. ����ֻ�ǿ���������"); q[12].diff = true; q[12].hu = false;
	q[13].s= QString::fromLocal8Bit("x. Ϊʲô���ɶ��û��"); q[13].diff = true; q[13].hu = false;

	q[12].l = 14; q[14].s = QString::fromLocal8Bit("С����ʲô��������"); q[14].diff = false; q[14].hu = false;

	q[14].l = 15; q[15].s= QString::fromLocal8Bit("�ң���Ҫ���˿��������ѡ���������ʵ����һֱ����"); q[15].diff = false; q[15].hu = false;

	q[15].l = 16; q[16].s = QString::fromLocal8Bit("С�����������������Ǹ������������"); q[16].diff = false; q[16].hu = false;

	q[16].l = 17; q[17].s = QString::fromLocal8Bit("�ң����᣿"); q[17].diff = false; q[17].hu = false;

	q[17].l = 18; q[18].s = QString::fromLocal8Bit("С��������������һ��"); q[18].diff = false; q[18].hu = false;

	q[13].l = 19; q[19].s = QString::fromLocal8Bit("С������Ǹ���������˵���������������ҵġ�����"); q[19].diff = false; q[19].hu = true;
	q[20].s = QString::fromLocal8Bit("��ֻ�������һ��"); q[20].diff = false; q[20].hu = false;

	q[19].l = 21; q[18].l = 21; q[21].s= QString::fromLocal8Bit("С������㣬��˵���ϵ�������ĺ����۾���"); q[21].diff = false; q[21].hu = false;

	q[21].l = 22; q[22].s= QString::fromLocal8Bit("z. ��Ȼ��"); q[22].diff = true; q[22].hu = false;
	q[23].s= QString::fromLocal8Bit("x. ��̫��"); q[23].diff = true; q[23].hu = false;

	q[22].l = 24; q[23].l = 24; q[24].s = QString::fromLocal8Bit("С������ԭ�������ã����ڿ������ˡ�"); q[24].diff = false; q[24].hu = false;

	q[24].l = 25; q[25].s = QString::fromLocal8Bit("С���������뿪�����Ϳ�ʼ���ˣ������Ǳ����۾����ˣ�"); q[25].diff = false; q[25].hu = true;
	q[26].s = QString::fromLocal8Bit("��Ŷ������ڴ�˭��ע�Ӱɡ�"); q[26].diff = false; q[26].hu = false;

	q[25].l = 27; q[27].s = QString::fromLocal8Bit("�ң���������Ҳ��ɡ�����"); q[27].diff = false; q[27].hu = false;
	q[27].l = 28; q[28].diff = false; q[28].hu = false; q[28].l = 28;


	q[30].s = QString::fromLocal8Bit("С��:лл���������ô�ã�����ɿ�������ɣ��ʺ�һ·����"); q[30].diff = false; q[30].hu = false;

	q[30].l = 31; q[31].s= QString::fromLocal8Bit("�ң�һ·������"); q[31].diff = false; q[31].hu = false;

	q[31].l = 32; q[32].s = QString::fromLocal8Bit("С����������㲻���ǻ�ͣ������"); q[32].diff = false; q[32].hu = false;

	q[32].l = 33; q[33].s = QString::fromLocal8Bit("�ң�ͣ����������"); q[33].diff = false; q[33].hu = false;

	q[40].s= QString::fromLocal8Bit("С������֮��лл��㣬�����������ɡ�������Ȼ������"); q[40].diff = false; q[40].hu = true;
	q[41].s= QString::fromLocal8Bit("͸���ģ����������������ռ�������ߡ�"); q[41].diff = false; q[41].hu = false;

	Ending1= QString::fromLocal8Bit("��ְ�...���ɫ�ĸ���...��Ȼ��̫����ӳ������õ�ɫ��..."); 
	Ending2 = QString::fromLocal8Bit("�õ�Ӱ�ŵ����綼Ѥ�����...������ֵ++��������...���Ӳ�����������");
}

SceneRuins::~SceneRuins()
{
    delete ui;
}
