#include "skills.h"

Skills::Skills(Map *map):map(map)
{

}

Skills& Skills::operator <<(Scenario* scenario)
{
    playlet<<scenario;
    scenario->ChangeMap(map);
    return *this;
}
