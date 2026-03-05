#include "RunSession.h"
#include "Card.h"
#include "ModifierFactory.h"

#include <iostream>
#include <vector>

void RunSession::run()
{
    int playerHP=63;
    int dealerHP=63;

    while(playerHP>0 && dealerHP>0)
    {
        std::vector<Card> player;
        std::vector<Card> dealer;

        player.push_back(drawCard());
        player.push_back(drawCard());

        dealer.push_back(drawCard());
        dealer.push_back(drawCard());

        char choice='s';

        std::cout<<"\n====================\n";
        std::cout<<"Player HP: "<<playerHP
                 <<" | Dealer HP: "<<dealerHP<<"\n";

        int playerTotal=0;

        while(true)
        {
            std::cout<<"\nDealer Cards: ";
            showHand(dealer,true);

            std::cout<<"Your Cards: ";
            showHand(player,false);

            playerTotal=calculateTotal(player);

            std::cout<<"Total: "<<playerTotal<<std::endl;

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
        {
            dealer.push_back(drawCard());
        }

        int dealerTotal=calculateTotal(dealer);

        Modifier* mod = ModifierFactory::createModifier(rand()%3);

        int damage = playerTotal;

        if(mod!=nullptr)
            damage = mod->apply(damage);

        if(playerTotal>dealerTotal)
        {
            dealerHP-=damage;

            std::cout<<"Dealer takes "
                     <<damage
                     <<" damage\n";
        }
        else
        {
            playerHP-=dealerTotal;

            std::cout<<"You take "
                     <<dealerTotal
                     <<" damage\n";
        }

        delete mod;
    }

    std::cout<<"\n===== GAME OVER =====\n";

    if(playerHP<=0)
        std::cout<<"You Lose\n";
    else
        std::cout<<"You Win\n";
}