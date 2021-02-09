#include "astar.h"
#include "widget.h"
#include "game_map.h"
#include "enemy_list.h"
#include "center_list.h"
Astar::Astar(Widget* p):
    w_ptr(p)
{
    update_map();
}

Widget *Astar::get_wptr() const
{
    return  w_ptr;
}

void Astar::InitAstar(std::vector<std::vector<int>>& _maze)

{

    maze = _maze;

    /*for (int i = 0; i < 20; i++)

    {

        for (int j = 0; j < 20; j++)

        {

            std::cout << maze[i][j] << " ";

        }

        std::cout << std::endl;

    }*/
}

//更新算法地图
void Astar::update_map()
{
    //清空以前的地图
    while(!maze.empty())
        maze.pop_back();

    position size_x(get_wptr()->get_map_x()/UNIT),
            size_y(get_wptr()->get_map_y()/UNIT);
    //确定大小，所有坐标先全部赋为0
    auto ptr(get_wptr()->get_map());
    for(int i=0;i<size_x;i++)
    {
        maze.push_back(std::vector<int>());
        for(int j=0;j<size_y;j++)
        {
            maze[i].push_back(0);
        }
    }

    //判断障碍，有障碍且不是树丛赋为1
    for(int i=0;i<size_x;i++)
    {
        for(int j=0;j<size_y;j++)
        {
            auto b_ptr(ptr->check_if_barrier(i, j));
            if(
                    b_ptr==nullptr ||
                    b_ptr->get_type()==WOOD||
                    b_ptr->get_type()==BRICK
                    )
                continue;
            else
                maze[i][j]=1;
        }
    }

    auto c_ptr=get_wptr()->get_center_ls()->get_list_ptr();
    for(auto iter=c_ptr->begin();
        iter!=c_ptr->end();
        iter++)
    {
        if((*iter)->get_type()!=ENEMY_CENTER)
            continue;
        position x((*iter)->get_x()/UNIT);
        position y((*iter)->get_y()/UNIT);
        maze[x][y]=1;
        maze[x][y+1]=1;
        maze[x+1][y]=1;
        maze[x+1][y+1]=1;
    }

    auto ai_ptr=get_wptr()->get_enemy_ls()->get_list_ptr();
    for(auto iter=ai_ptr->begin();
        iter!=ai_ptr->end();
        iter++)
    {
        if((*iter)->get_direction()!=5)
            continue;
        position x((*iter)->get_x()/UNIT);
        position y((*iter)->get_y()/UNIT);
        maze[x][y]=1;
        maze[x][y+1]=1;
        maze[x+1][y]=1;
        maze[x+1][y+1]=1;
    }




}

int Astar::calcG(Point* temp_start, Point* point)

{

        int extraG;
        if (abs(point->x - temp_start->x) == 1&& abs(point->y - temp_start->y) == 0)
            extraG = Cost2;
        if (abs(point->y - temp_start->y) == 1&& abs(point->x - temp_start->x) == 0)
            extraG = Cost1;
        //int extraG = (abs(point->x - temp_start->x) + abs(point->y - temp_start->y)) == 1 ? Cost1 : Cost1;//1 ? Cost1 : Cost2;

        int parentG = point->parent == NULL ? 0 : point->parent->G; //如果是初始节点，则其父节点是空

        return parentG + extraG;

}


int Astar::calcH(Point* point, Point* end)

{

    //用简单的欧几里得距离计算H

    return sqrt((double)(end->x - point->x) * (double)(end->x - point->x) + (double)(end->y - point->y) * (double)(end->y - point->y)) * Cost1;

}


int Astar::calcF(Point* point)

{

    return point->G + point->H;

}


Point* Astar::getLeastFpoint()

{

    if (!openList.empty())

    {

        auto resPoint = openList.front();

        for (auto& point : openList)

            if (point->F < resPoint->F)

                resPoint = point;

        return resPoint;

    }

    return nullptr;

}


Point* Astar::findPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner)

{

    openList.push_back(new Point(startPoint.x, startPoint.y)); //在开启列表置入起点,拷贝开辟一个节点，内外隔离

    while (!openList.empty())

    {

        auto curPoint = getLeastFpoint(); //找到F值最小的点

        openList.remove(curPoint); //从开启列表中删除

        closeList.push_back(curPoint); //放到关闭列表

        //1,找到当前周围四个格中可以通过的格子

        auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);

        for (auto& target : surroundPoints)

        {

            //2,对某一个格子，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H

            if (!isInList(openList, target))

            {

                target->parent = curPoint;



                target->G = calcG(curPoint, target);

                target->H = calcH(target, &endPoint);

                target->F = calcF(target);



                openList.push_back(target);

            }

            //3，对某一个格子，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F

            else

            {

                int tempG = calcG(curPoint, target);

                if (tempG < target->G)

                {

                    target->parent = curPoint;



                    target->G = tempG;

                    target->F = calcF(target);

                }

            }

            Point* resPoint = isInList(openList, &endPoint);

            if (resPoint)

                return resPoint; //返回列表里的节点指针，不要用原来传入的endpoint指针，因为发生了深拷贝

        }

    }



    return NULL;

}


std::list<Point*> Astar::GetPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner)

{

    Point* result = findPath(startPoint, endPoint, isIgnoreCorner);

    std::list<Point*> path;

    //返回路径，如果没找到路径，返回空链表

    while (result)

    {

        path.push_front(result);

        result = result->parent;

    }

    openList.clear();

    closeList.clear();

    return path;

}


Point* Astar::isInList(const std::list<Point*>& list, const Point* point) const

{

    //判断某个节点是否在列表中，比较坐标

    for (auto p : list)

        if (p->x == point->x && p->y == point->y)

            return p;

    return NULL;

}


bool Astar::isCanreach(const Point* point,
                       const Point* target
                       , bool) const

{
    //isIgnoreCorner=false;
    int x_size(maze.size() - 2), y_size(maze[0].size() - 2);

    if (target->x<0 || target->x > x_size

        || target->y<0 || target->y > y_size

        || maze[target->x][target->y]

        || maze[target->x + 1][target->y]

        || maze[target->x][target->y + 1]

        || maze[target->x + 1][target->y + 1]

        || (target->x == point->x && target->y == point->y)

        || isInList(closeList, target)) //如果点与当前节点重合、超出地图、是障碍物、或者在关闭列表中，返回false

        return false;

    else if (abs(point->x - target->x) + abs(point->y - target->y) == 1) //非斜角可以

        return true;

    else
        return true;
     /*
    {
    //暂不考虑
        //斜对角要判断是否绊住

        if (maze[point->x][target->y] == 0 && maze[target->x][point->y] == 0)

            return true;

        else

            return isIgnoreCorner;

    }
    */
}


std::vector<Point*> Astar::getSurroundPoints(const Point* point, bool isIgnoreCorner) const

{

    std::vector<Point*> surroundPoints;



    //for (int x = point->x - 1; x <= point->x + 1; x++)  //八向

        //for (int y = point->y - 1; y <= point->y + 1; y++)
    //四向
    int x = point->x - 1, y = point->y;
    if (isCanreach(point, new Point(x, y), isIgnoreCorner))

        surroundPoints.push_back(new Point(x, y));

    x = point->x + 1;
    y = point->y;
    if (isCanreach(point, new Point(x, y), isIgnoreCorner))

        surroundPoints.push_back(new Point(x, y));

    x = point->x;
    y = point->y + 1;
    if (isCanreach(point, new Point(x, y), isIgnoreCorner))

        surroundPoints.push_back(new Point(x, y));

    x = point->x;
    y = point->y - 1;
    if (isCanreach(point, new Point(x, y), isIgnoreCorner))

        surroundPoints.push_back(new Point(x, y));



    return surroundPoints;

}
