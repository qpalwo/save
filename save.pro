#-------------------------------------------------
#
# Project created by QtCreator 2018-07-03T09:52:35
#
#-------------------------------------------------

QT       += core gui network concurrent

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
    game/basegame.cpp \
    game/basegame.cpp \
    UI/wordwindow.cpp

HEADERS += \
        UI\mainwindow.h \
        UI\loading.h \
        UI\UiManager.h \
    attr/player.h \
    attr/gameworld.h \
    UI/scenedesert.h \
    UI/sceneforest.h \
    game/basegame.h \
    game/basegame.h \
    UI/wordwindow.h

FORMS += \
        UI\mainwindow.ui \
    UI\loading.ui \
    UI/scenedesert.ui \
    UI/sceneforest.ui \
    UI/wordwindow.ui

RESOURCES += \
    res/op/openres.qrc \
    res/people/player.qrc \
    res/desertb.qrc \
    res/op/opengif.qrc \
    res/conver.qrc
