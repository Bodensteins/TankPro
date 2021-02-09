#include "iron.h"

Iron::Iron(position xx, position yy, Widget* p):
    Barrier(xx,yy,p)
{
    set_type(IRON);
    set_type(IRON);
    iron_pic_1.load(IRON_1);
    iron_pic_2.load(IRON_2);
    iron_pic_3.load(IRON_3);
    iron_pic_4.load(IRON_4);
    iron_pic_5.load(IRON_5);
    times=0;
}

void Iron::draw(QPainter( &painter))
{
    position x(get_x()), y(get_y());

    coord_trans(x,y,get_wptr());//坐标转换

    if(times<300)  times++;
    else  times=0;
    if(check_inside_window(x,y,get_width(),get_height()))
    {
        if(times%300>=0&&times%300<276)
            painter.drawPixmap(x,y,iron_pic_1);
        else if(times%300>=276&&times%300<282)
            painter.drawPixmap(x,y,iron_pic_2);
        else if(times%300>=282&&times%300<288)
            painter.drawPixmap(x,y,iron_pic_3);
        else if(times%300>=288&&times%300<294)
            painter.drawPixmap(x,y,iron_pic_4);
        else if(times%300>=294&&times%300<300)
            painter.drawPixmap(x,y,iron_pic_5);
    }
}
