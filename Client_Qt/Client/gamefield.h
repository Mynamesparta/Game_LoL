#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QDebug>
#include <QThread>
#include <QEvent>
#include <QGraphicsScene>
#include <QRegExp>
#include <QFile>

#include "view.h"
#include "Object/summoner.h"
#include "Worlds/World_of_Const.h"
#include "Object/champion_selection.h"

class View;
class QSendToClientEvent;
class Summoner;
class ChampionSelection;

enum MOUSE;

class GameField : public QThread
{
    Q_OBJECT
private:
    void ReadyRead(QString);
    void SendToServer(QString text);                    
    void EndGame();

    bool ThisWorldMove();

    Summoner* summoner[10];
    QGraphicsScene scene;
    View view;
    QPoint mouse_position;
    QRegExp qre;
    QRegExp qreForFile;
    QString str;
    int maxIndex=-1;
    QObject* client;
    bool Timeout=0;
    bool pause=0;
    bool isSingleGame;
    bool isWallViseble=1;
    bool isMove=0;
public:
    GameField(QObject *client, bool isSingleGame);
    ~GameField();

    void run();
    void customEvent(QEvent* pe);
    void AddUser(QString);
    void addBot(int numberOfBotBlackTeam,int numberOfBotWhiteTeam);
public slots:
    void slotPause(bool);
signals:
    void sig_EndGame();
};

//----------------------------------------------------------------------
class QSendToClientEvent:public QEvent
{
public:
    enum {sendtoclienttype=User+1};
    QString Text;
    int forSwitch=-1;
    QSendToClientEvent():QEvent((Type)sendtoclienttype)
    {}
};

#endif // GAMEFIELD_H
