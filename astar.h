#ifndef ASTAR_H
#define ASTAR_H
#include "GameSet.h"

class Widget;
/*

//A*算法对象类

*/

#include <vector>

#include <list>

#include <cmath>

 //直移一格消耗
const int Cost1 = 10;

const int Cost2 = 15;



struct Point

{

    int x, y; //点坐标，x代表横排，y代表竖列

    int F, G, H; //F=G+H

    Point* parent; //parent的坐标

    Point(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL)  //变量初始化

    {

    }

};


class Astar

{

public:

    Astar(Widget*);

    //获取控制它的窗口指针
    Widget* get_wptr()const;

    void InitAstar(std::vector<std::vector<int>>& _maze);//初始化地图情况

    //更新算法的地图
    void update_map();

    std::list<Point*> GetPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner);//找路径


private:

    Point* findPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner);//找路径

    std::vector<Point*> getSurroundPoints(const Point* point, bool isIgnoreCorner) const;//得到周围可用点的坐标，使用isCanreach判断

    bool isCanreach(const Point* point, const Point* target
                    , bool isIgnoreCorner) const; //判断某点是否可以用于下一步判断

    Point* isInList(const std::list<Point*>& list, const Point* point) const; //判断开启/关闭列表中是否包含某点

    Point* getLeastFpoint(); //从开启列表中返回F值最小的节点

    //计算FGH值

    int calcG(Point* temp_start, Point* point);

    int calcH(Point* point, Point* end);

    int calcF(Point* point);

    std::vector<std::vector<int>> maze;

    std::list<Point*> openList;  //开启列表

    std::list<Point*> closeList; //关闭列表

    Widget *w_ptr;
};

#endif // ASTAR_H
