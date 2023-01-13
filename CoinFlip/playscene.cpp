#include "playscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QMenuBar>
#include <QLabel>
#include "coinbutton.h"
#include "dataconfig.h"
#include <QTimer>
#include <QMessageBox>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>
PlayScene::PlayScene(int level,QWidget *parent) : MyMainWindow(parent)
{
    this->mHashWin = false;
    //back返回按钮
    MyPushButton *btn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    btn->resize(72,32);
    btn->move(this->width()-72,this->height()-32);
    connect(btn,&QPushButton::clicked,this,&PlayScene::backBtnClicked);

    //添加左下角的label
    QLabel *label = new QLabel(this);
    //设置label大小
    label->resize(150,50);
    label->setText(QString("Level:%1").arg(level));
    //设置字体
    label->setFont(QFont("华文新魏",20));
    //移动到左下角
    label->move(30,this->height()-label->height());

    //取出第几关的二维数组数据
    dataConfig data;
    QVector<QVector<int>> dataArray = data.mData[level];

    //16个硬币按钮
    const int rowheight = 50;
    const int colWidth = 50;
    const int xOffset = 57;
    const int yOffset = 200;
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            CoinButton *btn = new CoinButton(this);
            //存储按钮到数组第几行第几列
            this->mCoins[row][col] = btn;
            //x坐标 = 列数 * 列宽 + x偏移
            //y坐标 = 行数 * 行宽 + y偏移
            int x = col * colWidth + xOffset;
            int y = row * rowheight + yOffset;
            btn->resize(50,50);
            btn->move(x,y);
            //设置按钮状态 row行和col列的值，从dataConfig的数据中获取
            btn->setStat(dataArray[row][col]);

            connect(btn,&CoinButton::clicked,[=](){
                //每次点击硬币的时候就改变状态，状态置反
                //btn->flip();
                this->flip(row,col);
            });
        }
    }
}

void PlayScene::flip(int row, int col)
{
    if(this->mHashWin)
    {
        //胜利直接返回
        return ;
    }
    this->mCoins[row][col]->flip();
    //翻金币的音效
    QSound::play(":/res/ConFlipSound.wav");
    //设置翻其他硬币延时
    QTimer::singleShot(250,[=](){
        //翻动上下左右的硬币
        if(row-1 > 0){
            //翻动上一行的硬币
            this->mCoins[row-1][col]->flip();
        }
        if(row+1 < 4){
            //翻动下一行的硬币
            this->mCoins[row+1][col]->flip();
        }
        if(col-1 > 0){
            //翻动左边的硬币
            this->mCoins[row][col-1]->flip();
        }
        if(col+1 < 4){
            //翻动右边的硬币
            this->mCoins[row][col+1]->flip();
        }
        //判断游戏是否胜利
        this->judgeWin();
    });

}

void PlayScene::judgeWin()
{
    //16个硬币按钮判断状态都是1  表示胜利
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
              //判断某个硬币是银币
            if(!this->mCoins[row][col]->stat()){
                //只要有一个银币，就返回，游戏继续
                return ;
            }
        }
    }
    //QMessageBox::information(this,"恭喜","你已经取得胜利");

    //播放胜利动画
    QLabel *labelWin = new QLabel(this);
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    labelWin->setPixmap(pix);
    labelWin->resize(pix.size());
    labelWin->move((this->width()-labelWin->width())/2,-labelWin->height());
    labelWin->show();

    QPropertyAnimation *animation = new QPropertyAnimation(labelWin,"geometry",this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(),labelWin->y()+100,labelWin->width(),labelWin->height()));
    animation->setDuration(1000);
    //设置运动曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //播放完自动删除动画对象
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    //播放胜利音效
    QSound::play(":/res/LevelWinSound.wav");
    //置胜利状态为true
    this->mHashWin = true;
    //胜利后按钮不可翻动
//    for(int row = 0; row < 4; row++){
//        for(int col = 0; col < 4; col++){
//            this->mCoins[row][col]->setEnabled(false);
//        }
//    }
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    //绘制背景图片
    QPainter painter(this);
    //搬动画家
    painter.translate(0,this->menuBar()->height());
    //画背景图
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制logo
    pix.load(":/res/Title.png");
    //将logo缩放50%
    pix = pix.scaled(pix.width()/2,pix.height()/2);
    painter.drawPixmap(0,0,pix);

}
