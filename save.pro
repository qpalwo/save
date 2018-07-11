#-------------------------------------------------
#
# Project created by QtCreator 2018-07-03T09:52:35
#
#-------------------------------------------------

QT       += core gui network concurrent multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = save
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += resources_big

SOURCES += \
        UI\main.cpp \
        UI\mainwindow.cpp \
        UI\loading.cpp \
        UI\UiManager.cpp \
    attr/player.cpp \
    attr/gameworld.cpp \
    UI/scenedesert.cpp \
    UI/sceneforest.cpp \
    UI/wordwindow.cpp \
    UI/openpagebutton.cpp \
    UI/menuwidget.cpp \
    UI/bag.cpp\
    game/sunsmellcollect.cpp \
    game/smellofgame.cpp \
	game/collecterofgame.cpp \
    game/tornado.cpp \
    game/playerinwind.cpp \
    game/avoidstorm.cpp \
    UI/sceneruins.cpp \
    UI/scenesnow.cpp \
    game/keepmoving.cpp \
    UI/begining.cpp \
    UI/achieve.cpp \
    UI/saveandload.cpp \
    game/burnbook.cpp \
    game/booktoburn.cpp \
    game/fireburnbook.cpp \
    UI/set.cpp \
    UI/set_menu.cpp \
    UI/gamemap.cpp \
    UI/gainachieve.cpp

HEADERS += \
        UI\mainwindow.h \
        UI\loading.h \
        UI\UiManager.h \
    attr/player.h \
    attr/gameworld.h \
    UI/scenedesert.h \
    UI/sceneforest.h \
    UI/wordwindow.h \
    UI/openpagebutton.h \
    UI/menuwidget.h \
    UI/bag.h \
    game/sunsmellcollect.h \
    game/smellofgame.h \
	game/collecterofgame.h \
    game/avoidstorm.h \
    game/tornado.h \
    game/playerinwind.h \
    UI/sceneruins.h \
    UI/scenesnow.h \
    game/keepmoving.h \
    UI/begining.h \
    UI/achieve.h \
    UI/saveandload.h \
    game/burnbook.h \
    game/booktoburn.h \
    game/fireburnbook.h \
    UI/set.h \
    UI/set_menu.h \
    UI/gamemap.h \
    UI/gainachieve.h

FORMS += \
        UI\mainwindow.ui \
    UI\loading.ui \
    UI/scenedesert.ui \
    UI/sceneforest.ui \
    UI/wordwindow.ui \
    UI/menuwidget.ui \
    UI/bag.ui \
    game/sunsmellcollect.ui \
    game/avoidstorm.ui \
    UI/sceneruins.ui \
    UI/scenesnow.ui \
    game/keepmoving.ui \
    UI/begining.ui \
    UI/achieve.ui \
    UI/saveandload.ui \
    game/burnbook.ui \
    UI/set.ui \
    UI/set_menu.ui \
    UI/gamemap.ui \
    UI/gainachieve.ui

RESOURCES += \
    res/op/openres.qrc \
    res/people/player.qrc \
    res/desertb.qrc \
    res/op/opengif.qrc \
    res/conver.qrc \
    res/forest.qrc \
    res/menuz.qrc  \
    res/button/button.qrc \
    res/music/music.qrc \
    res/ruins.qrc \
    res/snow.qrc \
    res/bag.qrc \
    res/game/gameRes.qrc \
    res/save/saveandload.qrc \
    res/achieve/achieve.qrc \
    res/game/gameRes.qrc \
    res/setting/setting.qrc \
    res/map/gamemap.qrc \
    res/game/gameres2.qrc \
    res/mouse/mouse.qrc

DISTFILES += \
    res/people/uncle.png \
    res/scene/begining.png
