#include "water.h"

Water::Water(position xx, position yy, Widget* p):
    Barrier(xx,yy,p)
{
    set_type(WATER);
    water_pic_1.load(WATER_1);
    water_pic_2.load(WATER_2);
    water_pic_3.load(WATER_3);
    water_pic_4.load(WATER_4);
    water_pic_5.load(WATER_5);
    times=0;
}

void Water::draw(QPainter &painter)
{
    position x(get_x()), y(get_y());

    coord_trans(x,y,get_wptr());//坐标转换

    if(times<50)  times++;
    else  times=0;
    if(check_inside_window(x,y,get_width(),get_height()))
    {
        if(times%50>=0&&times%50<10)
        {
            painter.drawPixmap(x,y,water_pic_1);
        }
        else if(times%50>=10&&times%50<20)
        {
            painter.drawPixmap(x,y,water_pic_2);
        }
        else if(times%50>=20&&times%50<30)
        {
            painter.drawPixmap(x,y,water_pic_3);
        }
        else if(times%50>=30&&times%50<40)
        {
            painter.drawPixmap(x,y,water_pic_4);
        }
        else if(times%50>=40&&times%50<50)
        {
            painter.drawPixmap(x,y,water_pic_5);
        }
    }
}

