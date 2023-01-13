#include "startscene.h"
#include <QPushButton>
#include "mypushbutton.h"
#include <QTimer>
#include "selectscene.h"
#include <QSound>
StartScene::StartScene(QWidget *parent) : MyMainWindow(parent)
{
    this->setWindowTitle("开始场景");
    MyPushButton *btn = new MyPushButton(":/res/MenuSceneStartButton.png",":/res/MenuSceneStartButton.png",this);
    btn->resize(114,114);
    //将按钮放在x=窗口的宽度一半-按钮的宽度一半，y=窗口高度*3/4-按钮的一半
    btn->move((this->width()-btn->width())/2,this->height()*3/4-btn->height()/2);

    //返回按钮被点击时
    connect(&this->mSelectScene,&SelectScene::backBtnClicked,[=](){
        QSound::play(":/res/BackButtonSound.wav");
        //当第二个窗口的返回按钮点击的时候
        this->show();
        this->mSelectScene.hide();
        //将返回的窗口移动到当前窗口的位置
        this->move(this->mSelectScene.pos());
    });
    //开始按钮被点击
    connect(btn,&QPushButton::clicked,[=](){
        //设置音效  必须引入 #include <QSound>  ,
        //使用QSound还得在.pro文件的QT       += core gui 后面加上multimedia
        QSound::play(":/res/TapButtonSound.wav");
        //将按钮设置为不可用
        btn->setEnabled(false);
        //播放向下的动画
        btn->moveDown();

        QTimer::singleShot(150,[=](){
            //往上走的动画会覆盖之前的动画，要等待之前的动画播放完毕后再调用
            btn->moveUp();
        });

        QTimer::singleShot(300,[=](){
            //将按钮设置为可用
            btn->setEnabled(true);

            //场景转换
            //隐藏当前场景
            this->hide();
            //显示第二个窗口
            this->mSelectScene.show();
            //将窗口移动到当前窗口的位置
            this->mSelectScene.move(this->pos());
        });

    });
}
