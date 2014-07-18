#ifndef INGAME_H
#define INGAME_H

#include <QWidget>
#include <QDebug>
#include "server.h"
#include <QThread>
#include <QRegExp>
#include <QFile>
#include "Object/wall.h"
#include "World_of_Const.h"
struct Point
{
    float x;
    float y;
};
class QTcpSocket;
//enum StateInGame{Alive,Win,Lose,Surrender};
class Infotmation;
class QSendToClientEvent;
class Map;
//class SendToClient;

class InGame : public QThread
{
    Q_OBJECT
private:
    void sendToClient(const QString& str,int Index=-1);
    void ReadyRead(int UserIndex, QString);

    Map* map;
    QRegExp qre;
    int maxIndexofUser;
    int Round = 0;
    int l;
    int dx;
    int dy;
    const unsigned int IndexOfGame;
    QObject* server;
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
    QTcpSocket* TakeSocket(int);

    Infotmation* UserInfo[World_of_const::N];

public slots:
private slots:
    bool ThisWorldMove();
signals:
    void sigEndGame(int);
};
//======================================
class Infotmation:public QObject
{
public:
    Infotmation(QTcpSocket* Socket,QString UserName,int Index):qtcpSocket(Socket),UserName(UserName),IndexOfClient(Index)
    {
        current_position.x=current_position.y=
                move_position.x=move_position.y=0;
    }
    QTcpSocket* qtcpSocket;
    const QString UserName;
    const int IndexOfClient;
    Point current_position;
    Point move_position;
    bool IsBlocked=0;
    bool IsLogOut;
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
