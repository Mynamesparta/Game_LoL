#include "gamefield.h"
#include "QApplication"

GameField::GameField(QObject *client, bool isSingleGame):
    client(client),isSingleGame(isSingleGame),
    view(&scene),qre("([0-9]+) ((?:move)|(?:end_move)|(?:skill_1)|(?:skill_2)|(?:skill_3)|(?:skill_4)):(\\-{0,1}[0-9]+\\.?[0-9]*) (\\-{0,1}[0-9]+\\.?[0-9]*)"),
    qreForFile("_([0-9]+),([0-9]+)_ ([0-9 ]+)")
{
    if(isWallViseble)
    {
        QFile file("Resources/Wall.txt");
        file.open(QIODevice::ReadOnly);
        if(!file.exists())
        {
            qDebug()<<"We lost fill Wall.txt :(";
            goto b;
        }
        QString str;
        QPoint point;
        bool b=0;
        while(!file.atEnd())
        {
            str=file.readLine();
            QPoint point2;
            QPoint point_b;
            if(str.contains(qreForFile))
            {
                scene.addEllipse(qreForFile.cap(1).toInt(),qreForFile.cap(2).toInt(),3,3,QPen(Qt::red,3));
                QStringList stlist=qreForFile.cap(3).split(" ");
                b=0;qDebug()<<stlist.length();
                while(stlist.length()>0)
                {
                    str=stlist.takeFirst();
                    if(b)
                    {
                        point.setY(str.toInt());
                        if(!point2.isNull())
                        {
                            scene.addLine(QLine(point,point2),QPen(Qt::red,1));
                            //qDebug()<<point<<point2;
                            point2=point;
                        }
                        else
                        {
                            point2=point;
                            point_b=point;
                        }
                        b=0;

                    }
                    else
                    {
                        b=1;
                        point.setX(str.toInt());
                    }
                }
                scene.addLine(QLine(point_b,point2),QPen(Qt::red,1));

            }
        }
        file.close();
    };
    b:;
}
GameField::~GameField()
{

}
void GameField::run()
{
    while (ThisWorldMove())
    {
        QApplication::processEvents();
        msleep(2*World_of_const::TimeStep_World_move-World_of_const::TimeStep_World_move);
    }


    sig_EndGame();//конец игри
}
void GameField::slotPause(bool b)
{
    pause=b;
}
bool GameField::ThisWorldMove()
{    
    //--------------------Mouse-----------------------
    switch(view.qpointMousePosition(mouse_position))
    {
        case Move:
        {
            if(isMove)
            {
                SendToServer("move:"+QString::number(mouse_position.x())
                             +" "+QString::number(mouse_position.y()));
            }
            break;
        }
        case Release:
        {
            isMove=0;
            break;
        }
        case PressLeft:
        {
            break;
        }
        case PressRight:
        {
            SendToServer("move:"+QString::number(mouse_position.x())
                         +" "+QString::number(mouse_position.y()));
            isMove=1;
            break;
        }
        case None:
        {
            break;
        }
    }
    //----------------------Key-----------------------------
    str=view.takeKey();
    if(str!="")
    {
        SendToServer(str+":0 0");
    }
    return 1;
}

void GameField::EndGame()
{
    Timeout=1;
}

void GameField::AddUser(QString str)
{    
    Champion* champion=ChampionSelection::take("Ryze");
    scene.addItem((QGraphicsItem*)champion);
    summoner[++maxIndex]=new Summoner(str,champion);
}
void GameField::addBot(int numberOfBotBlackTeam,int numberOfBotWhiteTeam)
{
    qDebug()<<"Number of bot for White Team:"<<numberOfBotWhiteTeam
           <<". Number of bot for Black Team:"<<numberOfBotBlackTeam<<".";        
    /*if (){
        for (int i=0; i<numberOfBotWhiteTeam; i++)
        {
            qDebug()<<"White Team!";
        }
        for (int i=0; i<numberOfBotBlackTeam; i++)
        {
            qDebug()<<"Black Team!";
        }
    }*/
}
void GameField::customEvent(QEvent* pe)
{
    if((int)(pe)->type()==QSendToClientEvent::sendtoclienttype)
    {
        QSendToClientEvent* qstce=(QSendToClientEvent*)pe;
        switch(qstce->forSwitch)
        {
            case 0:
            {
                ReadyRead(qstce->Text);

                break;
            }

        }
    }
    else qDebug()<<"Error!";
}
//==================Read=or=Send============
void GameField::ReadyRead(QString text)
{
    qDebug()<<text;
    if(text.contains(qre))
    {
        if(qre.cap(2)=="move")
        {
            summoner[qre.cap(1).toInt()]->
                    move(qre.cap(3).toFloat(),qre.cap(4).toFloat());
            return;
        }
        if(qre.cap(2)=="end_move")
        {
            summoner[qre.cap(1).toInt()]->
                    end_move(qre.cap(3).toFloat(),qre.cap(4).toFloat());
            return;
        }
        if(qre.cap(2)=="skill_1")
        {
            summoner[qre.cap(1).toInt()]->First_skill();
            return;
        }
        if(qre.cap(2)=="skill_2")
        {
            summoner[qre.cap(1).toInt()]->Second_skill();
            return;
        }
        if(qre.cap(2)=="skill_3")
        {
            summoner[qre.cap(1).toInt()]->Third_skill();
            return;
        }
        if(qre.cap(2)=="skill_4")
        {
            summoner[qre.cap(1).toInt()]->Fourth_skill();
            return;
        }
    }
}
void GameField::SendToServer(QString text)
{
    if(1)
    {
        QSendToClientEvent* pe=new QSendToClientEvent();
        pe->Text=text;
        pe->forSwitch=0;
        QApplication::postEvent(client,pe);
    }
}
