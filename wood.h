#ifndef WOOD_H
#define WOOD_H

#include "barrier.h"

//树丛、草丛
class Wood : public Barrier
{
public:
    Wood(position, position, Widget*);
    void draw(QPainter &) override;
    //void bullet_hit_react(Bullet*)override

    QPixmap wood_pic;
};

#endif // WOOD_H
