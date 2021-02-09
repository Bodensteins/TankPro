#ifndef GAMESET_H
#define GAMESET_H

#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QPixmap>
#include <QRect>
#include <QIcon>
#include <QFile>
#include <QDebug>
#include <fstream>
#include <list>

#include "ResourcesPath.h"


//方向定义
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//障碍类型
#define BRICK 0
#define IRON 1
#define WATER 2
#define WOOD 3
#define TNT 4

//基地类型
#define PLAYER_CENTER 0
#define ENEMY_CENTER 1
#define NORMAL_BULLET_CENTER 2
#define HP_CENTER 3
#define SUPER_BULLET_CENTER 4

//特征值
#define PLAYER_T 0
#define AI_T 1

//尺寸类型
typedef int sizetype;
//方向类型
typedef int direction;
//坐标类型（单元格的坐标）
typedef int position;
//速度类型
typedef int speed;
//生命值类型
typedef int hit_point;


//单位长度（像素）
#define UNIT 20

//游戏画面窗口尺寸
#define WINDOW_SIZE_X (26*UNIT)
#define WINDOW_SIZE_Y (26*UNIT)

//游戏界面尺寸
#define WIDGET_SIZE_X (42*UNIT)
#define WIDGET_SIZE_Y (26*UNIT)

//游戏最大坐标
#define MAP_X_1 40
#define MAP_Y_1 51

#define MAP_X_2 40
#define MAP_Y_2 51

#define MAP_X_3 112
#define MAP_Y_3 88

//游戏地图尺寸
#define MAP_SIZE_X_1 (MAP_X_1*UNIT)
#define MAP_SIZE_Y_1 (MAP_Y_1*UNIT)

#define MAP_SIZE_X_2 (MAP_X_2*UNIT)
#define MAP_SIZE_Y_2 (MAP_Y_2*UNIT)

#define MAP_SIZE_X_3 (MAP_X_3*UNIT)
#define MAP_SIZE_Y_3 (MAP_Y_3*UNIT)

//坦克尺寸
#define TANK_SIZE_X (2 * UNIT)
#define TANK_SIZE_Y (2 * UNIT)

//基地尺寸
#define BASE_X (2 * UNIT)
#define BASE_Y (2 * UNIT)

//单位障碍物尺寸
#define BARRIER_SIZE_X (1 * UNIT)
#define BARRIER_SIZE_Y (1 * UNIT)

//基地尺寸
#define CENTER_SIZE_X (2*UNIT)
#define CENTER_SIZE_Y (2*UNIT)

//炮弹半径
//#define BULLET_RADIUS (TANK_SIZE_X / 10)

//子弹速度
#define BULLET_SPEED 5

//坦克生命值
#define PLAYER_HP 60
#define NORMAL_ENEMY_HP 22
#define SUPER_ENEMY_HP 30
#define TURRET_HP 40

//基地生命值
#define PLAYER_CENTER_HP 50
#define ENEMY_CENTER_HP 50
#define BULLET_CENTER_HP 50
#define HP_CENTER_HP 50

//玩家最大子弹数量
#define MAX_NORMAL_BULLET_NUM 40
#define MAX_SUPER_BULLET_NUM 20

//坦克速度
#define TANK_SPEED 2
#define NORMAL_ENEMY_SPEED 1
//子弹伤害
#define NORMAL_BULLET_HURT 4
#define SUPER_BULLET_HURT 10


//AI射击频率
#define AI_SHOOT_LIMIT 70
//补给站重新补给时间
#define LOAD_TIME 5000
//血条显示时间
#define HP_BAR_LOAD_TIME 70

//游戏名称
#define GAME_TITLE "坦克大战"

//屏幕刷新时间间隔（单位毫秒）
#define RATE 10


//声明所有的类
class Base;
class Barrier;
class Tank;
class Player;
class Widget;
class Game_map;
class Brick;
class Iron;
class Normal_bullet;
class Super_bullet;
class Bullet;
class Normal_enemy;
class Astar;
class AI;
class Center;
class Enemy_list;
class Bullet_list;
class Center_list;
class Menu;
class MyPushButton;
class MenuPause;

#endif // GAMESET_H
