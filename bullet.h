#ifndef BULLET_H
#define BULLET_H

#include "base.h"
#include "tank.h"


class Bullet : public Base
{
public:
    Bullet(
            position,
            position,
            direction,
            int,
            Widget*
            );

    virtual void check_collision();

    virtual void bullet_move();

    direction get_direction()const;
    bool get_hit_state()const;
    bool get_clear_state()const;
    int get_type()const;

    void set_direction(direction);
    void set_hit_state(bool);
    void set_clear_state(bool);

protected:
    void check_edge_collision();
    virtual void check_all_tanks_collision();
    virtual void check_surround_barriers_collision();
    virtual void check_center_collision();
    virtual void check_tank_collision(Tank*);
    //virtual void check_bullet_collision(Bullet*);
    virtual void check_barrier_collision(Barrier*);

    bool bomb_flag;
    int times;

private:
    direction dir;
    int type;

    bool is_hit;
    bool is_clear;
};

#endif // BULLET_H
