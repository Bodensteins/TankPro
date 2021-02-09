#ifndef LEVEL_1_H
#define LEVEL_1_H

#include "widget.h"
#include "GameSet.h"
#include "menuchooselevel.h"
#include "menupause.h"

class Level_1 : public Widget
{
public:
    Level_1(MenuChooseLevel *, QWidget *parent = nullptr);

protected:
    void ini_scene() override;
    void ini_all_lists() override;
    void play_game() override;
    void check_game_over() override;

private:
    MyPushButton * pauseBtn;
    MenuPause *p_ptr;
};

#endif // LEVEL_1_H
