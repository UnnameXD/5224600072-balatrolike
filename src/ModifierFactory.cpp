#include "ModifierFactory.h"

Modifier* ModifierFactory::createModifier(int choice)
{
    if(choice==1)
        return new DoubleDamage();

    if(choice==2)
        return new BonusDamage();

    return nullptr;
}