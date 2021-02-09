#include "menu.h"
#include "level_1.h"
#include "enemy_list.h"
#include "bullet_list.h"
#include "center_list.h"
#include "game_map.h"
#include "turret.h"
#include "player.h"
#include "normal_enemy.h"
#include "super_enemy.h"
#include "center.h"

Level_1::Level_1(MenuChooseLevel *p, QWidget *parent):
    Widget(p, parent),
    pauseBtn(new MyPushButton(":/ui/pause.png")),
    p_ptr(nullptr)
{
    ini_scene();
    play_game();
}

void Level_1::ini_scene()
{
    bac_pic.load(":/bac/bac_6.png");

    map_x=MAP_SIZE_X_1;
    map_y=MAP_SIZE_Y_1;
    timer=new QTimer(this);
    g_map=new Game_map(MAP_1,this);
    player=new Player(27*UNIT, 40*UNIT, UP, PLAYER_HP,
                      MAX_NORMAL_BULLET_NUM, this);
    enemy_ls=new Enemy_list(this);
    bullet_ls=new Bullet_list(this);
    center_ls=new Center_list(this);
    astar=new Astar(this);
    x=player->get_x()-12*UNIT;
    y=player->get_y()-12*UNIT;
    lv=1;

    ini_all_lists();

    setAttribute(Qt::WA_DeleteOnClose);

    setFixedSize(WIDGET_SIZE_X, WIDGET_SIZE_Y);

    //设置窗口标题
    setWindowTitle("Level 1");
    //设置窗口图标
    setWindowIcon(QIcon(ICON));

    timer->setInterval(RATE);

    update();
}

void Level_1::ini_all_lists()
{
    enemy_ls->push_enemy(
                new Normal_enemy(2*UNIT, 0*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Normal_enemy(36*UNIT, 0*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Normal_enemy(6*UNIT, 15*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Normal_enemy(32*UNIT, 15*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Normal_enemy(3*UNIT, 35*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Normal_enemy(0, 46*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Normal_enemy(38*UNIT, 46*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Turret(19*UNIT, 2*UNIT, this));//
    enemy_ls->push_enemy(
                new Super_enemy(0*UNIT, 3*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Super_enemy(38*UNIT, 3*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Super_enemy(35*UNIT, 35*UNIT, DOWN, this));


    center_ls->push_center(
                new Center(38*UNIT,22*UNIT, 40,
                           SUPER_BULLET_CENTER,this));
    center_ls->push_center(
                new Center(19*UNIT,7*UNIT, 40,
                           SUPER_BULLET_CENTER,this));
    center_ls->push_center(
                new Center(0*UNIT,41*UNIT, 40,
                           NORMAL_BULLET_CENTER,this));
    center_ls->push_center(
                new Center(19*UNIT,48*UNIT, 40,
                           NORMAL_BULLET_CENTER,this));
    center_ls->push_center(
                new Center(19*UNIT,0, 40,
                           HP_CENTER,this));
    center_ls->push_center(
                new Center(0,22*UNIT, 40,
                           HP_CENTER,this));
    center_ls->push_center(
                new Center(38*UNIT,39*UNIT, 40,
                           HP_CENTER,this));
}

void Level_1::play_game()
{
    timer->start();
    //监听定时器的信号
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
        //qDebug()<<"You have lost!";
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
        //qDebug()<<"You have won!";
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

void Level_1::check_game_over()
{
    if(player->get_hp()<=0)
        lost();
    else if(enemy_ls->get_list_ptr()->empty())
        win();
}
