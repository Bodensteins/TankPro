#include "widget.h"
#include "menu.h"

#include "enemy_list.h"
#include "bullet_list.h"
#include "center_list.h"
#include "game_map.h"

#include "player.h"
#include "normal_enemy.h"
#include "ai.h"
#include "center.h"

Widget::Widget(MenuChooseLevel *p, QWidget *parent)
    :  QWidget(parent), menu_choose_level(p)
{

}

Widget::~Widget()
{
    delete timer;//定时器

    delete g_map;//障碍容器

    delete player;//玩家坦克

    delete enemy_ls;//敌人AI列表

    delete bullet_ls;//子弹容器

    delete center_ls;//基地容器

    delete astar;//A*算法对象

}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //加载背景图
    auto x_bac(0), y_bac(0);
    coord_trans(x_bac, y_bac, this);
    painter.drawPixmap(x_bac, y_bac,bac_pic);

    center_ls->draw_all_centers(painter);
    player->draw(painter);
    enemy_ls->draw_all_enemy(painter);
    g_map->draw_all_barriers(painter);
    bullet_ls->draw_all_bullet(painter);
    enemy_ls->redraw_all_enemy(painter);
    center_ls->redraw_all_centers(painter);

    //去除多于画面
    QBrush brush(Qt::white);
    QPen pen(Qt::white);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(QRect(26*UNIT, 0, 16*UNIT, 26*UNIT));

    show_game_state(painter);

}

void Widget::keyPressEvent(QKeyEvent *ev)
{
    player->ctrl_direction(ev);
    player->shoot(ev);

}

void Widget::keyReleaseEvent(QKeyEvent *ev)
{
    player->ctrl_stop(ev);
    //player->stop_shoot(ev);
}

position Widget:: get_x()const
{
    return x;
}
position Widget:: get_y()const
{
    return y;
}

Astar *Widget::get_astar() const
{
    return astar;
}

Player *Widget::get_player() const
{
    return player;
}

Enemy_list *Widget::get_enemy_ls() const
{
    return enemy_ls;
}

Bullet_list *Widget::get_bullet_ls() const
{
    return bullet_ls;
}

Center_list *Widget::get_center_ls() const
{
    return center_ls;
}

Game_map *Widget::get_map() const
{
    return g_map;
}

sizetype Widget::get_map_x() const
{
    return map_x;
}

sizetype Widget::get_map_y()const
{
    return map_y;
}

void Widget::set_position(position xx, position yy)
{
    x=xx;
    y=yy;
}

void Widget::show_game_state(QPainter &painter)
{

    QPen pen(Qt::darkRed);

       QBrush brush(QColor(222,211,140));
       painter.setPen(pen);
       painter.setBrush(brush);

       painter.drawRect(
                   QRect(27*UNIT, 0, 15*UNIT, 26*UNIT));


       double radio((double)player->get_hp()/PLAYER_HP);
       painter.drawRect(
                   QRect(28*UNIT, 4*UNIT, 12*UNIT, UNIT));
       brush.setColor(Qt::darkRed);
       painter.setBrush(brush);

       if(player->get_hp()>=0){
           painter.drawRect(
                       QRect(28*UNIT, 4*UNIT, 12*UNIT*radio, UNIT));
       }

       QFont font("Microsoft JhengHei", 14, 65);
       QString qs=QString::number(player->get_hp());
       painter.setFont(font);

       if(player->get_hp()>=0){
           painter.drawText(
                       QRect(28*UNIT, 2*UNIT, 6*UNIT,2*UNIT), "HP: "+qs);
       }
       else
           painter.drawText(
                       QRect(28*UNIT, 2*UNIT, 6*UNIT,2*UNIT), "HP: 0");

       switch (player->get_bullet_type()) {
       case 0:
           qs="Normal";
           break;
       case 1:
           qs="Super";
           break;
       }

       pen.setColor(QColor(67, 137, 148));
       painter.setPen(pen);
       painter.drawText(
                   QRect(28*UNIT, 7*UNIT, 10*UNIT,4*UNIT),
                   "Weapon: " + qs);

       qs=QString::number(player->get_bullet_num());
       painter.drawText(
                   QRect(28*UNIT, 12*UNIT, 14*UNIT,4*UNIT),
                   "Bullet Number: " + qs);

       painter.drawPixmap(29*UNIT,18*UNIT,QPixmap(":/icon.png"));

}


void Widget::check_game_over()
{

}


