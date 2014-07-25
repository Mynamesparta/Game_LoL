#include "skills.h"

Skills::Skills()
{

}

Skills& Skills::operator <<(Scenario* scenario)
{
    playlet<<scenario;
    return *this;
}
