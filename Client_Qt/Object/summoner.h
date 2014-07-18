#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsItem>
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QVector>
#include "champion.h"

class Champion;
class Summoner
{

public:
    Summoner(QString NameOfPLayer,Champion* champion);
    void move(float x, float y);
    void end_move(float x, float y);
    void First_skill();
    void Second_skill();
    void Third_skill();
    void Fourth_skill();
private:
    QString NameOfPLayer,NameOfChampion;
    Champion* champion;
};

#endif // PLAYER_H
