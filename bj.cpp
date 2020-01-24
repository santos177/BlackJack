#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include "croupier.h"
#include "player.h"

//g++ bj.cpp croupier.cpp player.cpp -o blackjack

/*
*  basic bj program
*
*/

// converting numbers into card symbols
std::string printCard(int c)
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
void checkCards(std::vector<int> hand, bool flag)
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


// playing a session
// nods: numbers of decks, minimal bet, rounds
void playBJ(int nods, int mbet, int pmoney, int rounds)
{

      int count = 0;
      int win = 0;
      int loss = 0;

      // creating croupier and player
      Croupier cr;
      Player  pl;

      // setting the Shoe
      cr.setDeck(nods);

      //minimal bet
      cr.minBet = mbet;

      //setting player's Money
      pl.Money = pmoney;

      // 300 rounds
      for (int i = 0; i < rounds; i++)
      {

          // player needs money and we need cards in the Shoe
          if (pl.Money <= cr.minBet || cr.cardTotal <= 10)
              break;

          // setting the first hands of the round (blackjacks?)
          cr.setFirstCards(pl);

          //checking the cards for player
          checkCards(pl.pCards, true);

          //checking the cards for croupier
          checkCards(cr.cCards, false);

          // checking total number for croupier
          int cHand = cr.checkHand(cr.cCards).first;
          int softC = cr.checkHand(cr.cCards).second;

          // checking total number for player
          int pHand = cr.checkHand(pl.pCards).first;
          int softP = cr.checkHand(pl.pCards).second;

          printf(" sum of player hand: %d\n",pHand);
          (softP) ? printf(" soft hand for player\n") : printf(" hard hand for player\n");

          printf(" sum of croupier hand: %d\n",cHand);
          (softC) ? printf(" soft hand for croupier\n") : printf(" hard hand for croupier\n");

          // pl.basicStrategy(pHand,softP,cr.getFirstCard());

          cr.dealingTo17();

          //checking the winner of round
          if (cr.getWinner(pl) == 1)
              win++;
          else if (cr.getWinner(pl) == -1)
              loss++;

          printf(" Money of player: %d\n\n",pl.Money);
          printf(" card total: %d\n\n",cr.cardTotal);
          printf(" end of round %d\n\n", i);

          printf("---------------------------------------------------------\n");


          cr.clearHand();
          pl.clearHand();
          count++;

       }

       printf(" Final balance of player: %d\n\n", pl.Money);
       printf(" Total of hands: %d\n\n", count);
       printf(" Total winnings: %d\n\n", win);
       printf(" Total losses: %d\n\n", loss);

}

int main ()
{
    // seed for randomness
    srand(time(NULL));


     return 0;

}
