#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "GameSet.h"

class Game_map
{
public:
    Game_map(Widget *);
    Game_map(QString, Widget*);
    //检查该坐标处是否有障碍，返回其指针
    Barrier* check_if_barrier(position, position) const;

    //添加一个障碍
    void push_barrier(Barrier*);

    //在该坐标处清除障碍
    void pop_barrier(position x, position y);

    //每次刷新后检查所有障碍的状态
    void check_all_barriers_states();

    //画出所有障碍
    void draw_all_barriers(QPainter&);

    //Widget指针，跟Base类的一样
    Widget* get_wptr()const;
    void set_wptr(Widget*);

    ~Game_map();

private:
    //存储障碍的数组
   Barrier* barriers[1300][1300];

   Widget* w_ptr;
};

#endif // GAME_MAP_H
