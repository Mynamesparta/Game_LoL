#ifndef CHAMPION_SELECTION_H
#define CHAMPION_SELECTION_H
#include "champion.h"
class Champion;

//---------Champion-class------------------------------------------
class Ryze;
//------------------------------------------------------------
class ChampionSelection
{
public:
    ChampionSelection();
    static Champion* take(QString nameofChampion);
};

//--------------------------------------------------------------------
class Ryze:public Champion
{
public:
    Ryze();
    virtual void First_skill();
    virtual void Second_skill();
    virtual void Third_skill();
    virtual void Fourth_skill();

};

#endif // CHAMPION_SELECTION_H
