#ifndef BASE_H
#define BASE_H

#include "GameSet.h"
#include "widget.h"
//检查两元素是否重叠(重叠返回true,否则返回false)
bool check_base_collision(Base *, Base *);
//检查是否可以画在窗口中
bool check_inside_window(position, position, sizetype, sizetype);
//坐标变换函数
void coord_trans(position &, position &, Widget*);

//所有游戏元素的基类
class Base
{
public:
    //构造函数
    Base(
            position,
            position,
            sizetype,
            sizetype,
            Widget*
            );

    //虚析构函数
    virtual ~Base();

    //绘图函数，纯虚函数
    virtual void draw(QPainter &)=0;
    virtual void redraw(QPainter &);

    //获取x坐标
    position get_x()const;
    //获取y坐标
    position get_y()const;

    //获取x方向上的宽度
    sizetype get_width()const;
    //获取y方向上的长度
    sizetype get_height()const;
    //获取控制它的窗口对象的指针
    Widget* get_wptr()const;

    //设置元素的x、y坐标
    void set_pos(position,position);
    //设置元素的宽度、长度
    void set_size(sizetype, sizetype);
    //设置控制它的窗口对象的指针
    void set_wptr(Widget *);

private:
    //元素的x、y坐标
    position x, y;

    //元素的x方向宽度(width)、y方向长度(height)
    sizetype width,height;

    //指向控制它的窗口对象的指针
    Widget *w_ptr;
};

#endif // BASE_H
