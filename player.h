#ifndef PLAYER_H
#define PLAYER_H
#include "tank.h"
#include "ai.h"
//#include "normal_enemy.h"
#include "enemy_list.h"

class Player : public Tank
{
public:
    //Player();

    Player(
            position,
            position,
            direction,
            hit_point,
            int,
            Widget*
            );

    bool check_collision() override;

    void enter_center_react() override;

    //玩家的方向由键盘控制
    void ctrl_direction(QKeyEvent *) override;

    //控制玩家坦克停下的函数
    void ctrl_stop(QKeyEvent *);

    //坦克移动函数
    void tank_move() override;

    //发射子弹
    void shoot(QKeyEvent *);
    //void stop_shoot(QKeyEvent *);

    //画出玩家坦克的画面
    void draw(QPainter &)override;

    int get_bullet_type()const;
    int get_bullet_num()const;

    void set_bullet_type(int);

    int lv3_vic;

protected:
    bool check_enemy_collision();
    bool check_center_collision();
private:

    int bullet_num;

    int bullet_type;

    bool is_up;
    bool is_down;
    bool is_left;
    bool is_right;

    //bool is_press_shoot;
};

#endif // PLAYER_H
