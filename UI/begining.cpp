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
	p[31] = QString::fromLocal8Bit("有什么东西到时候再说吧。");
	p[32] = QString::fromLocal8Bit("（滴滴答答的声音响起..）");
	p[33] = QString::fromLocal8Bit("不对...我, 似乎..上不了天堂啊..");
	p[34] = QString::fromLocal8Bit("抱歉，老头...（BadEnding）");

	p[10] = QString::fromLocal8Bit("打开信件:");
	p[11] = QString::fromLocal8Bit("丫头，老头这辈子没啥愿望，就想去外面把世界看一遭");
	p[12] = QString::fromLocal8Bit("知道你不喜欢这世界，但还是想厚着脸皮让你替我看一遍");
	p[13] = QString::fromLocal8Bit("如果你愿意的话，就带上老头子的拐杖一起");
	p[14] = QString::fromLocal8Bit("让我们");
	p[15] = QString::fromLocal8Bit("这一次，");
	p[16] = QString::fromLocal8Bit("再一次，");
	p[17] = QString::fromLocal8Bit("最后一次，");
	p[18] = QString::fromLocal8Bit("试着去爱这个世界吧。");

	p[21] = QString::fromLocal8Bit("什么嘛...这么自作主张的就决定了..");
	p[22] = QString::fromLocal8Bit("根本就没有考虑我的意见");
	p[23] = QString::fromLocal8Bit("..一开始擅自救我就是这样，到现在还是这样，");
	p[24] = QString::fromLocal8Bit("根本就没有问过我想不想活着啊。");
	p[25] = QString::fromLocal8Bit("z.决定出发    x.拒绝行动");

	p[40] = QString::fromLocal8Bit("抱歉啊，老头...一直以来都在为别人活着...");
	p[41] = QString::fromLocal8Bit("那么这次，请让我为自己去死。。");
	p[42] = QString::fromLocal8Bit("真是过分...肯定早就猜到我会同意了吧");
	p[43] = QString::fromLocal8Bit("不过，才不仅仅因为你啊，");
	p[44] = QString::fromLocal8Bit("只是因为，只是因为，");
	p[45] = QString::fromLocal8Bit("我也想在给自己一次机会，");
	p[46] = QString::fromLocal8Bit("一次救赎的机会。");
}

Begining::~Begining()
{
    delete ui;
}
