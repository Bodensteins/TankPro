#ifndef IRON_H
#define IRON_H
#include "barrier.h"

//铁
class Iron : public Barrier
{
public:
    Iron(position, position, Widget*);
    //绘图函数
    void draw(QPainter &) override;

    QPixmap iron_pic_1,
            iron_pic_2,
            iron_pic_3,
            iron_pic_4,
            iron_pic_5;

    int times;
};

#endif // IRON_H
