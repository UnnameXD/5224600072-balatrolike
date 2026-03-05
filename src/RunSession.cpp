#include "RunSession.h"
#include "Card.h"
#include "PerkFactory.h"
#include "Shop.h"

#include <iostream>
#include <vector>
#include <cstdlib>

void RunSession::run()
{
    int playerHP = 63;
    int round = 1;
    int cash = 0;

    std::vector<Perk*> perks;

    Perk* startPerk = PerkFactory::createStartingPerk();

    if(startPerk!=nullptr)
    {
        perks.push_back(startPerk);
        std::cout<<"Starting Perk: "<<startPerk->getName()<<"\n";
    }
    else
    {
        std::cout<<"No starting perk\n";
    }

    while(playerHP>0)
    {
        int dealerHP = 12 + round*5;

        std::cout<<"\n====================\n";
        std::cout<<"ROUND "<<round<<"\n";
        std::cout<<"Dealer HP: "<<dealerHP<<"\n";

        while(playerHP>0 && dealerHP>0)
        {
            std::vector<Card> player;
            std::vector<Card> dealer;

            player.push_back(drawCard());
            player.push_back(drawCard());

            dealer.push_back(drawCard());
            dealer.push_back(drawCard());

            char choice='s';

            std::cout<<"\nPlayer HP: "<<playerHP
                     <<" | Dealer HP: "<<dealerHP<<"\n";

            int playerTotal=0;

            while(true)
            {
                std::cout<<"\nDealer Cards: ";
                showHand(dealer,true);

                std::cout<<"Your Cards: ";
                showHand(player,false);

                playerTotal = calculateTotal(player);

                std::cout<<"Total: "<<playerTotal<<"\n";

                if(playerTotal>21)
                {
                    std::cout<<"Bust!\n";
                    break;
                }

                std::cout<<"Hit(h) Stand(s): ";
                std::cin>>choice;

                if(choice=='h')
                    player.push_back(drawCard());
                else
                    break;
            }

            while(calculateTotal(dealer)<17)
                dealer.push_back(drawCard());

            std::cout<<"\n=== ROUND RESULT ===\n";

            std::cout<<"Dealer Cards: ";
            showHand(dealer,false);

            int dealerTotal = calculateTotal(dealer);

            std::cout<<"Dealer Total: "<<dealerTotal<<"\n";

            std::cout<<"Your Cards: ";
            showHand(player,false);

            playerTotal = calculateTotal(player);

            std::cout<<"Your Total: "<<playerTotal<<"\n";

            int damage = playerTotal;

            for(Perk* p : perks)
                damage = p->modifyDamage(damage);

            if(playerTotal<=21 && dealerTotal>21)
            {
                dealerHP -= damage;

                std::cout<<"Dealer Bust!\n";
                std::cout<<"Dealer takes "<<damage<<" damage\n";
            }

            else if(playerTotal>21)
            {
                playerHP -= dealerTotal;

                std::cout<<"You Bust!\n";
                std::cout<<"You take "<<dealerTotal<<" damage\n";
            }

            else if(playerTotal>dealerTotal)
            {
                dealerHP -= damage;

                std::cout<<"You Win Round!\n";
                std::cout<<"Dealer takes "<<damage<<" damage\n";
            }

            else if(playerTotal<dealerTotal)
            {
                playerHP -= dealerTotal;

                std::cout<<"Dealer Wins Round!\n";
                std::cout<<"You take "<<dealerTotal<<" damage\n";
            }

            else
            {
                std::cout<<"Draw\n";
            }
        }

        if(playerHP<=0)
            break;

        std::cout<<"\nRound "<<round<<" cleared!\n";

        playerHP += 21;

        std::cout<<"Heal 21 HP\n";
        std::cout<<"Current HP: "<<playerHP<<"\n";

        int reward = 10 + round*5;

        cash += reward;

        std::cout<<"Earned "<<reward<<" cash\n";
        std::cout<<"Total Cash: "<<cash<<"\n";

        Shop::openShop(cash, perks);

        round++;
    }

    std::cout<<"\n===== GAME OVER =====\n";

    for(Perk* p : perks)
        delete p;
}