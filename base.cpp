#include "base.h"

Base::Base(
        position xx,
        position yy,
        sizetype w,
        sizetype h,
        Widget *p
           ):
    x(xx),y(yy),width(w),height(h),w_ptr(p)
{}

Base::~Base()
{}

void Base::redraw(QPainter &)
{}

position Base::get_x()const
{
    return x;
}
position Base::get_y()const
{
    return y;
}
sizetype Base::get_width() const
{
    return width;
}
sizetype Base::get_height() const
{
    return height;
}

Widget* Base::get_wptr() const
{
    return w_ptr;
}

void Base::set_pos(position xx, position yy)
{
    x=xx;
    y=yy;
}
void Base::set_size(sizetype w, sizetype h)
{
    width=w;
    height=h;
}


bool check_base_collision(Base *lhs, Base *rhs)
{
    position lx=lhs->get_x(), rx=rhs->get_x(),
            ly=lhs->get_y(), ry=rhs->get_y();
    sizetype lw=lhs->get_width(), rw=rhs->get_width(),
            lh=lhs->get_height(),rh=rhs->get_height();

    if(lx+lw<=rx && ly>=ry && ly<=ry+rh)
        return false;
    else if(lx+lw<=rx && ly+lh>=ry && ly+lh<=ry+rh)
        return false;
    else if(lx>=rx && lx<=rx+rw && ly+lh<=ry)
        return false;
    else if(lx+lw>=rx && lx+lw<=rx+rw && ly+lh<=ry)
        return false;

    else if(lx>=rx+rw && ly>=ry && ly<=ry+rh)
        return false;
    else if(lx>=rx+rw && ly+lh>=ry && ly+lh<=ry+rh)
        return false;
    else if(lx>=rx && lx<=rx+rw && ly>=ry+rh)
        return false;
    else if(lx+lw>=rx && lx+lw<=rx+rw && ly>=ry+rh)
        return false;


    else if(lx>=rx && lx<=rx+rw && ly>=ry && ly<=ry+rh)
        return true;
    else if(lx+lw>=rx && lx+lw<=rx+rw && ly>=ry && ly<=ry+rh)
        return true;
    else if(lx>=rx && lx<=rx+rw && ly+lh>=ry && ly+lh<=ry+rh)
        return true;
    else if(lx+lw>=rx && lx+lw<=rx+rw && ly+lh>=ry && ly+lh<=ry+rh)
        return true;

    /*
    else if(rx>lx && rx<lx+lw && ry>ly && ry<ly+rh)
        return true;
    else if(rx+rw>lx && rx+rw<lx+lw && ry+rh>ly && ry+rh<ly+lh)
        return true;

    else if(lx<rx && lx+lw>rx+rw && ry<ly && ry+rh>ly+lh)
        return true;
    else if(rx<lx && rx+rw>lx+lw && ly<ry && ly+lh>ry+rh)
        return true;
        */



    return false;
}

void coord_trans(position &x, position &y, Widget* p)
{
    x-=p->get_x();
    y-=p->get_y();
}

bool check_inside_window(position x, position y, sizetype w, sizetype h)
{
    if(x+w>=0 && y+h >=0 && x<=WINDOW_SIZE_X && y<=WINDOW_SIZE_Y)
        return true;
    else return false;
}
