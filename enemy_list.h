#ifndef ENEMY_LIST_H
#define ENEMY_LIST_H
#include "widget.h"
#include "ai.h"
#include "game_map.h"
#include "player.h"
#include "normal_bullet.h"

class Enemy_list
{
public:
    //构造函数
    Enemy_list(Widget*);//传入一个控制控制他的窗口指针
    Enemy_list(QString ,Widget*);//未定义

    //向列表中加入一个敌人AI
    void push_enemy(AI*);

    //获取敌人AI列表的指针
    std::list<AI*>* get_list_ptr();

    //更新敌人AI的路径
    void update_all_path();

    //检查敌人AI是否存活，若hp小于等于0则将其去除
    void check_enemy_exist();

    //控制敌人AI的方向和移动
    void ctrl_all_enemy();

    //画出所有的敌人AI
    void draw_all_enemy(QPainter&);

    void redraw_all_enemy(QPainter&);

    //析构函数
    ~Enemy_list();
private:

    //敌人AI列表
    std::list<AI*> ls;

    //指向控制他的窗口的指针
    Widget *w_ptr;
};

#endif // ENEMY_LIST_H
