#include "ending.h"
#include "ui_ending.h"

ending::ending(int flag,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ending)
{
    ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
    backGround.load(":/ending/hospital.png");
    grabKeyboard();
    initWord(flag);
    space = 0;
}

void ending::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(0,0,backGround);

    /*painter.setPen(QColor(255,255,255));
    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    painter.setFont(font);*/

    for(int i = 0; i <= space ; i++){
        painter.drawText(50,50+40*i,p[i]);
    }

}

void ending::initWord(int flag){
    /*switch (flag) {
    case 1:
        p[0] = QString::fromUtf8("余年少时,不好赏乐,");
        p[1] = QString::fromUtf8("不好交友,不好学习,不好生活,");
        p[2] = QString::fromUtf8("然受人所托,忠人之事,劳碌半生,终止与此.");
        p[3] = QString::fromUtf8("忆往昔,皆成梦幻.");
        p[4] = QString::fromUtf8("思今朝,悔未完成,");
        p[5] = QString::fromUtf8("盼来世,光景万千.");
        p[6] = QString::fromUtf8("医院里,病床前.");
        p[7] = QString::fromUtf8("护士焦急的声音:");
        p[8] = QString::fromUtf8("医生医生,不好了,患者心电图不变了.");
        p[9] = QString::fromUtf8("医生(叹了一口气):");
        p[10] = QString::fromUtf8("还是没能救得了这孩子，   只希望他在自己的选择里也快乐罢了.");
        break;
    case 2:
        p[0] = QString::fromUtf8("医院里,病床前.");
        p[1] = QString::fromUtf8("唔,头疼    这是哪儿?");
        p[2] = QString::fromUtf8("医生:孩子,你醒来了啊");
        p[3] = QString::fromUtf8("我:老头?!你不是----不对,这里是哪儿?");
        p[4] = QString::fromUtf8("突然之间记忆涌入我的脑海,");
        p[5] = QString::fromUtf8("抑郁症初期的挣扎,中期的忽视,晚期的放弃");
        p[6] = QString::fromUtf8("明明都,都已经喜欢不起来这个世界了啊");
        p[7] = QString::fromUtf8("可是  梦境中的一次次经历  一次次感知的恢复  ");
        p[8] = QString::fromUtf8("我想我还是喜欢这个世界的,");
        p[9] = QString::fromUtf8("我还想,努力的,继续生活下去.");
        p[10] = QString::fromUtf8("这就是,我的救赎之旅.");
        break;
    case 3:
        p[0] = QString::fromUtf8("我在这个世界呆了很久,直到我老去,");
        p[1] = QString::fromUtf8("我又回到了和老头原来住的地方,");
        p[2] = QString::fromUtf8("虽然没能喜欢上这个世界,");
        p[3] = QString::fromUtf8("但我想,我至少不讨厌他了.");
        p[4] = QString::fromUtf8("最后闭眼的那一刻,我有些遗憾,并不后悔.");
        p[5] = QString::fromUtf8("医院里,病床前.");
        p[6] = QString::fromUtf8("医生:虽然没能醒过来,");
        p[7] = QString::fromUtf8("但能幸福的离去,未必不是一种好事.");
    default:
        break;
    }*/
}

void ending::keyPressEvent(QKeyEvent *e){
    if(space<=10 && e->key() == Qt::Key_Space){
        space++;
        repaint();
    }
}
ending::~ending()
{
    delete ui;
}
