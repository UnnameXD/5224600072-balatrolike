#include "PerkFactory.h"
#include <cstdlib>

Perk* PerkFactory::createStartingPerk()
{
    int roll = rand() % 2;

    if(roll == 0)
        return new Bonus21Damage();

    return nullptr;
}