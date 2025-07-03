#include "dealer.h"

Dealer::Dealer(std::unique_ptr<Card> up, std::unique_ptr<Card> hole, bool hit17)
  : H17(hit17)
{
  hit(std::move(up));
  hit(std::move(hole));
  cards[1]->setVisible(false);
}
Card* Dealer::getCard(int index) const
{
  if (index < 0 || index >= cards.size()) return nullptr;
  return cards[index].get();
}
const std::vector<std::unique_ptr<Card>>& Dealer::getCards() const
{
  return cards;
}
int Dealer::total(bool onlyUp) const
{
  if (onlyUp) return cards[0]->getRank();
  int dealerTotal = 0;
  for (auto& card : cards)
  {
    dealerTotal += card->getRank();
  }
  return dealerTotal;
}
bool Dealer::isSoft() const
{
  for (auto& card : cards)
  {
    if (card->isSoft()) return true;
  }
  return false;
}
void Dealer::unSoft()
{
  for (auto& card : cards)
  {
    if (card->isSoft())
    {
      card->unSoft();
      return;
    }
  }
}
bool Dealer::isBlackjack() const
{
  return total(false) == 21 && cards.size() == 2;
}
bool Dealer::isBust() const
{
  return total(false) > 21;
}
bool Dealer::canInsure() const
{
  return cards[0]->getRank() == 11;
}
void Dealer::hit(std::unique_ptr<Card> hitCard)
{
  cards.push_back(std::move(hitCard));
  while (isBust() && isSoft())
  {
    unSoft();
  }
}
bool Dealer::stop() const
{
  if (total(false) > 17) return true;
  if (total(false) < 17) return false;
  if (isSoft()) return !H17;
  return true;
}
