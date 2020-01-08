#include <stdio.h>
#include "croupier.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

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

//checking each card in the hand
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


int main ()
{
    int count = 0;

    // number of decks into the Shoe
    int nods = 6;

    // creating croupier and player
    Croupier cr;
    Player  pl;

    // setting the Shoe
    cr.setDeck(nods);

    // 20 rounds
    for (int i = 0; i < 20; i++)
    {

        // setting the first hands of the round
        cr.setFirstCards(pl);

        //checking the cards for player
        checkCards(pl.pCards, true);

        //checking the cards for croupier
        checkCards(cr.cCards, false);

        // checking total number for croupier
        int cHand = cr.checkHand(cr.cCards);

        // checking total number for player
        int pHand = cr.checkHand(pl.pCards);

        printf(" sum of player hand: %d\n",pHand);
        printf(" sum of croupier hand: %d\n",cHand);

        printf(" player stand\n");

        cr.dealingTo17();

        //checking the winner of round
        cr.getWinner(pl);

        printf(" end of round %d\n\n", i);

        cr.clearHand();
        pl.clearHand();
     }

     return 0;
}
