#include "selectscene.h"
#include <QPushButton>
#include <QPainter>
#include "mypushbutton.h"
#include "playscene.h"
#include <QMenuBar>
#include <QSound>
SelectScene::SelectScene(QWidget *parent) : MyMainWindow(parent)
{
    //back返回按钮
    MyPushButton *btn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    btn->resize(72,32);
    btn->move(this->width()-72,this->height()-32);
    connect(btn,&QPushButton::clicked,this,&SelectScene::backBtnClicked);

    //关卡按钮20个
    const int colWidth = 70;
    const int rowHeigh = 70;
    //x，y偏移
    const int xOffset = 25;
    const int yOffset = 130;
    for(int i = 0; i < 20; i++)
    {
        MyPushButton *btn = new MyPushButton(":/res/LevelIcon.png",":/res/LevelIcon.png",this);
        btn->setText(QString::number(i+1));
        //排列
        //行 i / 4
        //列 i % 4
        int row = i/4;
        int col = i%4;
        //x坐标 = 列数 * 列宽 + x偏移
        //y坐标 = 行数 * 行宽 + y偏移

        int x = col * colWidth + xOffset;
        int y = row * rowHeigh + yOffset;

        btn->resize(57,57);
        btn->move(x,y);
        //选择关卡，添加音效
        connect(btn,&MyPushButton::clicked,[=](){
            QSound::play(":/res/TapButtonSound.wav");
            //点击关卡按钮后打开一个新的场景PlayScene
            PlayScene *playScene = new PlayScene(i+1);
            //设置playScene关闭的时候自动释放
            playScene->setAttribute(Qt::WA_DeleteOnClose);
            //隐藏当前界面
            this->hide();
            //显示新界面
            playScene->show();
            //将窗口移动到当前窗口的位置
            playScene->move(this->pos());

            //当PlayScene场景点击back按钮后，当前场景隐藏，selectScene显现
            //返回按钮被点击时，添加音效
            connect(playScene,&PlayScene::backBtnClicked,[=](){
                QSound::play(":/res/BackButtonSound.wav");
                this->show();
                playScene->close();
                //将窗口移动到当前窗口的位置
                this->move(playScene->pos());
            });
        });
    }
}

void SelectScene::paintEvent(QPaintEvent *event)
{
    //绘制背景图片
    QPainter painter(this);
    //搬动画家到菜单栏下
    painter.translate(0,this->menuBar()->height());
    //画背景图
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制logo
    pix.load(":/res/Title.png");
    painter.drawPixmap(0,0,pix);
}
