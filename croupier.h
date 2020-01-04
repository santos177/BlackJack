#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>

class Player {
  public:
    std::vector<int> pCards;


};

class Croupier {
  public:

    // cards in full Shoe
    int cardTotal;

    // total cards in a given hand
    std::vector<int> cCards;

    // map for card left in Shoe
    std::map<int,int> frecMap;

    // setting number of decks
    void setDeck (int n)
    {
        for (int i = 1; i <= 13;i++)
            frecMap.insert(std::pair<int, int>(i,4 * n));
        cardTotal = 52 * n;
    }

    //setting first cards for Croupier and Player
    void setFirstCards (Player &pl)
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

    }

    // getting a card from Shoe
    int getCard ()
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

    // checking the sum of points in the hand
    // int checkHand (std::vector<int> hand, bool flag)
    // {
    //     int count = 0;
    //     for (std::vector<int>::iterator it = hand.begin(); it != hand.end();++it)
    //     {
    //         int card = *(it);
    //
    //     }
    //
    // }
};