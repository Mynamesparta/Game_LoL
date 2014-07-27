#ifndef SCENARIO_H
#define SCENARIO_H
#include <QVector>
#include <QString>
#include <QRegExp>
#include <QDebug>
#include "Worlds/World_of_Struct.h"
#include "wall.h"
struct Activity::Activity;
class Map;
enum Activity::State_of_dependent;
class Scenario
{
public:
    Scenario(QString text,QString id);
    void ChangeMap(Map* map);
    QString nextStep();
private:
    Activity::Type toType(QString);
    Activity::State_of_activity toState_of_activity(QString);
    Activity::State_of_value toState_of_value(QString);
    QString id;
    QVector<Activity::Activity*> vector;
    QVector<Activity::Activity*>::iterator iterator;
    Activity::Activity* current_activity;
    Map* current_map=NULL;
};


#endif // SCENARIO_H
