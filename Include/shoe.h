#pragma once
#include <random>
#include <stack>
#include "card.h"

class Shoe 
{
  public:
    Shoe(int deckNumber = 1);
    std::vector<Card>& shoe();
    int size();
    int deckNumber();
    Card& top();
    void pop();
    Card& topPop();
  private:
    std::vector<Card> shoe_;
    int deckNumber_;
};
