#ifndef CROUPIER_H
#define CROUPIER_H

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <ctime>
#include "player.h"

class Player;

class Croupier {
  public:

    // cards in full Shoe
    int cardTotal;

    // total cards in a given hand
    std::vector<int> cCards;

    // map for card left in Shoe
    std::map<int,int> frecMap;

    //minimal bet
    int minBet;

    //blackjack?
    int blackjack = false;

    int getWinner(Player &pl);

    void clearHand();

    int getFirstCard();

    int getHiddenCard();

    bool checkBlackJack(std::vector<int> firstHand);

    void setDeck(int n);

    int setFirstCards(Player &pl);

    int getCard();

    std::pair<int, int> checkHand(std::vector<int> hand);

    int dealingTo17();

    std::string printCard(int c);

    void checkCards(std::vector<int> hand, bool flag);

};

#endif // CROUPIER_H
