#ifndef NORMAL_ENEMY_H
#define NORMAL_ENEMY_H

#include "ai.h"
#include "player.h"

class Normal_enemy : public AI
{
public:
    /*
     * 构造函数：
     * 形参：x坐标、y坐标、方向、生命值、窗口指针
     */
    Normal_enemy(
            position,
            position,
            direction,
            Widget*
            );

    //画出AI坦克的画面
    void draw(QPainter &)override;

    void redraw(QPainter &)override;

    void shoot()override;
};

#endif // NORMAL_ENEMY_H
