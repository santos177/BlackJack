#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>

class Player {
  public:
    std::vector<int> pCards;
    int Sum;

    void clearHand(){
        pCards.clear();
    }

};

class Croupier {
  public:

    // cards in full Shoe
    int cardTotal;

    // total cards in a given hand
    std::vector<int> cCards;

    // map for card left in Shoe
    std::map<int,int> frecMap;


    // clear the hand
    void getWinner(Player &pl)
    {
        int plSum = checkHand(pl.pCards);
        int crSum = checkHand(cCards);

        printf("plSum: %d\n",plSum);
        printf("crSum: %d\n",crSum);

        if (crSum > 21 || ((plSum > crSum) && (21 >= plSum)))
            printf("player wins!\n");
        else if (plSum > 21 || ((crSum > plSum) && (21 >= crSum)))
            printf("croupier wins!\n");
        else
            printf("nobody wins...\n");

    }

    // clear the hand
    void clearHand(){
        cCards.clear();
    }

    // get first card of croupier
    int getFirstCard()
    {
        return cCards.front();
    }

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

    //checking the sum of points in the hand
    int checkHand (std::vector<int> hand)
    {
        int sum = 0;
        int aceSum = 0;

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

        }

        // adding the Aces sum
        if(aceSum == 1)
            sum += 11;
        else if (aceSum > 1)
            sum += 10 + aceSum;

        return sum;

    }

    //croupier taking cards until 17
    int dealingTo17()
    {
       // first check
       int sum = checkHand(cCards);

       while(sum < 17)
       {
           int crC = getCard();
           printf("new card for croupier: %d\n",crC);
           cCards.push_back(crC);
           sum = checkHand(cCards);
           printf("sum for croupier: %d\n", sum);

       }

       return sum;

    }

};
