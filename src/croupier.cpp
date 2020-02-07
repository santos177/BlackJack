#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <ctime>
#include "croupier.h"
#include "player.h"

//NOTE: we need to change getWinner, into checkWinnerHands (considering splits)
//who is the winner? 1: player wins, -1: croupier wins, 0: nobody
int Croupier::getWinner(Player &pl)
{
    int bet = 0;
    int plSum = Croupier::checkHand(pl.pCards).first;
    int crSum = Croupier::checkHand(cCards).first;

    printf("plSum: %d\n",plSum);
    printf("crSum: %d\n",crSum);

    (pl.dble) ? bet = minBet * 2 : bet = minBet;

    if (pl.blackjack)  bet = minBet * 3 ;


    if(crSum > 21 && 21 >= plSum)
    {
        pl.Money += bet;
        printf("player wins!\n");

        return 1;

    } else if (plSum > 21 && 21 >= crSum){
        pl.Money -= bet;
        printf("croupier wins! (player above 21)\n");
        return -1;

    } else if(21 >= plSum && 21 >= crSum){

        if (plSum > crSum)
        {
            pl.Money += bet;
            printf("player wins\n");

            return 1;

        } else if (crSum > plSum){
            pl.Money -= bet;
            printf("croupier wins (crSum > plSum) !\n");
            return -1;

        } else {
          printf("nobody wins...\n");
          return 0;
        }

    }

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

int Croupier::getHiddenCard()
{
    return cCards[1];
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
    {
        printf("player has Blackjack...\n");
        return true;

    } else
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
    else if(aceSum > 0)
        flag = 1;  // soft hand

    // adding the Aces
    int preTotal = sum + aceSum * 11;

    if (21 < preTotal)
       sum += aceSum;
    else
       sum = preTotal;

    return std::make_pair(sum,flag);

}

//croupier taking cards until 17
int Croupier::dealingTo17()
{
    //showing hidden card
    int hidden = getHiddenCard();
    std::string strHdn = printCard(hidden);
    std::cout << "croupier's hidden card:" << strHdn << "\n";

    // first check
    int sum = checkHand(cCards).first;

    while(sum < 17)
    {
        int crC = getCard();
        std::string strCard = printCard(crC);
        std::cout << "new card for croupier:" << strCard << "\n";
        cCards.push_back(crC);
        sum = checkHand(cCards).first;
        printf("sum for croupier: %d\n", sum);

    }

    return sum;

}

// converting numbers into card symbols
std::string Croupier::printCard(int c)
{
    if (c == 1) {
        return "A";

    } else if (2 <= c && c <= 10){
        std::string result = std::to_string(c);
        return result;

    } else if (c == 11){
        return "J";

    } else if (c == 12){
        return "Q";

    } else if (c == 13) {
        return "K";
    }
}

//checking each card in the hand and print it as J,Q,K,A etc
void Croupier::checkCards(std::vector<int> hand, bool flag)
{
    int count = 0;
    std::string quote;

    (flag) ?  quote = "card in player's hand: " : quote = "card in croupier's hand: ";

    for (std::vector<int>::iterator it = hand.begin(); it != hand.end();++it)
    {
        int card = *(it);
        std::string strCard = printCard(card);
        std::cout << quote << strCard << "\n";
    }

}
