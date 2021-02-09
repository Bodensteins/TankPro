#include "level_3.h"
#include "menu.h"
#include "level_1.h"
#include "enemy_list.h"
#include "bullet_list.h"
#include "center_list.h"
#include "game_map.h"
#include "ai.h"
#include "player.h"
#include "normal_enemy.h"
#include "super_enemy.h"
#include "turret.h"
#include "center.h"
Level_3::Level_3(MenuChooseLevel *p, QWidget *parent):
    Widget(p, parent),
    pauseBtn(new MyPushButton(":/ui/pause.png")),
    p_ptr(nullptr)
{
    ini_scene();
    play_game();
}
const int pass=9;
void Level_3::ini_scene()
{
    bac_pic.load(":/bac/bac_3.png");

    map_x=MAP_SIZE_X_3;
    map_y=MAP_SIZE_Y_3;
    timer=new QTimer(this);
    g_map=new Game_map(MAP_3,this);
    player=new Player(1*UNIT, 84*UNIT, DOWN, PLAYER_HP,
                      MAX_NORMAL_BULLET_NUM, this);
    enemy_ls=new Enemy_list(this);
    bullet_ls=new Bullet_list(this);
    center_ls=new Center_list(this);
    astar=new Astar(this);
    x=player->get_x()-12*UNIT;
    y=player->get_y()-12*UNIT;

    is_win=false;
    lv=3;

    ini_all_lists();

    setFixedSize(WIDGET_SIZE_X, WIDGET_SIZE_Y);

    setAttribute(Qt::WA_DeleteOnClose);

    //设置窗口标题
    setWindowTitle("Level 3");
    //设置窗口图标
    setWindowIcon(QIcon(ICON));

    timer->setInterval(RATE);

    update();
}

void Level_3::ini_all_lists()
{
    QFile data(QString(":/map/ini_center_3.txt"));
    if(!data.open(QIODevice::ReadOnly))
        exit(-1);
    QTextStream qts(&data);
    position x, y, type;
    while(!qts.atEnd())
    {
        qts>>x>>y>>type;

            //qDebug()<<type;
        center_ls->push_center(
                   new Center(x*UNIT, y*UNIT, PLAYER_CENTER_HP, type,this));
    }

    QFile file(QString(":/map/ini_enemy_3.txt"));
    if(!file.open(QIODevice::ReadOnly))
        exit(-1);
    QTextStream qs(&file);
    //int num=0;
    while(!qs.atEnd())
    {
        //num++;
        qs>>x>>y>>type;
        switch(type){
        case 2:
            enemy_ls->push_enemy(new Turret(x*UNIT,y*UNIT,this));
            break;
        case 3:
            enemy_ls->push_enemy(new Normal_enemy(x*UNIT, y*UNIT, DOWN, this));
            break;
        case 4:
            enemy_ls->push_enemy(new Super_enemy(x*UNIT, y*UNIT, y%4, this));
            break;

        //default:
          //  qDebug()<<num<<type;
            //exit(-1);
        }
    }


}

void Level_3::play_game()
{

    timer->start();

    connect(timer , &QTimer::timeout,[=](){
    //游戏中的元素 绘制到屏幕中 再调用paintEvent函数
        bullet_ls->move_all_bullets();
        bullet_ls->check_bullet_list();

        center_ls->check_all_centers();

        astar->update_map();
        enemy_ls->update_all_path();
        enemy_ls->ctrl_all_enemy();
        enemy_ls->check_enemy_exist();

        player->tank_move();
        player->enter_center_react();
        //qDebug()<<player->get_x()/UNIT<<player->get_y()/UNIT;
        g_map->check_all_barriers_states();

        check_game_over();
        update();
    });

    //胜利图片加载
    QLabel * winLabel = new QLabel;
    QPixmap winPix;
    winPix.load(":/others/victory.png");
    winLabel->setGeometry(0,0,winPix.width(),winPix.height());
    winLabel->setPixmap(winPix);
    winLabel->setParent(this);
    winLabel->move(15,-347);

    //失败图片加载
    QLabel * defLabel = new QLabel;
    QPixmap defPix;
    defPix.load(":/others/defeat.png");
    defLabel->setGeometry(0,0,defPix.width(),defPix.height());
    defLabel->setPixmap(defPix);
    defLabel->setParent(this);
    defLabel->move(15,-347);

    //暂停按钮
    pauseBtn->setParent(this);
    pauseBtn->move(560,300);

    if(p_ptr!=nullptr)
        delete  p_ptr;

    p_ptr = new MenuPause(this);

    connect(pauseBtn,&MyPushButton::clicked,[=](){

       pauseBtn->zoom_down();
       pauseBtn->zoom_up();

       QTimer::singleShot(100,this,[=](){
            timer->stop();
            p_ptr->show();

            connect(p_ptr,&MenuPause::quit_game,this,[=](){
                //qDebug()<<"收到信号";
                this->close();
            });
            connect(p_ptr,&MenuPause::continue_game,this,[=](){
                //qDebug()<<"收到信号";
                timer->start();
            });
       });
    });


    connect(this, &Widget::lost, [=](){
        QPropertyAnimation * animation_lost = new QPropertyAnimation(defLabel,"geometry");
        animation_lost->setDuration(300);
        animation_lost->setStartValue(QRect(defLabel->x(),defLabel->y(),defLabel->width(),defLabel->height()));
        animation_lost->setEndValue(QRect(defLabel->x(),defLabel->y()+200,defLabel->width(),defLabel->height()));
        animation_lost->setEasingCurve(QEasingCurve::OutBounce);
        animation_lost->start();

        QTimer::singleShot(3600,this,[=](){
        menu_choose_level->show();
        close();
        });

    });

    connect(this, &Widget::win, [=](){
        QPropertyAnimation * animation_win = new QPropertyAnimation(winLabel,"geometry");
        animation_win->setDuration(300);
        animation_win->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
        animation_win->setEndValue(QRect(winLabel->x(),winLabel->y()+200,winLabel->width(),winLabel->height()));
        animation_win->setEasingCurve(QEasingCurve::OutBounce);
        animation_win->start();

        QTimer::singleShot(3600,this,[=](){
        menu_choose_level->show();
        close();
        });
    });
}

void Level_3::check_game_over()
{
    if(player->get_hp()<=0)
        lost();
    else if(player->lv3_vic==pass)
        win();

}
