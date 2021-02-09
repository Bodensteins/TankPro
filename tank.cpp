#include "tank.h"

Tank::Tank(
            position xx,
            position yy,
            direction d,
            hit_point h,
            Widget *p
        ):
    Base(xx,yy,TANK_SIZE_X,TANK_SIZE_Y,p),
    move_times(0), limit_shoot(0), hp_bar_times(0),
    dir(d), hp(h), is_move(false)
{
}

direction Tank::get_direction() const
{
    return dir;
}
hit_point Tank::get_hp() const
{
    return hp;
}
bool Tank::get_move_state()const
{
    return is_move;
}

int Tank::get_type() const
{
    return type;
}

void Tank::set_direction(direction d)
{
    dir=d;
}
void Tank::set_hp(hit_point h)
{
    hp=h;
}
void Tank::set_move_state(bool b)
{
    is_move=b;
}

void Tank::redraw_wave(QPainter &)
{}

void Tank::tank_move()
{
    if(get_move_state()==true||
            (get_move_state()==false&&move_times!=0))
    {
        position x0(get_x()), y0(get_y());

        switch (get_direction()) {
        case UP:
            set_pos(x0,y0-TANK_SPEED);
            break;

        case LEFT:
            set_pos(x0-TANK_SPEED,y0);
            break;

        case DOWN:
            set_pos(x0,y0+TANK_SPEED);
            break;

        case RIGHT:
            set_pos(x0+TANK_SPEED,y0);
            break;
        }

        if(check_collision())
        {
            move_times--;
            set_pos(x0,y0);
        }

        move_times++;
        move_times%=10;
    }
}

bool Tank::check_collision()
{
    if(check_edge_collision())
        return true;
    else if(check_barrier_collision())
        return true;

    return false;
}

bool Tank::check_edge_collision()
{
    position size_x(get_wptr()->get_map_x()),
            size_y(get_wptr()->get_map_y());
    position x(get_x()), y(get_y());
    if(x<0 || x>size_x-get_width() ||
            y<0 || y>size_y-get_height())
        return true;

    return false;
}

bool Tank::check_barrier_collision()
{
    auto m_ptr=get_wptr()->get_map();

    position x(get_x()/UNIT), y(get_y()/UNIT);
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
        {
            auto b_ptr(m_ptr->check_if_barrier(x+i,y+i));
            if(b_ptr!=nullptr && b_ptr->get_type()!=WOOD)
                return true;
        }


    if(get_x()%UNIT)
    {
        auto b_ptr(m_ptr->check_if_barrier(x+2,y));
        if(b_ptr!=nullptr && b_ptr->get_type()!=WOOD)
            return true;

        b_ptr=m_ptr->check_if_barrier(x+2,y+1);
        if(b_ptr!=nullptr && b_ptr->get_type()!=WOOD)
            return true;

        b_ptr=m_ptr->check_if_barrier(x,y+1);
        if(b_ptr!=nullptr&&get_direction()==LEFT
                && b_ptr->get_type()!=WOOD)
            return true;
    }

    else if(get_y()%UNIT)
    {
        auto b_ptr(m_ptr->check_if_barrier(x,y+2));
        if(b_ptr!=nullptr && b_ptr->get_type()!=WOOD)
            return true;

        b_ptr=m_ptr->check_if_barrier(x+1,y+2);
        if(b_ptr!=nullptr && b_ptr->get_type()!=WOOD)
            return true;

        b_ptr=m_ptr->check_if_barrier(x+1,y);
        if(b_ptr!=nullptr&&get_direction()==UP
                && b_ptr->get_type()!=WOOD)
            return true;

    }

    return false;
}

bool Tank::check_tank_collision(Tank *t_ptr)
{
    return check_base_collision(this, t_ptr);
}
