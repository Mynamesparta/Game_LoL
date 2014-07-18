#include "champion_selection.h"

ChampionSelection::ChampionSelection()
{
}

Champion* ChampionSelection::take(QString nameofChampion)
{
    if(nameofChampion=="Ryze")
    {
        Ryze* ryze=new Ryze();
        return(Champion*) ryze;
    }
}
