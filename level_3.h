#ifndef LEVEL_3_H
#define LEVEL_3_H

#include "widget.h"
#include "GameSet.h"
#include "menupause.h"

class Level_3 : public Widget
{
public:
    Level_3(MenuChooseLevel *, QWidget *parent = nullptr);

protected:
    void ini_scene() override;
    void ini_all_lists() override;
    void play_game() override;
    void check_game_over() override;

private:
    bool is_win;

    MyPushButton * pauseBtn;
    MenuPause *p_ptr;
};

#endif // LEVEL_3_H
