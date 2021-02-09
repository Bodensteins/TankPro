#include "game_map.h"
#include "brick.h"
#include "iron.h"
#include "water.h"
#include "wood.h"

Game_map::Game_map(Widget *p):
    w_ptr(p)
{
    position size_x(get_wptr()->get_map_x()/UNIT),
            size_y(get_wptr()->get_map_y()/UNIT);
    for(position i=0;i<size_x;i++)
    {
        for(position j=0;j<size_y;j++)
            barriers[i][j]=nullptr;
    }

}

Game_map::Game_map(QString qs, Widget *p):
    w_ptr(p)
{
    position size_x(get_wptr()->get_map_x()/UNIT),
            size_y(get_wptr()->get_map_y()/UNIT);
    for(position i=0;i<size_x;i++)
    {
        for(position j=0;j<size_y;j++)
            barriers[i][j]=nullptr;
    }

    QFile data(qs);
    if(!data.open(QIODevice::ReadOnly))
        exit(-1);
    QTextStream qts(&data);

    position x, y, x_pos, y_pos;
    int type;
    int debug_num=0;
    while(!qts.atEnd())
    {
        debug_num++;
        qts>>x_pos>>y_pos>>type;
        x=x_pos*UNIT;
        y=y_pos*UNIT;
        if(barriers[x_pos][y_pos]!=nullptr)
            continue;

        switch (type) {
        case 0:
            barriers[x_pos][y_pos]=new Brick(x, y, w_ptr);
            break;
        case 1:
            barriers[x_pos][y_pos]=new Iron(x, y, w_ptr);
            break;
        case 2:
            barriers[x_pos][y_pos]=new Water(x, y, w_ptr);
            break;
        case 3:
            barriers[x_pos][y_pos]=new Wood(x, y, w_ptr);
            break;
        default:
            qDebug()<<debug_num<<type<<" mistake";
            exit(-1);
        }

    }

    data.close();
}

Widget* Game_map::get_wptr()const
{
    return w_ptr;
}

void Game_map::set_wptr(Widget *p)
{
    w_ptr=p;
}

Barrier* Game_map::check_if_barrier(position x, position y) const
{
    return barriers[x][y];
}

void Game_map::push_barrier(Barrier* b_ptr)
{
    position x_pos(position(b_ptr->get_x()/UNIT));
    position y_pos(position(b_ptr->get_x()/UNIT));

    if(barriers[x_pos][y_pos]!=nullptr)
        delete barriers[x_pos][y_pos];

    barriers[x_pos][y_pos]=b_ptr;
}

void Game_map::pop_barrier(position x, position y)
{
    position x_pos(position(x/UNIT));
    position y_pos(position(y/UNIT));

    if(barriers[x_pos][y_pos]!=nullptr)
        delete barriers[x_pos][y_pos];

    barriers[x_pos][y_pos]=nullptr;
}

void Game_map::check_all_barriers_states()
{
    position size_x(get_wptr()->get_map_x()/UNIT),
            size_y(get_wptr()->get_map_y()/UNIT);
    for(position i=0;i<size_x;i++)
    {
        for(position j=0;j<size_y;j++)
        {
            /*
            auto ptr=barriers[i][j];
            if(ptr==nullptr)
                continue;
            else if(!ptr->check_exist())
            {
                delete ptr;
                ptr=nullptr;
            }
            */
            if(barriers[i][j]!=nullptr &&
                    !barriers[i][j]->check_exist())
            {
                pop_barrier(i*UNIT, j*UNIT);
            }
        }
    }
}

void Game_map::draw_all_barriers(QPainter &painter)
{
    position size_x(get_wptr()->get_map_x()/UNIT),
            size_y(get_wptr()->get_map_y()/UNIT);
    for(position i=0;i<size_x;i++)
    {
        for(position j=0;j<size_y;j++)
        {
            auto ptr=barriers[i][j];
            if(ptr!=nullptr)
                ptr->draw(painter);
        }
    }
}

Game_map::~Game_map()
{
    position size_x(get_wptr()->get_map_x()/UNIT),
            size_y(get_wptr()->get_map_y()/UNIT);
    for(position i=0;i<size_x;i++)
    {
        for(position j=0;j<size_y;j++)
        {
            if(barriers[i][j]!=nullptr)
                delete barriers[i][j];
        }
    }
}
