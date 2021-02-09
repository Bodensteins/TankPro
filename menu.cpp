#include "menu.h"
#include "widget.h"

Menu::Menu(QWidget *parent)
    : QWidget(parent),
      startBtn(new MyPushButton(":/ui/startBtn.png")),
      continueBtn(new MyPushButton(":/ui/continueBtn.png")),
      quitBtn(new MyPushButton(":/ui/quitBtn.png")),
      c_ptr(nullptr),
      i_ptr(nullptr)
{
    setFixedSize(26*UNIT,26*UNIT);
    //设置窗口标题
    setWindowTitle(GAME_TITLE);
    //设置窗口图标
    setWindowIcon(QIcon(ICON));

    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5, this->height()*0.2);
    continueBtn->setParent(this);
    continueBtn->move(this->width()*0.5-continueBtn->width()*0.5, this->height()*0.45);
    quitBtn->setParent(this);
    quitBtn->move(this->width()*0.5-quitBtn->width()*0.5, this->height()*0.7);

    c_ptr = new MenuChooseLevel;

    connect(startBtn,&MyPushButton::clicked,[=](){

       //按下弹起特效
       startBtn->zoom_down();
       startBtn->zoom_up();

       QTimer::singleShot(100,this,[=](){
           if(c_ptr==nullptr)
                c_ptr=new MenuChooseLevel;
           c_ptr->show();
           this->close();

           //监听关卡选择菜单返回信号
           connect(c_ptr,&MenuChooseLevel::back_menu,this,[=](){
               //qDebug()<<"收到信号";
               c_ptr->close();
               this->show();
           });
       });
    });

    connect(continueBtn,&MyPushButton::clicked,[=](){

       //按下弹起特效
       continueBtn->zoom_down();
       continueBtn->zoom_up();

       QTimer::singleShot(100,this,[=](){
            i_ptr=new Instruction;
            i_ptr->show();
       });

    });

    connect(quitBtn,&MyPushButton::clicked,[=](){

       //按下弹起特效
       quitBtn->zoom_down();
       quitBtn->zoom_up();

       QTimer::singleShot(100,this,[=](){
       this->close();
       });
    });



}

Menu::~Menu()
{}

void Menu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/ui/begin_background.png");
    painter.drawPixmap(0,0,pix);

    painter.drawPixmap(10,-11,QPixmap(ICON));

    painter.drawPixmap(140,10,QPixmap(TITTLE));
}
