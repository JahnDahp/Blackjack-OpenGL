#include "shoe.h"

Shoe::Shoe(int deckNumber) {
  deckNumber_ = deckNumber;
  std::random_device rd;
  std::mt19937 gen(rd());
  for (int i = 2; i <= 14; i++) {
    for (int j = 1; j <= 4; j++) {
      Card card(i, j);
      shoe_.push_back(card);
    }
  }
  shuffle(shoe_.begin(), shoe_.end(), gen);
}

std::vector<Card>& Shoe::shoe() { 
  return shoe_; 
}

int Shoe::size() {
  return shoe_.size();
}

int Shoe::deckNumber() {
  return deckNumber_;
}

Card& Shoe::top() {
  return shoe_.back();
}

void Shoe::pop() { 
  shoe_.pop_back();
  return;
}

Card& Shoe::topPop() { 
  Card& temp = shoe_.back();
  shoe_.pop_back();
  return temp;
}
