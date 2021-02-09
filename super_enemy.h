#ifndef SUPER_ENEMY_H
#define SUPER_ENEMY_H
#include "ai.h"

class Super_enemy : public AI
{
public:
    Super_enemy(
            position,
            position,
            direction,
            Widget*
            );

    void shoot() override;
    void draw(QPainter &)override;
    void redraw(QPainter &)override;
};

#endif // SUPER_ENEMY_H
