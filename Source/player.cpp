#include "player.h"

static std::string floatToString(float value, int precision = 2)
{
  int intPart = (int)value;
  float frac = std::abs(value - intPart);
  std::string result = std::to_string(intPart);
  if (precision > 0)
  {
    frac = std::round(frac * std::pow(10, precision));
    if (frac > 0)
    {
      result += '.';
      while (precision > 1 && frac < std::pow(10, precision - 1))
      {
        result += '0';
        precision--;
      }
      result += std::to_string((int)frac);
    }
  }
  return result;
}

Player::Player(std::unique_ptr<Card> one, std::unique_ptr<Card> two, float initialBet)
{
  hit(std::move(one));
  hit(std::move(two));
  bet = initialBet;
  betLabel = std::make_unique<Text>("../Resources/Fonts/SF.otf", "Bet: " + floatToString(bet, 2), glm::vec4(0.f, 0.f, 0.f, 1.f));
}
Card* Player::getCard(int index) const
{
  if (index < 0 || index >= cards.size()) return nullptr;
  return cards[index].get();
}
const std::vector<std::unique_ptr<Card>>& Player::getCards() const
{
  return cards;
}
Text* Player::getBetLabel() const
{
  return betLabel.get();
}
float Player::getBet() const
{
  return bet;
}
void Player::setBet(float newBet)
{
  bet = newBet;
  betLabel->setText("Bet: " + floatToString(bet, 2));
}
int Player::total() const
{
  int total = 0;
  int numSoftAces = 0;
  for (const auto& card : cards)
  {
    int rank = card->getRank();
    if (rank == 11) numSoftAces++;
    total += rank;
  }
  while (total > 21 && numSoftAces > 0)
  {
    total -= 10;
    numSoftAces--;
  }
  return total;
}
bool Player::isSoft() const 
{
  for (const auto& card : cards)
  {
    if (card->isSoft()) return true;
  }
  return false;
}
void Player::unSoft()
{
  for (const auto& card : cards)
  {
    if (card->isSoft())
    {
      card->unSoft();
      return;
    }
  }
}
bool Player::isBlackjack() const
{
  return total() == 21 && cards.size() == 2;
}
void Player::hit(std::unique_ptr<Card> hitCard)
{
  cards.push_back(std::move(hitCard));
}
bool Player::canSplit()
{
  if (cards.size() != 2) return false;
  return cards[0]->getRank() % 10 == cards[1]->getRank() % 10;
}
std::unique_ptr<Player> Player::split(std::unique_ptr<Card> newCard1, std::unique_ptr<Card> newCard2)
{
  std::unique_ptr<Card> splitCard = std::move(cards[1]);
  cards.erase(cards.begin() + 1); 
  hit(std::move(newCard1));
  return std::make_unique<Player>(std::move(splitCard), std::move(newCard2), bet);
}
bool Player::isBust() const
{
  return total() > 21;
}
