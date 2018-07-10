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
	font.setFamily("微软雅黑");
	font.setPointSize(14);	// 大小
	font.setBold(true);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);	// 设置字符间距
	painter.setFont(font);	// 使用字体

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

	p[0]= QString::fromLocal8Bit("今天是第6277天，");
	p[1] = QString::fromLocal8Bit("是那个老头离开后的第一天，");
	p[2] = QString::fromLocal8Bit("遇见老头的第157天");
	p[3] = QString::fromLocal8Bit("是—————"); 
	p[4] = QString::fromLocal8Bit("距离上次自杀失败后的第157天。");
	p[5] = QString::fromLocal8Bit("已经没什么值得留恋的了啊");
	p[6] = QString::fromLocal8Bit("除了——老头最后留下的信");
	p[7] = QString::fromLocal8Bit("是否查看信件?  ");
	p[8] = QString::fromLocal8Bit("  z. 不了     x. 看一下");

	p[30]= QString::fromLocal8Bit("还是算了...毕竟也是要去陪他的人了，");
	p[31] = QString::fromLocal8Bit("有什么东西在到时候再说吧。");
	p[32] = QString::fromLocal8Bit("（滴滴答答的声音响起..）");
	p[33] = QString::fromLocal8Bit("不对...我, 似乎..上不了天堂啊..");
	p[34] = QString::fromLocal8Bit("抱歉，老头...（BadEnding）");
}

Begining::~Begining()
{
    delete ui;
}
