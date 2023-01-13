#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include <QWidget>
#include "mymainwindow.h"
class SelectScene : public MyMainWindow
{
    Q_OBJECT
public:
    explicit SelectScene(QWidget *parent = nullptr);

signals:
    void backBtnClicked();

public slots:

protected:
    void paintEvent(QPaintEvent *event);


};

#endif // SELECTSCENE_H
