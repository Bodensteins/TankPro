#ifndef CENTER_LIST_H
#define CENTER_LIST_H
#include "center.h"

class Center_list
{
public:
    Center_list(Widget*);

    std::list<Center*>* get_list_ptr();

    void push_center(Center*);

    void check_all_centers();

    void draw_all_centers(QPainter &);

    void redraw_all_centers(QPainter &);

    ~Center_list();
private:
    Widget *w_ptr;
    std::list<Center*> ls;
};


#endif // CENTER_LIST_H
