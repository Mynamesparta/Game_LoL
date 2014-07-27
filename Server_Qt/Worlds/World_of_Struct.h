#ifndef WORLD_OF_STRUCT_H
#define WORLD_OF_STRUCT_H
#include "World_of_Const.h"

struct Point
{
    float x;
    float y;
};
namespace  Activity
{
    //============================Enum=============================
    enum State_of_activity
    {
        None_of_activity,
        Root,
        Stun,
        Damage
    };
    enum State_of_value
    {
        None_of_value,
        Time,
        Number_of_reflections,
        Renge,
        Press
    };
    enum State_of_dependent
    {
        None_of_dependent,
        After,
        At_one_time,
        Condition
    };
    enum Type
    {
        Line,
        Circle,
        Sector,
        Point,
        Object //circle+controlled
    };
    //=================================="Struct"=========================
    class Trajectory
    {
    public:
        Trajectory(Type type,int maxValue=0,int speed=0):type(type),maxValue(maxValue),
            speed(speed*World_of_const::TimeStep_World_move/50)
        {}
        const Type type;
        const unsigned int maxValue;
        const int speed;
        int value;
    };

    class Activity
    {
    public:
        Activity(char forSwitch,State_of_activity state_of_activity,State_of_value state_of_value,
                 State_of_dependent state_of_dependent,Type type,int maxValue,int speed=0):
            state_of_activity(state_of_activity),state_of_value(state_of_value),
            state_of_dependent(state_of_dependent),type(type),maxValue(maxValue),
            speed(speed),appointment(forSwitch)
        {}
        ~Activity()
        {
            if(validity!=NULL)
            {
                delete validity;
            }
            if(value!=NULL)
            {
                delete value;
            }
            if(condition!=NULL)
            {
                delete condition;
            }
            if(trajectory!=NULL)
            {
                delete trajectory;
            }
        }

        ::Point current_point;
        ::Point target;
        const unsigned int maxValue;
        const int speed;
        const char appointment;
        const State_of_activity state_of_activity;
        const State_of_value state_of_value;
        const State_of_dependent state_of_dependent;
        const Type type;
        int depth=-1;
        Trajectory* trajectory=NULL;
        Activity* dependent_activity=NULL;
        int* value=NULL;
        int* condition=NULL;
        int* validity=NULL;
    };


}

#endif // WORLD_OF_STRUCT_H
