QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ai.cpp \
    astar.cpp \
    barrier.cpp \
    base.cpp \
    brick.cpp \
    bullet.cpp \
    bullet_list.cpp \
    center.cpp \
    center_list.cpp \
    enemy_list.cpp \
    game_map.cpp \
    instruction.cpp \
    iron.cpp \
    level_1.cpp \
    level_2.cpp \
    level_3.cpp \
    main.cpp \
    menu.cpp \
    menuchooselevel.cpp \
    menupause.cpp \
    mypushbutton.cpp \
    normal_bullet.cpp \
    normal_enemy.cpp \
    player.cpp \
    super_bullet.cpp \
    super_enemy.cpp \
    tank.cpp \
    turret.cpp \
    water.cpp \
    widget.cpp \
    wood.cpp

HEADERS += \
    GameSet.h \
    ResourcesPath.h \
    ai.h \
    astar.h \
    barrier.h \
    base.h \
    brick.h \
    bullet.h \
    bullet_list.h \
    center.h \
    center_list.h \
    enemy_list.h \
    game_map.h \
    instruction.h \
    iron.h \
    level_1.h \
    level_2.h \
    level_3.h \
    menu.h \
    menuchooselevel.h \
    menupause.h \
    mypushbutton.h \
    normal_bullet.h \
    normal_enemy.h \
    player.h \
    super_bullet.h \
    super_enemy.h \
    tank.h \
    turret.h \
    water.h \
    widget.h \
    wood.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
 \    #test_data.qrc
    game_res.qrc

DISTFILES +=
    #bomb/bomb_1.png \
    #bomb/bomb_2.png \
    #bomb/bomb_3.png \
    #center/center_hp.png \
     #center/center_hp_blank.png
