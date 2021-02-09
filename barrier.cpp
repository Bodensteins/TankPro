#include "barrier.h"

Barrier::Barrier(position xx, position yy, Widget* p):
    Base(xx,yy,BARRIER_SIZE_X,BARRIER_SIZE_Y,p),is_exist(true)
{}

void Barrier::bullet_hit_react()
{
    set_exist(false);
}


bool Barrier::check_exist() const
{
    return is_exist;
}

void Barrier::set_exist(bool ex)
{
    is_exist=ex;
}

int Barrier::get_type() const
{
    return type;

}

void Barrier::set_type(int t)
{
    type=t;
}
