#include "Object/summoner.h"

Summoner::Summoner(QString NameOfPLayer,Champion* champion):
    NameOfPLayer(NameOfPLayer),champion(champion)
{

}

void Summoner::move(float x,float y)
{
    champion->move(x,y);
}

void Summoner::end_move(float x,float y)
{
    champion->end_move(x,y);
}

void Summoner::First_skill()
{
    champion->First_skill();
}

void Summoner::Second_skill()
{
    champion->Second_skill();
}

void Summoner::Third_skill()
{
    champion->Third_skill();
}

void Summoner::Fourth_skill()
{
    champion->Fourth_skill();
}
