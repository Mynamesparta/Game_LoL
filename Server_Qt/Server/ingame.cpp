#include "ingame.h"
#include "QApplication"

//=================Begin=Or=End=?========================================
InGame::InGame(QObject *server,int Index):server(server),/*Text(""),*/maxIndexofUser(-1),IndexOfGame(Index)
  ,QThread(0),
    qre("((?:move)||(?:skill_1)||(?:skill_2)||(?:skill_3)||(?:skill_4)):(\\-{0,1}[0-9]+) (\\-{0,1}[0-9]+)")
{

    for(int i=0;i<=World_of_const::N-1;i++)
    {
        UserInfo[i]=NULL;
    }
    map=new Map();
}
InGame::~InGame()
{
    for(int i=0;i<=maxIndexofUser;i++)
    {
        if(UserInfo[i]!=NULL)
        {
            delete UserInfo[i];
        }
    }
}



void InGame::run()
{
    QString Text="";
    Text+="Start Game:";
    for(int i=0;i<=maxIndexofUser;i++)
    {
        Text+=UserInfo[i]->UserName+" ";
    }
    sendToClient(Text);
    sendToClient("0 move:3000 5000");
    Point point;
    point.x=3000.0;
    point.y=5000.0;
    UserInfo[0]->current_position=UserInfo[0]->move_position=point;
    while(ThisWorldMove())
    {
        msleep(2*World_of_const::TimeStep_World_move-World_of_const::TimeStep_World_move);
        QApplication::processEvents();
    };
    sigEndGame(IndexOfGame);
}
void InGame::addUser(QTcpSocket* Socket,QString UserName,int Index,int Team)
{
    UserInfo[++maxIndexofUser]=new Infotmation(Socket,UserName,Index);
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
    return UserInfo[Index]->IndexOfClient;
}

QTcpSocket* InGame::TakeSocket(int Index)
{
    return UserInfo[Index]->qtcpSocket;
}



//====================Move=this=world========================================
bool InGame::ThisWorldMove()//QTimerEvent* event,TimerEvent,MoveThisWorld ((^.^)>)>)>)>>
{
    for(int i=0;i<=maxIndexofUser;i++)
    {
        if(!UserInfo[i]->IsLogOut)
        {
            dx=UserInfo[i]->move_position.x-UserInfo[i]->current_position.x;
            dy=UserInfo[i]->move_position.y-UserInfo[i]->current_position.y;
            l=sqrt(dx*dx+dy*dy);
            if(l!=0)
            {
                if(l<=World_of_const::L)
                {
                    UserInfo[i]->current_position=UserInfo[i]->move_position;
                    sendToClient(QString::number(i)+" end_move:"+QString::number(UserInfo[i]->current_position.x)+
                                 " "+QString::number(UserInfo[i]->current_position.y));
                }
                else
                {
                    UserInfo[i]->current_position.x+=World_of_const::L*dx/l;
                    UserInfo[i]->current_position.y+=World_of_const::L*dy/l;
                    map->isWall(UserInfo[i]->current_position,20);
                    sendToClient(QString::number(i)+" move:"+QString::number(UserInfo[i]->current_position.x)+
                                 " "+QString::number(UserInfo[i]->current_position.y));
                }
            }
        }
    }
    return 1;
}


//================Send=or=Read============================================
void InGame::sendToClient(const QString& str,int Index)
{
    if(Index==-1)
    {
        for(int i=0;i<=maxIndexofUser;i++)
        {
            if(!UserInfo[i]->IsLogOut)
            {
                //qDebug()<<Round-1;
                QSendToClientEvent* pe=new QSendToClientEvent(UserInfo[i]->IndexOfClient);
                pe->Text=str;
                pe->forSwitch=0;
                QApplication::postEvent(server,pe);
            }
        }
    }
    else
    {
        if(!UserInfo[Index]->IsLogOut)
        {
            QSendToClientEvent* pe=new QSendToClientEvent(UserInfo[Index]->IndexOfClient);
            pe->Text=str;
            pe->forSwitch=0;
            QApplication::postEvent(server,pe);
        }
    }

}

void InGame::ReadyRead(int UserIndex, QString str)
{
    qDebug()<<"ingame:User["<<UserInfo[UserIndex]->UserName<<"] send to Server:"<<str;

    if(str=="SUR")
    {
        UserInfo[UserIndex]->IsLogOut=1;
        return;
    }

    if(str.contains(qre))
    {
        if(qre.cap(1)=="move")
        {
            UserInfo[UserIndex]->move_position.x=qre.cap(2).toInt();
            UserInfo[UserIndex]->move_position.y=qre.cap(3).toInt();
            return;
        }
        if(qre.cap(1)=="skill_1")
        {
            qDebug()<<"ingame.cpp:skill_1";
            return;
        }
        if(qre.cap(1)=="skill_2")
        {
            qDebug()<<"ingame.cpp:skill_2";
            return;
        }
        if(qre.cap(1)=="skill_3")
        {
            qDebug()<<"ingame.cpp:skill_3";
            return;
        }
        if(qre.cap(1)=="skill_4")
        {
            qDebug()<<"ingame.cpp:skill_4";
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
