#ifndef TURRET_H
#define TURRET_H
#include "ai.h"
#include "player.h"

class Turret : public AI
{
public:
    Turret(
            position,
            position,
            Widget*
            );

    void ctrl_direction() override;

    void draw(QPainter&)override;

    void redraw_wave(QPainter&)override;

    void redraw(QPainter&)override;

    void path()override;

    void shoot()override;

    void tank_move() override;

    int times;

    QPixmap _pic;
    QPixmap wave1;
    QPixmap wave2;
    QPixmap wave3;
    QPixmap wave4;
    QPixmap wave5;



};

#endif // TURRET_H
