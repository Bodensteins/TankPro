#include "instruction.h"

Instruction::Instruction(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(500,500);
    setWindowTitle("操作说明");
    setWindowIcon(QIcon(ICON));
}

void Instruction::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QFont font("Microsoft JhengHei", 14, 75);

    QPixmap pix;
    pix.load(":/ui/begin_background.png");
    painter.drawPixmap(0,0,pix);


    painter.setFont(font);
    painter.setPen(QColor(67, 137, 148));

    painter.drawText(50,50, "w : 向上移动");
    painter.drawText(50,80, "a  : 向左移动");
    painter.drawText(50,110, "s  : 向下移动");
    painter.drawText(50,140, "d  : 向右移动");
    painter.drawText(50,170, "h  : 射击");

    painter.drawText(50,240, "Level 1: destroy all enemies");
    painter.drawText(QRect(50,260,350,100), tr("Level 2: defende your center and destroy the enemies' center"));
    painter.drawText(50,410, "Level 3: find all player centers");
}
