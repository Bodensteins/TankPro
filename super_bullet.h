#ifndef SUPER_BULLET_H
#define SUPER_BULLET_H
#include "bullet.h"

class Super_bullet : public Bullet
{
public:
public:
    Super_bullet(
            position,
            position,
            direction,
            int,
            Widget*
            );

    void draw(QPainter &) override;

protected:
    void check_tank_collision(Tank *) override;
    void check_center_collision() override;
};


#endif // SUPER_BULLET_H
