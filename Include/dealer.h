#pragma once
#include <vector>
#include "card.h"
#include "shoe.h"

class Dealer 
{
  public:
    Dealer(Card& up, Card& hole);
    Card& up();
    Card& hole();
    size_t total();
    bool isSoft();
    bool naturalBlackjack();
    std::vector<Card>& allCards();
    bool insurancePossible();
    void hit(Card& hitCard);
    bool bust();
  private:
    size_t dealerTotal = 0;
    std::vector<Card> cards;
    bool soft = false;
    bool insurance = false;
};
