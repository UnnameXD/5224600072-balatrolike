#include "RunSession.h"
#include "Card.h"
#include "PerkFactory.h"
#include "Perk.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void RunSession::run()
{
    srand(time(0));

    int playerHP = 63;
    int round = 1;

    std::vector<Perk*> perks;

    // Starting perk
    Perk* startPerk = PerkFactory::createStartingPerk();

    if(startPerk != nullptr)
    {
        perks.push_back(startPerk);
        std::cout<<"Starting Perk: +21% Damage\n";
    }
    else
    {
        std::cout<<"No starting perk.\n";
    }

    while(playerHP > 0)
    {
        int dealerHP = 12 + (round * 5);

        std::cout << "\n====================\n";
        std::cout << "ROUND " << round << "\n";
        std::cout << "Dealer HP: " << dealerHP << "\n";

        while(playerHP > 0 && dealerHP > 0)
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

            int dealerTotal = calculateTotal(dealer);

            std::cout<<"\nDealer Final Cards: ";
            showHand(dealer,false);

            std::cout<<"Dealer Total: "<<dealerTotal<<"\n";

            int damage = playerTotal;

            // Apply perks
            for(size_t i=0;i<perks.size();i++)
            {
                damage = perks[i]->apply(damage);
            }

            if(playerTotal <=21 && dealerTotal >21)
            {
                std::cout<<"Dealer Bust!\n";
                dealerHP -= damage;
                std::cout<<"You deal "<<damage<<" damage!\n";
            }
            else if(playerTotal >21)
            {
                std::cout<<"You Bust!\n";
                playerHP -= dealerTotal;
                std::cout<<"Dealer deals "<<dealerTotal<<" damage!\n";
            }
            else if(playerTotal > dealerTotal)
            {
                dealerHP -= damage;
                std::cout<<"You win hand!\n";
                std::cout<<"Damage: "<<damage<<"\n";
            }
            else if(playerTotal < dealerTotal)
            {
                playerHP -= dealerTotal;
                std::cout<<"Dealer wins hand!\n";
                std::cout<<"Damage taken: "<<dealerTotal<<"\n";
            }
            else
            {
                std::cout<<"Draw\n";
            }

            std::cout<<"Player HP: "<<playerHP<<"\n";
            std::cout<<"Dealer HP: "<<dealerHP<<"\n";
        }

        if(playerHP <= 0)
            break;

        std::cout<<"\nRound "<<round<<" cleared!\n";

        playerHP += 21;
        std::cout<<"You heal 21 HP!\n";
        std::cout<<"Current HP: "<<playerHP<<"\n";

        round++;
    }

    std::cout<<"\n===== GAME OVER =====\n";

    for(size_t i=0;i<perks.size();i++)
        delete perks[i];
}