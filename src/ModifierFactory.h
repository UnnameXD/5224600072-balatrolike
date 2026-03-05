#ifndef MODIFIER_FACTORY_H
#define MODIFIER_FACTORY_H

#include "Modifier.h"

class ModifierFactory
{
public:

    static Modifier* createModifier(int choice);
};

#endif