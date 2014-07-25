#include "scenario.h"

Scenario::Scenario(QString text)
{
    QRegExp qre("([a-zA-Z_]+) ?([0-9]*) ?([a-zA-Z_]+) ?([0-9]+) ([0-9]+) ?(,||;||(?:->))");
    // State_of_activity [int] State_of_value [int] [int] ( , || ; || -> )
    int pos = 0;
    int validity;

    Activity::State_of_dependent state_of_dependent=Activity::None_of_dependent;
    Activity::State_of_activity state_of_activity;
    Activity::State_of_value state_of_value;

    Activity::Activity* activity;
    while ((pos = qre.indexIn(text, pos)) != -1)
    {
        qDebug()<<"scenario.cpp:cap="<<qre.cap();
        if(qre.cap(2)!="")
        {
            validity=qre.cap(2).toInt();
        }
        else validity=0;
        //+++++++++++++++++++++state+of+activity+++++++++++++
        if(qre.cap(1)=="None")
        {
            state_of_activity=Activity::None_of_activity;
            goto end1;
        }
        if(qre.cap(1)=="Root")
        {
            state_of_activity=Activity::Root;
            goto end1;
        }
        if(qre.cap(1)=="Stun")
        {
            state_of_activity=Activity::Stun;
            goto end1;
        }
        end1:;
        //+++++++++++++++++++++state+of+value+++++++++++++
        if(qre.cap(3)=="Time")
        {
            state_of_value=Activity::Time;
            goto end2;
        }
        if(qre.cap(3)=="Reflections")
        {
            state_of_value=Activity::Number_of_reflections;
            goto end2;
        }
        if(qre.cap(3)=="Renge")
        {
            state_of_value=Activity::Renge;
            goto end2;
        }
        end2:;
        //+++++++++++++++++++++state+of+dependent+++++++++++++
        switch(state_of_dependent)
        {
        case Activity::None_of_dependent:
        {
            if(qre.cap(6)==",")
            {
                state_of_dependent=Activity::At_one_time;
            }
            else
            {
                if(qre.cap(6)=="->")
                {
                    state_of_dependent=Activity::After;
                }
            }
            activity=new Activity::Activity(state_of_activity,state_of_value,
                                            state_of_dependent,qre.cap(4).toInt());
            activity->value=qre.cap(5).toInt();
            activity->validity=validity;
            vector<<activity;
            break;
        }
        default:
        {
            if(qre.cap(6)==",")
            {
                state_of_dependent=Activity::At_one_time;
            }
            else
            {
                if(qre.cap(6)=="->")
                {
                    state_of_dependent=Activity::After;
                }
                else
                {
                    if(qre.cap(6)==";")
                    {
                        state_of_dependent=Activity::None_of_dependent;
                    }
                }
            }
            activity->dependent_activity=new Activity::Activity(state_of_activity,state_of_value,
                                            state_of_dependent,qre.cap(4).toInt());
            activity=activity->dependent_activity;
            activity->value=qre.cap(5).toInt();
            activity->validity=validity;
            break;
        }
        }
        qDebug()<<"scenario.cpp:state_of_activity="<<activity->state_of_activity;
        qDebug()<<"scenario.cpp:state_of_dependent="<<activity->state_of_dependent;
        qDebug()<<"scenario.cpp:state_of_value="<<activity->state_of_value;
        qDebug()<<"scenario.cpp:maxValue="<<activity->maxValue;
        qDebug()<<"scenario.cpp:value="<<activity->value;
        qDebug()<<"scenario.cpp:validity="<<activity->validity;
        qDebug()<<"scenario.cpp:activity="<<activity;
        qDebug()<<"scenario.cpp:dependent_activity="<<activity->dependent_activity;
        pos += qre.matchedLength();
    }
}
