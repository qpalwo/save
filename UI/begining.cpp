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
	count = 0;
	jump = 0;
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

	}

}

void Begining::keyPressEvent(QKeyEvent *e) {
	if (count < 7) {
		if (e->key() == Qt::Key_Space) count++;
	}
	else {
		if (e->key() == Qt::Key_Z) { zx = true; jump = 1; }
		if (e->key() == Qt::Key_X) { zx = true; jump = 2; }
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
	p[31] = QString::fromLocal8Bit("��ʲô�����ڵ�ʱ����˵�ɡ�");
	p[32] = QString::fromLocal8Bit("���εδ�����������..��");
	p[33] = QString::fromLocal8Bit("����...��, �ƺ�..�ϲ������ð�..");
	p[34] = QString::fromLocal8Bit("��Ǹ����ͷ...��BadEnding��");
}

Begining::~Begining()
{
    delete ui;
}
