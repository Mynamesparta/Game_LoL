#include "summoner.h"

Summoner::Summoner(QTcpSocket* Socket, QString UserName, int Index, Champion *champion):
    qtcpSocket(Socket),UserName(UserName),IndexOfClient(Index),champion(champion)
{
    current_position.x=current_position.y=move_position.x=move_position.y=0;
    last_position=current_position;
}


QTcpSocket const * Summoner::takeSocket()
{
    return  qtcpSocket;
}
