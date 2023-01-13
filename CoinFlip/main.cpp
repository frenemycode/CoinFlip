#include "mymainwindow.h"
#include <QApplication>
#include "startscene.h"
#include "selectscene.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MyMainWindow w;
//    w.show();
    //游戏开始场景
    StartScene s;
    s.show();
    //选择关卡
//    SelectScene ss;
//    ss.show();

    return a.exec();
}
