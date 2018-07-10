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
	font.setFamily("微软雅黑");
	font.setPointSize(14);	// 大小
	font.setBold(true);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);	// 设置字符间距
	painter.setFont(font);	// 使用字体

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

	p[0]= QString::fromLocal8Bit("今天是第6277天，");
	p[1] = QString::fromLocal8Bit("是那个老头离开后的第一天，");
	p[2] = QString::fromLocal8Bit("遇见老头的第157天");
	p[3] = QString::fromLocal8Bit("是—————"); 
	p[4] = QString::fromLocal8Bit("距离上次自杀失败后的第157天。");
	p[5] = QString::fromLocal8Bit("已经没什么值得留恋的了啊");
	p[6] = QString::fromLocal8Bit("除了——老头最后留下的信");
	p[7] = QString::fromLocal8Bit("是否查看信件?  ");
	p[8] = QString::fromLocal8Bit("  z. 不了     x. 看一下");
}

Begining::~Begining()
{
    delete ui;
}
