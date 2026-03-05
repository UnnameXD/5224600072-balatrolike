#include "Shop.h"
#include "PerkFactory.h"

#include <iostream>
#include <vector>
#include <cstdlib>

void Shop::openShop(int& cash, std::vector<Perk*>& perks)
{
    int option1 = rand()%3 + 1;
    int option2 = rand()%3 + 1;

    int price1 = 0;
    int price2 = 0;

    if(option1==1) price1=30;
    if(option1==2) price1=25;
    if(option1==3) price1=40;

    if(option2==1) price2=30;
    if(option2==2) price2=25;
    if(option2==3) price2=40;

    std::cout<<"\n===== SHOP =====\n";
    std::cout<<"Cash: "<<cash<<"\n\n";

    Perk* preview1 = PerkFactory::createShopPerk(option1);
    Perk* preview2 = PerkFactory::createShopPerk(option2);

    std::cout<<"1. "<<preview1->getName()<<" ("<<price1<<")\n";
    std::cout<<"2. "<<preview2->getName()<<" ("<<price2<<")\n";
    std::cout<<"0. Skip\n";

    int choice;
    std::cin>>choice;

    if(choice==1 && cash>=price1)
    {
        perks.push_back(preview1);
        cash-=price1;

        std::cout<<"Bought "<<preview1->getName()<<"\n";

        delete preview2;
    }

    else if(choice==2 && cash>=price2)
    {
        perks.push_back(preview2);
        cash-=price2;

        std::cout<<"Bought "<<preview2->getName()<<"\n";

        delete preview1;
    }

    else
    {
        std::cout<<"Skip shop\n";

        delete preview1;
        delete preview2;
    }
}