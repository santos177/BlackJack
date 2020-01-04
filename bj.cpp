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

    // setting the first hands of the round
    cr.setFirstCards(pl);

    //checking the cards for player
    checkCards(pl.pCards, true);

    //checking the cards for croupier
    checkCards(cr.cCards, false);

    return 0;
}
