#include "begining.h"
#include "ui_begining.h"

Begining::Begining(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Begining)
{
    ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);

	zx = false;
	jump1 = false;
	Lock = false;
	c2 = 0;
	count = 0;
	jump = 0;
	jump2 = 0;
	load();
}


void Begining::paintEvent(QPaintEvent * e) {
	int i;
	QPainter painter(this);

	painter.setPen(QColor(255,255,255));
	QFont font;
	font.setFamily("΢���ź�");
	font.setPointSize(14);	// ��С
	font.setBold(true);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);	// �����ַ����
	painter.setFont(font);	// ʹ������

	painter.drawImage(0,0,back);

	if (!zx) {
		for (i = 0; i <= count; i++) {
			if (i == 7) {
				painter.drawText(290, 100 + i * 40, p[i]);
				painter.drawText(290, 140 + i * 40, p[i + 1]);
				break;
			}
			painter.drawText(290, 100 + i * 40, p[i]);
		}
	}
	if (jump == 1) {
		painter.drawText(290, 200, p[30]);
		painter.drawText(290, 240, p[31]);
		if (jump1) {
			painter.drawText(290, 300, p[32]);
			painter.drawText(290, 340, p[33]);
			painter.drawText(290, 380, p[34]);
		}
	}
	if (jump == 2) {
		if (c2 < 1) {
			painter.drawText(160, 140, p[10]);
			painter.drawText(220, 180, p[11]);
			painter.drawText(220, 220, p[12]);
			painter.drawText(220, 260, p[13]);
			painter.drawText(220, 300, p[14]);
			painter.drawText(220, 340, p[15]);
			painter.drawText(220, 380, p[16]);
			painter.drawText(220, 420, p[17]);
			painter.drawText(220, 460, p[18]);
		}
		else {
			if (!Lock) {
				for (i = 1; i <= c2; i++)
					painter.drawText(270, 140 + i * 40, p[20 + i]);
			}
			else {
				if (jump2 == 1) { 
					painter.drawText(260, 300 , p[40]);
					painter.drawText(260, 350, p[41]);
				}
				if (jump2 == 2) {
					painter.drawText(270, 200, p[42]);
					painter.drawText(270, 240, p[43]);
					painter.drawText(270, 280, p[44]);
					painter.drawText(270, 320, p[45]);
					painter.drawText(270, 360, p[46]);
				}
			}
		}
	}

}

void Begining::keyPressEvent(QKeyEvent *e) {

	if (jump == 2) {
		if (e->key() == Qt::Key_Space) c2++;
		if (c2 > 5) c2 = 5;
		if (e->key() == Qt::Key_Z) { Lock = true; jump2 = 2; }
		if (e->key() == Qt::Key_X) { Lock = true; jump2 = 1; }
	}

	if (jump == 0) {
		if (count < 7) {
			if (e->key() == Qt::Key_Space) count++;
		}
		else {
			if (e->key() == Qt::Key_Z) { zx = true; jump = 1; }
			if (e->key() == Qt::Key_X) { zx = true; jump = 2; }
		}
	}
	if ((jump == 1) && (e->key() == Qt::Key_Space)) jump1 = true;

	update();
}



void Begining::load() {
	back.load(":/ruins/scene/begining.png");

	p[0]= QString::fromLocal8Bit("�����ǵ�6277�죬");
	p[1] = QString::fromLocal8Bit("���Ǹ���ͷ�뿪��ĵ�һ�죬");
	p[2] = QString::fromLocal8Bit("������ͷ�ĵ�157��");
	p[3] = QString::fromLocal8Bit("�ǡ���������"); 
	p[4] = QString::fromLocal8Bit("�����ϴ���ɱʧ�ܺ�ĵ�157�졣");
	p[5] = QString::fromLocal8Bit("�Ѿ�ûʲôֵ���������˰�");
	p[6] = QString::fromLocal8Bit("���ˡ�����ͷ������µ���");
	p[7] = QString::fromLocal8Bit("�Ƿ�鿴�ż�?  ");
	p[8] = QString::fromLocal8Bit("  z. ����     x. ��һ��");

	p[30]= QString::fromLocal8Bit("��������...�Ͼ�Ҳ��Ҫȥ���������ˣ�");
	p[31] = QString::fromLocal8Bit("��ʲô������ʱ����˵�ɡ�");
	p[32] = QString::fromLocal8Bit("���εδ�����������..��");
	p[33] = QString::fromLocal8Bit("����...��, �ƺ�..�ϲ������ð�..");
	p[34] = QString::fromLocal8Bit("��Ǹ����ͷ...��BadEnding��");

	p[10] = QString::fromLocal8Bit("���ż�:");
	p[11] = QString::fromLocal8Bit("Ѿͷ����ͷ�Ⱳ��ûɶԸ��������ȥ��������翴һ��");
	p[12] = QString::fromLocal8Bit("֪���㲻ϲ�������磬�������������Ƥ�������ҿ�һ��");
	p[13] = QString::fromLocal8Bit("�����Ը��Ļ����ʹ�����ͷ�ӵĹ���һ��");
	p[14] = QString::fromLocal8Bit("������");
	p[15] = QString::fromLocal8Bit("��һ�Σ�");
	p[16] = QString::fromLocal8Bit("��һ�Σ�");
	p[17] = QString::fromLocal8Bit("���һ�Σ�");
	p[18] = QString::fromLocal8Bit("����ȥ���������ɡ�");

	p[21] = QString::fromLocal8Bit("ʲô��...��ô�������ŵľ;�����..");
	p[22] = QString::fromLocal8Bit("������û�п����ҵ����");
	p[23] = QString::fromLocal8Bit("..һ��ʼ���Ծ��Ҿ��������������ڻ���������");
	p[24] = QString::fromLocal8Bit("������û���ʹ����벻����Ű���");
	p[25] = QString::fromLocal8Bit("z.��������    x.�ܾ��ж�");

	p[40] = QString::fromLocal8Bit("��Ǹ������ͷ...һֱ��������Ϊ���˻���...");
	p[41] = QString::fromLocal8Bit("��ô��Σ�������Ϊ�Լ�ȥ������");
	p[42] = QString::fromLocal8Bit("���ǹ���...�϶���Ͳµ��һ�ͬ���˰�");
	p[43] = QString::fromLocal8Bit("�������Ų�������Ϊ�㰡��");
	p[44] = QString::fromLocal8Bit("ֻ����Ϊ��ֻ����Ϊ��");
	p[45] = QString::fromLocal8Bit("��Ҳ���ڸ��Լ�һ�λ��ᣬ");
	p[46] = QString::fromLocal8Bit("һ�ξ���Ļ��ᡣ");
}

Begining::~Begining()
{
    delete ui;
}
