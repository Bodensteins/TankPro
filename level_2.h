#ifndef LEVEL_2_H
#define LEVEL_2_H

#include "widget.h"
#include "GameSet.h"
#include "menuchooselevel.h"
#include "menupause.h"


class Level_2 : public Widget
{
public:
    Level_2(MenuChooseLevel *p, QWidget *parent = nullptr);

protected:
    void ini_scene() override;
    void ini_all_lists() override;
    void play_game() override;
    void check_game_over() override;

private:
    Center *victory_point,
            *defeat_point;
    bool is_win;

    MyPushButton * pauseBtn;
    MenuPause *p_ptr;

};

#endif // LEVEL_2_H
