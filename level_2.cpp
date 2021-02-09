#include "level_2.h"
#include "turret.h"

#include "enemy_list.h"
#include "bullet_list.h"
#include "center_list.h"
#include "game_map.h"

#include "player.h"
#include "normal_enemy.h"
#include "super_enemy.h"
#include "center.h"

Level_2::Level_2(MenuChooseLevel *p, QWidget *parent):
    Widget(p, parent),
    pauseBtn(new MyPushButton(":/ui/pause.png")),
    p_ptr(nullptr)
{
    ini_scene();
    play_game();
}

void Level_2::ini_scene()
{
    bac_pic.load(":/bac/bac_7.jpg");

    map_x=MAP_SIZE_X_2;
    map_y=MAP_SIZE_Y_2;
    timer=new QTimer(this);
    g_map=new Game_map(MAP_2,this);
    player=new Player(15*UNIT, 47*UNIT, UP, PLAYER_HP,
                      MAX_NORMAL_BULLET_NUM, this);
    enemy_ls=new Enemy_list(this);
    bullet_ls=new Bullet_list(this);
    center_ls=new Center_list(this);
    astar=new Astar(this);
    x=player->get_x()-12*UNIT;
    y=player->get_y()-12*UNIT;
    is_win=false;
    lv=2;


    ini_all_lists();

    setFixedSize(WIDGET_SIZE_X, WIDGET_SIZE_Y);

    setAttribute(Qt::WA_DeleteOnClose);

    //设置窗口标题
    setWindowTitle("Level 2");
    //设置窗口图标
    setWindowIcon(QIcon(ICON));

    timer->setInterval(RATE);

    update();
}

void Level_2::ini_all_lists()
{
    enemy_ls->push_enemy(
                new Turret(11*UNIT, 5*UNIT, this));
    enemy_ls->push_enemy(
                new Turret(27*UNIT, 5*UNIT, this));
    enemy_ls->push_enemy(
                new Turret(19*UNIT, 25*UNIT, this));
    enemy_ls->push_enemy(
                new Turret(4*UNIT, 13*UNIT, this));
    enemy_ls->push_enemy(
                new Turret(34*UNIT, 13*UNIT, this));
    enemy_ls->push_enemy(
                new Super_enemy(26*UNIT, 3*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Super_enemy(14*UNIT, 2*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Normal_enemy(1*UNIT, 1*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Normal_enemy(37*UNIT, 1*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Normal_enemy(8*UNIT, 5*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Normal_enemy(19*UNIT, 13*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Super_enemy(15*UNIT, 25*UNIT, DOWN, this));
    enemy_ls->push_enemy(
                new Super_enemy(23*UNIT, 25*UNIT, DOWN, this));

    enemy_ls->push_enemy(
                new Normal_enemy(30*UNIT, 44*UNIT, LEFT, this));

    enemy_ls->push_enemy(
                new Normal_enemy(19*UNIT, 36*UNIT, LEFT, this));

    enemy_ls->push_enemy(
                new Normal_enemy(5*UNIT, 44*UNIT, RIGHT, this));

    enemy_ls->push_enemy(
                new Normal_enemy(30*UNIT, 5*UNIT, DOWN, this));

    center_ls->push_center(
                new Center(4*UNIT, 16*UNIT, 40,
                           NORMAL_BULLET_CENTER, this));
    center_ls->push_center(
                new Center(34*UNIT, 33*UNIT, 40,
                           SUPER_BULLET_CENTER, this));

    defeat_point=new Center(19*UNIT, 48*UNIT, 40, PLAYER_CENTER, this);
    center_ls->push_center(defeat_point);

    center_ls->push_center(
                new Center(34*UNIT, 16*UNIT, 40, HP_CENTER, this));
    center_ls->push_center(
                new Center(4*UNIT, 33*UNIT, 40, HP_CENTER, this));
    center_ls->push_center(
                new Center(19*UNIT, 1*UNIT, 40, ENEMY_CENTER, this));
    auto iter=center_ls->get_list_ptr()->end();
    iter--;
    victory_point=*iter;
}

void Level_2::play_game()
{
    timer->start();

    connect(timer , &QTimer::timeout,[=](){
    //游戏中的元素 绘制到屏幕中 再调用paintEvent函数
        bullet_ls->move_all_bullets();
        bullet_ls->check_bullet_list();

        check_game_over();
        center_ls->check_all_centers();

        astar->update_map();
        enemy_ls->update_all_path();
        enemy_ls->ctrl_all_enemy();




        enemy_ls->check_enemy_exist();

        player->tank_move();
        player->enter_center_react();
        //qDebug()<<player->get_x()/UNIT<<player->get_y()/UNIT;
        g_map->check_all_barriers_states();



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
        timer->stop();

        QTimer::singleShot(1500,this,[=](){
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

void Level_2::check_game_over()
{
    if(player->get_hp()<=0 || defeat_point->get_hp()<=0)
        lost();
    else if(victory_point->get_hp()<=0)
        win();
}
