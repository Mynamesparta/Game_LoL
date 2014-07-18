#include "champion_selection.h"

ChampionSelection::ChampionSelection()
{
}

Champion* ChampionSelection::take(QString nameofChampion)
{
    return new Champion("Ryze");
}
