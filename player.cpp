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

bool Player::mplay(int pHand, int type, int firstCard, Croupier &cr)
{

    while(true)
    {
        std::string option;
        std::cout << "What do you want to do?: [S]Stand, [H]Hit, [D]Double, [P] Split, [R] Surrender \n";
        std::cin >> option;
        if (option == "S")
          return true;
        else if (option == "D")
        {
            pCards.push_back(cr.getCard());
            return true;

        } else if (option == "H"){
            pCards.push_back(cr.getCard());
        } else if (option == "P") {
            // Split
            return true;
        } else if (option == "R"){
            printf("Surrender...\n");
            return true;
        } else {
            printf("Please enter a valid option!\n");
            return false;
        }

        int total = cr.checkHand(pCards).first;
        if (total > 21) return true;

    };

}
