#ifndef SUMMONER_H
#define SUMMONER_H

#include "champion.h"
#include "World_of_Const.h"

class Champion;
class QTcpSocket;

struct Point
{
    float x;
    float y;
};

class Summoner
{
public:
    Summoner(QTcpSocket* Socket,QString UserName,int Index,Champion* champion);
    QTcpSocket* qtcpSocket;
    const QString UserName;
    const int IndexOfClient;
    Point last_position;
    Point current_position;
    Point move_position;
    bool IsBlocked=0;
    bool IsLogOut;
private:
    Champion* champion;

};

#endif // SUMMONER_H
