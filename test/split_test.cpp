#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include "croupier.h"
#include "player.h"

/*
* manual testing for split
*
*/

int main ()
{
    // seed for randomness
    srand(time(NULL));

    Croupier cr;
    Player pl;

    // setting the Shoe
    cr.setDeck(6);

    //minimal bet
    cr.minBet = 2;

    //setting player's Money
    pl.Money = 2000;

    //testing split
    pl.pCards.push_back(1);
    pl.pCards.push_back(1);

    //checking the cards for player
    cr.checkCards(pl.pCards, true);

    pl.mplay(cr);

    return 0;

}
