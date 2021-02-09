#ifndef CENTER_H
#define CENTER_H

#include "base.h"

#include "base.h"

class Center : public Base
{
    friend class Normal_bullet;
    friend class Super_bullet;

public:
    Center(
            position,
            position,
            hit_point,
            int,
            Widget*
           );

    hit_point get_hp()const;
    int get_type()const;
    void set_hp(hit_point);

    void draw(QPainter &) override;
    void redraw(QPainter &) override;

    int times;

    bool is_player_come;
private:
    hit_point hp;
    int type;
    int hp_bar_times;


};

#endif // CENTER_H
