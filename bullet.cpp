#include "bullet.h"
#include "enemy_list.h"
#include "center_list.h"

Bullet::Bullet(
        position xx,
        position yy,
        direction d,
        int t,
        Widget* p
        ):
    Base(xx, yy, 7, 7, p), bomb_flag(false),times(0),
    dir(d), type(t), is_hit(false), is_clear(false)
{}


direction Bullet::get_direction()const
{
    return dir;
}
bool Bullet::get_hit_state() const
{
    return is_hit;
}
bool Bullet::get_clear_state() const
{
    return is_clear;
}

int Bullet::get_type() const
{
    return type;
}

void Bullet::set_direction(direction d)
{
    dir=d;
}
void Bullet::set_hit_state(bool b)
{
    is_hit=b;
}
void Bullet::set_clear_state(bool b)
{
    is_clear=b;
}

void Bullet::bullet_move()
{
    switch(get_direction()){
    case UP:
        set_pos(get_x(), get_y()-BULLET_SPEED);
        break;
    case LEFT:
        set_pos(get_x()-BULLET_SPEED, get_y());
        break;
    case DOWN:
        set_pos(get_x(), get_y()+BULLET_SPEED);
        break;
    case RIGHT:
        set_pos(get_x()+BULLET_SPEED, get_y());
        break;
    }
}



void Bullet::check_collision()
{
    check_edge_collision();
    if(is_clear || is_hit)return;
    check_surround_barriers_collision();
    if(is_clear || is_hit)return;
    check_all_tanks_collision();
    if(is_clear || is_hit)return;
    check_center_collision();
}
void Bullet::check_edge_collision()
{
    position size_x(get_wptr()->get_map_x()),
            size_y(get_wptr()->get_map_y());
    position x(get_x()), y(get_y());
    if(x<0 || x>=size_x-UNIT ||
            y<0 || y>=size_y-UNIT)
    {
        set_clear_state(true);
        bomb_flag=false;
        set_hit_state(true);
        if(x<-UNIT || x>=size_x ||
                y<-UNIT || y>=size_y)
            set_hit_state(false);
    }
}
void Bullet::check_all_tanks_collision()
{
    check_tank_collision(get_wptr()->get_player());

    auto tanks_ptr=get_wptr()->get_enemy_ls()->get_list_ptr();
    for(auto iter=tanks_ptr->begin();
        iter!=tanks_ptr->end();
        iter++)
    {
        if((*iter)->get_hp()>=0)
            check_tank_collision(*iter);
    }
}
void Bullet::check_surround_barriers_collision()
{
    position x(get_x()/UNIT), y(get_y()/UNIT);
    auto map_ptr=get_wptr()->get_map();
    check_barrier_collision(map_ptr->check_if_barrier(x, y));
    check_barrier_collision(map_ptr->check_if_barrier(x+1, y));
    check_barrier_collision(map_ptr->check_if_barrier(x, y+1));
    check_barrier_collision(map_ptr->check_if_barrier(x+1, y+1));
}

void Bullet::check_center_collision()
{
    auto ptr=get_wptr()->get_center_ls()->get_list_ptr();
    for(auto iter=ptr->begin();
        iter!=ptr->end();
        iter++)
    {
        if(check_base_collision(this, *iter))
        {
            set_hit_state(true);
            set_clear_state(true);
            auto temp((*iter)->get_hp());
            (*iter)->set_hp(temp-NORMAL_BULLET_HURT);
        }
    }
}

void Bullet::check_tank_collision(Tank *)
{}
void Bullet::check_barrier_collision(Barrier *b_ptr)
{
    if(b_ptr!=nullptr)
    {
        if(b_ptr->get_type()==BRICK)
        {
            b_ptr->set_exist(false);
            set_clear_state(true);
            set_hit_state(true);
        }
        else if(b_ptr->get_type()==IRON)
        {
            set_clear_state(true);
            set_hit_state(true);
        }
    }
}
