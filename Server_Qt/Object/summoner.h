#ifndef SUMMONER_H
#define SUMMONER_H

#include "champion.h"
#include "Worlds/World_of_Const.h"
#include "Worlds/World_of_Struct.h"

class Champion;
class QTcpSocket;
struct Point;

class Summoner
{
public:
    Summoner(QTcpSocket* Socket,QString UserName,int Index,Champion* champion);
    const QTcpSocket *takeSocket();
    const QString UserName;
    const int IndexOfClient;
    Point last_position;
    Point current_position;
    Point move_position;
    bool IsBlocked=0;
    bool IsLogOut;
private:
    Champion* champion;
    QTcpSocket const * qtcpSocket;

};

#endif // SUMMONER_H
