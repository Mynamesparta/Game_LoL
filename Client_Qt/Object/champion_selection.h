#ifndef CHAMPION_SELECTION_H
#define CHAMPION_SELECTION_H
#include "champion.h"
class Champion;

//---------Champion-class------------------------------------------
//------------------------------------------------------------
class ChampionSelection
{
public:
    ChampionSelection();
    static Champion* take(QString nameofChampion);
};

#endif // CHAMPION_SELECTION_H
