#include "level_1.h"
#include "level_2.h"
#include "menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu m;
    m.show();
    a.exec();
    return 0;
}
