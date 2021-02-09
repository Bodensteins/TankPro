#ifndef MENU_H
#define MENU_H

#include "GameSet.h"
#include <QWidget>
#include "mypushbutton.h"
#include <QPainter>
#include "menuchooselevel.h"
#include "instruction.h"

class Menu : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

    void paintEvent(QPaintEvent *);

private:
    MyPushButton * startBtn,
                 * continueBtn,
                 * quitBtn;

    MenuChooseLevel *c_ptr;
    Instruction *i_ptr;
};

#endif // MENU_H
