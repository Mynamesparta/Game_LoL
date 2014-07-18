QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rbServer
TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    server-main.cpp \
    Server/server.cpp \
    Server/ingame.cpp \
    Object/summoner.cpp \
    Object/champion.cpp \
    Object/wall.cpp

HEADERS  += \
    Server/server.h \
    Server/ingame.h \
    Object/summoner.h \
    Object/champion.h \
    Object/wall.h \
    World_of_Const.h

