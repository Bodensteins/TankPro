#include "menuchooselevel.h"
#include "level_1.h"
#include "level_2.h"
#include "level_3.h"
#include <QDebug>

MenuChooseLevel::MenuChooseLevel(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(520,520);
    setWindowTitle("关卡选择");
    setWindowIcon(QIcon(ICON));

    startBtn1 = new MyPushButton(":/ui/first.png");
    startBtn2 = new MyPushButton(":/ui/second.png");
    startBtn3 = new MyPushButton(":/ui/third.png");
    back = new MyPushButton(":/ui/back.png");

    //关卡选择按钮
    startBtn1->setParent(this);
    startBtn1->move(this->width()*0.5-startBtn1->width()*0.5, this->height()*0.2);
    startBtn2->setParent(this);
    startBtn2->move(this->width()*0.5-startBtn2->width()*0.5, this->height()*0.45);
    startBtn3->setParent(this);
    startBtn3->move(this->width()*0.5-startBtn3->width()*0.5, this->height()*0.7);
    back->setParent(this);
    back->move(20,10);

    connect(startBtn1,&MyPushButton::clicked,[=](){

       //按下弹起特效
       startBtn1->zoom_down();
       startBtn1->zoom_up();

       QTimer::singleShot(100,this,[=](){
           w_ptr=new Level_1(this);
           w_ptr->show();
           close();
       });

    });

    connect(startBtn2,&MyPushButton::clicked,[=](){

       //按下弹起特效
       startBtn2->zoom_down();
       startBtn2->zoom_up();

       QTimer::singleShot(100,this,[=](){
           w_ptr=new Level_2(this);
           w_ptr->show();
           close();
       });

    });

    connect(startBtn3,&MyPushButton::clicked,[=](){

       //按下弹起特效
       startBtn3->zoom_down();
       startBtn3->zoom_up();
       QTimer::singleShot(100,this,[=](){
           w_ptr=new Level_3(this);
           w_ptr->show();
           close();
       });
    });

    connect(back,&MyPushButton::clicked,[=](){
       //按下弹起特效
       back->zoom_down();
       back->zoom_up();

       QTimer::singleShot(100,this,[=](){
        emit this->back_menu();
       });

    });
}

void MenuChooseLevel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/ui/begin_background.png");
    painter.drawPixmap(0,0,pix);

    painter.drawPixmap(140,10,QPixmap(":/tittle.png"));
}
