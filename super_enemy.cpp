#include "super_enemy.h"
#include "super_bullet.h"
#include "bullet_list.h"

Super_enemy::Super_enemy(
        position xx,
        position yy,
        direction d,
        Widget *p
               ):
    AI(xx, yy, d, SUPER_ENEMY_HP, p)
{}

void Super_enemy::draw(QPainter &painter)
{
    position x(get_x()), y(get_y());

    coord_trans(x, y, get_wptr());//坐标转换

    if(check_inside_window(x,y,get_width(),get_height()))
    {
        //qDebug()<<"test_draw"<<'\n';
        QString qs;
        switch(get_direction())
        {
        case UP:
            if(move_times%2==0)  qs=SUPER_ENEMY_UP_1;
            else  qs=SUPER_ENEMY_UP_2;
            break;
        case RIGHT:
            if(move_times%2==0)  qs=SUPER_ENEMY_RIGHT_1;
            else  qs=SUPER_ENEMY_RIGHT_2;
            break;
        case DOWN:
            if(move_times%2==0)  qs=SUPER_ENEMY_DOWN_1;
            else  qs=SUPER_ENEMY_DOWN_2;
            break;
        case LEFT:
            if(move_times%2==0)  qs=SUPER_ENEMY_LEFT_1;
            else  qs=SUPER_ENEMY_LEFT_2;
            break;
        }
        painter.drawPixmap(x, y, qs);
    }
}

void Super_enemy::redraw(QPainter &painter)
{
    if(hp_bar_times)
        {
            hp_bar_times++;
            hp_bar_times%=HP_BAR_LOAD_TIME;

            position x(get_x()), y(get_y());
            coord_trans(x,y,get_wptr());

            double radio((double)get_hp()/SUPER_ENEMY_HP);

            QBrush brush(Qt::red);
            QPen pen(Qt::red);
            painter.setBrush(brush);
            painter.setPen(pen);
            painter.drawRect(
                        QRect(x,y,get_width(), 5));

            brush.setColor(Qt::green);
            pen.setColor(Qt::green);
            painter.setBrush(brush);
            painter.setPen(pen);
            painter.drawRect(
                        QRect(x,y,get_width()*radio, 5));
    }
}



void Super_enemy::shoot()
{
    if(get_shoot_state() && !limit_shoot)
    {
        position x0(get_x()), y0(get_y());

        switch (get_direction()) {
        case UP:
                y0-=UNIT;
                x0+=15;
                break;
        case LEFT:
                x0-=UNIT;
                y0+=15;
                break;
        case DOWN:
                y0+=2*UNIT;
                x0+=15;
                break;
        case RIGHT:
                x0+=2*UNIT;
                y0+=15;
                break;
        }
        auto b_ls_ptr=get_wptr()->get_bullet_ls();
        b_ls_ptr->push_bullet(
                    new Super_bullet(
                        x0, y0,
                        get_direction(),
                        AI_T,
                        get_wptr()
                        ));

    }

    limit_shoot++;
    limit_shoot%=AI_SHOOT_LIMIT;
}

