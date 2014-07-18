QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app
CONFIG += console
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    client-main.cpp \
    Client/gamefield.cpp\
    Client/game.cpp \
    Object/summoner.cpp \
    Object/champion.cpp \
    Client/view.cpp \
    Object/champion_selection.cpp

HEADERS  += \
    Client/gamefield.h\
    Client/game.h \
    Object/summoner.h \
    Object/champion.h \
    Client/view.h \
    Worlds/World_of_Const.h \
    Worlds/World_of_Button.h \
    Object/champion_selection.h


