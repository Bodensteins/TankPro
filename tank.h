#ifndef TANK_H
#define TANK_H

#include "base.h"
#include "widget.h"
#include "barrier.h"
#include "game_map.h"

class Tank : public Base
{
    friend class Normal_bullet;
    friend class Super_bullet;

public:
    Tank(
            position,
            position,
            direction,
            hit_point,
            Widget*
            );



    virtual bool check_collision();
    virtual void enter_center_react()=0;

    //控制坦克方向的函数（纯虚函数，玩家接键盘，AI接算法）
    virtual void ctrl_direction(QKeyEvent *)=0;

    //坦克移动函数
    virtual void tank_move();

    //获取坦克方向
    direction get_direction()const;
    //获取坦克生命值
    hit_point get_hp()const;
    //获取坦克移动状态（是否移动）
    bool get_move_state()const;
    int get_type()const;


    //设置坦克方向
    void set_direction(direction);
    //设置坦克生命值
    void set_hp(hit_point);
    //设置坦克移动状态
    void set_move_state(bool);

    virtual void redraw_wave(QPainter &);

protected:
    bool check_edge_collision();//检查坦克是否与边界相撞
    bool check_barrier_collision();//检查坦克是否与障碍相撞
    bool check_tank_collision(Tank*);//检查坦克是否与其他坦克相撞

    //坦克移动次数
    int move_times;
    //坦克开火限制变量
    int limit_shoot;
    //坦克血条显示变量
    int hp_bar_times;

    //特征值
    int type;

    QPixmap tank1;
    QPixmap tank2;


private:
    //坦克方向
    direction dir;
    //坦克生命值
    hit_point hp;
    //坦克移动状态（是否移动）
    bool is_move;

};


#endif // TANK_H
