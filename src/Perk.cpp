#include "Perk.h"

int Bonus21Damage::apply(int damage)
{
    return damage + (damage * 21 / 100);
}