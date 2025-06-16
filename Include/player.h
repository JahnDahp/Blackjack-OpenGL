#pragma once
#include <vector>
#include "card.h"

class Player
{
  public:
    Player(Card& one, Card& two);
    Card& first();
    Card& second();
    size_t total();
    bool isSoft();
    bool naturalBlackjack();
    std::vector<Card>& allCards();
    void hit(Card& hitCard);
    Card& split(Card& newCard);
    bool bust();
  private:
    int playerTotal = 0;
    std::vector<Card> cards;
    bool soft = false;
};
