#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QPainter>
MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    //窗口标题
    this->setWindowTitle("翻金币");
    //设置窗口icon
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置窗口固定大小
    this->setFixedSize(320,588);
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //绘制开始场景背景
    QPixmap pix(":/res/MenuSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
