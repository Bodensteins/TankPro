#ifndef MENUPAUSE_H
#define MENUPAUSE_H

#include <QWidget>
#include "mypushbutton.h"
#include <QPainter>
#include "GameSet.h"
#include <QTimer>

class MenuPause :public QWidget
{
    Q_OBJECT
public:
    explicit MenuPause(Widget*, QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

    MyPushButton * quitBtn,
                 * continueBtn;


private:
    Widget* w_ptr;
    Menu *m_ptr;

signals:
    //退出游戏
    void quit_game();
    //继续游戏
    void continue_game();
};

#endif // MENUPAUSE_H
