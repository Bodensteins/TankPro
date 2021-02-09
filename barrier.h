#ifndef BARRIER_H
#define BARRIER_H
#include "base.h"
#include "bullet.h"


class Barrier : public Base
{
public:
    Barrier(position, position, Widget*);

    virtual void draw(QPainter &)=0;

    virtual void bullet_hit_react();

    bool check_exist()const;
    void set_exist(bool);

    int get_type()const;
    void set_type(int);
private:
    bool is_exist;
    int type;
};

#endif // BARRIER_H
