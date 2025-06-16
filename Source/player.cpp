#include "player.h"

Player::Player(Card& one, Card& two) {
  cards.push_back(one);
  cards.push_back(two);
  if (cards[0].rank() == 14 || cards[1].rank() == 14) {
    soft = true;
  }
  playerTotal += cards[0].total();
  playerTotal += cards[1].total();
}

Card& Player::first() {
  return cards[0];
}

Card& Player::second() {
  return cards[1]; 
}

size_t Player::total() {
  return playerTotal;
}

bool Player::isSoft() {
  return soft; 
}

bool Player::naturalBlackjack() {
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

std::vector<Card>& Player::allCards() {
  return cards; 
}

void Player::hit(Card& hitCard) {
  int aceCount = 0;
  cards.push_back(hitCard);
  playerTotal += hitCard.total();
  if (hitCard.rank() == 14 && soft == false) {
    soft = true;
  }
  if (soft == true && playerTotal > 21) {
    for (Card& i : cards) {
      if (i.isAce()) {
        if (aceCount == 0) {
          i.unSoft();
          playerTotal -= 10;
        }
        aceCount++;
      }
    }
    if (aceCount == 1) {
      soft = false;
    }
  }
}

Card& Player::split(Card& newCard) {
  Card temp = cards[1];
  playerTotal -= cards[1].total();
  cards[1] = newCard;
  playerTotal += cards[1].total();
  return temp;
}

bool Player::bust() {
  return playerTotal > 21 ? true : false;
}
