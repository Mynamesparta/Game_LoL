#ifndef SCENARIO_H
#define SCENARIO_H
#include <QVector>
#include <QString>
#include <QRegExp>
#include <QDebug>
#include "Worlds/World_of_Struct.h"
struct Activity::Activity;
enum Activity::State_of_dependent;
class Scenario
{
public:
    Scenario(QString text);
private:
    QVector<Activity::Activity*> vector;
};


#endif // SCENARIO_H
