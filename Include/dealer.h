#pragma once

#include <vector>
#include "card.h"

class Dealer 
{
  public:
    Dealer(std::unique_ptr<Card> up, std::unique_ptr<Card> hole, bool hit17);
    Card* getCard(int index) const;
    const std::vector<std::unique_ptr<Card>>& getCards() const;
    int total(bool onlyUp) const;
    bool isSoft() const;
    void unSoft();
    bool isBlackjack() const;
    bool isBust() const;
    bool canInsure() const;
    void hit(std::unique_ptr<Card> hitCard);
    bool stop() const;
  private:
    std::vector<std::unique_ptr<Card>> cards;
    bool H17;
};
