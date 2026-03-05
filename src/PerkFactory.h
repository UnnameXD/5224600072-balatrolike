#ifndef PERKFACTORY_H
#define PERKFACTORY_H

#include "Perk.h"

class PerkFactory
{
public:
    static Perk* createStartingPerk();
};

#endif