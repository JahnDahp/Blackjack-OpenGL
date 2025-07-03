#include "shoe.h"

Shoe::Shoe(int num) 
  : deckNumber(num) 
{}
void Shoe::init()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  for (int deck = 0; deck < deckNumber; deck++) for (int i = 1; i <= 13; i++) for (int j = 1; j <= 4; j++)
  {
    std::unique_ptr<Card> card = std::make_unique<Card>(i, j);
    shoe.push_back(std::move(card));
  }
  shuffle(shoe.begin(), shoe.end(), gen);
}
int Shoe::size() const
{
  return shoe.size();
}
bool Shoe::empty() const
{
  return shoe.empty();
}
int Shoe::getDeckNumber() const
{
  return deckNumber;
}
std::unique_ptr<Card> Shoe::topPop()
{ 
  if (shoe.empty())
  {
    std::cout << "TopPop on empty shoe!\n";
    return nullptr;
  }
  std::unique_ptr<Card> temp = std::move(shoe.back());
  temp->init();
  shoe.pop_back();
  return temp;
}
