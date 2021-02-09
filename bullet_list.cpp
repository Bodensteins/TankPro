#include "bullet_list.h"

Bullet_list::Bullet_list(Widget* p):
    w_ptr(p)
{

}

Bullet_list::~Bullet_list()
{
    auto iter=ls.begin();
    while(iter!=ls.end())
    {
        delete *iter;
        iter++;
    }
}

void Bullet_list::push_bullet(Bullet *b_ptr)
{
    ls.push_back(b_ptr);
}

Widget* Bullet_list::get_wptr() const
{
    return w_ptr;
}
std::list<Bullet*>* Bullet_list::get_list_ptr()
{
    return &ls;
}
void Bullet_list::set_wptr(Widget *p)
{
    w_ptr=p;
}

void Bullet_list::check_bullet_list()
{
    auto iter=ls.begin();
    while(iter!=ls.end())
    {
        (*iter)->check_collision();

        if((*iter)->get_clear_state()&&!(*iter)->get_hit_state())
        {
            delete *iter;
            iter=ls.erase(iter);
        }
        else
            iter++;
    }
}

void Bullet_list::move_all_bullets()
{
    auto iter=ls.begin();
    while(iter!=ls.end())
    {
        (*iter)->bullet_move();
        iter++;
    }
}

void Bullet_list::draw_all_bullet(QPainter &painter)
{
    auto iter=ls.begin();
    while(iter!=ls.end())
    {
        (*iter)->draw(painter);
        iter++;
    }
}

