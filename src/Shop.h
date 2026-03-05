#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include "Perk.h"

class Shop
{
public:
    static void openShop(int& cash, std::vector<Perk*>& perks);
};

#endif