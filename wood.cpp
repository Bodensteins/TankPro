#include "wood.h"

Wood::Wood(position xx, position yy, Widget* p):
    Barrier(xx,yy,p)
{
    set_type(WOOD);
    wood_pic.load(GRASS_1);
}

void Wood::draw(QPainter &painter)
{
    position x(get_x()), y(get_y());

    coord_trans(x,y,get_wptr());//坐标转换
    if(check_inside_window(x,y,get_width(),get_height()))
        painter.drawPixmap(x,y,wood_pic);
}

