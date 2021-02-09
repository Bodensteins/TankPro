#include "super_bullet.h"
#include "tank.h"
#include "widget.h"
#include "center_list.h"
#include "center.h"

Super_bullet::Super_bullet(
        position xx,
        position yy,
        direction d,
        int t,
        Widget* p
        ):
    Bullet(xx, yy, d, t, p)
{}

void Super_bullet::draw(QPainter &painter)
{
    QString qs;

    position x(get_x()-6), y(get_y()-5);
    coord_trans(x, y, get_wptr());

    if(check_inside_window(x,y,get_width(),get_height()))
    {
        if(!get_clear_state())
        {
            switch(get_direction())
            {
            case UP:
                qs=SUPER_BULLET_UP;
                break;
            case RIGHT:
                qs=SUPER_BULLET_RIGHT;
                break;
            case DOWN:
                qs=SUPER_BULLET_DOWN;
                break;
            case LEFT:
                qs=SUPER_BULLET_LEFT;
                break;
            }
            bomb_flag=true;
        }
        else
        {
            if(bomb_flag)
            {
                times=0;
                bomb_flag=false;
            }
            else
                times++;

            if(times>=0&&times<2)
                qs=BOMB_1;
            else if(times>=2&&times<4)
                qs=BOMB_2;
            else if(times>=4&&times<6)
                qs=BOMB_3;
            else
            {
                set_hit_state(false);
                bomb_flag=true;
            }
        }
        painter.drawPixmap(x, y, qs);
    }
}


void Super_bullet::check_tank_collision(Tank *t_ptr)
{
    if(check_base_collision(this, t_ptr))
    {
        if(get_type()==t_ptr->get_type())
            return;

        t_ptr->set_hp(t_ptr->get_hp()-SUPER_BULLET_HURT);
        t_ptr->hp_bar_times=1;
        set_clear_state(true);
        set_hit_state(true);
    }
}

void Super_bullet::check_center_collision()
{
    auto ptr=get_wptr()->get_center_ls()->get_list_ptr();
    for(auto iter=ptr->begin();
        iter!=ptr->end();
        iter++)
    {
        if(check_base_collision(this, *iter))
        {
            (*iter)->hp_bar_times=1;
            set_hit_state(true);
            set_clear_state(true);
            auto temp((*iter)->get_hp());
            (*iter)->set_hp(temp-SUPER_BULLET_HURT);
        }
    }
}
