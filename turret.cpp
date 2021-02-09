#include "turret.h"

Turret::Turret(position xx, position yy, Widget *p):
    AI(xx, yy, 5, TURRET_HP, p), times(0)
{
    set_shoot_state(false);
    set_target(-1,-1);

    _pic.load(":/turret/turret.png");

    wave1.load(":/turret/blast_wave_3.png");
    wave2.load(":/turret/blast_wave_4.png");
    wave3.load(":/turret/blast_wave_5.png");
    wave4.load(":/turret/blast_wave_6.png");
    wave5.load(":/turret/blast_wave_7.png");
}


void Turret::tank_move()
{
    times++;
    times%=100;
}

void Turret::draw(QPainter &painter)
{
    position x(get_x()), y(get_y());

    coord_trans(x, y, get_wptr());//坐标转换

    painter.drawPixmap(x, y, _pic);
}

void Turret::redraw_wave(QPainter &painter)
{
    position x(get_x()), y(get_y());

    coord_trans(x, y, get_wptr());//坐标转换
    QPixmap qs;
       if(times>=0 && times<20)
       {
           x-=10, y-=10;
           qs=wave1;
       }
       else if(times>=20 && times<40)
       {
           x-=20,y-=20;
           qs=wave2;
       }
       else if(times>=40 && times<60)
       {
           x-=30, y-=30;
           qs=wave3;
       }
       else if(times>=60 && times<80)
       {
           x-=40, y-=40;
           qs=wave4;
       }
       else if(times>=80 && times<100)
       {
           x-=55,y-=55;
           qs=wave5;
       }


       painter.drawPixmap(x, y, qs);



}

void Turret::redraw(QPainter &painter)
{
    if(hp_bar_times)
        {
            hp_bar_times++;
            hp_bar_times%=HP_BAR_LOAD_TIME;

            position x(get_x()), y(get_y());
            coord_trans(x,y,get_wptr());

            double radio((double)get_hp()/TURRET_HP);

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

void Turret::ctrl_direction()
{}

void Turret::path()
{}

void Turret::shoot()
{
    auto plr=get_wptr()->get_player();
    if(
            !(times%20)
            &&plr->get_x()>=get_x()-60&&plr->get_y()>=get_y()-60
            &&plr->get_x()<=get_x()+80&&plr->get_y()<=get_y()+80
            )
    {
        //qDebug()<<"hurt!";
        plr->set_hp(plr->get_hp()-1);
    }
}
