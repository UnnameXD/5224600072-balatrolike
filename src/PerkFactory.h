#ifndef PERKFACTORY_H
#define PERKFACTORY_H

#include "Perk.h"

class PerkFactory
{
public:

    static Perk* createStartingPerk();

    static Perk* createShopPerk(int choice);

};

#endif