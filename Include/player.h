#pragma once

#include <vector>
#include "card.h"
#include "text.h"

class Player
{
  public:
    Player(std::unique_ptr<Card> one, std::unique_ptr<Card> two, float initialBet);
    Card* getCard(int index) const;
    const std::vector<std::unique_ptr<Card>>& getCards() const;
    Text* getBetLabel() const;
    float getBet() const;
    void setBet(float newBet);
    int total() const;
    bool isSoft() const;
    void unSoft();
    bool isBlackjack() const;
    void hit(std::unique_ptr<Card> hitCard);
    bool canSplit();
    std::unique_ptr<Player> split(std::unique_ptr<Card> newCard1, std::unique_ptr<Card> newCard2);
    bool isBust() const;
  private:
    std::vector<std::unique_ptr<Card>> cards;
    float bet;
    std::unique_ptr<Text> betLabel;
};
