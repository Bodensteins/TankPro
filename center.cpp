#include "center.h"
#include "widget.h"

Center::Center(position xx, position yy, hit_point h,int t, Widget*p):
    Base(xx, yy, CENTER_SIZE_X, CENTER_SIZE_Y, p),
     times(0), hp(h), type(t), hp_bar_times(0), is_player_come(false)
{}

hit_point Center::get_hp() const
{
    return hp;
}
int Center::get_type() const
{
    return type;
}

void Center::set_hp(hit_point h)
{
    hp=h;
}

void Center::draw(QPainter &painter)
{

    position x(get_x()), y(get_y());
    coord_trans(x,y,get_wptr());
    QString qs;
    switch(type){
    case HP_CENTER:
        if(!times)
            qs=HP_CENTER_1;
        else
            qs=HP_CENTER_2;
        break;
    case NORMAL_BULLET_CENTER:
        if(!times)
            qs=NORMAL_BULLET_CENTER_1;
        else
            qs=NORMAL_BULLET_CENTER_2;
        break;
    case SUPER_BULLET_CENTER:
        if(!times)
            qs=SUPER_BULLET_CENTER_1;
        else
            qs=SUPER_BULLET_CENTER_2;
        break;
    case PLAYER_CENTER:
         if(!is_player_come)qs=PLAYER_CENTER_1;
         else
             qs=PLAYER_CENTER_2;
        break;
    case ENEMY_CENTER:
            qs=ENEMY_CENTER_1;
        break;
    }

    if(times && type!=PLAYER_CENTER){
        times++;
        times%=LOAD_TIME;
    }

    if(check_inside_window(x,y,get_width(),get_height()))
        painter.drawPixmap(x, y, qs);
}

void Center::redraw(QPainter &painter)
{
    if(hp_bar_times)
    {
        hp_bar_times++;
        hp_bar_times%=HP_BAR_LOAD_TIME;

        position x(get_x()), y(get_y());
        coord_trans(x,y,get_wptr());

        hit_point full_hp;
        switch (type) {
        case PLAYER_CENTER:full_hp=PLAYER_CENTER_HP;break;
        case ENEMY_CENTER:full_hp=ENEMY_CENTER_HP;break;
        case NORMAL_BULLET_CENTER:full_hp=BULLET_CENTER_HP;break;
        case SUPER_BULLET_CENTER:full_hp=BULLET_CENTER_HP;break;
        case HP_CENTER:full_hp=HP_CENTER_HP;break;
        }

        double radio((double)hp/full_hp);

        QBrush brush(Qt::red);
        QPen pen(Qt::red);
        painter.setBrush(brush);
        painter.setPen(pen);
        painter.drawRect(
                    QRect(x,y,get_width(), 5));

        brush.setColor(Qt::green);
        pen.setColor(Qt::green);
        painter.setBrush(brush);
        painter.setPen(pen);
        painter.drawRect(
                    QRect(x,y,get_width()*radio, 5));
    }
}
