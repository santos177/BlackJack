#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <ctime>
#include "player.h"


void Player::clearHand(){
    pCards.clear();
    sptHand.clear();
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
          std::string option = inputOption();

          if (option == "P")
          {

               printf("special case: SPLIT\n");
               if (cr.checkHand(pCards).second == -1)
               {
                   split = true;
                   int spCard = pCards[0];
                   clearHand();

                  for (int i = 0; i <= 1; ++i)
                  {
                      spthand auxHand;
                      auxHand.Cards.push_back(spCard);

                      printf("splitted hand number %d\n",i+1);


                      std::string strCard = cr.printCard(auxHand.Cards[0]);
                      std::cout << "first card of splitted hand:" << strCard << "\n";


                      while(true)
                      {
                          std::string option = inputOption();

                          // just for split , in the future we can generalize this
                          if(option == "D")
                              auxHand.dble = true;

                          if(primitiveOp(cr, auxHand.Cards, option))
                          {
                              int sum = cr.checkHand(auxHand.Cards).first;
                              sptHand.push_back(auxHand);
                              printf("sum of hand = %d\n",sum);
                              if (auxHand.dble)
                                  printf("hand doubled!\n");
                              break;
                          }


                      };

                  }

                  return true;

               } else
                   printf("player doesn't have a pair!\n");

          } else {
              if(primitiveOp(cr, pCards, option)) return true;
          }


      };
}

bool Player::primitiveOp(Croupier &cr, std::vector<int> &Hand, std::string option)
{

    if (option == "S"){
         int total = cr.checkHand(Hand).first;
         printf("total now for player: %d\n", total);
         return true;

    } else if (option == "D" || option == "H"){

        int newCard = cr.getCard();
        Hand.push_back(newCard);
        // std::string strCard = cr.printCard(newCard);
        printf("new card for player: %d\n", newCard);
        // std::cout << "new card for player:" << strCard << "\n";
        int total = cr.checkHand(Hand).first;
        printf("total now for player: %d\n", total);

        if (option == "D")
        {
            dble = true; //double bet
            return true;
        }

        if (cr.checkHand(Hand).first > 21) return true;

        return false;

    }  else if (option == "R"){
        printf("Surrender...\n");
        return true;

    } else {
        printf("Please enter a valid option!\n");
        return false;
    }



}

std::string Player::inputOption()
{
    std::string option;
    std::cout << "What do you want to do?: [S]Stand, [H]Hit, [D]Double, [P] Split, [R] Surrender\n" << std::endl;
    std::cin >> option;
    std::cin.clear();
    return option;
}
