#include "scenario.h"

Scenario::Scenario(QString text,QString id):id(id)
{
    QRegExp qre("([act]) +([a-zA-Z_]+) +([a-zA-Z_]+)? *(?:([0-9]+) )(?:([0-9]+) )?(?:([0-9]+) )? *(,||;||(?:->)||(?:- ->)||(?:->\\|))?(?: ?([0-9]+))?");
    // (activity||condition||trajectory) State  [int]{1,3} ( , || ; || -> || - -> ||  ->|)
    int pos = 0;
    Activity::Activity* head[10];
    Activity::Activity* tail[10];
    int length[10];
    int Index=-1;
    bool isNewBranch=1;
    Activity::State_of_dependent state_of_dependent=Activity::None_of_dependent;
    Activity::State_of_activity state_of_activity;
    Activity::State_of_value state_of_value;

    Activity::Activity* activity;
    Activity::Trajectory* trajectory=NULL;
    char forSwitch;
    while ((pos = qre.indexIn(text, pos)) != -1)
    {
        qDebug()<<"scenario.cpp:cap="<<qre.cap();
        qDebug()<<"scenario.cpp:cap(1)="+qre.cap(1)<<"cap(2)="+qre.cap(2)<<"cap(3)="+qre.cap(3)<<"cap(4)="
               +qre.cap(4)<<"cap(5)="+qre.cap(5)<<"cap(6)="+qre.cap(6)<<"cap(7)="+qre.cap(7)<<"cap(8)="+qre.cap(8);
        if(qre.cap(1)=="a")
        {
            forSwitch='a';
        }
        else
        {
            if(qre.cap(1)=="c")
            {
                forSwitch='c';
            }
            else
            {
                if(qre.cap(1)=="t")
                {
                    forSwitch='t';
                }
                else
                {
                    forSwitch=' ';
                    qDebug()<<"scenario.cpp:ERROR! qre.cap(1)=?  [something strange]. ";
                    QApplication::exit();
                }
            }
        }
        switch(forSwitch)
        {
        case 'a':   //+++++++++++++++++++++state+of+activity+++++++++++++
        {
            state_of_activity=toState_of_activity(qre.cap(3));
            state_of_value=Activity::None_of_value;
            break;
        }
        case 'c':  //+++++++++++++++++++++state+of+value+++++++++++++
        {
            state_of_value=toState_of_value(qre.cap(3));
            state_of_activity=Activity::None_of_activity;
            break;
        }
        case 't':   //++++++++++++++++++++set+trajectory+++++++++++++++++++++++
        {

            trajectory=new Activity::Trajectory(toType(qre.cap(2)),qre.cap(4).toInt(),qre.cap(6).toInt());
            trajectory->value=qre.cap(5).toInt();
            break;
        }
        }
        if(forSwitch!='t')
        {
            //+++++++++++++++++++++state+of+dependent+++++++++++++
            switch(state_of_dependent)
            {
            case Activity::None_of_dependent:
            {
                if(qre.cap(7)==",")
                {
                    state_of_dependent=Activity::At_one_time;
                }
                else
                {
                    if(qre.cap(7)=="->")
                    {
                        state_of_dependent=Activity::After;
                    }
                    else
                    {
                        if(qre.cap(7)=="- ->")
                        {
                            state_of_dependent=Activity::Condition;
                        }
                        else
                        {
                            if(qre.cap(7)=="->|")
                            {
                                state_of_dependent=Activity::None_of_dependent;
                            }
                        }
                    }
                }
                if(Index==-1)
                {
                    activity->dependent_activity=new Activity::Activity(forSwitch,state_of_activity,state_of_value,
                                                                        state_of_dependent,toType(qre.cap(2)),qre.cap(4).toInt(),qre.cap(6).toInt());
                    activity=activity->dependent_activity;
                    if(activity->appointment=='c')
                    {
                        activity->trajectory=trajectory;
                    }
                    activity->value=new int(qre.cap(5).toInt());
                    //qDebug()<<activity;
                    vector<<activity;
                }
                else
                {
                    length[Index]++;
                    head[Index]->dependent_activity=new Activity::Activity(forSwitch,state_of_activity,state_of_value,
                                                                           state_of_dependent,toType(qre.cap(2)),qre.cap(4).toInt(),qre.cap(6).toInt());
                    head[Index]=head[Index]->dependent_activity;
                    if(head[Index]->appointment=='c')
                    {
                        head[Index]->trajectory=trajectory;
                    }
                    head[Index]->value=new int(qre.cap(5).toInt());
                    //qDebug()<<head[Index];
                    head[Index]->depth=Index;
                }
                break;
            }
            case Activity::Condition:
            {
                Index++;
                if(qre.cap(7)==",")
                {
                    state_of_dependent=Activity::At_one_time;
                }
                else
                {
                    if(qre.cap(7)=="->")
                    {
                        state_of_dependent=Activity::After;
                    }
                    else
                    {
                        if(qre.cap(7)==";")
                        {
                            state_of_dependent=Activity::None_of_dependent;
                        }
                        else
                        {
                            if(qre.cap(7)=="- ->")
                            {
                                state_of_dependent=Activity::Condition;
                            }
                            else
                            {
                                if(qre.cap(7)=="->|")
                                {
                                    state_of_dependent=Activity::None_of_dependent;
                                }
                            }
                        }
                    }
                }
                if(isNewBranch)
                {
                    length[Index]=1;
                    head[Index]=tail[Index]=new Activity::Activity(forSwitch,state_of_activity,state_of_value,
                                                                   state_of_dependent,toType(qre.cap(2)),qre.cap(4).toInt(),qre.cap(6).toInt());
                    if(head[Index]->appointment=='c')
                    {
                        head[Index]->trajectory=trajectory;
                    }
                    head[Index]->value=new int(qre.cap(5).toInt());
                    //qDebug()<<head[Index];
                    head[Index]->depth=Index;
                }
                else
                {
                    isNewBranch=1;
                    length[Index]++;
                    head[Index]->dependent_activity=new Activity::Activity(forSwitch,state_of_activity,state_of_value,
                                                                           state_of_dependent,toType(qre.cap(2)),qre.cap(4).toInt(),qre.cap(6).toInt());
                    head[Index]=head[Index]->dependent_activity;
                    //qDebug()<<head[Index];
                    if(head[Index]->appointment=='c')
                    {
                        head[Index]->trajectory=trajectory;
                    }
                    head[Index]->value=new int(qre.cap(5).toInt());
                    head[Index]->depth=Index;
                }
                if(Index>0)
                {
                    head[Index-1]->condition=new int(length[Index]);
                }
                else
                {
                    activity->condition=new int(length[Index]);
                }
                break;
            }
            default:
            {
                if(qre.cap(7)==",")
                {
                    state_of_dependent=Activity::At_one_time;
                }
                else
                {
                    if(qre.cap(7)=="->")
                    {
                        state_of_dependent=Activity::After;
                    }
                    else
                    {
                        if(qre.cap(7)==";")
                        {
                            state_of_dependent=Activity::None_of_dependent;
                        }
                        else
                        {
                            if(qre.cap(7)=="- ->")
                            {
                                state_of_dependent=Activity::Condition;
                            }
                            else
                            {
                                if(qre.cap(7)=="->|")
                                {
                                    state_of_dependent=Activity::None_of_dependent;
                                }
                            }
                        }
                    }
                }
                if(Index==-1)
                {
                    activity->dependent_activity=new Activity::Activity(forSwitch,state_of_activity,state_of_value,
                                                                        state_of_dependent,toType(qre.cap(2)),qre.cap(4).toInt(),qre.cap(6).toInt());
                    activity=activity->dependent_activity;
                    //qDebug()<<activity;
                    if(activity->appointment=='c')
                    {
                        activity->trajectory=trajectory;
                    }
                    activity->value=new int(qre.cap(5).toInt());
                }
                else
                {
                    length[Index]++;
                    head[Index]->dependent_activity=new Activity::Activity(forSwitch,state_of_activity,state_of_value,
                                                                           state_of_dependent,toType(qre.cap(2)),qre.cap(4).toInt(),qre.cap(6).toInt());
                    head[Index]=head[Index]->dependent_activity;
                    //qDebug()<<head[Index];
                    if(head[Index]->appointment=='c')
                    {
                        head[Index]->trajectory=trajectory;
                    }
                    head[Index]->value=new int(qre.cap(5).toInt());
                    head[Index]->depth=Index;
                }
                break;

            }
            }
            if(qre.cap(7)=="->|")
            {
                if(Index<0)
                {
                    qDebug()<<"scenario.cpp:ERROR! ->|  found earlier than - -> . ";
                    QApplication::exit();
                }
                if((qre.cap(8)=="")||(qre.cap(8).toInt()==1))
                {
                    if(isNewBranch)
                    {
                        isNewBranch=0;
                    }
                    else
                    {
                        head[Index]->dependent_activity=tail[Index+1];
                        head[Index]=head[Index+1];
                    }
                    Index--;
                }
                else
                {
                    for(int i=qre.cap(8).toInt();i;i--)
                    {
                        if(isNewBranch)
                        {
                            isNewBranch=0;
                        }
                        else
                        {
                            head[Index]->dependent_activity=tail[Index+1];
                            head[Index]=head[Index+1];

                        }
                        Index--;
                    }
                }
            }
            if(Index!=-1)
            {
                if(qre.cap(7)==";")
                {
                    for(int i=Index;i>-1;i--)
                    {
                        if(isNewBranch)
                        {
                            isNewBranch=0;
                        }
                        else
                        {
                            head[Index]->dependent_activity=tail[Index+1];
                            head[Index]=head[Index+1];
                        }
                        Index--;
                    }
                    activity->dependent_activity=tail[0];
                    //qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<Index;
                }
            }
        }
        pos += qre.matchedLength();
    }//return;
    activity=vector.first();
    while(activity!=NULL)
    {
        qDebug()<<"==============================================================";
        qDebug()<<"scenario.cpp:state_of_activity="<<activity->state_of_activity;
        qDebug()<<"scenario.cpp:state_of_dependent="<<activity->state_of_dependent;
        qDebug()<<"scenario.cpp:state_of_value="<<activity->state_of_value;
        qDebug()<<"scenario.cpp:maxValue="<<activity->maxValue;
        if(activity->value!=NULL)
        qDebug()<<"scenario.cpp:value="<<*activity->value;
        qDebug()<<"scenario.cpp:speed="<<activity->speed;
        qDebug()<<"scenario.cpp:depth="<<activity->depth;
        if(activity->condition!=NULL)
        qDebug()<<"scenario.cpp:condition="<<*activity->condition;
        qDebug()<<"==============================================================";
        activity=activity->dependent_activity;
    }
}

void Scenario::ChangeMap(Map* map)
{
    current_map=map;
}

QString Scenario::nextStep()
{
    return "";
    iterator=vector.begin();
    for(;iterator<vector.end();iterator++)
    {
        current_activity=*iterator;
        while(0)
        {

        }
    }
}
//==========================Convert======================================
Activity::Type Scenario::toType(QString type)
{
    if(type=="Line")
    {
        return Activity::Line;
    };
    if(type=="Circle")
    {
        return Activity::Circle;
    };
    if(type=="Sector")
    {
        return Activity::Sector;
    };
    if(type=="Point")
    {
        return Activity::Point;
    };
    if(type=="Object")
    {
        return Activity::Object;
    };
}

Activity::State_of_activity Scenario::toState_of_activity(QString state)
{
    if(state=="None")
    {
        return Activity::None_of_activity;
    }
    if(state=="Root")
    {
        return Activity::Root;
    }
    if(state=="Stun")
    {
        return Activity::Stun;
    }
}

Activity::State_of_value Scenario::toState_of_value(QString state)
{
    if(state=="Time")
    {
        return Activity::Time;
    }
    if(state=="Reflections")
    {
        return Activity::Number_of_reflections;
    }
    if(state=="Renge")
    {
        return Activity::Renge;
    }
}
