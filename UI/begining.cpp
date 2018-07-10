#include "begining.h"
#include "ui_begining.h"

Begining::Begining(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Begining)
{
    ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);

	count = 0;
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

	if (count < 8) {
		for (i = 0; i <= count; i++) {
			if (i == 7) {
				painter.drawText(290, 100 + i * 40, p[i]);
				painter.drawText(290, 140 + i * 40, p[i + 1]);
				break;
			}
			painter.drawText(290, 100 + i * 40, p[i]);
		}
	}


}

void Begining::keyPressEvent(QKeyEvent *e) {

	if (e->key()==Qt::Key_Space) count++;
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
}

Begining::~Begining()
{
    delete ui;
}
