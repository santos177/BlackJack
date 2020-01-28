#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include "croupier.h"
#include "player.h"


/*
*  basic bj program
*
*/


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
          cr.checkCards(pl.pCards, true);

          //checking the cards for croupier
          // cr.checkCards(cr.cCards, false);

          // checking total number for croupier
          int cHand = cr.checkHand(cr.cCards).first;
          int softC = cr.checkHand(cr.cCards).second;

          // checking total number for player
          int pHand = cr.checkHand(pl.pCards).first;
          int softP = cr.checkHand(pl.pCards).second;

          int fcard = cr.getFirstCard();

          printf("sum of player hand: %d\n",pHand);
          // (softP) ? printf(" soft hand for player\n") : printf(" hard hand for player\n");

          std::string strCard = cr.printCard(fcard);
          std::cout << "croupier's first card: " << strCard << "\n";
          // (softC) ? printf(" soft hand for croupier\n") : printf(" hard hand for croupier\n");

          // pl.basicStrategy(pHand,softP,cr.getFirstCard());

          // manual playing
          bool validH = pl.mplay(cr);

          if(!validH) printf("  player passed 21 !!!!!\n");


          // croupier finishing
          if(validH) cr.dealingTo17();

          //checking the winner of round
          int result = cr.getWinner(pl);

          if (result == 1)
              win++;
          else if (result == -1)
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

    int nods = 6;
    int mbet = 5;
    int pmoney = 200;
    int rounds = 10;

    playBJ(nods, mbet, pmoney, rounds);

    return 0;

}
