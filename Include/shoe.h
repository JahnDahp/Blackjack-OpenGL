#pragma once

#include <random>
#include <stack>
#include "card.h"

class Shoe 
{
  public:
    Shoe(int num = 1); 
    void init();
    int size() const;
    bool empty() const;
    int getDeckNumber() const;
    std::unique_ptr<Card> topPop();
  private:
    std::vector<std::unique_ptr<Card>> shoe;
    int deckNumber;
};
