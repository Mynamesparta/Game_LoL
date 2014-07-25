#include "ingame.h"
#include "QApplication"

//=================Begin=Or=End=?========================================
InGame::InGame(QObject *server,int Index):server(server),/*Text(""),*/maxIndexofUser(-1),IndexOfGame(Index)
  ,QThread(0),
    qre("((?:move)||(?:skill_1)||(?:skill_2)||(?:skill_3)||(?:skill_4)):(\\-{0,1}[0-9]+) (\\-{0,1}[0-9]+)")
{

    for(int i=0;i<=World_of_const::N-1;i++)
    {
        summoner[i]=NULL;
    }
    map=new Map();
}
InGame::~InGame()
{
    for(int i=0;i<=maxIndexofUser;i++)
    {
        if(summoner[i]!=NULL)
        {
            delete summoner[i];
        }
    }
}



void InGame::run()
{
    QString Text="";
    Text+="Start Game:";
    for(int i=0;i<=maxIndexofUser;i++)
    {
        Text+=summoner[i]->UserName+" ";
    }
    sendToClient(Text);
    sendToClient("0 move:3000 5000");
    Point point;
    point.x=3000.0;
    point.y=5000.0;
    summoner[0]->current_position=summoner[0]->move_position=point;
    unsigned int lastTime=World_of_const::TimeStep_World_move+1;
    timer.start();
    while(ThisWorldMove())
    {
        QApplication::processEvents();
        if(lastTime!=timer.elapsed())
        {
            qDebug()<<"####################################################";
            qDebug()<<"ingame.cpp:timer.elapsed()="<<timer.elapsed();
            qDebug()<<"####################################################";
        }
        lastTime=timer.elapsed();
        msleep(World_of_const::TimeStep_World_move-timer.elapsed());
        timer.restart();
    };
    sigEndGame(IndexOfGame);
}
void InGame::addUser(QTcpSocket* Socket,QString UserName,int Index,int Team)
{
    Champion* champion=ChampionSelection::take("Ryze");
    summoner[++maxIndexofUser]=new Summoner(Socket,UserName,Index,champion);
    map->summoner[maxIndexofUser]=summoner[maxIndexofUser];
    if(!Team)
    {
        if(maxIndexofUser%2==0)
        {
            qDebug()<<"Black Team!";
        }
        else
        {
            qDebug()<<"White Team!";
        }
    }
    else
    {
        if(Team==1)
        {
            qDebug()<<"Black Team!";
        }
        else
        {
            qDebug()<<"White Team!";
        }
    }
}
void InGame::addBot(int numberOfBotWhiteTeam,int numberOfBotBlackTeam)
{
    qDebug()<<"Number of bot for White Team:"<<numberOfBotWhiteTeam
          <<". Number of bot for Black Team:"<<numberOfBotBlackTeam<<".";
    for (int i=0; i<numberOfBotWhiteTeam; i++)
    {

    }
    for (int i=0; i<numberOfBotBlackTeam; i++)
    {

    }
}

//=================Helping=Functions============================
int InGame::takeMaxIndex()
{
    return maxIndexofUser;
}
int InGame::takeIndexOfClient(int Index)
{
    return summoner[Index]->IndexOfClient;
}

QTcpSocket const *  InGame::TakeSocket(int Index)
{
    return summoner[Index]->takeSocket();
}



//====================Move=this=world========================================
bool InGame::ThisWorldMove()//QTimerEvent* event,TimerEvent,MoveThisWorld ((^.^)>)>)>)>>
{
    //+++++++++++++++++++++++++Summoners+movement+++++++++++++++++++++
    for(int i=0;i<=maxIndexofUser;i++)
    {
        if(!summoner[i]->IsLogOut)
        {
            dx=summoner[i]->move_position.x-summoner[i]->current_position.x;
            dy=summoner[i]->move_position.y-summoner[i]->current_position.y;
            //qDebug()<<"ingame.cpp: after-current_position.x=("<<UserInfo[i]->current_position.x<<") current_position.y=("<<UserInfo[i]->current_position.y<<")";
            l=sqrt(dx*dx+dy*dy);
            if(l)
            {
                if(l<=World_of_const::L)
                {
                    summoner[i]->current_position=summoner[i]->move_position;
                    if(map->isWall(summoner[i]->current_position,20))
                    {
                        summoner[i]->move_position=summoner[i]->current_position;
                    }
                    sendToClient(QString::number(i)+" end_move:"+QString::number(summoner[i]->current_position.x)+
                                 " "+QString::number(summoner[i]->current_position.y));
                }
                else
                {
                    summoner[i]->current_position.x+=World_of_const::L*dx/l;
                    summoner[i]->current_position.y+=World_of_const::L*dy/l;
                    if(map->isWall(summoner[i]->current_position,World_of_const::radius_of_champion))
                    {
                        if(map->length(summoner[i]->last_position,summoner[i]->current_position)<2)
                        {
                            sendToClient(QString::number(i)+" end_move:"+QString::number(summoner[i]->current_position.x)+
                                         " "+QString::number(summoner[i]->current_position.y));
                            summoner[i]->last_position=summoner[i]->current_position;
                            summoner[i]->move_position=summoner[i]->current_position;
                            continue;
                        }
                    }
                    sendToClient(QString::number(i)+" move:"+QString::number(summoner[i]->current_position.x)+
                                 " "+QString::number(summoner[i]->current_position.y));
                }
                summoner[i]->last_position=summoner[i]->current_position;
            }
        }
    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    return 1;
}


//================Send=or=Read============================================
void InGame::sendToClient(const QString& str,int Index)
{
    if(Index==-1)
    {
        for(int i=0;i<=maxIndexofUser;i++)
        {
            if(!summoner[i]->IsLogOut)
            {
                QSendToClientEvent* pe=new QSendToClientEvent(summoner[i]->IndexOfClient);
                pe->Text=str;
                pe->forSwitch=0;
                QApplication::postEvent(server,pe);
            }
        }
    }
    else
    {
        if(!summoner[Index]->IsLogOut)
        {
            QSendToClientEvent* pe=new QSendToClientEvent(summoner[Index]->IndexOfClient);
            pe->Text=str;
            pe->forSwitch=0;
            QApplication::postEvent(server,pe);
        }
    }

}

void InGame::ReadyRead(int UserIndex, QString str)
{
    qDebug()<<"ingame:User["<<summoner[UserIndex]->UserName<<"] send to Server:"<<str;
    if(str=="SUR")
    {
        summoner[UserIndex]->IsLogOut=1;
        return;
    }

    if(str.contains(qre))
    {
        if(qre.cap(1)=="move")
        {
            summoner[UserIndex]->move_position.x=qre.cap(2).toInt();
            summoner[UserIndex]->move_position.y=qre.cap(3).toInt();
            return;
        }
        if(qre.cap(1)=="skill_1")
        {
            sendToClient(QString::number(UserIndex)+" skill_1:0 0");
            return;
        }
        if(qre.cap(1)=="skill_2")
        {
            sendToClient(QString::number(UserIndex)+" skill_2:0 0");
            return;
        }
        if(qre.cap(1)=="skill_3")
        {
            sendToClient(QString::number(UserIndex)+" skill_3:0 0");
            return;
        }
        if(qre.cap(1)=="skill_4")
        {
            sendToClient(QString::number(UserIndex)+" skill_4:0 0");
            return;
        }

    }
}
void InGame::customEvent(QEvent* pe)
{
    if((int)(pe)->type()==QSendToClientEvent::sendtoclienttype)
    {
        QSendToClientEvent* qstce=(QSendToClientEvent*)pe;
        ReadyRead(qstce->Index,qstce->Text);
    }
    else qDebug()<<"Error!";
}
