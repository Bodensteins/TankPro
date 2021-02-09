#include "center_list.h"

Center_list::Center_list(Widget *p):
    w_ptr(p)
{}

std::list<Center *> *Center_list::get_list_ptr()
{
    return &ls;
}

void Center_list::push_center(Center *c_ptr)
{
    ls.push_back(c_ptr);
}

void Center_list::check_all_centers()
{
    for(auto iter=ls.begin();
        iter!=ls.end();
        )
    {
        if((*iter)->get_hp()<=0)
        {
            delete *iter;
            iter=ls.erase(iter);
        }
        else
        {
            if((*iter)->times){
                (*iter)->times++;
                (*iter)->times%=5000;
            }
            iter++;
        }
    }
}

void Center_list::draw_all_centers(QPainter &painter)
{
    for(auto iter=ls.begin();
        iter!=ls.end();
        iter++)
        (*iter)->draw(painter);
}

void Center_list::redraw_all_centers(QPainter &painter)
{
    for(auto iter=ls.begin();
        iter!=ls.end();
        iter++)
        (*iter)->redraw(painter);
}

Center_list::~Center_list()
{
    for(auto iter=ls.begin();
        iter!=ls.end();
        iter++)
        delete *iter;
}
