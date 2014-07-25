#ifndef SKILLS_H
#define SKILLS_H
#include <QVector>
#include "scenario.h"

class Scenario;
class Skills
{
public:
    Skills();
    Skills& operator <<(Scenario*);

private:
    QVector<Scenario*> playlet;
    QVector<Scenario*>::iterator iter_playlet;
};

#endif // SKILLS_H
