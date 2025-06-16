#include "dealer.h"

Dealer::Dealer(Card& up, Card& hole) {
  cards.push_back(up);
  cards.push_back(hole);
  if (cards[0].rank() == 14 || cards[1].rank() == 14) {
    if (cards[0].rank() == 14) {
      insurance = true;
    }
    soft = true;
  }
  dealerTotal += cards[0].total();
  dealerTotal += cards[1].total();
}

Card& Dealer::up() {
  return cards[0];
}

Card& Dealer::hole() {
  return cards[1];
}

size_t Dealer::total() {
  return dealerTotal;
}

bool Dealer::isSoft() {
  return soft;
}

bool Dealer::naturalBlackjack() {
  int rank1 = cards[0].rank();
  int rank2 = cards[1].rank();
  if (rank1 == 11 || rank1 == 12 || rank1 == 13) {
    rank1 = 10;
  }
  if (rank2 == 11 || rank2 == 12 || rank2 == 13) {
    rank2 = 10;
  }
  if ((rank1 == 10 && rank2 == 14) || (rank1 == 14 && rank2 == 10)) {
    return true;
  }
  return false;
}

std::vector<Card>& Dealer::allCards() {
  return cards;
}

bool Dealer::insurancePossible() {
  return insurance;
}

void Dealer::hit(Card& hitCard) {
  int aceCount = 0;
  cards.push_back(hitCard);
  dealerTotal += hitCard.total();
  if (hitCard.rank() == 14 && soft == false) {
    soft = true;
  }
  if (soft == true && dealerTotal > 21) {
    for (Card& i : cards) {
      if (i.isAce()) {
        if (aceCount == 0) {
          i.unSoft();
          dealerTotal -= 10;
        }
        aceCount++;
      }
    }
    if (aceCount == 1) {
      soft = false;
    }
  }
}

bool Dealer::bust() {
  return dealerTotal > 21 ? true : false;
}
