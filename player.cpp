#include "player.h"
#include "bullet_list.h"
#include "center_list.h"
#include "super_bullet.h"

Player::Player(position xx,
               position yy,
               direction d,
               hit_point hp,
               int b_num,
               Widget *p
               ):
    Tank(xx, yy, d, hp, p), bullet_num(b_num), bullet_type(0)
{
    type=PLAYER_T;
    is_up=false;
    is_left=false;
    is_right=false;
    is_down=false;
    //is_press_shoot=false;
    lv3_vic=0;
}

bool Player::check_enemy_collision()
{
    auto enemy_ls_ptr=get_wptr()->get_enemy_ls()->get_list_ptr();
    auto iter=enemy_ls_ptr->begin();
    while(iter!=enemy_ls_ptr->end())
    {
        if(check_base_collision(*iter,this))
            return true;
        iter++;
    }
    return false;
}

bool Player::check_center_collision()
{
    auto center_ls_ptr=get_wptr()->get_center_ls()->get_list_ptr();
    auto iter=center_ls_ptr->begin();
    while(iter!=center_ls_ptr->end())
    {
        if((
              (*iter)->get_type()==ENEMY_CENTER )
                && check_base_collision(*iter,this))
            return true;
        iter++;
    }
    return false;
}

bool Player::check_collision()
{
    if(check_edge_collision())
        return true;
    if(check_barrier_collision())
        return true;
    if(check_enemy_collision())
        return true;
    if(check_center_collision())
        return true;

    return false;
}

void Player::enter_center_react()
{
    auto ptr=get_wptr()->get_center_ls()->get_list_ptr();
    for(auto iter=ptr->begin();
        iter!=ptr->end();
        iter++)
    {
        if(check_base_collision(this, *iter))
        {
            switch((*iter)->get_type())
            {
            case NORMAL_BULLET_CENTER:
                if(bullet_type==0){
                    if(!(*iter)->times &&
                            bullet_num<MAX_NORMAL_BULLET_NUM)
                    {
                        bullet_num=MAX_NORMAL_BULLET_NUM;
                        (*iter)->times=1;
                        //qDebug()<<"bullet!";
                    }
                }
                else
                {
                    bullet_type=0;
                    bullet_num=MAX_NORMAL_BULLET_NUM;
                    (*iter)->times=1;
                }
                break;

            case SUPER_BULLET_CENTER:
                if(bullet_type==1){
                    if(!(*iter)->times &&
                            bullet_num<MAX_SUPER_BULLET_NUM)
                    {
                        bullet_num=MAX_SUPER_BULLET_NUM;
                        (*iter)->times=1;
                        //qDebug()<<"bullet!";
                    }
                }
                else
                {
                    if(!(*iter)->times)
                    {
                        bullet_type=1;
                        bullet_num=MAX_SUPER_BULLET_NUM;
                        (*iter)->times=1;
                    }
                }
                break;

            case HP_CENTER:
                if(!(*iter)->times && get_hp()<PLAYER_HP)
                {
                    set_hp(get_hp()+20);
                    if(get_hp()>PLAYER_HP)
                        set_hp(PLAYER_HP);
                    (*iter)->times++;
                }
                break;

            case PLAYER_CENTER:
                if(!((*iter)->is_player_come))
                {
                    lv3_vic++;
                    (*iter)->is_player_come=true;
                    //qDebug()<<lv3_vic;
                }
                break;
            }
        }
    }
}

void Player::ctrl_direction(QKeyEvent *event)
{
        if(move_times)
            return;

        set_move_state(true);
        if(event->key()==Qt::Key_W)
        {
            is_up=true;
            is_left=false;
            is_right=false;
            is_down=false;

            set_direction(UP);
            return;
        }
        else if(event->key()==Qt::Key_A)
        {
            is_up=false;
            is_left=true;
            is_right=false;
            is_down=false;

            set_direction(LEFT);
            return;
        }
        else if(event->key()==Qt::Key_S)
        {
            is_up=false;
            is_left=false;
            is_right=false;
            is_down=true;

            set_direction(DOWN);
            return;
        }
        else if(event->key()==Qt::Key_D)
        {
            is_up=false;
            is_left=false;
            is_right=true;
            is_down=false;

            set_direction(RIGHT);
            return;

    }
}

void Player::ctrl_stop(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        set_move_state(false);
        is_up=false;
    }
    else if(event->key()==Qt::Key_A)
    {
        set_move_state(false);
        is_left=false;
    }
    else if(event->key()==Qt::Key_S)
    {
        set_move_state(false);
        is_down=false;
    }
    else if(event->key()==Qt::Key_D)
    {
        set_move_state(false);
        is_right=false;
    }

}

void Player::tank_move()
{


        position x(get_x());
        position y(get_y());
        auto ptr(get_wptr());

        if(move_times)
        {
            switch (get_direction()) {
            case UP:
                y-=TANK_SPEED;
                set_pos(x,y);
                ptr->set_position(ptr->get_x(),ptr->get_y()-TANK_SPEED);
                break;

            case LEFT:
                x-=TANK_SPEED;
                set_pos(x,y);
                ptr->set_position(ptr->get_x()-TANK_SPEED,ptr->get_y());
                break;
            case DOWN:
                y+=TANK_SPEED;
                set_pos(x,y);
                ptr->set_position(ptr->get_x(),ptr->get_y()+TANK_SPEED);
                break;
            case RIGHT:
                x+=TANK_SPEED;
                set_pos(x,y);
                ptr->set_position(ptr->get_x()+TANK_SPEED,ptr->get_y());
                break;
            }

            move_times++;
            move_times%=10;
        }

        else if(is_up)
        {
            y-=TANK_SPEED;
            set_pos(x,y);

            if(check_collision())
            {
                y+=TANK_SPEED;
                set_pos(x,y);
                is_up=false;
            }
            else
            {
                ptr->set_position(ptr->get_x(),
                              ptr->get_y()-TANK_SPEED);
                move_times++;
                move_times%=10;
            }
            return;

        }
        else if(is_down)
        {
            y+=TANK_SPEED;
            set_pos(x,y);

            if(check_collision())
            {
                y-=TANK_SPEED;
                set_pos(x,y);
                is_down=false;
            }
            else
            {
                ptr->set_position(ptr->get_x(),
                              ptr->get_y()+TANK_SPEED);
                move_times++;
                move_times%=10;
            }

        }
        else if(is_left)
        {
            x-=TANK_SPEED;
            set_pos(x,y);

            if(check_collision())
            {
                x+=TANK_SPEED;
                set_pos(x,y);
                is_left=false;
            }
            else
            {
                ptr->set_position(ptr->get_x()-TANK_SPEED,
                                ptr->get_y());
                move_times++;
                move_times%=10;
            }
        }
        else if(is_right)
        {
            x+=TANK_SPEED;
            set_pos(x,y);
            if(check_collision())
            {
                x-=TANK_SPEED;
                set_pos(x,y);
                is_right=false;
            }
            else
            {
                ptr->set_position(ptr->get_x()+TANK_SPEED,
                              ptr->get_y());
                move_times++;
                move_times%=10;
            }

        }


}

void Player::shoot(QKeyEvent *event)
{
    if(event->key()==Qt::Key_H && !limit_shoot
             && bullet_num)
    {
        //is_press_shoot=true;
        limit_shoot++;
        limit_shoot%=2;
        bullet_num--;
        position x0(get_x()), y0(get_y());

        switch (get_direction()) {
        case UP:
                y0-=UNIT;
                x0+=15;
                break;
        case LEFT:
                x0-=UNIT;
                y0+=15;
                break;
        case DOWN:
                y0+=2*UNIT;
                x0+=15;
                break;
        case RIGHT:
                x0+=2*UNIT;
                y0+=15;
                break;
        }
        auto b_ls_ptr=get_wptr()->get_bullet_ls();

        switch (bullet_type) {
        case 0:
            b_ls_ptr->push_bullet(
                        new Normal_bullet(
                            x0, y0,
                            get_direction(),
                            PLAYER_T,
                            get_wptr()
                            ));
            //qDebug()<<"Normal shoot!";
            break;

        case 1:
            b_ls_ptr->push_bullet(
                        new Super_bullet(
                            x0, y0,
                            get_direction(),
                            PLAYER_T,
                            get_wptr()
                            ));
            //qDebug()<<"Super shoot!";
        }

    }

    else
        limit_shoot=0;
}

/*
void Player::stop_shoot(QKeyEvent *event)
{
    if(event->key()==Qt::Key_H)
    {
        qDebug()<<"able to shoot";
        is_press_shoot=false;
    }
}
*/

void Player::draw(QPainter &painter)
{
    position x(get_x()), y(get_y());

    coord_trans(x, y, get_wptr());//坐标转换

    QString qs;
    switch(get_direction())
    {
    case UP:
        if(move_times%2==0)  qs=PLAYER_UP_1;
        else  qs=PLAYER_UP_2;
        break;
    case RIGHT:
        if(move_times%2==0)  qs=PLAYER_RIGHT_1;
        else  qs=PLAYER_RIGHT_2;
        break;
    case DOWN:
        if(move_times%2==0)  qs=PLAYER_DOWN_1;
        else  qs=PLAYER_DOWN_2;
        break;
    case LEFT:
        if(move_times%2==0)  qs=PLAYER_LEFT_1;
        else  qs=PLAYER_LEFT_2;
        break;
    }
    painter.drawPixmap(x, y, qs);
}

int Player::get_bullet_type() const
{
    return bullet_type;
}

int Player::get_bullet_num() const
{
    return bullet_num;
}

void Player::set_bullet_type(int t)
{
    type=t;
}
