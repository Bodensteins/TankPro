#include "menupause.h"
#include "GameSet.h"

MenuPause::MenuPause(Widget *p, QWidget *parent)
    : QWidget(parent),
      w_ptr(p)
{
    this->setFixedSize(300,300);

    //setAttribute(Qt::WA_DeleteOnClose);


    quitBtn = new MyPushButton(":/ui/pause_quit.png");
    continueBtn = new MyPushButton(":/ui/pause_continue.png");

    continueBtn->setParent(this);
    continueBtn->move(77,70);
    quitBtn->setParent(this);
    quitBtn->move(77,170);

    //退出游戏
    connect(quitBtn,&MyPushButton::clicked,[=](){

       //按下弹起特效
       quitBtn->zoom_down();
       quitBtn->zoom_up();


       QTimer::singleShot(100,this,[=](){
           this->close();
           emit this->quit_game();
       });

    });

    connect(continueBtn,&MyPushButton::clicked,[=](){

       //按下弹起特效
       continueBtn->zoom_down();
       continueBtn->zoom_up();

       QTimer::singleShot(100,this,[=](){
           this->close();
           emit this->continue_game();
       });

    });
}

void MenuPause::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/ui/begin_background.png");
    painter.drawPixmap(0,0,pix);
}
