#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
class CoinButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CoinButton(QWidget *parent = nullptr);

    int stat() const;//获取mStat的值
    void setStat(int stat);//设置mStat的值

    //setStat带动画的函数
    void setStatWithAnimation(int stat);

    //硬币翻转函数
    void flip();


signals:

public slots:
protected:
    //绘图事件
    void paintEvent(QPaintEvent *event);

private:
    //硬币状态：0表示银币，1表示金币
    int mStat;//按住alt+enter 就可以快速设置set和get函数

    //记录当前帧数动画帧数
    int mFrame;
    //定时器
    QTimer mTimer;
};

#endif // COINBUTTON_H
