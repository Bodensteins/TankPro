#ifndef BRICK_H
#define BRICK_H

#include "barrier.h"

//砖
class Brick : public Barrier
{
public:
    Brick(position, position, Widget*);
    //绘图函数
    void draw(QPainter &) override;
    //void bullet_hit_react(Bullet*)override;

    QPixmap brick_pic;
};

#endif // BRICK_H
