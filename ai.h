#ifndef AI_H
#define AI_H
#include "tank.h"
#include "astar.h"


class AI : public Tank
{
    friend class Enemy_list;

public:
    /*
     * 构造函数：
     * 形参：x坐标、y坐标、方向、生命值、窗口指针
     */
    AI(
            position,
            position,
            direction,
            hit_point,
            Widget*
            );

    //设置是否开枪
    bool get_shoot_state()const;
    void set_shoot_state(bool);

    //改变AI坦克的方向（一般不用这个）
    void ctrl_direction(QKeyEvent *) override;

    //改变AI坦克的方向
    virtual void ctrl_direction();

    //发射子弹函数
    virtual void shoot()=0;

    //清空AI路径列表
    void ls_clear();

    //重新生成一条AI路径
    virtual void path();
    void path(position, position);

    //坦克根据方向来移动
    void tank_move() override;

    //判断是否射击
    bool shoot_judge();
    void shoot_check();

    //碰撞检测
    bool check_collision()override;

    void enter_center_react() override;
    void set_target(position, position);

    ~AI()override;

protected:
    //检查跟其他AI的碰撞
    bool check_other_ai_collision();
    //是否射击
    bool is_shoot;
    //AI路径列表
    std::list<Point*> ls;
    //AI目标位置
    position x0, y0;
};

#endif // AI_H
