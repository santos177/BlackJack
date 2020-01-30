#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <ctime>
#include "croupier.h"

class Croupier;

class Player {
  public:

    //bankroll
    int Money;

    // x,x where x is 2,3,4,5,6,7,8,9,A,J,Q,K
    std::map<std::pair<int,int>, std::vector<int>> pairStrategy;

    // X where x is : 5,6,7,8,9,10 ..
    std::map<int, std::vector<int>> hardStrategy;

    //A,x where x is 2,3,4,5,6,7,8,9
    std::map<int, std::vector<int>> softStrategy;

    std::vector<int> pCards;

    // for split results : key: number of hand, pair(sum, flag)
    // flag = true when the hand is double down
    std::map<int,std::pair<int,bool>> splitRes;

    int Sum;

    //blackjack?
    int blackjack = false;

    //double bet?
    bool dble = false;

    void clearHand();

    void basicStrategy(int pHand, int type, int firstCard);

    bool mplay(Croupier &cr);

    bool primitiveOp(Croupier &cr, std::vector<int> &Hand, std::string option);

    std::string inputOption();

};

#endif // PLAYER_H
