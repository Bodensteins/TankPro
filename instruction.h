#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QWidget>
#include "GameSet.h"
#include <QPainter>

class Instruction : public QWidget
{
    Q_OBJECT
public:
    explicit Instruction(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
};

#endif // INSTRUCTION_H
