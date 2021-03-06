#ifndef INGAME_H
#define INGAME_H

#include <QWidget>
#include <QDebug>
#include <QThread>
#include <QRegExp>
#include <QFile>
#include <QTime>
#include "server.h"
#include "Object/wall.h"
#include "Worlds/World_of_Const.h"
#include "Worlds/World_of_Struct.h"
#include "Object/summoner.h"
#include "Object/champion_selection.h"
#include "Object/skills.h"

struct Point;

class QTcpSocket;
class QSendToClientEvent;
class Map;
class Summoner;
class ChampionSelection;
class Skills;

class InGame : public QThread
{
    Q_OBJECT
private:
    void sendToClient(const QString& str,int Index=-1);
    void ReadyRead(int UserIndex, QString);

    QRegExp qre;
    int maxIndexofUser;
    int Round = 0;
    int l;
    int dx;
    int dy;
    const unsigned int IndexOfGame;
    Skills* skills;
    QTime timer;
    QObject* server;
    Map* map;
    bool Timeout = 0;

public:
    InGame(QObject*,int Index);
    ~InGame();
    void run();
    void addUser(QTcpSocket* , QString , int , int Team=0);
    void addBot(int , int );
    void customEvent(QEvent* pe);
    int takeMaxIndex();
    int takeIndexOfClient(int);
    //StateInGame takeState(int Index);
    const QTcpSocket *TakeSocket(int);

    Summoner* summoner[World_of_const::N];

public slots:
private slots:
    bool ThisWorldMove();
signals:
    void sigEndGame(int);
};
//===========QSendToClientEvent============================
class QSendToClientEvent:public QEvent
{
public:
    enum {sendtoclienttype=User+1};
    QString Text;
    int Index;
    int forSwitch=-1;
    QSendToClientEvent(int Index):QEvent((Type)sendtoclienttype),
                       Index(Index)
    {}
};


//======================================

#endif // SERVER_H
