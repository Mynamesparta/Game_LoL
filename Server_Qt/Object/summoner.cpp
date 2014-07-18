#include "summoner.h"

Summoner::Summoner(QTcpSocket* Socket,QString UserName,int Index):qtcpSocket(Socket),UserName(UserName),IndexOfClient(Index)
{
    current_position.x=current_position.y=move_position.x=move_position.y=0;
    last_position=current_position;
}
