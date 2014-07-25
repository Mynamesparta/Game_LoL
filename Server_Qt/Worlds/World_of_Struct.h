#ifndef WORLD_OF_STRUCT_H
#define WORLD_OF_STRUCT_H


struct Point
{
    float x;
    float y;
};
namespace  Activity
{
    enum State_of_activity
    {
        None_of_activity,
        Root,
        Stun
    };
    enum State_of_value
    {
        None_of_value,
        End_Scenario,
        Time,
        Number_of_reflections,
        Renge
    };
    enum State_of_dependent
    {
        None_of_dependent,
        After,
        At_one_time
    };

    class Activity
    {
    public:
        Activity(State_of_activity state_of_activity,State_of_value state_of_value,State_of_dependent state_of_dependent,int maxValue):
            state_of_activity(state_of_activity),state_of_value(state_of_value),state_of_dependent(state_of_dependent),maxValue(maxValue)
        {}
        const State_of_activity state_of_activity;
        const State_of_value state_of_value;
        const State_of_dependent state_of_dependent;
        const unsigned int maxValue;
        int value;
        int validity;
        Activity* dependent_activity=NULL;
    };


}

#endif // WORLD_OF_STRUCT_H
