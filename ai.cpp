#include "ai.h"
//#include "iostream"
#include "player.h"
#include "center_list.h"

AI::AI(
        position xx,
        position yy,
        direction d,
        hit_point hp,
        Widget *p
               ):
    Tank(xx, yy, d, hp, p), is_shoot(false)
{
    type=AI_T;
    x0=y0=-1;
}

bool AI::get_shoot_state() const
{
    return is_shoot;
}

void AI::set_shoot_state(bool b)
{
    is_shoot=b;
}

void AI::ctrl_direction(QKeyEvent *)
{}

void AI::ctrl_direction()
{
    if(ls.empty())
    {
        set_move_state(false);
        return;
    }

    auto iter=ls.begin();
    position x0(get_x()), y0(get_y());

    if((*iter)->x==get_x() && (*iter)->y==get_y())
    {
        delete *iter;
        iter=ls.erase(iter);
    }

    if(iter!=ls.end())
    {

        set_move_state(true);
        if(x0<(*iter)->x)
            set_direction(RIGHT);
        else if(x0>(*iter)->x)
            set_direction(LEFT);
        else if(y0<(*iter)->y)
            set_direction(DOWN);
        else if(y0>(*iter)->y)
            set_direction(UP);
    }

}

void AI::ls_clear()
{
    //释放所有动态内存
    auto iter=ls.begin();
    while(iter!=ls.end())
    {
        delete *iter;
        iter++;
    }
    ls.clear();
}


void AI::path()
{
    if(x0>=0&&y0>=0)
        path(x0, y0);
}

void AI::path(position xx, position yy)
{
    /*
    由于要将像素坐标转化到格子上，所以所有坐标都要除以UNIT
*/

    //清空列表
    ls_clear();

    //起点为自己的坐标
    Point start(get_x()/UNIT, get_y()/UNIT);

    //终点暂时直接设置为玩家的坐标
    Point end(xx/UNIT, yy/UNIT);

    //获取A*算法接口
    auto astar=get_wptr()->get_astar();

    //运行A*算法，取得路径列表
    ls=astar->GetPath(start, end, false);

    //重新转化为像素坐标
    for(auto &it:ls)
    {
        it->x*=UNIT;
        it->y*=UNIT;
    }
    /*
    if(ls.size())
        qDebug()<<ls.size();
*/
}

void AI::tank_move()
{
    //射击
    shoot_check();

    position xx(get_x()), yy(get_y());
    if(get_move_state()==true||
           move_times!=0)
    {

        switch (get_direction()) {
        case UP:
            set_pos(xx,yy-NORMAL_ENEMY_SPEED);
            break;

        case LEFT:
            set_pos(xx-NORMAL_ENEMY_SPEED,yy);
            break;

        case DOWN:
            set_pos(xx,yy+NORMAL_ENEMY_SPEED);
            break;

        case RIGHT:
            set_pos(xx+NORMAL_ENEMY_SPEED,yy);
            break;
        }

        //AI碰撞缓冲

        if(check_collision())
        {
            move_times=0;
            set_move_state(false);
            set_shoot_state(true);
            auto x0_before(xx);
            auto y0_before(yy);
            xx/=UNIT;
            yy/=UNIT;
            ls_clear();

            switch (get_direction()) {
            case UP:
                if(yy*UNIT<y0_before)yy++;
                //set_pos(x0*UNIT,y0*UNIT);
                //set_direction(DOWN);
                break;

            case LEFT:
                if(xx*UNIT<x0_before)xx++;
                //set_pos(x0*UNIT,y0*UNIT);
                //set_direction(RIGHT);
                break;

            }
            set_pos(xx*UNIT,yy*UNIT);
            //set_move_state(false);
            /*
            path(get_wptr()->get_player()->get_x(),
                 get_wptr()->get_player()->get_x());
                 */
        }


        else
            move_times++;
            move_times%=10;
    }

}
//判断是否射击
bool  AI::shoot_judge()
{
    int oj=((get_x()-x0)*(get_x()-x0)+
            (get_y()-y0)*(get_y()-y0));
    if(oj<=200*UNIT*UNIT&&get_x()==x0)
        return true;
    if(oj<=200*UNIT*UNIT&&get_y()==y0)
        return true;
    return false;
}

void AI::shoot_check()
{
    if(shoot_judge() && !(get_x()%UNIT) && !(get_y()%UNIT))
    {
        set_shoot_state(false);
        if(get_x()>x0){
            set_direction(LEFT);
            set_shoot_state(true);
        }
        else if(get_x()<x0){
            set_direction(RIGHT);
            set_shoot_state(true);
        }
        else if(get_y()>y0){
            set_direction(UP);
            set_shoot_state(true);
        }
        else if(get_y()<y0){
            set_direction(DOWN);
        set_shoot_state(true);
        }
        set_move_state(false);

    }
    else
        set_shoot_state(false);
}

bool AI::check_collision()
{
    if(check_edge_collision())
        return true;
    else if(check_barrier_collision())
        return true;
    else if(check_base_collision(this, get_wptr()->get_player()))
        return true;
    else if(check_other_ai_collision())
        return true;

    return false;
}

void AI::enter_center_react()
{
    auto ptr=get_wptr()->get_center_ls()->get_list_ptr();
    for(auto iter=ptr->begin();
        iter!=ptr->end();
        iter++)
    {
        switch((*iter)->get_type())
        {
        case PLAYER_CENTER:
            (*iter)->set_hp(0);
            break;
        case NORMAL_BULLET_CENTER:
            if(!(*iter)->times)
                (*iter)->times++;
            break;
        case SUPER_BULLET_CENTER:
            if(!(*iter)->times)
                (*iter)->times++;
            break;
        case HP_CENTER:
            if(!(*iter)->times)
                (*iter)->times++;
        }
    }
}

void AI::set_target(position xx, position yy)
{
    x0=xx;
    y0=yy;
}

bool AI::check_other_ai_collision()
{
    auto ai_list_ptr=get_wptr()->get_enemy_ls()->get_list_ptr();

    for( auto iter=ai_list_ptr->begin();
         iter!=ai_list_ptr->end();
         iter++)
    {
        if(*iter==this)
            continue;

        else if(check_base_collision(this, *iter))
            return  true;
    }

    return false;
}



AI::~AI()
{

    auto iter=ls.begin();
    while(iter!=ls.end())
    {
        delete *iter;
        iter++;
    }

}




