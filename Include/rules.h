#pragma once

#include <unordered_map>

struct Rules
{
  Rules()
    : blackjackPay(1.5f),
    H17(false),
    decks(6),
    DAS(true),
    numSplits(3),
    drawSplitAces(false),
    resplitAces(false),
    surrender(true),
    pen(0.75f)
  {}
  float blackjackPay;
  bool H17;
  int decks;
  bool DAS;
  int numSplits;
  bool drawSplitAces;
  bool resplitAces;
  bool surrender;
  float pen;
  std::unordered_map<int, bool> doubles;
};
