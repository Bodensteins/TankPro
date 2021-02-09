#ifndef NORMALBULLET_H
#define NORMALBULLET_H

#include "GameSet.h"
#include "bullet.h"

#include "GameSet.h"
#include "bullet.h"

class Normal_bullet : public Bullet
{
public:
    Normal_bullet(
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
#endif // NORMALBULLET_H
