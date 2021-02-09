#include "enemy_list.h"
#include "center_list.h"
#include "widget.h"

Enemy_list::Enemy_list(Widget* p):
    w_ptr(p)
{}

Enemy_list::Enemy_list(QString, Widget*p):
    w_ptr(p)
{}

void Enemy_list::push_enemy(AI *ai_ptr)
{
    ls.push_back(ai_ptr);
}

std::list<AI *> *Enemy_list::get_list_ptr()
{
    return &ls;
}

void Enemy_list::update_all_path()
{

    position x(w_ptr->get_player()->get_x());
    position y(w_ptr->get_player()->get_y());
    for(auto iter=ls.begin();
        iter!=ls.end();
        iter++)
        if(!((*iter)->get_x()%UNIT)
                && !((*iter)->get_y()%UNIT)
                && (*iter)->get_direction()!=5)
        {

            int oj=((*iter)->get_x()-x)*((*iter)->get_x()-x)+
                    ((*iter)->get_y()-y)*((*iter)->get_y()-y);
            if(oj<=200*UNIT*UNIT)
            {
                (*iter)->set_target(x,y);
                (*iter)->path();
            }


        }
}

void Enemy_list::check_enemy_exist()
{
    //qDebug()<<ls.size();
    auto iter=ls.begin();
    while(iter!=ls.end())
    {
        //qDebug()<<"eve";
        if((*iter)->get_hp()<=0)
        {
            delete (*iter);
            iter=ls.erase(iter);
        }

        else
            iter++;
    }
}

void Enemy_list::ctrl_all_enemy()
{
    for(auto iter=ls.begin();
        iter!=ls.end();
        iter++)
    {
        /*
        if((*iter)->ls.empty())
        {
            position x(w_ptr->get_player()->get_x());
            position y(w_ptr->get_player()->get_y());
            (*iter)->path(x,y);
        }
        */
        (*iter)->ctrl_direction();
        (*iter)->tank_move();
        (*iter)->shoot();
    }
}

void Enemy_list::draw_all_enemy(QPainter &painter)
{
    for(auto iter=ls.begin();
        iter!=ls.end();
        iter++)
    {
        (*iter)->draw(painter);
        //qDebug()<<"yes"<<'\n';
    }

}

void Enemy_list::redraw_all_enemy(QPainter &painter)
{
    for(auto iter=ls.begin();
        iter!=ls.end();
        iter++)
    {
        if((*iter)->get_direction()==5)
            (*iter)->redraw_wave(painter);
        (*iter)->redraw(painter);
        //qDebug()<<"yes"<<'\n';
    }
}


Enemy_list::~Enemy_list()
{
    auto iter=ls.begin();
    while(iter!=ls.end())
    {
        delete (*iter);
        iter++;
    }
}
