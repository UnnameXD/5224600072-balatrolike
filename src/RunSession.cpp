#include "RunSession.h"
#include "Card.h"
#include "ModifierFactory.h"

#include <iostream>
#include <vector>
#include <cstdlib>

void RunSession::run()
{
    int playerHP = 63;
    int round = 1;

    while(playerHP > 0)
    {
        int dealerHP = 7 + (round * 14);

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

            char choice = 's';
            int playerTotal = 0;

            std::cout << "\nPlayer HP: " << playerHP
                      << " | Dealer HP: " << dealerHP << "\n";

            // ===== PLAYER TURN =====
            while(true)
            {
                std::cout << "\nDealer Cards: ";
                showHand(dealer,true);

                std::cout << "Your Cards: ";
                showHand(player,false);

                playerTotal = calculateTotal(player);

                std::cout << "Total: " << playerTotal << "\n";

                if(playerTotal > 21)
                {
                    std::cout << "Bust!\n";
                    break;
                }

                std::cout << "Hit(h) Stand(s): ";
                std::cin >> choice;

                if(choice == 'h')
                    player.push_back(drawCard());
                else
                    break;
            }

            // ===== DEALER TURN =====
            while(calculateTotal(dealer) < 17)
                dealer.push_back(drawCard());

            std::cout << "\n=== ROUND RESULT ===\n";

            std::cout << "Dealer Cards: ";
            showHand(dealer,false);

            int dealerTotal = calculateTotal(dealer);

            std::cout << "Dealer Total: " << dealerTotal << "\n";

            std::cout << "\nYour Cards: ";
            showHand(player,false);

            playerTotal = calculateTotal(player);

            std::cout << "Your Total: " << playerTotal << "\n";

            // ===== MODIFIER SYSTEM =====
            Modifier* mod = ModifierFactory::createModifier(rand()%3);

            int damage = playerTotal;

            if(mod != nullptr)
                damage = mod->apply(damage);

            // ===== DAMAGE SYSTEM =====
            if(playerTotal <= 21 && dealerTotal > 21)
            {
                dealerHP -= damage;

                std::cout << "\nDealer Bust!\n";
                std::cout << "Dealer takes " << damage << " damage\n";
            }
            else if(playerTotal > 21)
            {
                playerHP -= dealerTotal;

                std::cout << "\nYou Bust!\n";
                std::cout << "You take " << dealerTotal << " damage\n";
            }
            else if(playerTotal > dealerTotal)
            {
                dealerHP -= damage;

                std::cout << "\nYou Win Round!\n";
                std::cout << "Dealer takes " << damage << " damage\n";
            }
            else if(playerTotal < dealerTotal)
            {
                playerHP -= dealerTotal;

                std::cout << "\nDealer Wins Round!\n";
                std::cout << "You take " << dealerTotal << " damage\n";
            }
            else
            {
                std::cout << "\nDraw!\n";
            }

            std::cout << "\nCurrent HP -> Player: "
                      << playerHP
                      << " | Dealer: "
                      << dealerHP
                      << "\n";

            delete mod;
        }

        if(playerHP <= 0)
            break;

        std::cout << "\nRound " << round << " cleared!\n";

        // ===== HEAL SYSTEM =====
        playerHP += 21;

        std::cout << "You heal 21 HP!\n";
        std::cout << "Player HP is now: " << playerHP << "\n";

        round++;
    }

    std::cout << "\n===== GAME OVER =====\n";

    if(playerHP <= 0)
        std::cout << "You Lose!\n";
    else
        std::cout << "You Survived All Rounds!\n";
}