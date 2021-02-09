#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "GameSet.h"
#include "astar.h"
#include "menuchooselevel.h"
#include <QLabel>
#include <QPropertyAnimation>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(MenuChooseLevel *,QWidget *parent = nullptr);
    virtual ~Widget();


    position get_x()const;//获取窗口x坐标
    position get_y()const;//获取窗口y坐标
    Astar* get_astar()const;//获取A*对象指针
    Player* get_player()const;//获取玩家对象指针
    Enemy_list* get_enemy_ls()const;//获取AI敌人列表
    Bullet_list* get_bullet_ls()const;//获取子弹容器
    Center_list* get_center_ls()const;//获取基地容器
    Game_map* get_map()const;//获取地图容器
    sizetype get_map_x()const;
    sizetype get_map_y()const;

    void set_position(position, position);//设置窗口位置

    //void save();


protected:

    virtual void ini_scene()=0;//游戏初始化
    virtual void ini_all_lists()=0;
    virtual void play_game()=0;//游戏进行

    virtual void check_game_over()=0;

    virtual void show_game_state(QPainter &);

    void paintEvent(QPaintEvent *);//绘图事件

    void keyPressEvent(QKeyEvent *);//键盘按下事件

    void keyReleaseEvent(QKeyEvent *);//键盘松开事件

    sizetype map_x, map_y;

    Menu *menu;
    MenuChooseLevel *menu_choose_level;//关卡菜单

    QTimer *timer;//定时器

    Game_map *g_map;//障碍容器

    Player *player;//玩家坦克

    Enemy_list *enemy_ls;//敌人AI列表

    Bullet_list *bullet_ls;//子弹容器

    Center_list *center_ls;//基地容器

    Astar *astar;//A*算法对象

    position x, y;//窗口坐标

    QPixmap bac_pic;

    int lv;

signals:
    void lost();
    void win();
};
#endif // WIDGET_H
