#include "champion.h"

Champion::Champion(QString NameOfChampion):NameOfChampion(NameOfChampion),
    qreAnimation("((?:stand)|(?:start_move)|(?:move)|(?:end_move)|(?:autoattacks)): ([a-zA-Z0-9_ .]+)")
{
    QString Adress="Resources/models/"+NameOfChampion+"/";
    QFile file(Adress+"animation.txt");
    if(!file.exists())
    {
        qDebug()<<"We lost fill "+NameOfChampion+"/animation.txt :(";
                  return;
    }
    file.open(QIODevice::ReadOnly);
    //######
    QString str;
    QStringList qsl;
    QVector<QPixmap> vector;
    QPixmap pix;
    while(!file.atEnd())
    {
        str=file.readLine();
        str.contains(qreAnimation);
        str=qreAnimation.cap(2);
        qsl=str.split(" ");
        while(qsl.length()>0)
        {
            str=qsl.takeFirst();
            if(str!="")
            {
                pix.load(Adress+qreAnimation.cap(1)+"/"+str);
                if(!pix.isNull())
                {
                    vector<<pix;
                    qDebug()<<Adress+qreAnimation.cap(1)+"/"+str+" loaded.";
                }
                else
                {
                    qDebug()<<Adress+qreAnimation.cap(1)+"/"+str+" can't found.";
                }
            }
        }
        if(qreAnimation.cap(1)=="stand")
        {
            qvAnimation_Stand<<vector;
            vector.clear();
            qviAnimation_Stand=qvAnimation_Stand.begin();
            //qDebug()<<qviAnimation_Stand->isNull();
            continue;
        }
        if(qreAnimation.cap(1)=="start_move")
        {
            qvAnimation_Start_move<<vector;
            vector.clear();
            qviAnimation_Start_move=qvAnimation_Start_move.begin();
            //qDebug()<<qviAnimation_Start_move->isNull();
            continue;
        }
        if(qreAnimation.cap(1)=="move")
        {
            qvAnimation_Move<<vector;
            vector.clear();
            qviAnimation_Move=qvAnimation_Move.begin();
            //qDebug()<<qviAnimation_Move->isNull();
            continue;
        }
        if(qreAnimation.cap(1)=="end_move")
        {
            qvAnimation_End_move<<vector;
            vector.clear();
            qviAnimation_End_move=qvAnimation_End_move.begin();
            //qDebug()<<qviAnimation_End_move->isNull();
            continue;
        }
        if(qreAnimation.cap(1)=="autoattacks")
        {
            qvAnimation_Autoattacks<<vector;
            vector.clear();
            qviAnimation_Autoattacks=qvAnimation_Autoattacks.begin();
            //qDebug()<<qviAnimation_Autoattacks->isNull();
            continue;
        }
    }
    current_pixmap=qviAnimation_Stand;
    //######
    file.close();
    stateofAnimation=World_of_const::Stand;
}
QRectF Champion::boundingRect() const
{
    QPointF ptPosition(-current_pixmap->height(),
                       -current_pixmap->width());
    QSizeF size(current_pixmap->height()*2,2*current_pixmap->width());
    return QRectF(ptPosition,size);
}
void Champion::paint(QPainter* ppainter,const QStyleOptionGraphicsItem*,QWidget*)
{
    ppainter->save();
    ppainter->rotate(angle);
    ppainter->drawPixmap(-current_pixmap->height()/2,
                         -current_pixmap->width()/2,
                         current_pixmap->height(),
                         current_pixmap->width(),
                         *current_pixmap);
    ppainter->restore();
}
//===========================Animation=================
void Champion::move(float x,float y)
{
    this->setPos(x,y);
    dx=x-current_X;
    dy=y-current_Y;
    l=sqrt(dx*dx+dy*dy);//                      180/пі
    angle=(dy>0?1:-1)*(acos(dx/l) - (this->rotation()) )*57.29577951;//
    current_X=x;
    current_Y=y;
    if(isTimeToChangeMoveAnimation)
    {
        switch(stateofAnimation)
        {
        case World_of_const::Stand:
        {
            stateofAnimation=World_of_const::Start_move;
            qviAnimation_Start_move=qvAnimation_Start_move.begin();
            current_pixmap=qviAnimation_Start_move;
            qviAnimation_Start_move++;
            break;
        }
        case World_of_const::Start_move:
        {
            if(qviAnimation_Start_move==qvAnimation_Start_move.end())
            {
                stateofAnimation=World_of_const::Move;
                qviAnimation_Move=qvAnimation_Move.begin();
                qviAnimation_End_move=qvAnimation_End_move.begin();
                current_pixmap=qviAnimation_Move;
            }
            else
            {
                current_pixmap=qviAnimation_Start_move;
                qviAnimation_Start_move++;
            }
            break;
        }
        case World_of_const::Move:
        {
            qviAnimation_Move++;
            qviAnimation_End_move++;
            if(qviAnimation_Move==qvAnimation_Move.end())
            {
                qviAnimation_Move=qvAnimation_Move.begin();
                qviAnimation_End_move=qvAnimation_End_move.begin();
            }
            current_pixmap=qviAnimation_Move;
            break;
        }
        }
        isTimeToChangeMoveAnimation=0;
        qTimerforAnimation.start();
        while(qTimerforAnimation.elapsed()<World_of_const::TimeStep_Animation)
        {
            QApplication::processEvents();
        }
        isTimeToChangeMoveAnimation=1;
    }
}

void Champion::end_move(float x,float y)
{
    this->setPos(x,y);dx=x-current_X;
    dy=y-current_Y;
    l=sqrt(dx*dx+dy*dy);//                      180/пі
    angle=(dy>0?1:-1)*(acos(dx/l) - (this->rotation()) )*57.29577951;//
    current_X=x;
    current_Y=y;
    switch(stateofAnimation)
    {
        case World_of_const::Move:
        {
            stateofAnimation=World_of_const::End_move;
            if(qviAnimation_End_move==qvAnimation_End_move.end())
            {
                qviAnimation_End_move=qvAnimation_End_move.begin();
            }
            current_pixmap=qviAnimation_End_move;

            qTimerforAnimation.start();
            while(qTimerforAnimation.elapsed()<World_of_const::TimeStep_Animation)
            {
                QApplication::processEvents();
            }
            stateofAnimation=World_of_const::Stand;
            qviAnimation_Stand=qvAnimation_Stand.begin();
            current_pixmap=qvAnimation_Stand.begin();
            this->setPos(x+1,y);
            this->setPos(x,y);
            break;
        }
        case World_of_const::Start_move:
        {
            stateofAnimation=World_of_const::End_move;
            qviAnimation_End_move=qvAnimation_End_move.begin();
            qviAnimation_End_move++;
            current_pixmap=qviAnimation_End_move;
            qTimerforAnimation.start();
            while(qTimerforAnimation.elapsed()<World_of_const::TimeStep_Animation)
            {
                QApplication::processEvents();
            }
            stateofAnimation=World_of_const::Stand;
            qviAnimation_Stand=qvAnimation_Stand.begin();
            current_pixmap=qvAnimation_Stand.begin();
            this->setPos(x+1,y);
            this->setPos(x,y);
            break;
        }
    }
}
//=====================virtual=function=======================

void Champion::First_skill()
{
    qDebug()<<"champion.cpp: class Champion \"First_skill\"";
}

void Champion::Second_skill()
{
    qDebug()<<"champion.cpp: class Champion \"Second_skill\"";
}

void Champion::Third_skill()
{
    qDebug()<<"champion.cpp: class Champion \"Third_skill\"";
}

void Champion::Fourth_skill()
{
    qDebug()<<"champion.cpp: class Champion \"Fourth_skill\"";
}
