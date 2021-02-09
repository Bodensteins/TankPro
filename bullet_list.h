#ifndef BULLET_LIST_H
#define BULLET_LIST_H

#include "bullet.h"
#include "widget.h"

class Bullet_list
{
public:
    Bullet_list(Widget*);

    ~Bullet_list();

    void push_bullet(Bullet*);
    Widget* get_wptr()const;
    std::list<Bullet*>* get_list_ptr();
    void set_wptr(Widget*);

    void check_bullet_list();

    void move_all_bullets();

    void draw_all_bullet(QPainter &);

private:
    std::list<Bullet*> ls;

    Widget* w_ptr;
};

#endif // BULLET_LIST_H
