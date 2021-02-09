#ifndef MENUCHOOSELEVEL_H
#define MENUCHOOSELEVEL_H

#include <QWidget>
#include "mypushbutton.h"
#include <QPainter>
#include "GameSet.h"
#include <QTimer>


class MenuChooseLevel :public QWidget
{
    Q_OBJECT
public:
    explicit MenuChooseLevel(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

    MyPushButton * startBtn1,
                 * startBtn2,
                 * startBtn3,
                 * back;

private:
    Widget *w_ptr;

signals:
    //返回主菜单信号
    void back_menu();

};

#endif // MENUCHOOSELEVEL_H
