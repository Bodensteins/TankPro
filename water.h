#ifndef WATER_H
#define WATER_H

#include "barrier.h"

//水域
class Water : public Barrier
{
public:
    Water(position, position, Widget*);
    void draw(QPainter &) override;
    //void bullet_hit_react(Bullet*)override;

    QPixmap water_pic_1,
            water_pic_2,
            water_pic_3,
            water_pic_4,
            water_pic_5;

    int times;
};

#endif // WATER_H
