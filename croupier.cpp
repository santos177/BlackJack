#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <ctime>
#include "croupier.h"
#include "player.h"

// //who is the winner? 1: player wins, -1: croupier wins, 0: nobody
int Croupier::getWinner(Player &pl)
{
    int plSum = Croupier::checkHand(pl.pCards).first;
    int crSum = Croupier::checkHand(cCards).first;

    printf("plSum: %d\n",plSum);
    printf("crSum: %d\n",crSum);

    if (crSum > 21 || ((plSum > crSum) && (21 >= plSum)))
    {
        if(pl.blackjack){
            pl.Money += 3;
        } else
            pl.Money += 2;

        printf("player wins!\n");
        return 1;

    } else if (plSum > 21 || ((crSum > plSum) && (21 >= crSum))){
        pl.Money -= 2;
        printf("croupier wins!\n");
        return -1;
    } else
        printf("nobody wins...\n");
        return 0;
}

// clear the hand
void Croupier::clearHand(){
    cCards.clear();
}

// get first card of croupier
int Croupier::getFirstCard()
{
    return cCards.front();
}

// do we have Blackjack?
bool Croupier::checkBlackJack(std::vector<int> firstHand)
{

    bool ace = false;
    bool ten = false;

    for(std::vector<int>::iterator it = firstHand.begin(); it!=firstHand.end();++it)
    {
        int card = *(it);

        if (card == 1)
            ace = true;
        else if (10 <= card && card <= 13)
            ten = true;

    }

    if (ace && ten)
        return true;
    else
        return false;

}


// setting number of decks
void Croupier::setDeck (int n)
{
    for (int i = 1; i <= 13;i++)
        frecMap.insert(std::pair<int, int>(i,4 * n));
    cardTotal = 52 * n;
}

// setting first cards for Croupier and Player
// (return 1 : blackjack for player, -1: blackjack for croupier, 0: none)
// (return -2 : empty Shoe!)
int Croupier::setFirstCards (Player &pl)
{

  for (int j = 0; j <= 1; j++)
  {
      // one card for player
      pl.pCards.push_back(getCard());

      // another for croupier (NOTE: the last is the hidden card!)
      int crC = getCard();
      // printf("card for croupier: %d\n",crC);
      cCards.push_back(crC);
  }

  bool plBj = checkBlackJack(pl.pCards);
  bool crBj = checkBlackJack(cCards);

  if (plBj && !crBj)
  {
      pl.blackjack = true;
      return 1;
  } else if (!plBj && crBj){
      blackjack = true;
      return -1;
  } else
     return 0;
}

// getting a card from Shoe
int Croupier::getCard()
{
    int num = 0;
    while (0 < cardTotal)
    {

        // A(1),2,3,4,5,6,7,8,9,10,J(11),Q(12),K(13)
        num = rand() % 13 + 1;

        // checking if the card is inside the shoe
        std::map<int,int>::iterator it = frecMap.find(num);
        int left = it->second;

        // discounting the card from Shoe
        if (0 < left)
        {
            it->second -= 1;
            cardTotal -= 1;
            return num;
        }

    }

    return num;
}

//checking the sum of points in the hand
std::pair<int, int> Croupier::checkHand (std::vector<int> hand)
{
    int count = 0;
    int sum = 0;
    int aceSum = 0;
    int flag = 0;  // -1 : pair, 0 : hard hand, 1: soft hand

    for (std::vector<int>::iterator it = hand.begin(); it != hand.end();++it)
    {
        int card = *(it);

        if (2 <= card && card <= 10)
            sum += card;
        else if (11 <= card && card <= 13){
            sum += 10;
        } else {
            aceSum++;
        }

        count++;

    }

    if (count == 2 && (hand[0] == hand[1]))
        flag = -1; //pairs
    else if(aceSum != 0)
        flag = 1;  // soft hand

    // adding the Aces sum
    if(aceSum == 1)
        sum += 11;
    else if (aceSum > 1)
        sum += 10 + aceSum;

    return std::make_pair(sum,flag);

}

//croupier taking cards until 17
int Croupier::dealingTo17()
{
    // first check
    int sum = checkHand(cCards).first;

    while(sum < 17)
    {
        int crC = getCard();
        // std::string strCard = printCard(crC);
        // std::cout << "new card for croupier:" << strCard << "\n";
        cCards.push_back(crC);
        sum = checkHand(cCards).first;
        printf("sum for croupier: %d\n", sum);

    }

    return sum;

}
