#ifndef SKILLS_H
#define SKILLS_H
#include <QVector>
#include "scenario.h"
#include "wall.h"
class Scenario;
class Map;
class Skills
{
public:
    Skills(Map * map);
    Skills& operator <<(Scenario*);

private:
    QVector<Scenario*> playlet;
    QVector<Scenario*>::iterator iter_playlet;
    Map* map;
};

#endif // SKILLS_H
