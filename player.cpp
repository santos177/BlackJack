#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <ctime>
#include "player.h"


void Player::clearHand(){
    pCards.clear();
}

// inputs: amount of player; type: pair, soft or hard hand for player; croupier's first card
void Player::basicStrategy(int pHand, int type, int firstCard)
{
    bool Stand = false;

    while (!Stand)
    {
        if (type == 0)
        {
            // use hard hands strategy
        } else if (type == -1){
          // use pair hands strategy
        } else if (type == 1){
          // use soft hands strategy
        }
    }

}

bool Player::mplay(Croupier &cr)
{

    while(true)
    {
        std::string option;
        std::cout << "What do you want to do?: [S]Stand, [H]Hit, [D]Double, [P] Split, [R] Surrender \n";
        std::cin >> option;
        if (option == "S"){
          int total = cr.checkHand(pCards).first;
          printf("total now for player: %d\n", total);
          return true;

        } else if (option == "D" || option == "H"){
          
            int newCard = cr.getCard();
            pCards.push_back(newCard);
            std::string strCard = cr.printCard(newCard);
            std::cout << "new card for player:" << strCard << "\n";
            int total = cr.checkHand(pCards).first;
            printf("total now for player: %d\n", total);

            if (option == "D")
            {
                dble = true; //double bet
                return true;
            }

        } else if (option == "P") {
            // Split
            printf("Splitting...\n");
            return true;

        } else if (option == "R"){
            printf("Surrender...\n");
            return true;

        } else {
            printf("Please enter a valid option!\n");
        }

        if (cr.checkHand(pCards).first > 21) return false;

    };

}
